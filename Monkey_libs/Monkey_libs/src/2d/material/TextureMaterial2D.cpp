//
//  QuadMaterial2D.cpp
//  Opengl2D
//
//  Created by Neil on 7/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#include "2d/material/TextureMaterial2D.h"
#include "core/material/GLSLProgram.h"
#include "core/material/Geometry3D.h"
#include "core/texture/Texture2D.h"
#include "core/geom/Matrix3D.h"
#include "2d/material/Shaders2D.h"
#include "App.h"

NS_MONKEY_BEGIN

TextureMaterial2D* TextureMaterial2D::_instance = nullptr;

void TextureMaterial2D::dispose() {
    if (_instance) {
        delete _instance;
        _instance = nullptr;
    }
}

TextureMaterial2D* TextureMaterial2D::getInstance() {
    if (!_instance) {
        _instance = new TextureMaterial2D();
    }
    return _instance;
}

TextureMaterial2D::TextureMaterial2D():Material3D() {
    
    program = GLSLProgram::createFromStrings(SHADER_TEXTURE_VERT, SHADER_TEXTURE_FRAG);
    
    _posVaInstance  = program->getAttribLocation("posVa");
    _uvVaInstance   = program->getAttribLocation("uvVa");
    _textureUnifrom = program->getUniformLocation("texture");
    _mvpUniform     = program->getUniformLocation("mvp");
    _alphaUniform   = program->getUniformLocation("alpha");
}

TextureMaterial2D::~TextureMaterial2D() {
    
}

void TextureMaterial2D::draw(Geometry3D *geometry, Texture2D *texture, Matrix3D &world, float alpha) {
    
    App::getInstance()->vertices  += 4;
    App::getInstance()->drawcalls += 1;
    App::getInstance()->triangles += 2;
    
    program->enable();
    // enabe 顶点和uv
    geometry->enableVertexBuffer(Geometry3D::VertexType::POSITION,  _posVaInstance);
    geometry->enableVertexBuffer(Geometry3D::VertexType::UV0,       _uvVaInstance);
    // 启用texture
    texture->enableTexture();
    program->setUniform1i(_textureUnifrom, 0);
    program->setUniform1f(_alphaUniform, alpha);
    program->setUniformMatrix4fv(_mvpUniform, world.rawData, 1, GL_FALSE);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->getIndexBuffer());
    // draw
    glDrawElements(GL_TRIANGLES, geometry->getTrianglesNum(), GL_UNSIGNED_SHORT, 0);
    // disable
    geometry->disableVertexBuffer(Geometry3D::VertexType::POSITION, _posVaInstance);
    geometry->disableVertexBuffer(Geometry3D::VertexType::UV0,      _uvVaInstance);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    texture->disableTexture();
}

NS_MONKEY_END
