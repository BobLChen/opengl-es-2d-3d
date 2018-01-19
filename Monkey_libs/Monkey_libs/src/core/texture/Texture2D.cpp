//
//  Texture2D.cpp
//  Opengl2D
//
//  Created by Neil on 3/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#include "core/texture/Texture2D.h"
#include "core/utils/BitmapData.h"
#include "core/utils/Log.h"
#include "core/geom/mmath.h"
#include "platform/TextureUtils.h"
#include "App.h"

#include "platform/PlatformMacros.h"

NS_MONKEY_BEGIN

namespace {
    
    typedef Texture2D::PixelFormatInfoMap::value_type PixelFormatInfoMapValue;
    
    static const PixelFormatInfoMapValue TexturePixelFormatInfoTablesValue[] =
    {
        PixelFormatInfoMapValue(Texture2D::PixelFormat::BGRA8888, Texture2D::PixelFormatInfo(GL_BGRA, GL_BGRA, GL_UNSIGNED_BYTE, 32, false, true)),
        PixelFormatInfoMapValue(Texture2D::PixelFormat::RGBA8888, Texture2D::PixelFormatInfo(GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, 32, false, true)),
        PixelFormatInfoMapValue(Texture2D::PixelFormat::RGBA4444, Texture2D::PixelFormatInfo(GL_RGBA, GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4, 16, false, true)),
        PixelFormatInfoMapValue(Texture2D::PixelFormat::RGB5A1, Texture2D::PixelFormatInfo(GL_RGBA, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, 16, false, true)),
        PixelFormatInfoMapValue(Texture2D::PixelFormat::RGB565, Texture2D::PixelFormatInfo(GL_RGB, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, 16, false, false)),
        PixelFormatInfoMapValue(Texture2D::PixelFormat::RGB888, Texture2D::PixelFormatInfo(GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, 24, false, false)),
        PixelFormatInfoMapValue(Texture2D::PixelFormat::A8, Texture2D::PixelFormatInfo(GL_ALPHA, GL_ALPHA, GL_UNSIGNED_BYTE, 8, false, false)),
        PixelFormatInfoMapValue(Texture2D::PixelFormat::I8, Texture2D::PixelFormatInfo(GL_LUMINANCE, GL_LUMINANCE, GL_UNSIGNED_BYTE, 8, false, false)),
        PixelFormatInfoMapValue(Texture2D::PixelFormat::AI88, Texture2D::PixelFormatInfo(GL_LUMINANCE_ALPHA, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, 16, false, true)),
        
#ifdef GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG
        PixelFormatInfoMapValue(Texture2D::PixelFormat::PVRTC2, Texture2D::PixelFormatInfo(GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG, 0xFFFFFFFF, 0xFFFFFFFF, 2, true, false)),
        PixelFormatInfoMapValue(Texture2D::PixelFormat::PVRTC2A, Texture2D::PixelFormatInfo(GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG, 0xFFFFFFFF, 0xFFFFFFFF, 2, true, true)),
        PixelFormatInfoMapValue(Texture2D::PixelFormat::PVRTC4, Texture2D::PixelFormatInfo(GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG, 0xFFFFFFFF, 0xFFFFFFFF, 4, true, false)),
        PixelFormatInfoMapValue(Texture2D::PixelFormat::PVRTC4A, Texture2D::PixelFormatInfo(GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG, 0xFFFFFFFF, 0xFFFFFFFF, 4, true, true)),
#endif
        
#ifdef GL_ETC1_RGB8_OES
        PixelFormatInfoMapValue(Texture2D::PixelFormat::ETC, Texture2D::PixelFormatInfo(GL_ETC1_RGB8_OES, 0xFFFFFFFF, 0xFFFFFFFF, 24, true, false)),
#endif
        
#ifdef GL_COMPRESSED_RGBA_S3TC_DXT1_EXT
        PixelFormatInfoMapValue(Texture2D::PixelFormat::S3TC_DXT1, Texture2D::PixelFormatInfo(GL_COMPRESSED_RGBA_S3TC_DXT1_EXT, 0xFFFFFFFF, 0xFFFFFFFF, 4, true, false)),
#endif
        
#ifdef GL_COMPRESSED_RGBA_S3TC_DXT3_EXT
        PixelFormatInfoMapValue(Texture2D::PixelFormat::S3TC_DXT3, Texture2D::PixelFormatInfo(GL_COMPRESSED_RGBA_S3TC_DXT3_EXT, 0xFFFFFFFF, 0xFFFFFFFF, 8, true, false)),
#endif
        
#ifdef GL_COMPRESSED_RGBA_S3TC_DXT5_EXT
        PixelFormatInfoMapValue(Texture2D::PixelFormat::S3TC_DXT5, Texture2D::PixelFormatInfo(GL_COMPRESSED_RGBA_S3TC_DXT5_EXT, 0xFFFFFFFF, 0xFFFFFFFF, 8, true, false)),
#endif
        
#ifdef GL_ATC_RGB_AMD
        PixelFormatInfoMapValue(Texture2D::PixelFormat::ATC_RGB, Texture2D::PixelFormatInfo(GL_ATC_RGB_AMD,
                                                                                            0xFFFFFFFF, 0xFFFFFFFF, 4, true, false)),
#endif
        
#ifdef GL_ATC_RGBA_EXPLICIT_ALPHA_AMD
        PixelFormatInfoMapValue(Texture2D::PixelFormat::ATC_EXPLICIT_ALPHA, Texture2D::PixelFormatInfo(GL_ATC_RGBA_EXPLICIT_ALPHA_AMD,
                                                                                                       0xFFFFFFFF, 0xFFFFFFFF, 8, true, false)),
#endif
        
#ifdef GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD
        PixelFormatInfoMapValue(Texture2D::PixelFormat::ATC_INTERPOLATED_ALPHA, Texture2D::PixelFormatInfo(GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD,
                                                                                                           0xFFFFFFFF, 0xFFFFFFFF, 8, true, false)),
#endif
    };
}

