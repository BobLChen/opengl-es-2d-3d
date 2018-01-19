//
//  main.m
//  mac
//
//  Created by Neil on 30/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#import <Cocoa/Cocoa.h>

#import "2d/scene/Scene2D.h"
#import "2d/entities/Image.h"
#import "platform/desktop/GLViewDesktop.h"
#import "App.h"

#import "MainDelegate.h"

USING_NS_MONKEY

int main(int argc, const char * argv[]) {
    
    GLViewDesktop *glview = new GLViewDesktop();
    glview->initWithRect("Monkey", 0, 0, 1024, 768);
    
    App::getInstance()->setOpenGLView(glview);
    App::getInstance()->setBackcolor(0x333333);
    
    MainDelegate *delegate = new MainDelegate();
    delegate->didFinishLaunching();
    
    while (true) {
        App::getInstance()->update();
    }
    
    return 1;
}
