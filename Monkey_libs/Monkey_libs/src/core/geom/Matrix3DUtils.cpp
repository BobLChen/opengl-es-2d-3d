//
//  Matrix3DUtils.cpp
//  TestOpenglES
//
//  Created by Neil on 25/8/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#include "core/geom/Matrix3DUtils.h"
#include "platform/PlatformMacros.h"

NS_MONKEY_BEGIN

static float MIN_SCALE = 0.000001f;

const static Vector3D X_AXIS = Vector3D::X_AXIS;
const static Vector3D Y_AXIS = Vector3D::Y_AXIS;
const static Vector3D Z_AXIS = Vector3D::Z_AXIS;

float Matrix3DUtils::_x = 0.0f;
float Matrix3DUtils::_y = 0.0f;
float Matrix3DUtils::_z = 0.0f;
float Matrix3DUtils::_toRad = 0.0174532925199433f;
float Matrix3DUtils::_toAng = 57.2957795130823f;
float Matrix3DUtils::_raw[16] = {0.0f};
float Matrix3DUtils::RAW_DATA_CONTAINER[16] = {0.0f};

Vector3D Matrix3DUtils::_vector = Vector3D();
Vector3D Matrix3DUtils::_right = Vector3D();
Vector3D Matrix3DUtils::_up = Vector3D();
Vector3D Matrix3DUtils::_dir = Vector3D();
Vector3D Matrix3DUtils::_scale = Vector3D();
Vector3D Matrix3DUtils::_pos = Vector3D();

float Matrix3DUtils::absf(float f) {
    if (f < 0) {
        f = -f;
    }
    return f;
}

void Matrix3DUtils::getRight(const Matrix3D &m, Vector3D &out) {
    m.copyColumnTo(0, out);
}

void Matrix3DUtils::getUp(const Matrix3D &m, Vector3D &out) {
    m.copyColumnTo(1, out);
}

void Matrix3DUtils::getDir(const Matrix3D &m, Vector3D &out) {
    m.copyColumnTo(2, out);
}

void Matrix3DUtils::getLeft(const Matrix3D &m, Vector3D &out) {
    m.copyColumnTo(0, out);
    out.negate();
}

void Matrix3DUtils::getBackward(const Matrix3D &m, Vector3D &out) {
    m.copyColumnTo(2, out);
    out.negate();
}

void Matrix3DUtils::getDown(const Matrix3D &m, Vector3D &out) {
    m.copyColumnTo(1, out);
    out.negate();
}

void Matrix3DUtils::getPosition(const Matrix3D &m, Vector3D &out) {
    m.copyColumnTo(3, out);
}

void Matrix3DUtils::getScale(const Matrix3D &m, Vector3D &out) {
    m.copyColumnTo(0, _right);
    m.copyColumnTo(1, _up);
    m.copyColumnTo(2, _dir);
    out.x = _right.length();
    out.y = _up.length();
    out.z = _dir.length();
}

void Matrix3DUtils::setPosition(Matrix3D &m, const float x, const float y, const float z, const float smooth) {
    if (smooth == 1.0f) {
        _vector.setTo(x, y, z);
        _vector.w = 1.0f;
        m.copyColumnFrom(3, _vector);
    } else {
        m.copyColumnTo(3, _pos);
        _pos.x += (x - _pos.x) * smooth;
        _pos.y += (y - _pos.y) * smooth;
        _pos.z += (z - _pos.z) * smooth;
        m.copyColumnFrom(3, _pos);
    }
}

void Matrix3DUtils::setOrientation(Matrix3D &m, const Vector3D &dir, const Vector3D &up, const float smooth) {
    getScale(m, _scale);
    
    Vector3D upp;
    Vector3D dirr;
    
    upp.copyFrom(up);
    dirr.copyFrom(dir);
    
    if (smooth != 1) {
        getDir(m, _dir);
        _dir.x += (dir.x - _dir.x) * smooth;
        _dir.y += (dir.y - _dir.y) * smooth;
        _dir.z += (dir.z - _dir.z) * smooth;
        dirr = _dir;
        
        getUp(m, _up);
        _up.x += (up.x - _up.x) * smooth;
        _up.y += (up.y - _up.y) * smooth;
        _up.z += (up.z - _up.z) * smooth;
        upp = _up;
    } else {
        dirr = dir;
    }
    dirr.normalize();
    
    Vector3D rVec;
    Vector3D::crossProduct(upp, dirr, &rVec);
    rVec.normalize();
    
    Vector3D uVec;
    Vector3D::crossProduct(dirr, rVec, &uVec);
    
    rVec.scaleBy(_scale.x);
    uVec.scaleBy(_scale.y);
    dirr.scaleBy(_scale.z);
    
    rVec.w = 0.0f;
    uVec.w = 0.0f;
    dirr.w = 0.0f;
    
    setVectors(m,rVec, uVec, dirr);
}

