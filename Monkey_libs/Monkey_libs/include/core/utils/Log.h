//
//  Log.h
//  Monkey
//
//  Created by Neil on 23/8/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef _LOGS_H
#define _LOGS_H

#include <stdlib.h>
#include <stdio.h>

#include "platform/PlatformConfig.h"
#include "platform/PlatformMacros.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
// Android log
#include <android/log.h>

NS_MONKEY_BEGIN
#define LOGI(FORMAT,...) \
{ __android_log_print(ANDROID_LOG_DEBUG, "t", FORMAT, ##__VA_ARGS__); }
#define LOGE(FORMAT,...) \
{ __android_log_print(ANDROID_LOG_DEBUG, "t", FORMAT, ##__VA_ARGS__); }
NS_MONKEY_END

#else
// ios mac log
NS_MONKEY_BEGIN

#define LOGI(...) { fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n"); }
#define LOGE(...) { fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n"); }

NS_MONKEY_END

#endif// end #if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#endif
