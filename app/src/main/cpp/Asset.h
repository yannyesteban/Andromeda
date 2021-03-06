//
// Created by yanny on 22/7/2019.
//

#ifndef RINCONADA_ASSET_H
#define RINCONADA_ASSET_H
#include <android/asset_manager.h>

struct AssetDescriptor{
    int32_t descriptor;
    off_t   start;
    off_t   length;
};


class Asset {
public:

    Asset(const char* pPath);
    Asset(const char* pPath, int pMode);
    int open();

    void close();

    void load();
    void unLoad();
    uint8_t* getBuffer();


    int read(void* pBuffer, size_t pCount);
    int read(void* pBuffer);
    off_t getLength();
    const char* getPath();
    AssetDescriptor descriptor();

    static void setAssetManager(AAssetManager* pAssetManager);
    static void setDataPath(const char * pInternalDataPath,  const char * pExternalDataPath);


    bool operator==(const Asset& pOther);
    static AAssetManager * _assetManager;
private:

    AAsset* _asset;
    const char* _path;

    uint8_t* buffer;
    off_t length;

    static const char * _externalDataPath;
    static const char * _internalDataPath;

    int _mode = AASSET_MODE_UNKNOWN;


};


#endif //RINCONADA_ASSET_H
