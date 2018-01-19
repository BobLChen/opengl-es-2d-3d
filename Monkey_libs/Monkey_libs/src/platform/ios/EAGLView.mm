//
//  CCEAGLView.m
//  TestOpenglES
//
//  Created by Neil on 17/8/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#include "platform/ios/ES2Renderer.h"
#include "platform/ios/EAGLView.h"
#include "platform/PlatformMacros.h"

#include "core/geom/Vector2D.h"
#include "core/event/TouchEvent.h"

#include "core/utils/Input3D.h"

#include "App.h"

USING_NS_MONKEY

@interface EAGLView (Private)
- (BOOL)            setupSurfaceWithSharegroup:(EAGLSharegroup*)sharegroup;
- (unsigned int)    convertPixelFormat:(NSString*) pixelFormat;
@end

@implementation EAGLView

@synthesize surfaceSize              = size_;
@synthesize pixelFormat              = pixelformat_, depthFormat = depthFormat_;
@synthesize context                  = context_;
@synthesize multiSampling            = multiSampling_;
@synthesize isKeyboardShown          = isKeyboardShown_;
@synthesize keyboardShowNotification = keyboardShowNotification_;

+ (Class) layerClass
{
    return [CAEAGLLayer class];
}

+ (id) viewWithFrame:(CGRect)frame
{
    return [[[self alloc] initWithFrame:frame] autorelease];
}

+ (id) viewWithFrame:(CGRect)frame pixelFormat:(NSString*)format
{
    return [[[self alloc]initWithFrame:frame pixelFormat:format] autorelease];
}

+ (id) viewWithFrame:(CGRect)frame pixelFormat:(NSString*)format depthFormat:(GLuint)depth
{
    return [[[self alloc] initWithFrame:frame pixelFormat:format depthFormat:depth preserveBackbuffer:NO sharegroup:nil multiSampling:NO numberOfSamples:0] autorelease];
}

+ (id) viewWithFrame:(CGRect)frame pixelFormat:(NSString*)format depthFormat:(GLuint)depth preserveBackbuffer:(BOOL)retained sharegroup:(EAGLSharegroup*)sharegroup multiSampling:(BOOL)multisampling numberOfSamples:(unsigned int)samples
{
    return [[[self alloc]initWithFrame:frame pixelFormat:format depthFormat:depth preserveBackbuffer:retained sharegroup:sharegroup multiSampling:multisampling numberOfSamples:samples] autorelease];
}

- (id) initWithFrame:(CGRect)frame
{
    return [self initWithFrame:frame pixelFormat:kEAGLColorFormatRGB565 depthFormat:0 preserveBackbuffer:NO sharegroup:nil multiSampling:NO numberOfSamples:0];
}

- (id) initWithFrame:(CGRect)frame pixelFormat:(NSString*)format
{
    return [self initWithFrame:frame pixelFormat:format depthFormat:0 preserveBackbuffer:NO sharegroup:nil multiSampling:NO numberOfSamples:0];
}

- (id) initWithFrame:(CGRect)frame pixelFormat:(NSString*)format depthFormat:(GLuint)depth preserveBackbuffer:(BOOL)retained sharegroup:(EAGLSharegroup*)sharegroup multiSampling:(BOOL)sampling numberOfSamples:(unsigned int)nSamples;
{
    if((self = [super initWithFrame:frame]))
    {
        isUseUITextField    = YES;
        pixelformat_        = format;
        depthFormat_        = depth;
        multiSampling_      = sampling;
        requestedSamples_   = nSamples;
        preserveBackbuffer_ = retained;
        markedText_ = nil;
        
        if( ! [self setupSurfaceWithSharegroup:sharegroup] ) {
            [self release];
            return nil;
        }
        
        originalRect_ = self.frame;
        self.keyboardShowNotification = nil;
        
		if ([self respondsToSelector:@selector(setContentScaleFactor:)])
		{
			self.contentScaleFactor = [[UIScreen mainScreen] scale];
		}
        
        App::getInstance()->setScaleFactor(self.contentScaleFactor);
        App::getInstance()->setViewport(0, 0, self.contentScaleFactor * originalRect_.size.width, originalRect_.size.height * self.contentScaleFactor);
    }
    
    return self;
}

