//
//  Matrix3D.cpp
//  TestOpenglES
//
//  Created by Neil on 26/8/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#include "core/geom/Matrix3D.h"
#include "core/geom/mmath.h"

#include "platform/PlatformMacros.h"

NS_MONKEY_BEGIN

Matrix3D Matrix3D::_mt = Matrix3D();

void Matrix3D::identity() {
    rawData[0] = 1.0f;
    rawData[1] = 0.0f;
    rawData[2] = 0.0f;
    rawData[3] = 0.0f;
    
    rawData[4] = 0.0f;
    rawData[5] = 1.0f;
    rawData[6] = 0.0f;
    rawData[7] = 0.0f;
    
    rawData[8] = 0.0f;
    rawData[9] = 0.0f;
    rawData[10] = 1.0f;
    rawData[11] = 0.0f;
    
    rawData[12] = 0.0f;
    rawData[13] = 0.0f;
    rawData[14] = 0.0f;
    rawData[15] = 1.0f;
}

Matrix3D::Matrix3D() {
    identity();
}

Matrix3D::Matrix3D(const float *v) {
    for (int i = 0; i < 16; i++) {
        rawData[i] = v[i];
    }
}

void Matrix3D::append(const Matrix3D &lhs) {
    
    float m111 = rawData[0];
    float m121 = rawData[4];
    float m131 = rawData[8];
    float m141 = rawData[12];
    
    float m112 = rawData[1];
    float m122 = rawData[5];
    float m132 = rawData[9];
    float m142 = rawData[13];
    
    float m113 = rawData[2];
    float m123 = rawData[6];
    float m133 = rawData[10];
    float m143 = rawData[14];
    
    float m114 = rawData[3];
    float m124 = rawData[7];
    float m134 = rawData[11];
    float m144 = rawData[15];
    
    float m211 = lhs.rawData[0];
    float m221 = lhs.rawData[4];
    float m231 = lhs.rawData[8];
    float m241 = lhs.rawData[12];
    
    float m212 = lhs.rawData[1];
    float m222 = lhs.rawData[5];
    float m232 = lhs.rawData[9];
    float m242 = lhs.rawData[13];
    
    float m213 = lhs.rawData[2];
    float m223 = lhs.rawData[6];
    float m233 = lhs.rawData[10];
    float m243 = lhs.rawData[14];
    
    float m214 = lhs.rawData[3];
    float m224 = lhs.rawData[7];
    float m234 = lhs.rawData[11];
    float m244 = lhs.rawData[15];
    
    rawData[0] = m111*m211 + m112*m221 + m113*m231 + m114*m241;
    rawData[1] = m111*m212 + m112*m222 + m113*m232 + m114*m242;
    rawData[2] = m111*m213 + m112*m223 + m113*m233 + m114*m243;
    rawData[3] = m111*m214 + m112*m224 + m113*m234 + m114*m244;
    
    rawData[4] = m121*m211 + m122*m221 + m123*m231 + m124*m241;
    rawData[5] = m121*m212 + m122*m222 + m123*m232 + m124*m242;
    rawData[6] = m121*m213 + m122*m223 + m123*m233 + m124*m243;
    rawData[7] = m121*m214 + m122*m224 + m123*m234 + m124*m244;
    
    rawData[8] = m131*m211 + m132*m221 + m133*m231 + m134*m241;
    rawData[9] = m131*m212 + m132*m222 + m133*m232 + m134*m242;
    rawData[10] = m131*m213 + m132*m223 + m133*m233 + m134*m243;
    rawData[11] = m131*m214 + m132*m224 + m133*m234 + m134*m244;
    
    rawData[12] = m141*m211 + m142*m221 + m143*m231 + m144*m241;
    rawData[13] = m141*m212 + m142*m222 + m143*m232 + m144*m242;
    rawData[14] = m141*m213 + m142*m223 + m143*m233 + m144*m243;
    rawData[15] = m141*m214 + m142*m224 + m143*m234 + m144*m244;
}

