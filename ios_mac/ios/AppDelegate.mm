//
//  AppDelegate.m
//  MonkeyIOS
//
//  Created by Neil on 30/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#import "AppDelegate.h"
#import "RootViewController.h"
#import "MainDelegate.h"

#import "platform/ios/GLViewIOS.h"
#import "platform/ios/EAGLView.h"

#import "App.h"

USING_NS_MONKEY

MainDelegate* mainDelegate = nullptr;

@interface AppDelegate ()

@end

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    
    _window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    
    // 初始化EAGLVIEW
    EAGLView *eaglView = [EAGLView viewWithFrame: [_window bounds]
                                         pixelFormat: kEAGLColorFormatRGBA8
                                         depthFormat: GL_DEPTH24_STENCIL8_OES
                                  preserveBackbuffer: NO
                                          sharegroup: nil
                                       multiSampling: NO
                                     numberOfSamples: 0];
    // 初始化view controller
    _viewController = [[RootViewController alloc] initWithNibName:nil bundle:nil];
    _viewController.view = eaglView;

    [[_viewController view] setMultipleTouchEnabled:true];
    [_window setRootViewController:_viewController];
    [_window makeKeyAndVisible];
    
    [[UIApplication sharedApplication] setStatusBarHidden:true];

    self.window.backgroundColor = [UIColor whiteColor];
    
    // 初始化glview
    GLViewIOS *glview = new GLViewIOS();
    glview->initWithEAGLView((void*)eaglView);
    // 初始化app
    id runner = [NSClassFromString(@"CADisplayLink") displayLinkWithTarget:self selector:@selector(doCaller:)];
    [runner setFrameInterval: 1];
    [runner addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
    
    App::getInstance()->setOpenGLView(glview);
    App::getInstance()->setBackcolor(0x333333);
    
    CGSize size = [[UIScreen mainScreen] bounds].size;
    App::getInstance()->setViewport(0, 0, size.width * App::getInstance()->getScaleFactor(), size.height * App::getInstance()->getScaleFactor());
    
    mainDelegate = new MainDelegate();
    mainDelegate->didFinishLaunching();
    
    return YES;
}

/**
 *  update
 *
 *  @param sender
 */
-(void) doCaller: (id) sender
{
    // update
    App::getInstance()->update();
}

- (void)applicationWillResignActive:(UIApplication *)application {
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
    
    mainDelegate->didEnterBackground();
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
    mainDelegate->didEnterForeground();
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}

- (void)applicationWillTerminate:(UIApplication *)application {
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}

@end
