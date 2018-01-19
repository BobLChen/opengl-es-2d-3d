//
//  CCES2Renderer.h
//  Monkey
//
//  Created by Neil on 17/8/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef _RENDERER_
#define _RENDERER_

#import "platform/PlatformConfig.h"
#import "platform/PlatformMacros.h"

#if TARGET_PLATFORM == PLATFORM_IOS

#import "ESRenderer.h"
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

@interface ES2Renderer : NSObject <ESRenderer>
{
    
    GLint               backingWidth_;               // backbuffer 宽度
    GLint               backingHeight_;              // backbuffer 高度
    
    unsigned int        samplesToUse_;               // 可用贴图数量
    BOOL                multiSampling_;              // 是否支持多重贴图
    
    unsigned int        depthFormat_;                // 深度格式
    unsigned int        pixelFormat_;                // pixel格式
    
    GLuint              defaultFramebuffer_;         // 帧缓存
    GLuint              colorRenderbuffer_;          // 颜色缓存
    GLuint              depthBuffer_;                // 深度以及模板缓存
    
    // buffers for MSAA
    // TODO:用FXAA代替
    GLuint              msaaFramebuffer_;            // msaa帧缓存
    GLuint              msaaColorbuffer_;            // msaa颜色buffer
    
    EAGLContext         *context_;                   // opengl上下文
}

/** Color Renderbuffer */
@property (nonatomic,readonly) GLuint colorRenderbuffer;

/** Default Renderbuffer */
@property (nonatomic,readonly) GLuint defaultFramebuffer;

/** MSAA Framebuffer */
@property (nonatomic,readonly) GLuint msaaFramebuffer;

/** MSAA Color Buffer */
@property (nonatomic,readonly) GLuint msaaColorbuffer;

/** EAGLContext */
@property (nonatomic,readonly) EAGLContext* context;

- (BOOL)resizeFromLayer:(CAEAGLLayer *)layer;
@end

#endif

#endif

