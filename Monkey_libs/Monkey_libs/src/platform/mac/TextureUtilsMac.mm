//
//  TextureUtilsMac.cpp
//  Monkey_libs
//
//  Created by Neil on 2/10/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#include "TextureUtilsMac.h"
#include "platform/PlatformMacros.h"

#include <Foundation/Foundation.h>
#include <Cocoa/Cocoa.h>
#include <string>

NS_MONKEY_BEGIN

#define ALIGN_TOP    1
#define ALIGN_CENTER 3
#define ALIGN_BOTTOM 2

typedef struct {
    int             height;
    int             width;
    bool            hasAlpha;
    bool            isPremultipliedAlpha;
    int             strokeColorR;
    int             strokeColorG;
    int             strokeColorB;
    bool            hasStroke;
    unsigned char*  data;
} TextureInfo;

TextureUtils* TextureUtils::getInstance() {
    if (_instance == nullptr) {
        _instance = new TextureUtilsMac();
    }
    return _instance;
}

static bool _initWithString(const char* text, TextAlign align, const char* fontName, int size, TextureInfo &info)
{
    bool ret = false;
    
    do {
        NSString *string  = [NSString stringWithUTF8String:text];
        
        // font
        NSFont *font = [[NSFontManager sharedFontManager]
                        fontWithFamily:[NSString stringWithUTF8String:fontName]
                        traits:NSUnboldFontMask | NSUnitalicFontMask
                        weight:0
                        size:size];
        
        if (font == nil) {
            font = [[NSFontManager sharedFontManager]
                    fontWithFamily:@"Arial"
                    traits:NSUnboldFontMask | NSUnitalicFontMask
                    weight:0
                    size:size];
        }
        
        
        // color
        NSColor* foregroundColor;
        
        if (info.hasStroke) {
            foregroundColor = [NSColor colorWithDeviceRed:info.strokeColorR/255.0 green:info.strokeColorG/255.0 blue:info.strokeColorB/255.0 alpha:1];
        } else {
            foregroundColor = [NSColor whiteColor];
        }
        
        // alignment, linebreak
        unsigned horiFlag = (int)align & 0x0f;
        unsigned vertFlag = ((int)align >> 4) & 0x0f;
        NSTextAlignment textAlign = (2 == horiFlag) ? NSRightTextAlignment
        : (3 == horiFlag) ? NSCenterTextAlignment
        : NSLeftTextAlignment;
        
        NSMutableParagraphStyle *paragraphStyle = [[[NSMutableParagraphStyle alloc] init] autorelease];
        [paragraphStyle setParagraphStyle:[NSParagraphStyle defaultParagraphStyle]];
        [paragraphStyle setLineBreakMode:NSLineBreakByCharWrapping];
        [paragraphStyle setAlignment:textAlign];
        
        // attribute
        NSDictionary* tokenAttributesDict = [NSDictionary dictionaryWithObjectsAndKeys:
                                             foregroundColor,NSForegroundColorAttributeName,
                                             font, NSFontAttributeName,
                                             paragraphStyle, NSParagraphStyleAttributeName, nil];
        
        // linebreak
        if (info.width > 0) {
            if ([string sizeWithAttributes:tokenAttributesDict].width > info.width) {
                NSMutableString *lineBreak = [[[NSMutableString alloc] init] autorelease];
                NSUInteger length = [string length];
                NSRange range = NSMakeRange(0, 1);
                CGSize textSize;
                NSUInteger lastBreakLocation = 0;
                NSUInteger insertCount = 0;
                for (NSUInteger i = 0; i < length; i++) {
                    range.location = i;
                    NSString *character = [string substringWithRange:range];
                    [lineBreak appendString:character];
                    if ([@"!?.,-= " rangeOfString:character].location != NSNotFound) {
                        lastBreakLocation = i + insertCount;
                    }
                    textSize = [lineBreak sizeWithAttributes:tokenAttributesDict];
                    if(textSize.height > info.height)
                        break;
                    if (textSize.width > info.width) {
                        if(lastBreakLocation > 0) {
                            [lineBreak insertString:@"\r" atIndex:lastBreakLocation];
                            lastBreakLocation = 0;
                        }
                        else {
                            [lineBreak insertString:@"\r" atIndex:[lineBreak length] - 1];
                        }
                        insertCount += 1;
                    }
                }
                
                string = lineBreak;
            }
        }
        
        NSAttributedString *stringWithAttributes =[[[NSAttributedString alloc] initWithString:string
                                                                                   attributes:tokenAttributesDict] autorelease];
        
        NSSize realDimensions = [stringWithAttributes size];
        // Mac crashes if the width or height is 0
        
        CGSize dimensions = CGSizeMake(info.width, info.height);
        
        if(dimensions.width <= 0 && dimensions.height <= 0) {
            dimensions.width = realDimensions.width;
            dimensions.height = realDimensions.height;
        } else if (dimensions.height <= 0) {
            dimensions.height = realDimensions.height;
        }
        
        NSInteger POTWide = dimensions.width;
        NSInteger POTHigh = MAX(dimensions.height, realDimensions.height);
        unsigned char*			data;
        //Alignment
        
        CGFloat xPadding = 0;
        switch (textAlign) {
            case NSLeftTextAlignment: xPadding = 0; break;
            case NSCenterTextAlignment: xPadding = (dimensions.width-realDimensions.width)/2.0f; break;
            case NSRightTextAlignment: xPadding = dimensions.width-realDimensions.width; break;
            default: break;
        }
        
        // 1: TOP
        // 2: BOTTOM
        // 3: CENTER
        CGFloat yPadding = (1 == vertFlag || realDimensions.height >= dimensions.height) ? (dimensions.height - realDimensions.height)	// align to top
        : (2 == vertFlag) ? 0																	// align to bottom
        : (dimensions.height - realDimensions.height) / 2.0f;									// align to center
        
        
        NSRect textRect = NSMakeRect(xPadding, POTHigh - dimensions.height + yPadding, realDimensions.width, realDimensions.height);
        //Disable antialias
        
        [[NSGraphicsContext currentContext] setShouldAntialias:NO];
        
        NSImage *image = [[NSImage alloc] initWithSize:NSMakeSize(POTWide, POTHigh)];
        
        [image lockFocus];
        
        // patch for mac retina display and lableTTF
        [[NSAffineTransform transform] set];
        
        //[stringWithAttributes drawAtPoint:NSMakePoint(xPadding, offsetY)]; // draw at offset position
        [stringWithAttributes drawInRect:textRect];
        //[stringWithAttributes drawInRect:textRect withAttributes:tokenAttributesDict];
        NSBitmapImageRep *bitmap = [[NSBitmapImageRep alloc] initWithFocusedViewRect:NSMakeRect (0.0f, 0.0f, POTWide, POTHigh)];
        [image unlockFocus];
        
        data = (unsigned char*) [bitmap bitmapData];  //Use the same buffer to improve the performance.
        
        NSUInteger textureSize = POTWide*POTHigh*4;
        
        unsigned char* dataNew = (unsigned char*)malloc(sizeof(unsigned char) * textureSize);
        if (dataNew) {
            memcpy(dataNew, data, textureSize);
            // output params
            info.width = static_cast<int>(POTWide);
            info.height = static_cast<int>(POTHigh);
            info.data = dataNew;
            info.hasAlpha = true;
            info.isPremultipliedAlpha = true;
            ret = true;
        }
        [bitmap release];
        [image release];
    } while (0);
    return ret;
}

ByteArray* TextureUtilsMac::getTextureDataWithText(const char *text, const TextFormatter &format, int &width, int &height, bool &hasAlpha) {
    
    TextureInfo info = {0};
    info.width  = format.width;
    info.height = format.height;
    info.strokeColorR = format.stroke.red;
    info.strokeColorG = format.stroke.green;
    info.strokeColorB = format.stroke.blue;
    info.hasStroke    = format.stroke.enabled;
    
     if (!_initWithString(text, format.align, format.fontName.c_str(), format.fontSize, info)) {
        return nullptr;
    }
    
    width  = info.width;
    height = info.height;
    hasAlpha = info.isPremultipliedAlpha;
    
    ByteArray* bytes = new ByteArray(info.data, info.width * info.height * 4);
    return bytes;
}

NS_MONKEY_END