-(id) initWithCoder:(NSCoder *)aDecoder
{
    if( (self = [super initWithCoder:aDecoder]) ) {
        
        CAEAGLLayer*            eaglLayer = (CAEAGLLayer*)[self layer];
        
        pixelformat_        = kEAGLColorFormatRGB565;
        depthFormat_        = 0;                        // GL_DEPTH_COMPONENT24_OES;
        multiSampling_      = NO;
        requestedSamples_   = 0;
        size_ = [eaglLayer bounds].size;
        markedText_ = nil;
        
        if( ! [self setupSurfaceWithSharegroup:nil] ) {
            [self release];
            return nil;
        }
    }
    
    return self;
}

- (void)didMoveToWindow;
{
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(onUIKeyboardNotification:)
                                                 name:UIKeyboardWillShowNotification object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(onUIKeyboardNotification:)
                                                 name:UIKeyboardDidShowNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(onUIKeyboardNotification:)
                                                 name:UIKeyboardWillHideNotification object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(onUIKeyboardNotification:)
                                                 name:UIKeyboardDidHideNotification object:nil];
    
}

-(int) getWidth
{
    CGSize bound = [self bounds].size;
    return (int)bound.width * self.contentScaleFactor;
}

-(int) getHeight
{
    CGSize bound = [self bounds].size;
    return (int)bound.height * self.contentScaleFactor;
}


-(BOOL) setupSurfaceWithSharegroup:(EAGLSharegroup*)sharegroup
{
    CAEAGLLayer *eaglLayer = (CAEAGLLayer *)self.layer;
    
    eaglLayer.opaque = YES;
    eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
                                    [NSNumber numberWithBool:preserveBackbuffer_], kEAGLDrawablePropertyRetainedBacking,
                                    pixelformat_, kEAGLDrawablePropertyColorFormat, nil];
    
    renderer_ = [[ES2Renderer alloc] initWithDepthFormat:depthFormat_
                                           withPixelFormat:[self convertPixelFormat:pixelformat_]
                                            withSharegroup:sharegroup
                                         withMultiSampling:multiSampling_
                                       withNumberOfSamples:requestedSamples_];
    
    NSAssert(renderer_, @"OpenGL ES 2.O is required.");
    if (!renderer_)
        return NO;
    
    context_ = [renderer_ context];
    
    printf("Context init done ... \n");
    
#if GL_EXT_discard_framebuffer == 1
    discardFramebufferSupported_ = YES;
#else
    discardFramebufferSupported_ = NO;
    printf("discardFramebufferSupported_=NO\n");
#endif
    
    return YES;
}

- (void) dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self]; // remove keyboard notification
    [renderer_ release];
    self.keyboardShowNotification = NULL; // implicit release
    [super dealloc];
}

- (void) layoutSubviews
{
    //TODO:解决旋转问题
    [renderer_ resizeFromLayer:(CAEAGLLayer*)self.layer];
    size_ = [renderer_ backingSize];
    App::getInstance()->setViewport(0, 0, size_.width, size_.height);
}

-(id<ESRenderer>) getRender
{
    return renderer_;
}

- (void) swapBuffers
{
    // IMPORTANT:
    // - preconditions
    //    -> context_ MUST be the OpenGL context
    //    -> renderbuffer_ must be the the RENDER BUFFER
    
#ifdef __IPHONE_4_0
    
    if (multiSampling_)
    {
        /* Resolve from msaaFramebuffer to resolveFramebuffer */
        //glDisable(GL_SCISSOR_TEST);
        glBindFramebuffer(GL_READ_FRAMEBUFFER_APPLE, [renderer_ msaaFrameBuffer]);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER_APPLE, [renderer_ defaultFrameBuffer]);
        glResolveMultisampleFramebufferAPPLE();
    }
    
    if(discardFramebufferSupported_)
    {
        if (multiSampling_)
        {
            if (depthFormat_)
            {
                GLenum attachments[] = {GL_COLOR_ATTACHMENT0, GL_DEPTH_ATTACHMENT};
                glDiscardFramebufferEXT(GL_READ_FRAMEBUFFER_APPLE, 2, attachments);
            }
            else
            {
                GLenum attachments[] = {GL_COLOR_ATTACHMENT0};
                glDiscardFramebufferEXT(GL_READ_FRAMEBUFFER_APPLE, 1, attachments);
            }
            
            glBindRenderbuffer(GL_RENDERBUFFER, [renderer_ colorRenderBuffer]);
            
        }
        
        // not MSAA
        else if (depthFormat_ ) {
            GLenum attachments[] = { GL_DEPTH_ATTACHMENT};
            glDiscardFramebufferEXT(GL_FRAMEBUFFER, 1, attachments);
        }
    }
