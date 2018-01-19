//
//  BitmapData.cpp
//  Monkey
//
//  Created by Neil on 1/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#include <stdlib.h>
#include <time.h>

#include "core/utils/Log.h"
#include "core/utils/BitmapData.h"
#include "core/utils/ByteArray.h"
#include "platform/FileUtils.h"

#include "jpeglib.h"
#include "png.h"

#include "platform/PlatformMacros.h"

NS_MONKEY_BEGIN

// ---------------------- png ----------------------
typedef struct {
    const unsigned char * data;
    ssize_t             size;
    int                 offset;
}PngSource;

static void pngReadCallback(png_structp png_ptr, png_bytep data, png_size_t length) {
    PngSource* isource = (PngSource*)png_get_io_ptr(png_ptr);
    if((int)(isource->offset + length) <= isource->size) {
        memcpy(data, isource->data+isource->offset, length);
        isource->offset += length;
    } else {
        png_error(png_ptr, "pngReaderCallback failed");
    }
}

// ---------------------- jpg ----------------------
typedef struct {
    struct jpeg_error_mgr pub;
    jmp_buf setjmp_buffer;
}JpgError;

METHODDEF(void) myErrorExit(j_common_ptr cinfo) {
    JpgError* err = (JpgError*) cinfo->err;
    char buffer[JMSG_LENGTH_MAX];
    (*cinfo->err->format_message) (cinfo, buffer);
    longjmp(err->setjmp_buffer, 1);
}

// --------------------------------------------------------------------------------

BitmapData::BitmapData():
_data(nullptr),
_dataSize(0),
_width(0),
_height(0),
_alpha(false),
_renderFormat(Texture2D::PixelFormat::BGRA8888)
{
    
}

BitmapData::~BitmapData() {
    if (_data) {
        free(_data);
    }
}

bool BitmapData::initWithFile(const std::string &path) {
    _filePath = FileUtils::getInstance()->getFullPath(path);
    ByteArray *data = FileUtils::getInstance()->getFileData(_filePath, "rb");
    bool result = false;
    if (!data->isNull()) {
        result = initWithData(data->getBytes(), data->getLength());
    }
    delete data;
    return result;
}

bool BitmapData::initWithData(const unsigned char *data, ssize_t size) {
    
    Format imgType = checkImageFormat(data, size);
    
    bool result = false;
    
    switch (imgType) {
        case Format::PNG:
            result = initWithPNGData(data, size);
            break;
        case Format::JPG:
            result = initWithJPGData(data, size);
            break;
        default:
            result = false;
            break;
    }
    
    return result;
}

BitmapData::Format BitmapData::checkImageFormat(const unsigned char *data, ssize_t size) {
    if (isPNG(data, size)) {
        return Format::PNG;
    } else if (isJPG(data, size)) {
        return Format::JPG;
    } else {
        return Format::UNKOWN;
    }
    return Format::UNKOWN;
}

bool BitmapData::initWithPNGData(const unsigned char *data, ssize_t size) {
    
    static const int PNGSIGSIZE = 8;
    
    png_byte        header[PNGSIGSIZE] = {0};
    png_structp     png_ptr     = 0;
    png_infop       info_ptr    = 0;
    
    memcpy(header, data, PNGSIGSIZE);
    if (png_sig_cmp(header, 0, PNGSIGSIZE) != 0) {
        return false;
    }
    
    png_ptr  = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
    info_ptr = png_create_info_struct(png_ptr);
    setjmp(png_jmpbuf(png_ptr));
    
    
    PngSource pngSource;
    pngSource.data    = (unsigned char*)data;
    pngSource.size    = size;
    pngSource.offset  = 0;
    png_set_read_fn(png_ptr, &pngSource, pngReadCallback);
    
    png_read_info(png_ptr, info_ptr);
    _width = png_get_image_width(png_ptr, info_ptr);
    _height = png_get_image_height(png_ptr, info_ptr);
    png_byte bit_depth = png_get_bit_depth(png_ptr, info_ptr);
    png_uint_32 color_type = png_get_color_type(png_ptr, info_ptr);
    
    if (color_type == PNG_COLOR_TYPE_PALETTE) {
        png_set_palette_to_rgb(png_ptr);
    }
    if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) {
        bit_depth = 8;
    }
    if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS)) {
        png_set_tRNS_to_alpha(png_ptr);
    }
    if (bit_depth == 16) {
        png_set_strip_16(png_ptr);
    }
    if (bit_depth < 8) {
        png_set_packing(png_ptr);
    }
    // update info
    png_read_update_info(png_ptr, info_ptr);
    bit_depth  = png_get_bit_depth(png_ptr, info_ptr);
    color_type = png_get_color_type(png_ptr, info_ptr);
    
    switch (color_type) {
        case PNG_COLOR_TYPE_GRAY:
            _renderFormat = Texture2D::PixelFormat::I8;
            break;
        case PNG_COLOR_TYPE_GRAY_ALPHA:
            _renderFormat = Texture2D::PixelFormat::AI88;
            break;
        case PNG_COLOR_TYPE_RGB:
            _renderFormat = Texture2D::PixelFormat::RGB888;
            break;
        case PNG_COLOR_TYPE_RGB_ALPHA:
            _renderFormat = Texture2D::PixelFormat::RGBA8888;
            break;
        default:
            break;
    }
    
    // read png data
    png_size_t rowbytes;
    png_bytep* row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * _height);
    rowbytes = png_get_rowbytes(png_ptr, info_ptr);
    
    _dataSize = rowbytes * _height;
    _data = static_cast<unsigned char*>(malloc(_dataSize * sizeof(unsigned char)));
    
    if(!_data) {
        if (row_pointers != nullptr) {
            free(row_pointers);
        }
        return false;
    }
    
    for (unsigned short i = 0; i < _height; ++i) {
        row_pointers[i] = _data + i*rowbytes;
    }
    
    png_read_image(png_ptr, row_pointers);
    png_read_end(png_ptr, nullptr);
    
    if (color_type == PNG_COLOR_TYPE_RGB_ALPHA) {
        _alpha = true;
    } else {
        _alpha = false;
    }
    
    if (row_pointers != nullptr) {
        free(row_pointers);
    }
    
    if (png_ptr) {
        png_destroy_read_struct(&png_ptr, (info_ptr) ? &info_ptr : 0, 0);
    }
    
    return true;
}