void Matrix3D::copyColumnFrom(const int column, const Vector3D &vec) {
    rawData[column * 4 + 0] = vec.x;
    rawData[column * 4 + 1] = vec.y;
    rawData[column * 4 + 2] = vec.z;
    rawData[column * 4 + 3] = vec.w;
}

void Matrix3D::copyColumnTo(const int column, Vector3D &vec) const {
    vec.x = rawData[column * 4 + 0];
    vec.y = rawData[column * 4 + 1];
    vec.z = rawData[column * 4 + 2];
    vec.w = rawData[column * 4 + 3];
}

void Matrix3D::copyFrom(const Matrix3D &mt) {
    for (int i = 0; i < 16; i++) {
        rawData[i] = mt.rawData[i];
    }
}

void Matrix3D::copyRawDataFrom(const float *v) {
    for (int i = 0; i < 16; i++) {
        rawData[i] = v[i];
    }
}

void Matrix3D::copyRawDataTo(float *v) const {
    for (int i = 0; i < 16; i++) {
        v[i] = rawData[i];
    }
}

void Matrix3D::copyRawFrom(int raw, const Vector3D &vec) {
    rawData[raw + 0] = vec.x;
    rawData[raw + 4] = vec.y;
    rawData[raw + 8] = vec.z;
    rawData[raw + 12] = vec.w;
}

void Matrix3D::copyRawTo(int raw, Vector3D &vec) const {
    vec.x = rawData[raw + 0];
    vec.y = rawData[raw + 4];
    vec.z = rawData[raw + 8];
    vec.w = rawData[raw + 12];
}

void Matrix3D::copyToMatrix3D(Matrix3D &dest) const {
    for (int i = 0; i < 16; i++) {
        dest.rawData[i] = rawData[i];
    }
}

void Matrix3D::decompose(Style style, Vector3D *vec) const {
    
    float mr[16] = {0.0f};
    copyRawDataTo(mr);
    // postion
    vec[0].x = mr[12];
    vec[0].y = mr[13];
    vec[0].z = mr[14];
    
    mr[12] = mr[13] = mr[14] = 0.0f;
    // scale
    vec[2].x = sqrtf(mr[0] * mr[0] + mr[1] * mr[1] + mr[2] * mr[2]);
    vec[2].y = sqrtf(mr[4] * mr[4] + mr[5] * mr[5] + mr[6] * mr[6]);
    vec[2].z = sqrtf(mr[8] * mr[8] + mr[9] * mr[9] + mr[10] * mr[10]);
    
    if (mr[0]*(mr[5]*mr[10] - mr[6]*mr[9]) - mr[1]*(mr[4]*mr[10] - mr[6]*mr[8]) + mr[2]*(mr[4]*mr[9] - mr[5]*mr[8]) < 0)
        vec[2].z = -vec[2].z;
    
    mr[0] /= vec[2].x;
    mr[1] /= vec[2].x;
    mr[2] /= vec[2].x;
    mr[4] /= vec[2].y;
    mr[5] /= vec[2].y;
    mr[6] /= vec[2].y;
    mr[8] /= vec[2].z;
    mr[9] /= vec[2].z;
    mr[10] /= vec[2].z;
    
    if (style == Style::EulerAngles) {
        vec[1].y = asinf(-mr[2]);
        if (mr[2] != 1 && mr[2] != -1) {
            vec[1].x = atan2f(mr[6], mr[10]);
            vec[1].z = atan2f(mr[1], mr[0]);
        } else {
            vec[1].z = 0;
            vec[1].x = atan2f(mr[4], mr[5]);
        }
    } else if (style == Style::AxisAngle) {
        vec[1].w = acosf((mr[0] + mr[5] + mr[10] - 1) / 2);
        float len = sqrtf((mr[6] - mr[9])*(mr[6] - mr[9]) + (mr[8] - mr[2])*(mr[8] - mr[2]) + (mr[1] - mr[4])*(mr[1] - mr[4]));
        vec[1].x = (mr[6] - mr[9]) / len;
        vec[1].y = (mr[8] - mr[2]) / len;
        vec[1].z = (mr[1] - mr[4]) / len;
    } else if (style == Style::Quaternion) {
        float tr = mr[0] + mr[5] + mr[10];
        if (tr > 0) {
            vec[1].w = sqrtf(1 + tr) / 2;
            vec[1].x = (mr[6] - mr[9]) / (4 * vec[1].w);
            vec[1].y = (mr[8] - mr[2]) / (4 * vec[1].w);
            vec[1].z = (mr[1] - mr[4]) / (4 * vec[1].w);
        } else if ((mr[0] > mr[5]) && (mr[0] > mr[10])) {
            vec[1].x = sqrtf(1 + mr[0] - mr[5] - mr[10])/2;
            vec[1].w = (mr[6] - mr[9]) / (4 * vec[1].x);
            vec[1].y = (mr[1] + mr[4]) / (4 * vec[1].x);
            vec[1].z = (mr[8] + mr[2]) / (4 * vec[1].x);
        } else {
            vec[1].z = sqrtf(1 + mr[10] - mr[0] - mr[5])/2;
            vec[1].x = (mr[8] + mr[2]) / (4 * vec[1].z);
            vec[1].y = (mr[6] + mr[9]) / (4 * vec[1].z);
            vec[1].w = (mr[1] - mr[4]) / (4 * vec[1].z);
        }
    }
    
}

