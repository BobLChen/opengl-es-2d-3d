//
//  ColorMaterial2D.cpp
//  Opengl2D
//
//  Created by Neil on 8/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#include "2d/material/ColorMaterial2D.h"
#include "2d/material/Shaders2D.h"

#include "core/material/GLSLProgram.h"
#include "core/material/Geometry3D.h"
#include "core/texture/Texture2D.h"
#include "core/geom/Matrix3D.h"

#include "App.h"

NS_MONKEY_BEGIN


ColorMaterial2D* ColorMaterial2D::_instance = nullptr;

ColorMaterial2D* ColorMaterial2D::getInstance() {
    if (!_instance) {
        _instance = new ColorMaterial2D();
    }
    
    return _instance;
}

ColorMaterial2D::ColorMaterial2D() : Material3D(), _red(1.0f), _green(1.0f), _blue(1.0f), _alpha(1.0f) {
    program = GLSLProgram::createFromStrings(SHADER_COLOR_VERT, SHADER_COLOR_FRAG);
    _posVa = program->getAttribLocation("posVa");
    _mvpUniform = program->getUniformLocation("mvp");
    _colorAlphaUniform = program->getUniformLocation("colorAlpha");
}

ColorMaterial2D::~ColorMaterial2D() {
    
}

void ColorMaterial2D::dispose() {
    if (_instance) {
        delete _instance;
        _instance = nullptr;
    }
}

void ColorMaterial2D::setColor(float red, float green, float blue, float alpha) {
    _red    = red;
    _green  = green;
    _blue   = blue;
    _alpha  = alpha;
}

void ColorMaterial2D::draw(Geometry3D *geometry, Matrix3D &world) {
    
    App::getInstance()->vertices  += 4;
    App::getInstance()->drawcalls += 1;
    App::getInstance()->triangles += 2;
    
    program->enable();
    
    geometry->enableVertexBuffer(Geometry3D::VertexType::POSITION, _posVa);
    
    program->setUniform4f(_colorAlphaUniform, _red, _green, _blue, _alpha);
    program->setUniformMatrix4fv(_mvpUniform, world.rawData, 1, GL_FALSE);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->getIndexBuffer());
    glDrawElements(GL_TRIANGLES, geometry->getTrianglesNum(), GL_UNSIGNED_SHORT, 0);
    
    geometry->disableVertexBuffer(Geometry3D::VertexType::POSITION, _posVa);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

NS_MONKEY_END
