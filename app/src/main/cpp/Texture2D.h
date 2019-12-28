//
// Created by Yanny on 27/12/2019.
//

#ifndef ANDROMEDA_TEXTURE2D_H
#define ANDROMEDA_TEXTURE2D_H
#include <cstring>
//#include <android/asset_manager.h>
#include <png.h>
#include <pngconf.h>
#include <GLES/gl.h>
#include <GLES2/gl2.h>
//#include "types.h"
#include "Asset.h"
//#include "loadpng.h"

struct text_png2{
    GLuint texture;
    GLint format;
    png_byte* image;
    png_uint_32 width;
    png_uint_32 height;

};

struct PNG_PROP2{
    GLint format;

    png_byte* image;
    png_uint_32 width;
    png_uint_32 height;
};


void callback_readPng2(png_structp pStruct, png_bytep pData, png_size_t pSize);


class Texture2D {

public:
    Texture2D();
    PNG_PROP2 pngFile(const char * pPath, PNG_PROP2 & PNG);
    GLuint bind(const char * pPath);

};


#endif //ANDROMEDA_TEXTURE2D_H