void Matrix3D::interpolateTo(Matrix3D &dest, float percent) {
    for (int i = 0; i < 16; i++) {
        dest.rawData[i] = rawData[i] + (dest.rawData[i] - rawData[i]) * percent;
    }
}

float Matrix3D::determinant() {
    return ((rawData[0] * rawData[5] - rawData[4] * rawData[1]) * (rawData[10]*rawData[15] - rawData[14]*rawData[11]) - (rawData[0]*rawData[9] - rawData[8]*rawData[1])*(rawData[6]*rawData[15] - rawData[14]*rawData[7]) + (rawData[0]*rawData[13] - rawData[12]*rawData[1])*(rawData[6]*rawData[11] - rawData[10]*rawData[7]) + (rawData[4]*rawData[9] - rawData[8]*rawData[5])*(rawData[2]*rawData[15] - rawData[14]*rawData[3]) - (rawData[4]*rawData[13] - rawData[12]*rawData[5])*(rawData[2]*rawData[11] - rawData[10]*rawData[3]) + (rawData[8]*rawData[13] - rawData[12]*rawData[9])*(rawData[2]*rawData[7] - rawData[6]*rawData[3]));
}

void Matrix3D::invert() {
    float d = determinant();
    if (d < 0.0f) {
        d = -d;
    }
    bool invertable = d > 0.00000000001f;
    if (invertable) {
        d = 1/d;
        float m11 = rawData[0];
        float m21 = rawData[4];
        float m31 = rawData[8];
        float m41 = rawData[12];
        float m12 = rawData[1];
        float m22 = rawData[5];
        float m32 = rawData[9];
        float m42 = rawData[13];
        float m13 = rawData[2];
        float m23 = rawData[6];
        float m33 = rawData[10];
        float m43 = rawData[14];
        float m14 = rawData[3];
        float m24 = rawData[7];
        float m34 = rawData[11];
        float m44 = rawData[15];
        
        rawData[0] = d*(m22*(m33*m44 - m43*m34) - m32*(m23*m44 - m43*m24) + m42*(m23*m34 - m33*m24));
        rawData[1] = -d*(m12*(m33*m44 - m43*m34) - m32*(m13*m44 - m43*m14) + m42*(m13*m34 - m33*m14));
        rawData[2] = d*(m12*(m23*m44 - m43*m24) - m22*(m13*m44 - m43*m14) + m42*(m13*m24 - m23*m14));
        rawData[3] = -d*(m12*(m23*m34 - m33*m24) - m22*(m13*m34 - m33*m14) + m32*(m13*m24 - m23*m14));
        rawData[4] = -d*(m21*(m33*m44 - m43*m34) - m31*(m23*m44 - m43*m24) + m41*(m23*m34 - m33*m24));
        rawData[5] = d*(m11*(m33*m44 - m43*m34) - m31*(m13*m44 - m43*m14) + m41*(m13*m34 - m33*m14));
        rawData[6] = -d*(m11*(m23*m44 - m43*m24) - m21*(m13*m44 - m43*m14) + m41*(m13*m24 - m23*m14));
        rawData[7] = d*(m11*(m23*m34 - m33*m24) - m21*(m13*m34 - m33*m14) + m31*(m13*m24 - m23*m14));
        rawData[8] = d*(m21*(m32*m44 - m42*m34) - m31*(m22*m44 - m42*m24) + m41*(m22*m34 - m32*m24));
        rawData[9] = -d*(m11*(m32*m44 - m42*m34) - m31*(m12*m44 - m42*m14) + m41*(m12*m34 - m32*m14));
        rawData[10] = d*(m11*(m22*m44 - m42*m24) - m21*(m12*m44 - m42*m14) + m41*(m12*m24 - m22*m14));
        rawData[11] = -d*(m11*(m22*m34 - m32*m24) - m21*(m12*m34 - m32*m14) + m31*(m12*m24 - m22*m14));
        rawData[12] = -d*(m21*(m32*m43 - m42*m33) - m31*(m22*m43 - m42*m23) + m41*(m22*m33 - m32*m23));
        rawData[13] = d*(m11*(m32*m43 - m42*m33) - m31*(m12*m43 - m42*m13) + m41*(m12*m33 - m32*m13));
        rawData[14] = -d*(m11*(m22*m43 - m42*m23) - m21*(m12*m43 - m42*m13) + m41*(m12*m23 - m22*m13));
        rawData[15] = d*(m11*(m22*m33 - m32*m23) - m21*(m12*m33 - m32*m13) + m31*(m12*m23 - m22*m13));
    }
}

