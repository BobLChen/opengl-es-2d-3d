//
//  Application.cpp
//  HelloMonkey
//
//  Created by Neil on 7/10/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#include "MainDelegate.h"
#include "HelloWorld.h"
#include <App.h>


USING_NS_MONKEY

MainDelegate::MainDelegate() {
    
}

MainDelegate::~MainDelegate() {
    
}

void MainDelegate::didFinishLaunching() {
    HellWorld *world = new HellWorld();
    App::getInstance()->addScene2D(world);
}

void MainDelegate::didEnterBackground() {
    
}

void MainDelegate::didEnterForeground() {
    
}