void Matrix3DUtils::setVectors(Matrix3D &m, const Vector3D &right, const Vector3D &up, const Vector3D &dir) {
    m.copyColumnFrom(0, right);
    m.copyColumnFrom(1, up);
    m.copyColumnFrom(2, dir);
}

void Matrix3DUtils::lookAt(Matrix3D &m, const float x, const float y, const float z, const Vector3D &up, const float smooth) {
    m.copyColumnTo(3, _pos);
    _vector.x = x - _pos.x;
    _vector.y = y - _pos.y;
    _vector.z = z - _pos.z;
    setOrientation(m, _vector, up, smooth);
}

void Matrix3DUtils::setTranslation(Matrix3D &m, const float x, const float y, const float z) {
    m.setPosition(x, y, z);
}

void Matrix3DUtils::translateX(Matrix3D &m, const float distance) {
    m.copyColumnTo(3, _pos);
    m.copyColumnTo(0, _right);
    _pos.x += distance * _right.x;
    _pos.y += distance * _right.y;
    _pos.z += distance * _right.z;
    m.copyColumnFrom(3, _pos);
}

void Matrix3DUtils::translateY(Matrix3D &m, const float distance) {
    m.copyColumnTo(3, _pos);
    m.copyColumnTo(1, _up);
    _pos.x += distance * _up.x;
    _pos.y += distance * _up.y;
    _pos.z += distance * _up.z;
    m.copyColumnFrom(3, _pos);
}

void Matrix3DUtils::translateZ(Matrix3D &m, const float distance) {
    m.copyColumnTo(3, _pos);
    m.copyColumnTo(2, _dir);
    _pos.x += distance * _dir.x;
    _pos.y += distance * _dir.y;
    _pos.z += distance * _dir.z;
    m.copyColumnFrom(3, _pos);
}

void Matrix3DUtils::translateAxis(Matrix3D &m, const float distance, const Vector3D &axis) {
    m.copyColumnTo(3, _pos);
    _pos.x += distance * axis.x;
    _pos.y += distance * axis.y;
    _pos.z += distance * axis.z;
    m.copyColumnFrom(3, _pos);
}

void Matrix3DUtils::setScale(Matrix3D &m, float x, float y, float z, const float smooth) {
    if (x < MIN_SCALE) {
        x = MIN_SCALE;
    }
    if (y < MIN_SCALE) {
        y = MIN_SCALE;
    }
    if (z < MIN_SCALE) {
        z = MIN_SCALE;
    }
    getScale(m, _scale);
    _x = _scale.x;
    _y = _scale.y;
    _z = _scale.z;
    _scale.x += (x - _scale.x) * smooth;
    _scale.y += (y - _scale.y) * smooth;
    _scale.z += (z - _scale.z) * smooth;
    _right.scaleBy(_scale.x / _x);
    _up.scaleBy(_scale.y / _y);
    _dir.scaleBy(_scale.z / _z);
    setVectors(m, _right, _up, _dir);
}

void Matrix3DUtils::scaleX(Matrix3D &m, float scale) {
    if (scale < MIN_SCALE) {
        scale = MIN_SCALE;
    }
    m.copyColumnTo(0, _right);
    _right.normalize();
    _right.scaleBy(scale);
    m.copyColumnFrom(0, _right);
}

void Matrix3DUtils::scaleY(Matrix3D &m, float scale) {
    if (scale < MIN_SCALE) {
        scale = MIN_SCALE;
    }
    m.copyColumnTo(1, _up);
    _up.normalize();
    _up.scaleBy(scale);
    m.copyColumnFrom(1, _up);
}

void Matrix3DUtils::scaleZ(Matrix3D &m, float scale) {
    if (scale < MIN_SCALE) {
        scale = MIN_SCALE;
    }
    m.copyColumnTo(2, _dir);
    _dir.normalize();
    _dir.scaleBy(scale);
    m.copyColumnFrom(2, _dir);
}