#endif // __IPHONE_4_0
    
    if(![context_ presentRenderbuffer:GL_RENDERBUFFER])
    {
    }
    
    // We can safely re-bind the framebuffer here, since this will be the
    // 1st instruction of the new main loop
    if( multiSampling_ )
        glBindFramebuffer(GL_FRAMEBUFFER, [renderer_ msaaFrameBuffer]);
    
}

- (unsigned int) convertPixelFormat:(NSString*) pixelFormat
{
    // define the pixel format
    GLenum pFormat;
    
    if([pixelFormat isEqualToString:@"EAGLColorFormat565"])
        pFormat = GL_RGB565;
    else
        pFormat = GL_RGBA8_OES;
    
    return pFormat;
}

#pragma mark CCEAGLView - Point conversion

- (CGPoint) convertPointFromViewToSurface:(CGPoint)point
{
    CGRect bounds = [self bounds];
    
    CGPoint ret;
    ret.x =  (point.x - bounds.origin.x)  / bounds.size.width * size_.width;
    ret.y =  (point.y - bounds.origin.y) / bounds.size.height * size_.height;
    
    return ret;
}

- (CGRect) convertRectFromViewToSurface:(CGRect)rect
{
    CGRect bounds = [self bounds];
    
    CGRect ret;
    ret.origin.x = (rect.origin.x - bounds.origin.x) / bounds.size.width * size_.width;
    ret.origin.y = (rect.origin.y - bounds.origin.y) / bounds.size.height * size_.height;
    ret.size.width = rect.size.width / bounds.size.width * size_.width;
    ret.size.height = rect.size.height / bounds.size.height * size_.height;
    
    return ret;
}


-(void) handleTouchesAfterKeyboardShow
{
    NSArray *subviews = self.subviews;
    
    for(UIView* view in subviews)
    {
        if([view isKindOfClass:NSClassFromString(@"CCCustomUITextField")])
        {
            if ([view isFirstResponder])
            {
                [view resignFirstResponder];
                return;
            }
        }
    }
}

// Pass the touches to the superview
- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    if (isKeyboardShown_)
    {
        [self handleTouchesAfterKeyboardShow];
    }
    // 统计数量
    int length = 0;
    for (UITouch *touch in touches) {
        length++;
    }
    // new
    Point2D *points = new Point2D[length]();
    // set zero
    length = 0;
    for (UITouch *touch in touches) {
        float x = [touch locationInView: [touch view]].x;
        float y = [touch locationInView: [touch view]].y;
        points[length].x = x * self.contentScaleFactor;
        points[length].y = y * self.contentScaleFactor;
        length++;
    }
    // handle events
    MouseEvent mouseEvent(MouseEvent::TOUCH_BEGAN, true, points, length);
    App::getInstance()->handleTouchesBegan(mouseEvent);
    Input3D::mouseDown(points, length);
    // delete
    delete [] points;
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    
    int size = 0;
    for (UITouch *touch in touches) {
        size++;
    }
    
    Point2D *points = new Point2D[size]();
    
    size = 0;
    for (UITouch *touch in touches) {
        float x = [touch locationInView: [touch view]].x;
        float y = [touch locationInView: [touch view]].y;
        points[size].x = x * self.contentScaleFactor;
        points[size].y = y * self.contentScaleFactor;
        size++;
    }
    
    MouseEvent mouseEvent(MouseEvent::TOUCH_MOVE, true, points, size);
    App::getInstance()->handleTouchesMove(mouseEvent);
    Input3D::mouseMove(points, size);
    
    delete [] points;
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    
    int size = 0;
    for(UITouch *touch in touches) {
        size++;
    }
    
    Point2D *points = new Point2D[size]();
    size = 0;
    for (UITouch *touch in touches) {
        float x = [touch locationInView: [touch view]].x;
        float y = [touch locationInView: [touch view]].y;
        points[size].x = x * self.contentScaleFactor;
        points[size].y = y * self.contentScaleFactor;
        size++;
    }
    
    MouseEvent mouseEvent(MouseEvent::TOUCH_END, true, points, size);
    App::getInstance()->handleTouchesEnd(mouseEvent);
    Input3D::mouseUP(points, size);
    
    delete [] points;
 }

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
    
    for (UITouch *touch in touches) {
        float x = [touch locationInView: [touch view]].x;
        float y = [touch locationInView: [touch view]].y;
        printf("Touch Cancelled:x=%f, y=%f\n", x, y);
    }
    
}

