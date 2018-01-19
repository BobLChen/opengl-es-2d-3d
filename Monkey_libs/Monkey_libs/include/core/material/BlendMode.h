//
//  BlendMode.h
//  Monkey
//
//  Created by Neil on 6/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef __BlendMode__
#define __BlendMode__

#include "platform/PlatformMacros.h"

NS_MONKEY_BEGIN

/**
 * 混合模式
 */
enum BlendMode {
    NORMAL,
    ADD,
    ALPHA,
    ALPHA_PREMULTIPILED,
    MULTIPLE,
    SCREEN
};

NS_MONKEY_END

#endif