void Matrix3D::prepend(const Matrix3D &rhs) {
    
    float m111 = rhs.rawData[0];
    float m121 = rhs.rawData[4];
    float m131 = rhs.rawData[8];
    float m141 = rhs.rawData[12];
    float m112 = rhs.rawData[1];
    float m122 = rhs.rawData[5];
    float m132 = rhs.rawData[9];
    float m142 = rhs.rawData[13];
    float m113 = rhs.rawData[2];
    float m123 = rhs.rawData[6];
    float m133 = rhs.rawData[10];
    float m143 = rhs.rawData[14];
    float m114 = rhs.rawData[3];
    float m124 = rhs.rawData[7];
    float m134 = rhs.rawData[11];
    float m144 = rhs.rawData[15];
    float m211 = rawData[0];
    float m221 = rawData[4];
    float m231 = rawData[8];
    float m241 = rawData[12];
    float m212 = rawData[1];
    float m222 = rawData[5];
    float m232 = rawData[9];
    float m242 = rawData[13];
    float m213 = rawData[2];
    float m223 = rawData[6];
    float m233 = rawData[10];
    float m243 = rawData[14];
    float m214 = rawData[3];
    float m224 = rawData[7];
    float m234 = rawData[11];
    float m244 = rawData[15];
    
    rawData[0] = m111*m211 + m112*m221 + m113*m231 + m114*m241;
    rawData[1] = m111*m212 + m112*m222 + m113*m232 + m114*m242;
    rawData[2] = m111*m213 + m112*m223 + m113*m233 + m114*m243;
    rawData[3] = m111*m214 + m112*m224 + m113*m234 + m114*m244;
    
    rawData[4] = m121*m211 + m122*m221 + m123*m231 + m124*m241;
    rawData[5] = m121*m212 + m122*m222 + m123*m232 + m124*m242;
    rawData[6] = m121*m213 + m122*m223 + m123*m233 + m124*m243;
    rawData[7] = m121*m214 + m122*m224 + m123*m234 + m124*m244;
    
    rawData[8] = m131*m211 + m132*m221 + m133*m231 + m134*m241;
    rawData[9] = m131*m212 + m132*m222 + m133*m232 + m134*m242;
    rawData[10] = m131*m213 + m132*m223 + m133*m233 + m134*m243;
    rawData[11] = m131*m214 + m132*m224 + m133*m234 + m134*m244;
    
    rawData[12] = m141*m211 + m142*m221 + m143*m231 + m144*m241;
    rawData[13] = m141*m212 + m142*m222 + m143*m232 + m144*m242;
    rawData[14] = m141*m213 + m142*m223 + m143*m233 + m144*m243;
    rawData[15] = m141*m214 + m142*m224 + m143*m234 + m144*m244;
}