#pragma mark - UIView - Responder

- (BOOL)canBecomeFirstResponder
{
    if (nil != markedText_) {
        [markedText_ release];
    }
    markedText_ = nil;
    if (isUseUITextField)
    {
        return NO;
    }
    return YES;
}

- (BOOL)becomeFirstResponder
{
    isUseUITextField = NO;
    return [super becomeFirstResponder];
}

- (BOOL)resignFirstResponder
{
    isUseUITextField = YES;
    return [super resignFirstResponder];
}

#pragma mark - UIKeyInput protocol


- (BOOL)hasText
{
    return NO;
}

- (void)insertText:(NSString *)text
{
    if (nil != markedText_) {
        [markedText_ release];
        markedText_ = nil;
    }
}

- (void)deleteBackward
{
    if (nil != markedText_) {
        [markedText_ release];
        markedText_ = nil;
    }
}

#pragma mark - UITextInputTrait protocol

-(UITextAutocapitalizationType) autocapitalizationType
{
    return UITextAutocapitalizationTypeNone;
}

#pragma mark - UITextInput protocol

#pragma mark UITextInput - properties

@synthesize beginningOfDocument;
@synthesize endOfDocument;
@synthesize inputDelegate;
@synthesize markedTextRange;
@synthesize markedTextStyle;
// @synthesize selectedTextRange;       // must implement
@synthesize tokenizer;

/* Text may have a selection, either zero-length (a caret) or ranged.  Editing operations are
 * always performed on the text from this selection.  nil corresponds to no selection. */
- (void)setSelectedTextRange:(UITextRange *)aSelectedTextRange;
{
}
- (UITextRange *)selectedTextRange;
{
    return [[[UITextRange alloc] init] autorelease];
}

#pragma mark UITextInput - Replacing and Returning Text

- (NSString *)textInRange:(UITextRange *)range;
{
    return @"";
}
- (void)replaceRange:(UITextRange *)range withText:(NSString *)theText;
{
}

#pragma mark UITextInput - Working with Marked and Selected Text



/* If text can be selected, it can be marked. Marked text represents provisionally
 * inserted text that has yet to be confirmed by the user.  It requires unique visual
 * treatment in its display.  If there is any marked text, the selection, whether a
 * caret or an extended range, always resides within.
 *
 * Setting marked text either replaces the existing marked text or, if none is present,
 * inserts it from the current selection. */

- (void)setMarkedTextRange:(UITextRange *)markedTextRange;
{
}

- (UITextRange *)markedTextRange;
{
    return nil; // Nil if no marked text.
}
- (void)setMarkedTextStyle:(NSDictionary *)markedTextStyle;
{
    
}
- (NSDictionary *)markedTextStyle;
{
    return nil;
}
- (void)setMarkedText:(NSString *)markedText selectedRange:(NSRange)selectedRange;
{
    if (markedText == markedText_) {
        return;
    }
    if (nil != markedText_) {
        [markedText_ release];
    }
    markedText_ = markedText;
    [markedText_ retain];
}
- (void)unmarkText;
{
    if (nil == markedText_)
    {
        return;
    }
    [markedText_ release];
    markedText_ = nil;
}

#pragma mark Methods for creating ranges and positions.

- (UITextRange *)textRangeFromPosition:(UITextPosition *)fromPosition toPosition:(UITextPosition *)toPosition;
{
    return nil;
}
- (UITextPosition *)positionFromPosition:(UITextPosition *)position offset:(NSInteger)offset;
{
    return nil;
}
- (UITextPosition *)positionFromPosition:(UITextPosition *)position inDirection:(UITextLayoutDirection)direction offset:(NSInteger)offset;
{
    return nil;
}

/* Simple evaluation of positions */
- (NSComparisonResult)comparePosition:(UITextPosition *)position toPosition:(UITextPosition *)other;
{
    return (NSComparisonResult)0;
}
- (NSInteger)offsetFromPosition:(UITextPosition *)from toPosition:(UITextPosition *)toPosition;
{
    return 0;
}

