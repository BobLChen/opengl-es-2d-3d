//
//  TextureUtilsIOS.cpp
//  Opengl2D
//
//  Created by Neil on 21/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#include "platform/ios/TextureUtilsIOS.h"
#include "core/utils/Log.h"

#import <UIKit/UIKit.h>

#include "platform/PlatformMacros.h"

NS_MONKEY_BEGIN

#define ALIGN_TOP    1
#define ALIGN_CENTER 3
#define ALIGN_BOTTOM 2

typedef struct {
    unsigned int    height;
    unsigned int    width;
    bool            isPremultipliedAlpha;
    bool            hasShadow;
    float           offsetX;
    float           offsetY;
    float           shadowBlur;
    float           shadowOpacity;
    bool            hasStroke;
    float           strokeR;
    float           strokeG;
    float           strokeB;
    float           strokeSize;
    float           tintR;
    float           tintG;
    float           tintB;
    unsigned char*  data;
} TextureInfo;

TextureUtils* TextureUtils::getInstance() {
    if (_instance == nullptr) {
        _instance = new TextureUtilsIOS();
    }
    return _instance;
}

static CGSize caculateStringSize(NSString *str, id font, CGSize *constrainSize) {
    CGSize textRect = CGSizeZero;
    textRect.width  = constrainSize->width > 0 ? constrainSize->width : 0x7fffffff;
    textRect.height = constrainSize->height > 0 ? constrainSize->height : 0x7fffffff;
    CGSize dim = [str sizeWithFont:font constrainedToSize:textRect];
    dim.width = ceilf(dim.width);
    dim.height = ceilf(dim.height);
    return dim;
}

static bool IS_IOS7_HIGHER = false;
static bool IS_CHECKED     = false;

static inline void checkIOS7() {
    if (!IS_CHECKED) {
        IS_IOS7_HIGHER = [[[UIDevice currentDevice] systemVersion] compare:@"7.0" options:NSNumericSearch] != NSOrderedAscending;
        IS_CHECKED = true;
    }
}

