//
// Created by yanny on 22/7/2019.
//

#include <cstring>

#include "Asset.h"
#include "Log.h"

const char * Asset::_externalDataPath = "";
const char * Asset::_internalDataPath = "";
AAssetManager* Asset::_assetManager = nullptr;

Asset::Asset(const char *pPath):
    _path(pPath),
    _asset(nullptr)
    {
}
Asset::Asset(const char *pPath, int pMode):
    _path(pPath),
    _mode(pMode),
    _asset(nullptr) {

}

void Asset::setAssetManager(AAssetManager *pAssetManager) {
    Asset::_assetManager = pAssetManager;
}

void Asset::setDataPath(const char* pInternalDataPath, const char* pExternalDataPath) {
    _internalDataPath = pInternalDataPath;
    _externalDataPath = pExternalDataPath;
}

int Asset::open() {
    _LOGE("ONE - A1 %s", _path);

    if(_assetManager){

        _LOGE("ONE - A.001 %s", _path);
    }
/*
    _LOGE("ONE - A2  .%d", (_asset != NULL) ? 1 : 0);


    off_t outStart;

    off_t fileLength = AAsset_getLength(_asset);
    int descriptor = AAsset_openFileDescriptor(_asset, &outStart, &fileLength);
    _LOGE("ONE PNG 555 xxx longitud: %d", fileLength);
*/
    _asset = AAssetManager_open(_assetManager, _path, _mode);
    return (_asset != NULL) ? 1 : 0;
}

void Asset::close() {
    if (_asset != NULL) {
        AAsset_close(_asset);
        _asset = NULL;
    }
}

int Asset::read(void *pBuffer, size_t pCount) {
    int32_t readCount = AAsset_read(_asset, pBuffer, pCount);
    return (readCount == pCount) ?1 :0;
}
int Asset::read(void *pBuffer) {
    off_t pCount = AAsset_getLength(_asset);
    int32_t readCount = AAsset_read(_asset, pBuffer, pCount);
    return (readCount == pCount) ?1 :0;
}

AssetDescriptor Asset::descriptor() {
    AssetDescriptor lDescriptor = { -1, 0, 0 };
    AAsset* lAsset = AAssetManager_open(_assetManager, _path, AASSET_MODE_UNKNOWN);
    if (lAsset != NULL) {
        lDescriptor.descriptor = AAsset_openFileDescriptor(lAsset, &lDescriptor.start, &lDescriptor.length);
        AAsset_close(lAsset);
    }
    return lDescriptor;
 }


bool Asset::operator==(const Asset& pOther) {
    return !strcmp(_path, pOther._path);
}

off_t Asset::getLength() {
    return AAsset_getLength(_asset);
}

const char *Asset::getPath() {
    return _path;
}

void Asset::load() {
    open();
    length = getLength();
    buffer = new uint8_t[length];
    read(buffer, length);
    //close();

}

uint8_t *Asset::getBuffer() {
    return buffer;
}

void Asset::unLoad() {
    delete[] buffer;
    buffer = NULL;
    length = 0;

}