//CLASS IMPLEMENTATIONS:

//The PixpelFormat corresponding information
const Texture2D::PixelFormatInfoMap Texture2D::_pixelFormatInfoTables(TexturePixelFormatInfoTablesValue,
                                                                      TexturePixelFormatInfoTablesValue + sizeof(TexturePixelFormatInfoTablesValue) / sizeof(TexturePixelFormatInfoTablesValue[0]));

static Texture2D::PixelFormat _defaultPixelFormat = Texture2D::PixelFormat::DEFAULT;

Texture2D::PixelFormat Texture2D::convertDataToFormat(const unsigned char* data, ssize_t dataLen, PixelFormat originFormat, PixelFormat format, unsigned char** outData, ssize_t* outDataLen)
{
    // don't need to convert
    if (format == originFormat || format == PixelFormat::AUTO)
    {
        *outData = (unsigned char*)data;
        *outDataLen = dataLen;
        return originFormat;
    }
    
    switch (originFormat)
    {
        case PixelFormat::I8:
            return convertI8ToFormat(data, dataLen, format, outData, outDataLen);
        case PixelFormat::AI88:
            return convertAI88ToFormat(data, dataLen, format, outData, outDataLen);
        case PixelFormat::RGB888:
            return convertRGB888ToFormat(data, dataLen, format, outData, outDataLen);
        case PixelFormat::RGBA8888:
            return convertRGBA8888ToFormat(data, dataLen, format, outData, outDataLen);
        default:
            LOGE("unsupport convert for format %d to format %d", originFormat, format);
            *outData = (unsigned char*)data;
            *outDataLen = dataLen;
            return originFormat;
    }
}

Texture2D::PixelFormat Texture2D::convertRGBA8888ToFormat(const unsigned char* data, ssize_t dataLen, PixelFormat format, unsigned char** outData, ssize_t* outDataLen)
{
    
    switch (format)
    {
        case PixelFormat::RGB888:
            *outDataLen = dataLen/4*3;
            *outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
            convertRGBA8888ToRGB888(data, dataLen, *outData);
            break;
        case PixelFormat::RGB565:
            *outDataLen = dataLen/2;
            *outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
            convertRGBA8888ToRGB565(data, dataLen, *outData);
            break;
        case PixelFormat::A8:
            *outDataLen = dataLen/4;
            *outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
            convertRGBA8888ToA8(data, dataLen, *outData);
            break;
        case PixelFormat::I8:
            *outDataLen = dataLen/4;
            *outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
            convertRGBA8888ToI8(data, dataLen, *outData);
            break;
        case PixelFormat::AI88:
            *outDataLen = dataLen/2;
            *outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
            convertRGBA8888ToAI88(data, dataLen, *outData);
            break;
        case PixelFormat::RGBA4444:
            *outDataLen = dataLen/2;
            *outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
            convertRGBA8888ToRGBA4444(data, dataLen, *outData);
            break;
        case PixelFormat::RGB5A1:
            *outDataLen = dataLen/2;
            *outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
            convertRGBA8888ToRGB5A1(data, dataLen, *outData);
            break;
        default:
            // unsupport convertion or don't need to convert
            if (format != PixelFormat::AUTO && format != PixelFormat::RGBA8888)
            {
                LOGE("Can not convert image format PixelFormat::RGBA8888 to format ID:%d, we will use it's origin format PixelFormat::RGBA8888", format);
            }
            
            *outData = (unsigned char*)data;
            *outDataLen = dataLen;
            return PixelFormat::RGBA8888;
    }
    
    return format;
}


