//
//  Geometry3D.cpp
//  TestOpenglES
//
//  Created by Neil on 30/8/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#include "core/material/Geometry3D.h"
#include "core/utils/Log.h"

#include <stdlib.h>

NS_MONKEY_BEGIN

Geometry3D::Geometry3D() {
    for (int i = 0; i <= VertexType::CUSTOM6; i++) {
        formats[i]          = -1;
        vertexBuffers[i]    = 0;
        dataSizes[i]        = -1;
        bufferDatas[i]      = nullptr;
    }
    indexBuffer = 0;
    indexSize   = 0;
}

Geometry3D::~Geometry3D() {
    for (int i = 0; i <= VertexType::CUSTOM6; i++) {
        if (bufferDatas[i]) {
            free((void*)bufferDatas[i]);
        }
        if (vertexBuffers[i] != 0) {
            glDeleteBuffers(1, &vertexBuffers[i]);
        }
    }
    free(indexbufferData);
    glDeleteBuffers(1, &indexBuffer);
}

void Geometry3D::setIndexBuffer(const char *data, const ssize_t size, const int triangleNum) {
    char *buf = (char*)malloc(size);
    memcpy(buf, data, size);
    this->indexbufferData   = buf;
    this->indexSize         = (int)size;
    this->triangleNum       = triangleNum;
}

GLuint& Geometry3D::getIndexBuffer() {
    if (indexBuffer == 0) {
        glGenBuffers(1, &indexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize, indexbufferData, GL_STATIC_DRAW);
    }
    return indexBuffer;
}

int Geometry3D::getTrianglesNum() {
    return triangleNum;
}

void Geometry3D::addVertexBuffer(Geometry3D::VertexType type, const char *data, const ssize_t size, const int formatSize) {
    char *buf = (char*)malloc(size);
    memcpy(buf, data, size);
    formats[type] = formatSize;
    bufferDatas[type] = buf;
    dataSizes[type] = (int)size;
}

void Geometry3D::removeVertexBuffer(Geometry3D::VertexType type) {
    if (bufferDatas[type] != nullptr) {
        free(bufferDatas[type]);
        bufferDatas[type] = nullptr;
    }
    if (vertexBuffers[type] != 0) {
        glDeleteBuffers(1, &vertexBuffers[type]);
        vertexBuffers[type] = 0;
    }
    formats[type] = -1;
    dataSizes[type] = -1;
}

void Geometry3D::enableVertexBuffer(Geometry3D::VertexType type, const GLuint &index) {
    if (vertexBuffers[type] == 0) {
        glGenBuffers(1, &(vertexBuffers[type]));
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffers[type]);
        glBufferData(GL_ARRAY_BUFFER, dataSizes[type], bufferDatas[type], GL_STATIC_DRAW);
    }
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffers[type]);
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, formats[type], GL_FLOAT, GL_FALSE, formats[type] * sizeof(float), 0);
}

void Geometry3D::disableVertexBuffer(Geometry3D::VertexType type, const GLuint &index) {
    glDisableVertexAttribArray(index);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

const char* Geometry3D::getVertexBuffer(Geometry3D::VertexType type) {
    return (const char*)bufferDatas[type];
}

NS_MONKEY_END