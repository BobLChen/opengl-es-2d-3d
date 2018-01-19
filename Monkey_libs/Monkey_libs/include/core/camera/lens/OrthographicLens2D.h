//
//  OrthographicLens2D.h
//  Monkey_libs
//
//  Created by Neil on 7/10/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef Monkey_libs_OrthographicLens2D_h
#define Monkey_libs_OrthographicLens2D_h

#include "core/camera/lens/OrthographicLens.h"

NS_MONKEY_BEGIN

class OrthographicLens2D : public OrthographicLens {
    
public:
    
    OrthographicLens2D();
    virtual ~OrthographicLens2D();
    
    /**
     *  更新projection矩阵
     */
    virtual void updateProjectionMatrix() override;
    
};

NS_MONKEY_END

#endif