Texture2D::PixelFormat Texture2D::convertRGB888ToFormat(const unsigned char* data, ssize_t dataLen, PixelFormat format, unsigned char** outData, ssize_t* outDataLen)
{
    switch (format)
    {
        case PixelFormat::RGBA8888:
            *outDataLen = dataLen/3*4;
            *outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
            convertRGB888ToRGBA8888(data, dataLen, *outData);
            break;
        case PixelFormat::RGB565:
            *outDataLen = dataLen/3*2;
            *outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
            convertRGB888ToRGB565(data, dataLen, *outData);
            break;
        case PixelFormat::I8:
            *outDataLen = dataLen/3;
            *outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
            convertRGB888ToI8(data, dataLen, *outData);
            break;
        case PixelFormat::AI88:
            *outDataLen = dataLen/3*2;
            *outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
            convertRGB888ToAI88(data, dataLen, *outData);
            break;
        case PixelFormat::RGBA4444:
            *outDataLen = dataLen/3*2;
            *outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
            convertRGB888ToRGBA4444(data, dataLen, *outData);
            break;
        case PixelFormat::RGB5A1:
            *outDataLen = dataLen;
            *outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
            convertRGB888ToRGB5A1(data, dataLen, *outData);
            break;
        default:
            // unsupport convertion or don't need to convert
            if (format != PixelFormat::AUTO && format != PixelFormat::RGB888)
            {
                LOGE("Can not convert image format PixelFormat::RGB888 to format ID:%d, we will use it's origin format PixelFormat::RGB888", format);
            }
            
            *outData = (unsigned char*)data;
            *outDataLen = dataLen;
            return PixelFormat::RGB888;
    }
    return format;
}


Texture2D::PixelFormat Texture2D::convertAI88ToFormat(const unsigned char* data, ssize_t dataLen, PixelFormat format, unsigned char** outData, ssize_t* outDataLen)
{
    switch (format)
    {
        case PixelFormat::RGBA8888:
            *outDataLen = dataLen*2;
            *outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
            convertAI88ToRGBA8888(data, dataLen, *outData);
            break;
        case PixelFormat::RGB888:
            *outDataLen = dataLen/2*3;
            *outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
            convertAI88ToRGB888(data, dataLen, *outData);
            break;
        case PixelFormat::RGB565:
            *outDataLen = dataLen;
            *outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
            convertAI88ToRGB565(data, dataLen, *outData);
            break;
        case PixelFormat::A8:
            *outDataLen = dataLen/2;
            *outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
            convertAI88ToA8(data, dataLen, *outData);
            break;
        case PixelFormat::I8:
            *outDataLen = dataLen/2;
            *outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
            convertAI88ToI8(data, dataLen, *outData);
            break;
        case PixelFormat::RGBA4444:
            *outDataLen = dataLen;
            *outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
            convertAI88ToRGBA4444(data, dataLen, *outData);
            break;
        case PixelFormat::RGB5A1:
            *outDataLen = dataLen;
            *outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
            convertAI88ToRGB5A1(data, dataLen, *outData);
            break;
        default:
            // unsupport convertion or don't need to convert
            if (format != PixelFormat::AUTO && format != PixelFormat::AI88)
            {
                LOGE("Can not convert image format PixelFormat::AI88 to format ID:%d, we will use it's origin format PixelFormat::AI88", format);
            }
            
            *outData = (unsigned char*)data;
            *outDataLen = dataLen;
            return PixelFormat::AI88;
            break;
    }
    
    return format;
}

