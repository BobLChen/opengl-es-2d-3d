//
//  CCEAGLView.h
//  TestOpenglES
//
//  Created by Neil on 17/8/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#import "platform/PlatformConfig.h"

#if TARGET_PLATFORM == PLATFORM_IOS

#import <UIKit/UIKit.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/EAGLDrawable.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#import <CoreFoundation/CoreFoundation.h>

#import "platform/ios/ES2Renderer.h"

@interface EAGLView : UIView <UIKeyInput, UITextInput>
{
    id                          <ESRenderer> renderer_;         // render buffer
    EAGLContext                 *context_;                      // context 上下文
    
    NSString                    *pixelformat_;                  // pixel格式
    GLuint                      depthFormat_;                   // 深度格式
    BOOL                        preserveBackbuffer_;            //
    
    CGSize                      size_;                          // backbuffer size
    BOOL                        discardFramebufferSupported_;   // 是否舍去像素
    
    BOOL                        multisampling_;                 // 多重采样
    unsigned int                requestedSamples_;              // 可用多重采数量
    BOOL                        isUseUITextField;               // TODO:add description
@private
    NSString *                  markedText_;                    // TODO:add description
    CGRect                      caretRect_;
    CGRect                      originalRect_;
    NSNotification*             keyboardShowNotification_;      //
    BOOL                        isKeyboardShown_;
}

@property(nonatomic, readonly)  UITextPosition              *beginningOfDocument;
@property(nonatomic, readonly)  UITextPosition              *endOfDocument;
@property(nonatomic, assign)    id<UITextInputDelegate>     inputDelegate;
@property(nonatomic, readonly)  UITextRange                 *markedTextRange;
@property(nonatomic, copy)      NSDictionary                *markedTextStyle;
@property(readwrite, copy)      UITextRange                 *selectedTextRange;
@property(nonatomic, readonly)  id<UITextInputTokenizer>    tokenizer;
@property(nonatomic, readonly,  getter = isKeyboardShown)   BOOL isKeyboardShown;
@property(nonatomic, copy)      NSNotification              *keyboardShowNotification;

+ (id) viewWithFrame:(CGRect)frame;
+ (id) viewWithFrame:(CGRect)frame pixelFormat:(NSString*)format;
+ (id) viewWithFrame:(CGRect)frame pixelFormat:(NSString*)format depthFormat:(GLuint)depth;
+ (id) viewWithFrame:(CGRect)frame pixelFormat:(NSString*)format depthFormat:(GLuint)depth preserveBackbuffer:(BOOL)retained sharegroup:(EAGLSharegroup*)sharegroup multiSampling:(BOOL)multisampling numberOfSamples:(unsigned int)samples;
- (id) initWithFrame:(CGRect)frame;
- (id) initWithFrame:(CGRect)frame pixelFormat:(NSString*)format;
- (id) initWithFrame:(CGRect)frame pixelFormat:(NSString*)format depthFormat:(GLuint)depth preserveBackbuffer:(BOOL)retained sharegroup:(EAGLSharegroup*)sharegroup multiSampling:(BOOL)sampling numberOfSamples:(unsigned int)nSamples;

@property(nonatomic,readonly)   NSString        *pixelFormat;
@property(nonatomic,readonly)   GLuint          depthFormat;
@property(nonatomic,readonly)   CGSize          surfaceSize;
@property(nonatomic,readonly)   EAGLContext     *context;
@property(nonatomic,readwrite)  BOOL            multiSampling;

-(void)             swapBuffers;    // 显示画面
-(id<ESRenderer>)   getRender;      // 获取render

- (CGRect)  convertRectFromViewToSurface :(CGRect) rect;
- (CGPoint) convertPointFromViewToSurface:(CGPoint)point;

-(int) getWidth;    // 获取宽度
-(int) getHeight;   // 获取高度

-(void) doAnimationWhenKeyboardMoveWithDuration:(float) duration distance:(float) dis;
-(void) doAnimationWhenAnotherEditBeClicked;
@end

#endif