- (UITextPosition *)positionWithinRange:(UITextRange *)range farthestInDirection:(UITextLayoutDirection)direction;
{
    return nil;
}
- (UITextRange *)characterRangeByExtendingPosition:(UITextPosition *)position inDirection:(UITextLayoutDirection)direction;
{
    return nil;
}

#pragma mark Writing direction

- (UITextWritingDirection)baseWritingDirectionForPosition:(UITextPosition *)position inDirection:(UITextStorageDirection)direction;
{
    return UITextWritingDirectionNatural;
}
- (void)setBaseWritingDirection:(UITextWritingDirection)writingDirection forRange:(UITextRange *)range;
{
}

#pragma mark Geometry

/* Geometry used to provide, for example, a correction rect. */
- (CGRect)firstRectForRange:(UITextRange *)range;
{
    return CGRectNull;
}
- (CGRect)caretRectForPosition:(UITextPosition *)position;
{
    return caretRect_;
}

#pragma mark Hit testing

/* JS - Find the closest position to a given point */
- (UITextPosition *)closestPositionToPoint:(CGPoint)point;
{
    return nil;
}
- (UITextPosition *)closestPositionToPoint:(CGPoint)point withinRange:(UITextRange *)range;
{
    return nil;
}
- (UITextRange *)characterRangeAtPoint:(CGPoint)point;
{
    return nil;
}

- (NSArray *)selectionRectsForRange:(UITextRange *)range
{
    return nil;
}

#pragma mark - UIKeyboard notification

- (void)onUIKeyboardNotification:(NSNotification *)notif;
{
//    NSString * type = notif.name;
    
    NSDictionary* info = [notif userInfo];
    CGRect begin = [self convertRect:
                    [[info objectForKey:UIKeyboardFrameBeginUserInfoKey] CGRectValue]
                            fromView:self];
    CGRect end = [self convertRect:
                  [[info objectForKey:UIKeyboardFrameEndUserInfoKey] CGRectValue]
                          fromView:self];
//    double aniDuration = [[info objectForKey:UIKeyboardAnimationDurationUserInfoKey] doubleValue];
    
    CGSize viewSize = self.frame.size;
    CGFloat tmp;
    
    switch ([[UIApplication sharedApplication] statusBarOrientation])
    {
        case UIInterfaceOrientationPortrait:
            begin.origin.y = viewSize.height - begin.origin.y - begin.size.height;
            end.origin.y = viewSize.height - end.origin.y - end.size.height;
            break;
            
        case UIInterfaceOrientationPortraitUpsideDown:
            begin.origin.x = viewSize.width - (begin.origin.x + begin.size.width);
            end.origin.x = viewSize.width - (end.origin.x + end.size.width);
            break;
            
        case UIInterfaceOrientationLandscapeLeft:
            tmp = begin.size.width;
            begin.size.width = begin.size.height;
            begin.size.height = tmp;
            tmp = end.size.width;
            end.size.width = end.size.height;
            end.size.height = tmp;
            tmp = viewSize.width;
            viewSize.width = viewSize.height;
            viewSize.height = tmp;
            
            tmp = begin.origin.x;
            begin.origin.x = begin.origin.y;
            begin.origin.y = viewSize.height - tmp - begin.size.height;
            tmp = end.origin.x;
            end.origin.x = end.origin.y;
            end.origin.y = viewSize.height - tmp - end.size.height;
            break;
            
        case UIInterfaceOrientationLandscapeRight:
            tmp = begin.size.width;
            begin.size.width = begin.size.height;
            begin.size.height = tmp;
            tmp = end.size.width;
            end.size.width = end.size.height;
            end.size.height = tmp;
            tmp = viewSize.width;
            viewSize.width = viewSize.height;
            viewSize.height = tmp;
            
            tmp = begin.origin.x;
            begin.origin.x = begin.origin.y;
            begin.origin.y = tmp;
            tmp = end.origin.x;
            end.origin.x = end.origin.y;
            end.origin.y = tmp;
            break;
            
        default:
            break;
    }
    
}

-(void) doAnimationWhenKeyboardMoveWithDuration:(float)duration distance:(float)dis
{
    
}


-(void) doAnimationWhenAnotherEditBeClicked
{
    if (self.keyboardShowNotification != nil)
    {
        [[NSNotificationCenter defaultCenter]postNotification:self.keyboardShowNotification];
    }
}

@end