Texture2D::PixelFormat Texture2D::convertI8ToFormat(const unsigned char* data, ssize_t dataLen, PixelFormat format, unsigned char** outData, ssize_t* outDataLen)
{
    switch (format)
    {
        case PixelFormat::RGBA8888:
            *outDataLen = dataLen*4;
            *outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
            convertI8ToRGBA8888(data, dataLen, *outData);
            break;
        case PixelFormat::RGB888:
            *outDataLen = dataLen*3;
            *outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
            convertI8ToRGB888(data, dataLen, *outData);
            break;
        case PixelFormat::RGB565:
            *outDataLen = dataLen*2;
            *outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
            convertI8ToRGB565(data, dataLen, *outData);
            break;
        case PixelFormat::AI88:
            *outDataLen = dataLen*2;
            *outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
            convertI8ToAI88(data, dataLen, *outData);
            break;
        case PixelFormat::RGBA4444:
            *outDataLen = dataLen*2;
            *outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
            convertI8ToRGBA4444(data, dataLen, *outData);
            break;
        case PixelFormat::RGB5A1:
            *outDataLen = dataLen*2;
            *outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
            convertI8ToRGB5A1(data, dataLen, *outData);
            break;
        default:
            // unsupport convertion or don't need to convert
            if (format != PixelFormat::AUTO && format != PixelFormat::I8)
            {
                LOGE("Can not convert image format PixelFormat::I8 to format ID:%d, we will use it's origin format PixelFormat::I8", format);
            }
            
            *outData = (unsigned char*)data;
            *outDataLen = dataLen;
            return PixelFormat::I8;
    }
    
    return format;
}


// IIIIIIII -> RRRRRRRRGGGGGGGGGBBBBBBBB
void Texture2D::convertI8ToRGB888(const unsigned char* data, ssize_t dataLen, unsigned char* outData)
{
    for (ssize_t i=0; i < dataLen; ++i)
    {
        *outData++ = data[i];     //R
        *outData++ = data[i];     //G
        *outData++ = data[i];     //B
    }
}

// IIIIIIIIAAAAAAAA -> RRRRRRRRGGGGGGGGBBBBBBBB
void Texture2D::convertAI88ToRGB888(const unsigned char* data, ssize_t dataLen, unsigned char* outData)
{
    for (ssize_t i = 0, l = dataLen - 1; i < l; i += 2)
    {
        *outData++ = data[i];     //R
        *outData++ = data[i];     //G
        *outData++ = data[i];     //B
    }
}

// IIIIIIII -> RRRRRRRRGGGGGGGGGBBBBBBBBAAAAAAAA
void Texture2D::convertI8ToRGBA8888(const unsigned char* data, ssize_t dataLen, unsigned char* outData)
{
    for (ssize_t i = 0; i < dataLen; ++i)
    {
        *outData++ = data[i];     //R
        *outData++ = data[i];     //G
        *outData++ = data[i];     //B
        *outData++ = 0xFF;        //A
    }
}

// IIIIIIIIAAAAAAAA -> RRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA
void Texture2D::convertAI88ToRGBA8888(const unsigned char* data, ssize_t dataLen, unsigned char* outData)
{
    for (ssize_t i = 0, l = dataLen - 1; i < l; i += 2)
    {
        *outData++ = data[i];     //R
        *outData++ = data[i];     //G
        *outData++ = data[i];     //B
        *outData++ = data[i + 1]; //A
    }
}

// IIIIIIII -> RRRRRGGGGGGBBBBB
void Texture2D::convertI8ToRGB565(const unsigned char* data, ssize_t dataLen, unsigned char* outData)
{
    unsigned short* out16 = (unsigned short*)outData;
    for (int i = 0; i < dataLen; ++i)
    {
        *out16++ = (data[i] & 0x00F8) << 8    //R
        | (data[i] & 0x00FC) << 3         //G
        | (data[i] & 0x00F8) >> 3;        //B
    }
}

// IIIIIIIIAAAAAAAA -> RRRRRGGGGGGBBBBB
void Texture2D::convertAI88ToRGB565(const unsigned char* data, ssize_t dataLen, unsigned char* outData)
{
    unsigned short* out16 = (unsigned short*)outData;
    for (ssize_t i = 0, l = dataLen - 1; i < l; i += 2)
    {
        *out16++ = (data[i] & 0x00F8) << 8    //R
        | (data[i] & 0x00FC) << 3         //G
        | (data[i] & 0x00F8) >> 3;        //B
    }
}

// IIIIIIII -> RRRRGGGGBBBBAAAA
void Texture2D::convertI8ToRGBA4444(const unsigned char* data, ssize_t dataLen, unsigned char* outData)
{
    unsigned short* out16 = (unsigned short*)outData;
    for (ssize_t i = 0; i < dataLen; ++i)
    {
        *out16++ = (data[i] & 0x00F0) << 8    //R
        | (data[i] & 0x00F0) << 4             //G
        | (data[i] & 0x00F0)                  //B
        | 0x000F;                             //A
    }
}