void Matrix3D::getAxisRotation(float u, float v, float w, const float a, const float b, const float c, const float degress, Matrix3D &m) {
    
    float rad = degress / 180.0f * PI;
    
    float u2 = u * u;
    float v2 = v * v;
    float w2 = w * w;
    float l2 = u2 + v2 + w2;
    float l  = sqrtf(l2);
    
    u /= l;
    v /= l;
    w /= l;
    u2 /= l2;
    v2 /= l2;
    w2 /= l2;
    
    float cos = cosf(rad);
    float sin = sinf(rad);
    
    m.rawData[0] = u2 + (v2 + w2) * cos;
    m.rawData[1] = u * v * (1 - cos) + w * sin;
    m.rawData[2] = u * w * (1 - cos) - v * sin;
    m.rawData[3] = 0;
    
    m.rawData[4] = u * v * (1 - cos) - w * sin;
    m.rawData[5] = v2 + (u2 + w2) * cos;
    m.rawData[6] = v * w * (1 - cos) + u * sin;
    m.rawData[7] = 0;
    
    m.rawData[8] = u * w * (1 - cos) + v * sin;
    m.rawData[9] = v * w * (1 - cos) - u * sin;
    m.rawData[10] = w2 + (u2 + v2) * cos;
    m.rawData[11] = 0;
    
    m.rawData[12] = (a * (v2 + w2) - u * (b * v + c * w)) * (1 - cos) + (b * w - c * v) * sin;
    m.rawData[13] = (b * (u2 + w2) - v * (a * u + c * w)) * (1 - cos) + (c * u - a * w) * sin;
    m.rawData[14] = (c * (u2 + v2) - w * (a * u + b * v)) * (1 - cos) + (a * v - b * u) * sin;
    m.rawData[15] = 1;
    
}

void Matrix3D::prependRotation(const float degrees, const Vector3D &axis, Vector3D *pivot) {
    if (pivot) {
        getAxisRotation(axis.x, axis.y, axis.y, pivot->x, pivot->y, pivot->z, degrees, _mt);
    } else {
        getAxisRotation(axis.x, axis.y, axis.y, 0, 0, 0, degrees, _mt);
    }
    prepend(_mt);
}

void Matrix3D::prependScale(const float x, const float y, const float z) {
    float v[] = {x, 0, 0, 0, 0, y, 0, 0, 0, 0, z, 0, 0, 0, 0, 1};
    _mt.copyRawDataFrom(v);
    prepend(_mt);
}

void Matrix3D::setPosition(const float x, const float y, const float z) {
    rawData[12] = x;
    rawData[13] = y;
    rawData[14] = z;
}

