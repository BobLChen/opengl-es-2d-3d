//
//  mmath.h
//  Monkey
//
//  Created by Neil on 6/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef _mmath_h
#define _mmath_h

#include "platform/PlatformMacros.h"

#include <stdlib.h>
#include <math.h>
#include <time.h>

NS_MONKEY_BEGIN

const static float PI = 3.141592653589793f;

const inline static int NextPOT(int x) {
    x = x - 1;
    x = x | (x >> 1);
    x = x | (x >> 2);
    x = x | (x >> 4);
    x = x | (x >> 8);
    x = x | (x >>16);
    return x + 1;
}

const inline static float randomf() {
    return arc4random() % RAND_MAX * 1.0f / RAND_MAX;
}

const inline static float absf(float f) {
    return f > 0 ? f : -f;
}

#ifndef MIN
#define MIN(x,y) (((x) > (y)) ? (y) : (x))
#endif  // MIN

#ifndef MAX
#define MAX(x,y) (((x) < (y)) ? (y) : (x))
#endif  // MAX

NS_MONKEY_END

#endif
