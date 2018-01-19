//
//  RootViewController.m
//  TestOpenglES
//
//  Created by Neil on 17/8/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#import "RootViewController.h"
//#import "GLView.h"
//#import "EAGLView.h"
//#import "App.h"

@implementation RootViewController

// Override to allow orientations other than the default portrait orientation.
// This method is deprecated on ios6
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    return UIInterfaceOrientationIsLandscape( interfaceOrientation );
}

// For ios6, use supportedInterfaceOrientations & shouldAutorotate instead
- (NSUInteger) supportedInterfaceOrientations{
#ifdef __IPHONE_6_0
    return UIInterfaceOrientationMaskAllButUpsideDown;
#endif
}

- (BOOL) shouldAutorotate {
    return YES;
}

- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation {
    [super didRotateFromInterfaceOrientation:fromInterfaceOrientation];
//    GLView *glview = App::getInstance()->getOpenGLView();
//    if (glview) {
//        if (glview->isOpenGLReady()) {
//            CGRect rect = [[UIScreen mainScreen] bounds];
//            glview->setViewPort(0, 0, rect.size.width, rect.size.height);
//            printf("Scene Size Changed %fx%f\n", rect.size.width, rect.size.height);
//        }
//    }
}

//fix not hide status on ios7
- (BOOL)prefersStatusBarHidden
{
    return YES;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

- (void)viewDidUnload {
    [super viewDidUnload];
}

- (void)dealloc {
    [super dealloc];
}


@end
