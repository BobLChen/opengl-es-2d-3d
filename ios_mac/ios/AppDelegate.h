//
//  AppDelegate.h
//  MonkeyIOS
//
//  Created by Neil on 30/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#import <UIKit/UIKit.h>

@class RootViewController;

@interface AppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow *window;

@property(nonatomic, readonly) RootViewController* viewController;

@end


