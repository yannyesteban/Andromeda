//
// Created by Yanny on 27/12/2019.
//

#include "Texture2D.h"
#include "Log.h"

void callback_readPng2(png_structp pStruct, png_bytep pData, png_size_t pSize) {

    Asset  *asset = ((Asset*)png_get_io_ptr(pStruct));

    _LOGE("PNG xxx2.0 callback size:%d", pSize);
    //dinfo * d = ((dinfo*)png_get_io_ptr(pStruct));
    //LOGW("xxx2.1 callback size:%d", pSize);

    int32_t readCount = asset->read(pData, pSize);
    _LOGE("PNG xxx2.2 callback size:%d", pSize);
    if(readCount == pSize) {
        _LOGE("PNG xxx error psize readcount %d", readCount);
        //ERROR
    };
    //LOGW("xxx2.3 callback size:%d", pSize);

    //LOGW("xxx2.5 callback OUT size:%d", pSize);
}


PNG_PROP2 Texture2D::pngFile(const char * pPath, PNG_PROP2 & PNG){
    Asset *asset = new Asset(pPath);

    //AAsset* mAsset;
    //mAsset = AAssetManager_open(mAssetManager, pPath, AASSET_MODE_UNKNOWN);

    if(asset->open()){
        _LOGE("PNG - cool");
    }else{
        _LOGE("PNG - error 1");
    }

    //off_t outStart;

    //off_t fileLength = AAsset_getLength(mAsset);
    //int descriptor = AAsset_openFileDescriptor(mAsset, &outStart, &fileLength);
//LOGW("xxx longitud: %d", fileLength);

    GLuint texture;
    GLint format;

    png_byte header[8];
    png_structp pngPtr = NULL;
    png_infop infoPtr = NULL;
    png_byte* image = NULL;
    png_bytep* rowPtrs = NULL;
    png_int_32 rowSize;
    bool transparency;

    /* leer el encabezado*/
    //dinfo d;
    //d.mAsset = mAsset;
    int32_t readCount = asset->read(header, sizeof(header));


    if (png_sig_cmp(header, 0, 8) != 0){
        _LOGE("PNG - error 2");

    }else{
        _LOGE("PNG - bien 2");
    }


    //LOGW("xxx  Creating required structures.");
    pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!pngPtr) {
        _LOGE("PNG - error 3");
    }
    infoPtr = png_create_info_struct(pngPtr);
    if (!infoPtr) {
        _LOGE("PNG - error 4");
    }

    _LOGE("PNG - bien 3");
    // Prepares reading operation by setting-up a read callback.
    png_set_read_fn(pngPtr, asset, callback_readPng2);

    if (setjmp(png_jmpbuf(pngPtr))) {
        _LOGE("PNG - error 5");
    };



    // Ignores first 8 bytes already read.
    _LOGE("PNG - bien 4");

    png_set_sig_bytes(pngPtr, 8);
    _LOGE("PNG - bien 4.1");
    // Retrieves PNG info and updates PNG struct accordingly.
    png_read_info(pngPtr, infoPtr);
    _LOGE("PNG - bien 4.2");
    png_int_32 depth, colorType;
    _LOGE("PNG - bien 4.3");
    png_uint_32 width, height;
    _LOGE("PNG - bien 5");
    //LOGW("xxx hasta aqui tres3");
    //return;
    png_get_IHDR(pngPtr, infoPtr, &width, &height, &depth, &colorType, NULL, NULL, NULL);

    // Creates a full alpha channel if transparency is encoded as
    // an array of palette entries or a single transparent color.
    transparency = false;
    if (png_get_valid(pngPtr, infoPtr, PNG_INFO_tRNS)) {
        png_set_tRNS_to_alpha(pngPtr);
        transparency = true;
    }
    _LOGE("PNG - bien 6");
    // Expands PNG with less than 8bits per channel to 8bits.
    if (depth < 8) {
        png_set_packing (pngPtr);
        // Shrinks PNG with 16bits per color channel down to 8bits.
    } else if (depth == 16) {
        png_set_strip_16(pngPtr);
    }

    //LOGW("xxx hasta aqui cuatro");
    _LOGE("PNG - bien 7");
    // Indicates that image needs conversion to RGBA if needed.
    switch (colorType) {
        case PNG_COLOR_TYPE_PALETTE:
            png_set_palette_to_rgb(pngPtr);
            format = transparency ? GL_RGBA : GL_RGB;
            break;
        case PNG_COLOR_TYPE_RGB:
            format = transparency ? GL_RGBA : GL_RGB;
            break;
        case PNG_COLOR_TYPE_RGBA:
            format = GL_RGBA;
            break;
        case PNG_COLOR_TYPE_GRAY:
            png_set_expand_gray_1_2_4_to_8(pngPtr);
            format = transparency ? GL_LUMINANCE_ALPHA:GL_LUMINANCE;
            break;
        case PNG_COLOR_TYPE_GA:
            png_set_expand_gray_1_2_4_to_8(pngPtr);
            format = GL_LUMINANCE_ALPHA;
            break;
    }
    // Validates all transformations.
    //LOGW("xxx hasta aqui cinco");
    _LOGE("PNG - bien 8");
    png_read_update_info(pngPtr, infoPtr);
    /******************/
    // Get row size in bytes.
    rowSize = png_get_rowbytes(pngPtr, infoPtr);
    if (rowSize <= 0) {
        _LOGE("PNG - error 6");
        //error
    }
    _LOGE("PNG - bien 9");
    // Ceates the image buffer that will be sent to OpenGL.
    image = new png_byte[rowSize * height];
    if (!image) {
        _LOGE("PNG - error 7");
        //ERROR;
    }
    _LOGE("PNG - bien 10");
    // Pointers to each row of the image buffer. Row order is
    // inverted because different coordinate systems are used by
    // OpenGL (1st pixel is at bottom left) and PNGs (top-left).
    //LOGW("xxx hasta aqui seis");
    rowPtrs = new png_bytep[height];
    if (!rowPtrs) {
        _LOGE("PNG - error 8");
        //ERROR
    }
    for (int32_t i = 0; i < height; ++i) {
        rowPtrs[height - (i + 1)] = image + i * rowSize;
    }
    _LOGE("PNG - bien 11");
    //LOGW("xxx hasta aqui siete");
    // Reads image content.
    png_read_image(pngPtr, rowPtrs);



    asset->close();
    _LOGE("PNG - bien 12");
    png_destroy_read_struct(&pngPtr, &infoPtr, NULL);
    delete[] rowPtrs;
    PNG.image = image;
    PNG.width = width;
    PNG.height = height;
    PNG.format = format;

    return PNG;


}


GLuint Texture2D::bind(const char *pPath) {
    GLuint texture;
    PNG_PROP2 PNG;
    pngFile(pPath, PNG);

    _LOGE("PNG - bien 20 width:@");

    //LOGW("xxx hasta aqui ocho");
    GLenum errorResult;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // Set-up texture properties.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Loads image data into OpenGL.
    glTexImage2D(GL_TEXTURE_2D, 0, PNG.format, PNG.width, PNG.height, 0, PNG.format, GL_UNSIGNED_BYTE, PNG.image);
    // Finished working with the texture.
    glBindTexture(GL_TEXTURE_2D, 0);

    _LOGE("PNG - bien 20 width: %d, height: %d", PNG.width, PNG.height);
    delete[] PNG.image;
    if (glGetError() != GL_NO_ERROR) {

        _LOGE("SPRITE PNG - BIEN ERROR 2020 %d, %d ", glGetError(), GL_NO_ERROR);
        //error
    }
    //LOGW("Texture size: %d x %d", width, height);
    return texture;
}

Texture2D::Texture2D() {

}

