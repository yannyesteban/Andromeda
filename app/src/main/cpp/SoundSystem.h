//
// Created by yanny on 11/1/2020.
//

#ifndef ANDROMEDA_SOUNDSYSTEM_H
#define ANDROMEDA_SOUNDSYSTEM_H
#include <android_native_app_glue.h>
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include "Asset.h"
class SoundSystem {
public:
    SoundSystem(android_app* pApplication);
    ~SoundSystem();
    int32_t start();
    void stop();

    int32_t playBGM(Asset& pResource);
    void stopBGM();

    //Sound* registerSound(Resource& pResource);
    //void playSound(Sound* pSound);
private:
    android_app* mApplication;
    SLObjectItf mEngineObj;
    SLEngineItf mEngine;
    SLObjectItf mOutputMixObj;

    SLObjectItf mBGMPlayerObj; SLPlayItf mBGMPlayer;
    SLSeekItf mBGMPlayerSeek;

    static const int32_t QUEUE_COUNT = 4;
    //SoundQueue mSoundQueues[QUEUE_COUNT]; int32_t mCurrentQueue;
    //Sound* mSounds[32]; int32_t mSoundCount;

};


#endif //ANDROMEDA_SOUNDSYSTEM_H