// IIIIIIIIAAAAAAAA -> RRRRGGGGBBBBAAAA
void Texture2D::convertAI88ToRGBA4444(const unsigned char* data, ssize_t dataLen, unsigned char* outData)
{
    unsigned short* out16 = (unsigned short*)outData;
    for (ssize_t i = 0, l = dataLen - 1; i < l; i += 2)
    {
        *out16++ = (data[i] & 0x00F0) << 8    //R
        | (data[i] & 0x00F0) << 4             //G
        | (data[i] & 0x00F0)                  //B
        | (data[i+1] & 0x00F0) >> 4;          //A
    }
}

// IIIIIIII -> RRRRRGGGGGBBBBBA
void Texture2D::convertI8ToRGB5A1(const unsigned char* data, ssize_t dataLen, unsigned char* outData)
{
    unsigned short* out16 = (unsigned short*)outData;
    for (int i = 0; i < dataLen; ++i)
    {
        *out16++ = (data[i] & 0x00F8) << 8    //R
        | (data[i] & 0x00F8) << 3         //G
        | (data[i] & 0x00F8) >> 2         //B
        | 0x0001;                         //A
    }
}

// IIIIIIIIAAAAAAAA -> RRRRRGGGGGBBBBBA
void Texture2D::convertAI88ToRGB5A1(const unsigned char* data, ssize_t dataLen, unsigned char* outData)
{
    unsigned short* out16 = (unsigned short*)outData;
    for (ssize_t i = 0, l = dataLen - 1; i < l; i += 2)
    {
        *out16++ = (data[i] & 0x00F8) << 8    //R
        | (data[i] & 0x00F8) << 3         //G
        | (data[i] & 0x00F8) >> 2         //B
        | (data[i + 1] & 0x0080) >> 7;    //A
    }
}

// IIIIIIII -> IIIIIIIIAAAAAAAA
void Texture2D::convertI8ToAI88(const unsigned char* data, ssize_t dataLen, unsigned char* outData)
{
    unsigned short* out16 = (unsigned short*)outData;
    for (ssize_t i = 0; i < dataLen; ++i)
    {
        *out16++ = 0xFF00     //A
        | data[i];            //I
    }
}

// IIIIIIIIAAAAAAAA -> AAAAAAAA
void Texture2D::convertAI88ToA8(const unsigned char* data, ssize_t dataLen, unsigned char* outData)
{
    for (ssize_t i = 1; i < dataLen; i += 2)
    {
        *outData++ = data[i]; //A
    }
}

// IIIIIIIIAAAAAAAA -> IIIIIIII
void Texture2D::convertAI88ToI8(const unsigned char* data, ssize_t dataLen, unsigned char* outData)
{
    for (ssize_t i = 0, l = dataLen - 1; i < l; i += 2)
    {
        *outData++ = data[i]; //R
    }
}

// RRRRRRRRGGGGGGGGBBBBBBBB -> RRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA
void Texture2D::convertRGB888ToRGBA8888(const unsigned char* data, ssize_t dataLen, unsigned char* outData)
{
    for (ssize_t i = 0, l = dataLen - 2; i < l; i += 3)
    {
        *outData++ = data[i];         //R
        *outData++ = data[i + 1];     //G
        *outData++ = data[i + 2];     //B
        *outData++ = 0xFF;            //A
    }
}

// RRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA -> RRRRRRRRGGGGGGGGBBBBBBBB
void Texture2D::convertRGBA8888ToRGB888(const unsigned char* data, ssize_t dataLen, unsigned char* outData)
{
    for (ssize_t i = 0, l = dataLen - 3; i < l; i += 4)
    {
        *outData++ = data[i];         //R
        *outData++ = data[i + 1];     //G
        *outData++ = data[i + 2];     //B
    }
}

// RRRRRRRRGGGGGGGGBBBBBBBB -> RRRRRGGGGGGBBBBB
void Texture2D::convertRGB888ToRGB565(const unsigned char* data, ssize_t dataLen, unsigned char* outData)
{
    unsigned short* out16 = (unsigned short*)outData;
    for (ssize_t i = 0, l = dataLen - 2; i < l; i += 3)
    {
        *out16++ = (data[i] & 0x00F8) << 8    //R
        | (data[i + 1] & 0x00FC) << 3     //G
        | (data[i + 2] & 0x00F8) >> 3;    //B
    }
}

// RRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA -> RRRRRGGGGGGBBBBB
void Texture2D::convertRGBA8888ToRGB565(const unsigned char* data, ssize_t dataLen, unsigned char* outData)
{
    unsigned short* out16 = (unsigned short*)outData;
    for (ssize_t i = 0, l = dataLen - 3; i < l; i += 4)
    {
        *out16++ = (data[i] & 0x00F8) << 8    //R
        | (data[i + 1] & 0x00FC) << 3     //G
        | (data[i + 2] & 0x00F8) >> 3;    //B
    }
}

// RRRRRRRRGGGGGGGGBBBBBBBB -> IIIIIIII
void Texture2D::convertRGB888ToI8(const unsigned char* data, ssize_t dataLen, unsigned char* outData)
{
    for (ssize_t i = 0, l = dataLen - 2; i < l; i += 3)
    {
        *outData++ = (data[i] * 299 + data[i + 1] * 587 + data[i + 2] * 114 + 500) / 1000;  //I =  (R*299 + G*587 + B*114 + 500) / 1000
    }
}

// RRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA -> IIIIIIII
void Texture2D::convertRGBA8888ToI8(const unsigned char* data, ssize_t dataLen, unsigned char* outData)
{
    for (ssize_t i = 0, l = dataLen - 3; i < l; i += 4)
    {
        *outData++ = (data[i] * 299 + data[i + 1] * 587 + data[i + 2] * 114 + 500) / 1000;  //I =  (R*299 + G*587 + B*114 + 500) / 1000
    }
}

// RRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA -> AAAAAAAA
void Texture2D::convertRGBA8888ToA8(const unsigned char* data, ssize_t dataLen, unsigned char* outData)
{
    for (ssize_t i = 0, l = dataLen -3; i < l; i += 4)
    {
        *outData++ = data[i + 3]; //A
    }
}

// RRRRRRRRGGGGGGGGBBBBBBBB -> IIIIIIIIAAAAAAAA
void Texture2D::convertRGB888ToAI88(const unsigned char* data, ssize_t dataLen, unsigned char* outData)
{
    for (ssize_t i = 0, l = dataLen - 2; i < l; i += 3)
    {
        *outData++ = (data[i] * 299 + data[i + 1] * 587 + data[i + 2] * 114 + 500) / 1000;  //I =  (R*299 + G*587 + B*114 + 500) / 1000
        *outData++ = 0xFF;
    }
}


// RRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA -> IIIIIIIIAAAAAAAA
void Texture2D::convertRGBA8888ToAI88(const unsigned char* data, ssize_t dataLen, unsigned char* outData)
{
    for (ssize_t i = 0, l = dataLen - 3; i < l; i += 4)
    {
        *outData++ = (data[i] * 299 + data[i + 1] * 587 + data[i + 2] * 114 + 500) / 1000;  //I =  (R*299 + G*587 + B*114 + 500) / 1000
        *outData++ = data[i + 3];
    }
}

// RRRRRRRRGGGGGGGGBBBBBBBB -> RRRRGGGGBBBBAAAA
void Texture2D::convertRGB888ToRGBA4444(const unsigned char* data, ssize_t dataLen, unsigned char* outData)
{
    unsigned short* out16 = (unsigned short*)outData;
    for (ssize_t i = 0, l = dataLen - 2; i < l; i += 3)
    {
        *out16++ = ((data[i] & 0x00F0) << 8           //R
                    | (data[i + 1] & 0x00F0) << 4     //G
                    | (data[i + 2] & 0xF0)            //B
                    |  0x0F);                         //A
    }
}

// RRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA -> RRRRGGGGBBBBAAAA
void Texture2D::convertRGBA8888ToRGBA4444(const unsigned char* data, ssize_t dataLen, unsigned char* outData)
{
    unsigned short* out16 = (unsigned short*)outData;
    for (ssize_t i = 0, l = dataLen - 3; i < l; i += 4)
    {
        *out16++ = (data[i] & 0x00F0) << 8    //R
        | (data[i + 1] & 0x00F0) << 4         //G
        | (data[i + 2] & 0xF0)                //B
        |  (data[i + 3] & 0xF0) >> 4;         //A
    }
}

// RRRRRRRRGGGGGGGGBBBBBBBB -> RRRRRGGGGGBBBBBA
void Texture2D::convertRGB888ToRGB5A1(const unsigned char* data, ssize_t dataLen, unsigned char* outData)
{
    unsigned short* out16 = (unsigned short*)outData;
    for (ssize_t i = 0, l = dataLen - 2; i < l; i += 3)
    {
        *out16++ = (data[i] & 0x00F8) << 8    //R
        | (data[i + 1] & 0x00F8) << 3     //G
        | (data[i + 2] & 0x00F8) >> 2     //B
        |  0x01;                          //A
    }
}