void Matrix3D::appendScale(const float x, const float y, const float z) {
    float v[] = {x, 0.0, 0.0, 0.0, 0.0, y, 0.0, 0.0, 0.0, 0.0, z, 0.0, 0.0, 0.0, 0.0, 1.0};
    _mt.copyRawDataFrom(v);
    append(_mt);
}

void Matrix3D::appendRotation(const float degrees, const Vector3D &axis, Vector3D *pivot) {
    if (pivot) {
        getAxisRotation(axis.x, axis.y, axis.z, pivot->x, pivot->y, pivot->z, degrees, _mt);
    } else {
        getAxisRotation(axis.x, axis.y, axis.z, 0, 0, 0, degrees, _mt);
    }
    append(_mt);
}

void Matrix3D::appendTranslation(const float x, const float y, const float z) {
    rawData[12] += x;
    rawData[13] += y;
    rawData[14] += z;
}

void Matrix3D::setPosition(const Vector3D &position) {
    rawData[12] = position.x;
    rawData[13] = position.y;
    rawData[14] = position.z;
}

void Matrix3D::prependTranslation(const float x, const float y, const float z) {
    _mt.identity();
    _mt.setPosition(x, y, z);
    prepend(_mt);
}

void Matrix3D::recompose(const Vector3D *components) {
    identity();
    appendScale(components[2].x, components[2].y, components[2].z);
    
    float angle = -components[1].x;
    float v[] = {1, 0, 0, 0, 0, cosf(angle), -sinf(angle), 0, 0, sinf(angle), cosf(angle), 0, 0, 0, 0 , 0};
    _mt.copyRawDataFrom(v);
    append(_mt);
    
    angle = -components[1].y;
    float v0[] = {cosf(angle), 0, sinf(angle), 0, 0, 1, 0, 0, -sinf(angle), 0, cosf(angle), 0, 0, 0, 0, 0};
    _mt.copyRawDataFrom(v0);
    append(_mt);
    
    angle = -components[1].z;
    float v1[] = {cosf(angle), -sinf(angle), 0, 0, sinf(angle), cosf(angle), 0, 0, 0, 0, 1, 0, 0, 0, 0, 0};
    _mt.copyRawDataFrom(v1);
    append(_mt);
    
    setPosition(components[0]);
    rawData[15] = 1.0f;
}

void Matrix3D::transformVector(const Vector3D &in, Vector3D &out) {
    float x = in.x;
    float y = in.y;
    float z = in.z;
    out.x = (x*rawData[0] + y*rawData[4] + z*rawData[8] + rawData[12]);
    out.y = (x*rawData[1] + y*rawData[5] + z*rawData[9] + rawData[13]);
    out.z = (x*rawData[2] + y*rawData[6] + z*rawData[10] + rawData[14]);
    out.w = (x*rawData[3] + y*rawData[7] + z*rawData[11] + rawData[15]);
}

void Matrix3D::transformVectors(const float *vin, float *vout) {
    int i = 0;
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    
    while (i + 3 <= 24) {
        x = vin[i];
        y = vin[i + 1];
        z = vin[i + 2];
        vout[i + 0] = x * rawData[0] + y * rawData[4] + z * rawData[8] + rawData[12];
        vout[i + 1] = x * rawData[1] + y * rawData[5] + z * rawData[9] + rawData[13];
        vout[i + 2] = x * rawData[2] + y * rawData[6] + z * rawData[10] + rawData[14];
        i += 3;
    }
}

void Matrix3D::transpose() {
    
    float v[16] = {0.0f};
    
    for (int i = 0; i < 16; i++) {
        v[i] = rawData[i];
    }
    
    rawData[1] = v[4];
    rawData[2] = v[8];
    rawData[3] = v[12];
    rawData[4] = v[1];
    rawData[6] = v[9];
    rawData[7] = v[13];
    rawData[8] = v[2];
    rawData[9] = v[6];
    rawData[11] = v[14];
    rawData[12] = v[3];
    rawData[13] = v[7];
    rawData[14] = v[11];
}

NS_MONKEY_END