static bool initWithString(const char* text, TextAlign align, const char *fontName, int size, TextureInfo *info) {
    
    checkIOS7();
    
    NSString *str       = [NSString stringWithUTF8String:text];
    NSString *fntName   = [NSString stringWithUTF8String:fontName];
    
    CGSize dim, constrainSize;
    constrainSize.width = info->width;
    constrainSize.height= info->height;
    
    fntName = [[fntName lastPathComponent] stringByDeletingPathExtension];
    id font = [UIFont fontWithName:fntName size:size];
    
    if (font) {
        dim = caculateStringSize(str, font, &constrainSize);
    } else {
        if (!font) {
            font = [UIFont systemFontOfSize:size];
        }
        if (font) {
            dim = caculateStringSize(str, font, &constrainSize);
        }
    }
    
    if (!font) {
        LOGE("Faild to create font:%s", fontName);
        return false;
    }
    
    int startH = 0;
    if (constrainSize.height > dim.height) {
        unsigned int vAlignment = ((int)align >> 4) & 0x0F;
        if (vAlignment == ALIGN_TOP) {
            startH = 0;
        } else if (vAlignment == ALIGN_CENTER) {
            startH = (constrainSize.height - dim.height) / 2;
        } else {
            startH = constrainSize.height - dim.height;
        }
    }
    
    if (constrainSize.width > 0 && constrainSize.width > dim.width) {
        dim.width = constrainSize.width;
    }
    if (constrainSize.height > 0 && constrainSize.height > dim.height) {
        dim.height = constrainSize.height;
    }
    
    float shadowStrokePaddingX = 0.0f;
    float shadowStrokePaddingY = 0.0f;
    
    if (info->hasStroke) {
        shadowStrokePaddingX = ceilf(info->strokeSize);
        shadowStrokePaddingY = ceilf(info->strokeSize);
    }
    
    dim.width  += shadowStrokePaddingX * 2;
    dim.height += shadowStrokePaddingY * 2;
    
    unsigned char* data = (unsigned char*)malloc(sizeof(unsigned char) * int(dim.width * dim.height * 4));
    memset(data, 0, (int)(dim.width * dim.height * 4));
    
    // draw text
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    CGContextRef    context    = CGBitmapContextCreate(data,
                                                       dim.width,
                                                       dim.height,
                                                       8,
                                                       (int)(dim.width) * 4,
                                                       colorSpace,
                                                       kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);
    
    if (!context) {
        CGColorSpaceRelease(colorSpace);
        free(data);
        LOGE("Font:Context Create Faild. FontName:%s", fontName);
        return  false;
    }
    
    CGContextSetRGBFillColor(context, info->tintR / 255.0f, info->tintG / 255.0f, info->tintB / 255.0f, 1);
    CGContextTranslateCTM(context, 0.0f, (dim.height - shadowStrokePaddingY));
    CGContextScaleCTM(context, 1.0f, -1.0f);
    UIGraphicsPushContext(context);
    unsigned uHoriFlag = (int)align & 0x0f;
    NSTextAlignment nsAlign = (2 == uHoriFlag) ? NSTextAlignmentRight : (3 == uHoriFlag) ? NSTextAlignmentCenter : NSTextAlignmentLeft;
    CGColorSpaceRelease(colorSpace);
    
    float textOriginX  = 0;
    float textOrigingY = startH;
    
    float textWidth    = dim.width;
    float textHeight   = dim.height;
    
    CGRect rect = CGRectMake(textOriginX, textOrigingY, textWidth, textHeight);
    CGContextSetShouldSubpixelQuantizeFonts(context, false);
    CGContextBeginTransparencyLayerWithRect(context, rect, NULL);
    
    if (info->hasStroke) {
        CGContextSetTextDrawingMode(context, kCGTextStroke);
        if(IS_IOS7_HIGHER) {
            NSMutableParagraphStyle *paragraphStyle = [[NSMutableParagraphStyle alloc] init];
            paragraphStyle.alignment = nsAlign;
            paragraphStyle.lineBreakMode = NSLineBreakByWordWrapping;
            [str drawInRect:rect withAttributes:@{
                                NSFontAttributeName: font,
                                NSStrokeWidthAttributeName: [
                                                    NSNumber numberWithFloat: info->strokeSize / size * 100 ],
                                NSForegroundColorAttributeName:[
                                                    UIColor colorWithRed:info->tintR
                                                    green:info->tintG
                                                    blue:info->tintB
                                                    alpha:1.0f],
                                NSParagraphStyleAttributeName:paragraphStyle,
                                NSStrokeColorAttributeName: [
                                                    UIColor colorWithRed:info->strokeR
                                                    green:info->strokeG
                                                    blue:info->strokeB
                                                    alpha:1.0f]
             }
             ];
            [paragraphStyle release];
        } else {
            CGContextSetRGBStrokeColor(context, info->strokeR, info->strokeG, info->strokeB, 1);
            CGContextSetLineWidth(context, info->strokeSize);
            [str drawInRect: rect withFont:font lineBreakMode:NSLineBreakByWordWrapping alignment:nsAlign];
        }
    }
    
    CGContextSetTextDrawingMode(context, kCGTextFill);
    [str drawInRect: rect withFont:font lineBreakMode:NSLineBreakByWordWrapping alignment:nsAlign];
    CGContextEndTransparencyLayer(context);
    UIGraphicsPopContext();
    CGContextRelease(context);
    
    info->data                  = data;
    info->isPremultipliedAlpha  = true;
    info->width                 = dim.width;
    info->height                = dim.height;
    
    return true;
}

ByteArray* TextureUtilsIOS::getTextureDataWithText(const char *text, const TextFormatter &format, int &width, int &height, bool &hasAlpha) {
    
    TextureInfo info;
    info.width  = format.width;
    info.height = format.height;
    info.hasShadow = format.shadow.enabled;
    info.offsetX   = format.shadow.offsetX;
    info.offsetY   = format.shadow.offsetY;
    info.shadowBlur= format.shadow.shadowBlur;
    info.shadowOpacity = format.shadow.shadowOpacity;
    info.hasStroke = format.stroke.enabled;
    info.strokeR   = format.stroke.red;
    info.strokeG   = format.stroke.green;
    info.strokeB   = format.stroke.blue;
    info.strokeSize= format.stroke.size;
    info.tintR     = format.fontFillColorR;
    info.tintG     = format.fontFillColorG;
    info.tintB     = format.fontFillColorB;
    
    if (!initWithString(text, format.align, format.fontName.c_str(), format.fontSize, &info)) {
        return nullptr;
    }
    
    height   = info.height;
    width    = info.width;
    hasAlpha = info.isPremultipliedAlpha;
    
    ByteArray *bytes = new ByteArray(info.data, width * height * 4);
    
    return bytes;
}

NS_MONKEY_END