// RRRRRRRRGGGGGGGGBBBBBBBB -> RRRRRGGGGGBBBBBA
void Texture2D::convertRGBA8888ToRGB5A1(const unsigned char* data, ssize_t dataLen, unsigned char* outData)
{
    unsigned short* out16 = (unsigned short*)outData;
    for (ssize_t i = 0, l = dataLen - 2; i < l; i += 4)
    {
        *out16++ = (data[i] & 0x00F8) << 8    //R
        | (data[i + 1] & 0x00F8) << 3     //G
        | (data[i + 2] & 0x00F8) >> 2     //B
        |  (data[i + 3] & 0x0080) >> 7;   //A
    }
}


Texture2D::Texture2D(GLuint min, GLuint mag, GLuint warpS, GLuint warpT) :
_pixelWidth(0.0f),
_pixelHeight(0.0f),
_name(0),
_alpha(false),
_hasMipmaps(false),
_unitID(0),
_maxS(0),
_maxT(0)
{
    _filter.minFilter = min;
    _filter.magFilter = mag;
    _filter.wrapS     = warpS;
    _filter.wrapT     = warpT;
}

Texture2D::~Texture2D() {
    if (_name != 0) {
        glDeleteTextures(1, &_name);
        _name = 0;
    }
}

bool Texture2D::initWithString(const char *text, const TextFormatter &format) {
    
    if (!text || strlen(text) == 0) {
        return false;
    }
    
    unsigned char *outTempData = nullptr;
    ssize_t     outTempDataLen = 0;
    
    int imageWidth  = 0;
    int imageHeight = 0;
    
    auto formatter = format;
    formatter.fontSize      *= App::getInstance()->getScaleFactor();
    formatter.width         *= App::getInstance()->getScaleFactor();
    formatter.height        *= App::getInstance()->getScaleFactor();
    formatter.stroke.size   *= App::getInstance()->getScaleFactor();
    formatter.shadow.enabled = false;
    
    bool hasPremultipliedAlpha = false;
    ByteArray *outData = TextureUtils::getInstance()->getTextureDataWithText(text, formatter, imageWidth, imageHeight, hasPremultipliedAlpha);
    
    if (!outData || outData->isNull()) {
        return false;
    }
    
    PixelFormat pixelFormat = _defaultPixelFormat;
    pixelFormat = convertDataToFormat(outData->getBytes(), outData->getLength(), PixelFormat::RGBA8888, pixelFormat, &outTempData, &outTempDataLen);
    
    bool result = initWithData(outTempData, outTempDataLen, pixelFormat, imageWidth, imageHeight);
    
    if (outTempData != nullptr && outTempData != outData->getBytes()) {
        free(outTempData);
    }
    
    _alpha = hasPremultipliedAlpha;
    
    delete outData;
    return result;
}

bool Texture2D::initWithBitmapData(BitmapData *bmp, int unitID) {
    return initWithBitmapData(bmp, _defaultPixelFormat, unitID);
}

bool Texture2D::initWithBitmapData(BitmapData *bmp, Texture2D::PixelFormat format, int unitID) {
    
    if (bmp == nullptr) {
        LOGE("Can't create Texture ------> Image is Null");
        return false;
    }
    
    int imageWidth      = bmp->getWidth();
    int imageHeight     = bmp->getHeight();
    int maxTextureSize  = App::getInstance()->getMaxTextureSize();
    
    if (imageWidth > maxTextureSize || imageHeight > maxTextureSize) {
        LOGE("Image (%d x %d) is bigger than the supported %d x %d", imageWidth, imageHeight, maxTextureSize, maxTextureSize);
        return false;
    }
    
    unsigned char* tempData = bmp->getData();
    PixelFormat pixelFormat = ((PixelFormat::NONE == format) || (PixelFormat::AUTO == format)) ? bmp->getPixcelFormat() : format;
    PixelFormat renderFormat= bmp->getPixcelFormat();
    size_t      tempDataSize= bmp->getSize();
    
    
    // convert
    unsigned char* outTempData = nullptr;
    ssize_t outTempDataLen = 0;
    
    pixelFormat = convertDataToFormat(tempData, tempDataSize, renderFormat, pixelFormat, &outTempData, &outTempDataLen);
    
    
    initWithData(outTempData, outTempDataLen, pixelFormat, imageWidth, imageHeight, unitID);
    
    if (outTempData != nullptr && outTempData != tempData) {
        free(outTempData);
    }
    
    if (bmp->hasAlpha()) {
        _alpha = true;
    } else {
        _alpha = false;
    }
    
    return true;
}

