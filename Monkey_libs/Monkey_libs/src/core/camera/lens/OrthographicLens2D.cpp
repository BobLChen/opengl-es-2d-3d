//
//  OrthographicLens2D.cpp
//  Monkey_libs
//
//  Created by Neil on 7/10/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#include "core/camera/lens/OrthographicLens2D.h"

NS_MONKEY_BEGIN

OrthographicLens2D::OrthographicLens2D() : OrthographicLens() {
    
}

OrthographicLens2D::~OrthographicLens2D () {
    
}

void OrthographicLens2D::updateProjectionMatrix() {
    
    float scaleX = 2 / (_right - _left);
    float scaleY = 2 / (_top - _bottom);
    float scaleZ = 1 / (_far - _near);
    float offseX = (-0.5 * (_right + _left)) * scaleX;
    float offseY = (-0.5 * (_top + _bottom)) * scaleY;
    float offseZ = _near * scaleZ;
    
    _projection.rawData[0] = scaleX;
    _projection.rawData[5] = scaleY;
    _projection.rawData[10]= scaleZ;
    _projection.rawData[12]= offseX;
    _projection.rawData[13]= -offseY;
    _projection.rawData[14]= -offseZ;
    _projection.rawData[1] = _projection.rawData[2] = _projection.rawData[4] = _projection.rawData[6] =
    _projection.rawData[9] = _projection.rawData[3] = _projection.rawData[7] = _projection.rawData[11]= 0.0f;
    _projection.rawData[15] = 1.0f;
    
    LensBase::updateProjectionMatrix();
}

NS_MONKEY_END