void Matrix3DUtils::getRotation(const Matrix3D &m, Vector3D &out) {
    Vector3D *v = new Vector3D[3]();
    m.decompose(Matrix3D::Style::EulerAngles, v);
    _vector.copyFrom(v[1]);
    out.x = _vector.x * _toAng;
    out.y = _vector.y * _toAng;
    out.z = _vector.z * _toAng;
    // free v
    delete [] v;
}

void Matrix3DUtils::setRotation(Matrix3D &m, const float x, const float y, const float z) {
    Vector3D *v = new Vector3D[3]();
    m.decompose(Matrix3D::Style::EulerAngles, v);
    v[1].x = x * _toRad;
    v[1].y = y * _toRad;
    v[1].z = z * _toRad;
    m.recompose(v);
    delete [] v;
}

void Matrix3DUtils::rotateAxis(Matrix3D &m, const float angle, const Vector3D &axis, Vector3D *pivot) {
    _vector.x = axis.x;
    _vector.y = axis.y;
    _vector.z = axis.z;
    _vector.normalize();
    m.copyColumnTo(3, _pos);
    if (pivot) {
        m.appendRotation(angle, _vector, pivot);
    } else {
        m.appendRotation(angle, _vector, &_pos);
    }
}

void Matrix3DUtils::rotateX(Matrix3D &m, const float angle, bool local, Vector3D *pivot) {
    if (local) {
        getRight(m, _vector);
        rotateAxis(m, angle, _vector, pivot);
    } else {
        rotateAxis(m, angle, X_AXIS, pivot);
    }
}

void Matrix3DUtils::rotateY(Matrix3D &m, const float angle, bool local, Vector3D *pivot) {
    if (local) {
        getUp(m, _vector);
        rotateAxis(m, angle, _vector, pivot);
    } else {
        rotateAxis(m, angle, Y_AXIS, pivot);
    }
}

void Matrix3DUtils::rotateZ(Matrix3D &m, const float angle, bool local, Vector3D *pivot) {
    if (local) {
        getDir(m, _vector);
        rotateAxis(m, angle, _vector, pivot);
    } else {
        rotateAxis(m, angle, Z_AXIS, pivot);
    }
}

void Matrix3DUtils::transformVector(const Matrix3D &m, const Vector3D &in, Vector3D &out) {
    _vector.copyFrom(in);
    m.copyRawTo(0, _right);
    m.copyRawTo(1, _up);
    m.copyRawTo(2, _dir);
    m.copyColumnTo(3, out);
    out.x += _vector.x * _right.x + _vector.y * _right.y + _vector.z * _right.z;
    out.y += _vector.x * _up.x + _vector.y * _up.y + _vector.z * _up.z;
    out.z += _vector.z * _dir.x + _vector.y * _dir.y + _vector.z * _dir.z;
}

void Matrix3DUtils::deltaTransformVector(const Matrix3D &m, const Vector3D &in, Vector3D &out) {
    _vector.copyFrom(in);
    m.copyRawTo(0, _right);
    m.copyRawTo(1, _up);
    m.copyRawTo(2, _dir);
    out.x = _vector.x * _right.x + _vector.y * _right.y + _vector.z * _right.z;
    out.y = _vector.x * _up.x + _vector.y * _up.y + _vector.z * _up.z;
    out.z = _vector.x * _dir.x + _vector.y * _dir.y + _vector.z * _dir.z;
}

void Matrix3DUtils::invert(const Matrix3D &m, Matrix3D &out) {
    out.copyFrom(m);
    out.invert();
}

bool Matrix3DUtils::equal(const Matrix3D &a, const Matrix3D &b) {
    for (int i = 0; i < 16; i++) {
        if (a.rawData[i] != b.rawData[i]) {
            return false;
        }
    }
    return true;
}

void Matrix3DUtils::buildOrthoProjection(float left, float right, float top, float bottom, float near, float far, Matrix3D &out) {
    out.rawData[0] = 2 / (right - left);
    out.rawData[1] = 0.0f;
    out.rawData[2] = 0.0f;
    out.rawData[3] = 0.0f;
    
    out.rawData[4] = 0.0f;
    out.rawData[5] = 2 / (bottom - top);
    out.rawData[6] = 0.0f;
    out.rawData[7] = 0.0f;
    
    out.rawData[8] = 0.0f;
    out.rawData[9] = 0.0f;
    out.rawData[10] = 1 / (far - near);
    out.rawData[11] = 0.0f;
    
    out.rawData[12] = 0.0f;
    out.rawData[13] = 0.0f;
    out.rawData[14] = near / (near - far);
    out.rawData[15] = 1.0f;
}

NS_MONKEY_END
