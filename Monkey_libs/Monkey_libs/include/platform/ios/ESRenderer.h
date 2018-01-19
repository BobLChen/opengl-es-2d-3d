//
//  CCESRenderer.h
//  Monkey
//
//  Created by Neil on 17/8/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef _RENDER_
#define _RENDER_

#import "platform/PlatformConfig.h"

#if TARGET_PLATFORM == PLATFORM_IOS

#import <QuartzCore/QuartzCore.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/EAGLDrawable.h>

#import "platform/PlatformMacros.h"

@protocol ESRenderer <NSObject>

- (id) initWithDepthFormat:(unsigned int)depthFormat withPixelFormat:(unsigned int)pixelFormat withSharegroup:(EAGLSharegroup*)sharegroup withMultiSampling:(BOOL) multiSampling withNumberOfSamples:(unsigned int) requestedSamples;

- (BOOL) resizeFromLayer:(CAEAGLLayer *)layer;

- (EAGLContext*) context;
- (CGSize) backingSize;

- (unsigned int) colorRenderBuffer;
- (unsigned int) defaultFrameBuffer;
- (unsigned int) msaaFrameBuffer;
- (unsigned int) msaaColorBuffer;

@end

#endif

#endif