bool Texture2D::initWithFile(std::string path, int unitID) {
    BitmapData *bitmap = new BitmapData();
    bitmap->initWithFile(path);
    initWithBitmapData(bitmap, unitID);
    delete bitmap;
    return true;
}

bool Texture2D::initWithData(const unsigned char *data, ssize_t size, Texture2D::PixelFormat format, int pixelWidth, int pixcelHeight, int unitID) {
    return initWidthMipMaps(data, size, 1, format, pixelWidth, pixcelHeight, unitID);
}

bool Texture2D::initWidthMipMaps(const unsigned char *data, ssize_t dataSize, int mipNum, Texture2D::PixelFormat pixelFormat, int pixelWidth, int pixelHeight, int unitID) {
    
    if (pixelWidth <= 0 || pixelHeight <= 0) {
        LOGE("Invalid size %d x %d\n", pixelWidth, pixelHeight);
        return false;
    }
    if (pixelFormat == PixelFormat::NONE || pixelFormat == PixelFormat::AUTO) {
        LOGE("unsupported pixelformat %d\n", pixelFormat);
        return false;
    }
    
    const PixelFormatInfo& info = _pixelFormatInfoTables.at(pixelFormat);
    
    if (mipNum == 1) {
        unsigned int bytesPerRow = pixelWidth * info.bpp / 8;
        if(bytesPerRow % 8 == 0) {
            glPixelStorei(GL_UNPACK_ALIGNMENT, 8);
        } else if(bytesPerRow % 4 == 0) {
            glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
        } else if(bytesPerRow % 2 == 0) {
            glPixelStorei(GL_UNPACK_ALIGNMENT, 2);
        } else {
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        }
    } else {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    }
    
    if (_name != 0) {
        glDeleteTextures(1, &_name);
        _name = 0;
    }
    
    glGenTextures(1, &_name);
    glActiveTexture(GL_TEXTURE0 + unitID);
    setTextureFilter(_filter);
    glBindTexture(GL_TEXTURE_2D, _name);
    
    int width  = pixelWidth;
    int height = pixelHeight;
    
    for (int i = 0; i < mipNum; i++) {
        
        GLsizei datalen = (GLsizei)dataSize;
        
        if (info.compressed) {
            glCompressedTexImage2D(GL_TEXTURE_2D, i, info.internalFormat, (GLsizei)width, (GLsizei)height, 0, datalen, data);
        } else {
            glTexImage2D(GL_TEXTURE_2D, i, info.internalFormat, (GLsizei)width, (GLsizei)height, 0, info.format, info.type, data);
        }
        
        if (i > 0 && (width != height || NextPOT(width) != width )) {
            LOGE("Texture2D. WARNING. Mipmap level %u is not squared. Texture won't render correctly. width=%d != height=%d", i, width, height);
        }
        
        GLenum err = glGetError();
        if (err != GL_NO_ERROR) {
            LOGE("Texture2D: Error uploading compressed texture level: %u . glError: 0x%04X", i, err);
            return false;
        }
        
        width = MAX(width >> 1, 1);
        height = MAX(height >> 1, 1);
    }
    
    _pixelWidth     = pixelWidth;
    _pixelHeight    = pixelHeight;
    _maxS           = 1;
    _maxT           = 1;
    _unitID         = unitID;
    _alpha          = false;
    _hasMipmaps = mipNum > 1;
    
    return true;
}

void Texture2D::enableTexture() {
    glActiveTexture(GL_TEXTURE0 + _unitID);
    glBindTexture(GL_TEXTURE_2D, _name);
}

void Texture2D::disableTexture() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

float Texture2D::getWidth() {
    return _pixelWidth;
}

float Texture2D::getHeight() {
    return _pixelHeight;
}

int Texture2D::getUnitID() {
    return _unitID;
}

GLuint Texture2D::getTexture() {
    return _name;
}

void Texture2D::setDefaultPixelFormat(Texture2D::PixelFormat format) {
    _defaultPixelFormat = format;
}

bool Texture2D::isAlpha() {
    return _alpha;
}

void Texture2D::setTextureFilter(Texture2DFilter filter) {
    _filter = filter;
    glBindTexture(GL_TEXTURE_2D, _name);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _filter.minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _filter.magFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _filter.wrapS); // GL_REPEAT _filter.wrapS
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _filter.wrapT); //
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture2D::Texture2DFilter& Texture2D::getTextureFilter() {
    return _filter;
}

NS_MONKEY_END
