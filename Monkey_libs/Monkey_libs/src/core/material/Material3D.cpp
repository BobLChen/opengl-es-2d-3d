//
//  Material3D.cpp
//  TestOpenglES
//
//  Created by Neil on 31/8/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#include "core/material/Material3D.h"
#include "core/material/GLSLProgram.h"
#include "platform/FileUtils.h"

NS_MONKEY_BEGIN

Material3D::Material3D() : program(nullptr) {
    
}

Material3D::Material3D(const std::string &vertPath, const std::string &fragPath) : program(nullptr) {
    program = GLSLProgram::createFromFiles(
                                           FileUtils::getInstance()->getFullPath(vertPath).c_str(),
                                           FileUtils::getInstance()->getFullPath(fragPath).c_str()
                                           );
}

Material3D::~Material3D() {
    if (program) {
        program->disable();
        delete program;
        program = nullptr;
    }
}

GLSLProgram* Material3D::getProgram() {
    return program;
}

void Material3D::draw(Geometry3D *geometry) {
    
}

NS_MONKEY_END