bool BitmapData::initWithJPGData(const unsigned char *data, ssize_t size) {
    
    struct jpeg_decompress_struct cinfo;
    
    JpgError jerr;
    
    JSAMPROW row_pointer[1] = {0};
    unsigned long location = 0;
    unsigned int  i = 0;
    
    cinfo.err = jpeg_std_error(&jerr.pub);
    jerr.pub.error_exit = myErrorExit;
    
    if (setjmp(jerr.setjmp_buffer)) {
        jpeg_destroy_decompress(&cinfo);
        return false;
    }
    
    jpeg_create_decompress(&cinfo);
    
#ifndef CC_TARGET_QT5
    jpeg_mem_src( &cinfo, const_cast<unsigned char*>(data), size);
#endif /* CC_TARGET_QT5 */

#if (JPEG_LIB_VERSION >= 90)
    jpeg_read_header( &cinfo, TRUE );
#else
    jpeg_read_header( &cinfo, true );
#endif
    
    if (cinfo.jpeg_color_space == JCS_GRAYSCALE) {
        _renderFormat = Texture2D::PixelFormat::I8;
    } else {
        cinfo.out_color_space = JCS_RGB;
        _renderFormat = Texture2D::PixelFormat::RGB888;
    }
    
    jpeg_start_decompress(&cinfo);
    
    _width  = cinfo.output_width;
    _height = cinfo.output_height;
    
    row_pointer[0] = static_cast<unsigned char*>(malloc(cinfo.output_width*cinfo.output_components * sizeof(unsigned char)));

    _dataSize = cinfo.output_width*cinfo.output_height*cinfo.output_components;
    _data     = static_cast<unsigned char*>(malloc(_dataSize * sizeof(unsigned char)));
    
    while(cinfo.output_scanline < cinfo.output_height) {
        jpeg_read_scanlines( &cinfo, row_pointer, 1 );
        for(i=0; i<cinfo.output_width*cinfo.output_components;i++) {
            _data[location++] = row_pointer[0][i];
        }
    }
    
    jpeg_destroy_decompress(&cinfo);
    
    if (row_pointer[0] != nullptr) {
        free(row_pointer[0]);
    };
    
    _alpha = false;
    
    return true;
}

bool BitmapData::isJPG(const unsigned char *data, ssize_t size) {
    static const unsigned char JPG_SOI[] = {0xFF, 0xD8};
    int jpgSize = sizeof(JPG_SOI);
    if (size <= jpgSize) {
        return false;
    }
    return memcmp(JPG_SOI, data, jpgSize) == 0;
}

bool BitmapData::isPNG(const unsigned char *data, ssize_t size) {
    static const unsigned char PNG_SIGNATURE[] = {0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a};
    int pngSize = sizeof(PNG_SIGNATURE);
    if (size <= pngSize) {
        return false;
    }
    return memcmp(PNG_SIGNATURE, data, pngSize) == 0;
}

bool BitmapData::hasAlpha() {
    return _alpha;
}

Texture2D::PixelFormat& BitmapData::getPixcelFormat() {
    return _renderFormat;
}

int BitmapData::getWidth() {
    return _width;
}

int BitmapData::getHeight() {
    return _height;
}

ssize_t BitmapData::getSize() {
    return _dataSize;
}

unsigned char* BitmapData::getData() {
    return _data;
}

NS_MONKEY_END