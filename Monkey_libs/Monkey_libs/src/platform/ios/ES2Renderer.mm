//
//  CCES2Renderer.m
//  TestOpenglES
//
//  Created by Neil on 17/8/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#import "ES2Renderer.h"
#import "platform/PlatformMacros.h"

@implementation ES2Renderer

@synthesize context             =   context_;
@synthesize defaultFramebuffer  =   defaultFramebuffer_;
@synthesize colorRenderbuffer   =   colorRenderbuffer_;
@synthesize msaaColorbuffer     =   msaaColorbuffer_;
@synthesize msaaFramebuffer     =   msaaFramebuffer_;

// Create an OpenGL ES 2.0 context
- (id) initWithDepthFormat:(unsigned int)depthFormat withPixelFormat:(unsigned int)pixelFormat withSharegroup:(EAGLSharegroup*)sharegroup withMultiSampling:(BOOL) multiSampling withNumberOfSamples:(unsigned int) requestedSamples
{
    self = [super init];
    if (self)
    {
        if( ! sharegroup )
            context_ = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
        else
            context_ = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2 sharegroup:sharegroup];
        
        if (!context_ || ![EAGLContext setCurrentContext:context_] )
        {
            [self release];
            return nil;
        }
        
        depthFormat_   = depthFormat;
        pixelFormat_   = pixelFormat;
        multiSampling_ = multiSampling;
        
        // 启用剔除
        glEnable(GL_CULL_FACE);
        // 设置顺时针为正面、剔除掉逆时针
        glFrontFace(GL_CW);
        // 启用深度测试
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        // 启用模板
        glEnable(GL_STENCIL_TEST);
        
        // background color
        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
        
        // 创建帧缓存对象
        glGenFramebuffers(1, &defaultFramebuffer_);
        NSAssert(defaultFramebuffer_, @"Can't create default frame buffer");
        // 创建缓存对象
        glGenRenderbuffers(1, &colorRenderbuffer_);
        NSAssert(colorRenderbuffer_,  @"Can't create default render buffer");
        // 绑定帧缓存对象
        glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebuffer_);
        // 绑定color缓存对象
        glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbuffer_);
        // 将colorRenderbuffer绑定到帧缓存对象。
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colorRenderbuffer_);
        // 多重采样
        if (multiSampling_) {
            GLint maxSamplesAllowed;
            glGetIntegerv(GL_MAX_SAMPLES_APPLE, &maxSamplesAllowed);
            samplesToUse_ = MIN(maxSamplesAllowed,requestedSamples);
            /* Create the MSAA framebuffer (offscreen) */
            glGenFramebuffers(1, &msaaFramebuffer_);
            NSAssert( msaaFramebuffer_, @"Can't create default MSAA frame buffer");
            glBindFramebuffer(GL_FRAMEBUFFER, msaaFramebuffer_);
        }
    }
    
    return self;
}

- (BOOL)resizeFromLayer:(CAEAGLLayer *)layer {
    
    glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbuffer_);
    
    if( ! [context_ renderbufferStorage:GL_RENDERBUFFER fromDrawable:layer] ) {
        NSLog(@"failed to call context");
    }
    // 获取render buffer size
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH,  &backingWidth_);
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &backingHeight_);
    
    NSLog(@"surface size: %dx%d", (int)backingWidth_, (int)backingHeight_);
    
    if (multiSampling_) {
        if (msaaColorbuffer_) {
            glDeleteRenderbuffers(1, &msaaColorbuffer_);
            msaaColorbuffer_ = 0;
        }
        // 绑定msaa frame buffer
        glBindFramebuffer(GL_FRAMEBUFFER, msaaFramebuffer_);
        // 创建msaa color buffer
        glGenRenderbuffers(1, &msaaColorbuffer_);
        NSAssert(msaaFramebuffer_, @"Can't create MSAA color buffer");
        // 绑定msaa color buffer
        glBindRenderbuffer(GL_RENDERBUFFER, msaaColorbuffer_);
        // 设置renderbuffer大小
        glRenderbufferStorageMultisampleAPPLE(GL_RENDERBUFFER, samplesToUse_, pixelFormat_ , backingWidth_, backingHeight_);
        // mass frame buffer 绑定到 msaa color buffer
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, msaaColorbuffer_);
        // check error
        GLenum error;
        if ( (error=glCheckFramebufferStatus(GL_FRAMEBUFFER)) != GL_FRAMEBUFFER_COMPLETE) {
            NSLog(@"Failed to make complete framebuffer object 0x%X", error);
            return NO;
        }
    }
    // 深度格式
    if (depthFormat_) {
        // 深度buffer不存在，创建深度buffer
        if (!depthBuffer_) {
            glGenRenderbuffers(1, &depthBuffer_);
            NSAssert(depthBuffer_, @"Can't create depth buffer");
        }
        // 绑定深度缓存buffer
        glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer_);
        if( multiSampling_ ) {
            glRenderbufferStorageMultisampleAPPLE(GL_RENDERBUFFER, samplesToUse_, depthFormat_,backingWidth_, backingHeight_);
        } else {
            glRenderbufferStorage(GL_RENDERBUFFER, depthFormat_, backingWidth_, backingHeight_);
        }
        // depth buffer 绑定到 frame buffer
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer_);
        // 绑定深度stencil buffer
        if (depthFormat_ == GL_DEPTH24_STENCIL8_OES) {
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthBuffer_);
		}
        // bind color buffer
        glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbuffer_);
    }
    GLenum error;
    if((error=glCheckFramebufferStatus(GL_FRAMEBUFFER)) != GL_FRAMEBUFFER_COMPLETE) {
        NSLog(@"Failed to make complete framebuffer object 0x%X", error);
        return NO;
    }
    
    return YES;
}

-(CGSize) backingSize
{
    return CGSizeMake(backingWidth_, backingHeight_);
}

- (unsigned int) colorRenderBuffer
{
    return colorRenderbuffer_;
}

- (unsigned int) defaultFrameBuffer
{
    return defaultFramebuffer_;
}

- (unsigned int) msaaFrameBuffer
{
    return msaaFramebuffer_;
}

- (unsigned int) msaaColorBuffer
{
    return msaaColorbuffer_;
}

- (void)dealloc
{
    // Tear down GL
    if (defaultFramebuffer_) {
        glDeleteFramebuffers(1, &defaultFramebuffer_);
        defaultFramebuffer_ = 0;
    }
    
    if (colorRenderbuffer_) {
        glDeleteRenderbuffers(1, &colorRenderbuffer_);
        colorRenderbuffer_ = 0;
    }
    
    if( depthBuffer_ ) {
        glDeleteRenderbuffers(1, &depthBuffer_ );
        depthBuffer_ = 0;
    }
    
    if ( msaaColorbuffer_)
    {
        glDeleteRenderbuffers(1, &msaaColorbuffer_);
        msaaColorbuffer_ = 0;
    }
    
    if ( msaaFramebuffer_)
    {
        glDeleteRenderbuffers(1, &msaaFramebuffer_);
        msaaFramebuffer_ = 0;
    }
    
    // Tear down context
    if ([EAGLContext currentContext] == context_)
        [EAGLContext setCurrentContext:nil];
    
    [context_ release];
    context_ = nil;
    
    [super dealloc];
}


@end