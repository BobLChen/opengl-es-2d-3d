//
//  QuadUtils.h
//  Monkey
//
//  Created by Neil on 18/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#ifndef _QuadUtils_h
#define _QuadUtils_h

#include "core/material/Geometry3D.h"
#include "core/base/GLBase.h"

NS_MONKEY_BEGIN

/**
 *  创建QuadGeometry
 *  @param width   宽度
 *  @param height  高度
 *  @param anchorX 锚点x
 *  @param anchorY 锚点y
 *  @param su      uv起点u
 *  @param sv      uv起点v
 *  @param eu      uv终点u
 *  @param ev      uv终点v
 *  @param rotated 是否倒置
 *  @return        Geometry3D、由你自己回收。
 */
static inline Geometry3D* createQuadGeometry(int width, int height, float anchorX, float anchorY, float su = 0.0f, float sv = 0.0f, float eu = 1.0f, float ev = 1.0f, bool rotated = false) {
    
    float dw = width  * anchorX;
    float dh = height * anchorY;
    
    float wl = -dw;             // 左边宽度
    float wr = width - dw;      // 右边宽度
    float ht = dh;              // 上方高度
    float hb = dh - height;     // 下方高度
    
    Geometry3D *geo = new Geometry3D();
    
    float vertices[12] = {
        wl, hb, 0.0f,           // 左下角
        wl, ht, 0.0f,           // 左上角
        wr, hb, 0.0f,           // 右下角
        wr, ht, 0.0f,           // 右上角
    };
    
    if (rotated) {
        if (rotated) {
            float tmp = width;
            width = height;
            height = tmp;
        }
        vertices[0] = height - dw;
        vertices[1] = -width + dh;
        vertices[2] = 0;
        
        vertices[3] = 0.0f - dw;
        vertices[4] = -width + dh;
        vertices[5] = 0.0f;
        
        vertices[6] = height - dw;
        vertices[7] = 0.0f + dh;
        vertices[8] = 0.0f;
        
        vertices[9] = 0.0f - dw;
        vertices[10] = 0.0f + dh;
        vertices[11] = 0.0f;
    }
    
    float uvs[8] = {
        su, ev,
        su, sv,
        eu, ev,
        eu, sv
    };
    
    GLushort indices[6] = {0, 1, 2, 2, 1, 3};
    
    geo->addVertexBuffer(Geometry3D::VertexType::POSITION, (const char*)vertices, sizeof(vertices), 3);
    geo->addVertexBuffer(Geometry3D::VertexType::UV0, (const char*)uvs, sizeof(uvs), 2);
    geo->setIndexBuffer((const char*)indices, sizeof(indices), 6);
    
    return geo;
}

NS_MONKEY_END

#endif
