//
// Created by yanny on 11/1/2020.
//

#include "SoundSystem.h"
#include "Log.h"


SoundSystem::SoundSystem(android_app *pApplication) :
        mApplication(pApplication),
        mEngineObj(NULL), mEngine(NULL),
        mOutputMixObj(NULL){

}

int32_t SoundSystem::start() {

    SLresult result;
    const SLuint32 engineMixIIDCount = 1;
    const SLInterfaceID engineMixIIDs[] = {SL_IID_ENGINE};
    const SLboolean engineMixReqs[] = {SL_BOOLEAN_TRUE};
    const SLuint32 outputMixIIDCount = 0;
    const SLInterfaceID outputMixIIDs[] = {};
    const SLboolean outputMixReqs[] = {};

    // Creates OpenSL ES engine and dumps its capabilities.
    result = slCreateEngine(&mEngineObj, 0, NULL, engineMixIIDCount, engineMixIIDs, engineMixReqs);
    if (result != SL_RESULT_SUCCESS) goto ERROR;

    result = (*mEngineObj)->Realize(mEngineObj, SL_BOOLEAN_FALSE);
    if (result != SL_RESULT_SUCCESS) goto ERROR;

    result = (*mEngineObj)->GetInterface(mEngineObj, SL_IID_ENGINE, &mEngine);
    if (result != SL_RESULT_SUCCESS) goto ERROR;
    // Creates audio output.

    result = (*mEngine)->CreateOutputMix(mEngine, &mOutputMixObj, outputMixIIDCount, outputMixIIDs, outputMixReqs);
    result = (*mOutputMixObj)->Realize(mOutputMixObj, SL_BOOLEAN_FALSE);

    //Log::info("Starting sound player.");
    for (int32_t i= 0; i < QUEUE_COUNT; ++i) {
        if (mSoundQueues[i].initialize(mEngine, mOutputMixObj) != 1) goto ERROR;
    }
    for (int32_t i = 0; i < mSoundCount; ++i) {
        mSounds[i]->load();// != 1) goto ERROR;
    }


    return 1;

    ERROR:
        //Log::error("Error while starting SoundManager");
        stop();
        return 0;
}

void SoundSystem::stop() {
    //Log::info("Stopping SoundManager.");

    stopBGM();

    for (int32_t i= 0; i < QUEUE_COUNT; ++i) {
        mSoundQueues[i].finalize();
    }

    if (mOutputMixObj != NULL) {
        (*mOutputMixObj)->Destroy(mOutputMixObj);
        mOutputMixObj = NULL;
    }
    if (mEngineObj != NULL) {
        (*mEngineObj)->Destroy(mEngineObj);
        mEngineObj = NULL; mEngine = NULL;
    }

    for (int32_t i = 0; i < mSoundCount; ++i) {
        mSounds[i]->unLoad();
    }


}

int32_t SoundSystem::playBGM(Asset &pResource) {
    SLresult result;
    //Log::info("Opening BGM %s", pResource.getPath());
    AssetDescriptor descriptor = pResource.descriptor();
    if (descriptor.descriptor < 0) {
        //Log::info("Could not open BGM file");
        return 0;
    }
    SLDataLocator_AndroidFD dataLocatorIn;
    dataLocatorIn.locatorType = SL_DATALOCATOR_ANDROIDFD;
    dataLocatorIn.fd = descriptor.descriptor;
    dataLocatorIn.offset = descriptor.start;
    dataLocatorIn.length = descriptor.length;

    SLDataFormat_MIME dataFormat;
    dataFormat.formatType = SL_DATAFORMAT_MIME;
    dataFormat.mimeType = NULL;
    dataFormat.containerType = SL_CONTAINERTYPE_UNSPECIFIED;

    SLDataSource dataSource;
    dataSource.pLocator = &dataLocatorIn;
    dataSource.pFormat = &dataFormat;

    SLDataLocator_OutputMix dataLocatorOut;
    dataLocatorOut.locatorType = SL_DATALOCATOR_OUTPUTMIX;
    dataLocatorOut.outputMix = mOutputMixObj;
    SLDataSink dataSink;
    dataSink.pLocator = &dataLocatorOut;
    dataSink.pFormat = NULL;

    //Then, create the OpenSL ES audio player. As always, with OpenSL ES objects,
    //instantiate it through the engine first and then realize it. Two interfaces, SL_IID_
    //PLAY and SL_IID_SEEK, are imperatively required:

    const SLuint32 bgmPlayerIIDCount = 2;
    const SLInterfaceID bgmPlayerIIDs[] = { SL_IID_PLAY, SL_IID_SEEK };
    const SLboolean bgmPlayerReqs[] = { SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE };
    result = (*mEngine)->CreateAudioPlayer(mEngine,
                                           &mBGMPlayerObj, &dataSource, &dataSink,
                                           bgmPlayerIIDCount, bgmPlayerIIDs, bgmPlayerReqs);
    if (result != SL_RESULT_SUCCESS) goto ERROR;

    result = (*mBGMPlayerObj)->Realize(mBGMPlayerObj, SL_BOOLEAN_FALSE);
    if (result != SL_RESULT_SUCCESS) goto ERROR;

    result = (*mBGMPlayerObj)->GetInterface(mBGMPlayerObj, SL_IID_PLAY, &mBGMPlayer);
    if (result != SL_RESULT_SUCCESS) goto ERROR;

    result = (*mBGMPlayerObj)->GetInterface(mBGMPlayerObj, SL_IID_SEEK, &mBGMPlayerSeek);
    if (result != SL_RESULT_SUCCESS) goto ERROR;
    /*
     * Finally, using the play and seek interfaces, switch the playback in loop mode (that
    is, the music keeps playing) from the track's beginning (that is, 0 milliseconds) until
    its end (SL_TIME_UNKNOWN), and then start playing (SetPlayState() with
    SL_PLAYSTATE_PLAYING).
     */
    result = (*mBGMPlayerSeek)->SetLoop(mBGMPlayerSeek,
                                        SL_BOOLEAN_TRUE, 0, SL_TIME_UNKNOWN);
    if (result != SL_RESULT_SUCCESS) goto ERROR;
    result = (*mBGMPlayer)->SetPlayState(mBGMPlayer,
                                         SL_PLAYSTATE_PLAYING);
    if (result != SL_RESULT_SUCCESS) goto ERROR;
    return 1;
    ERROR:
    //Log::error("Error playing BGM");
    return 0;
}

void SoundSystem::stopBGM() {
    if (mBGMPlayer != NULL) {
        SLuint32 bgmPlayerState;
        (*mBGMPlayerObj)->GetState(mBGMPlayerObj, &bgmPlayerState);

        if (bgmPlayerState == SL_OBJECT_STATE_REALIZED) {
            (*mBGMPlayer)->SetPlayState(mBGMPlayer, SL_PLAYSTATE_PAUSED);
            (*mBGMPlayerObj)->Destroy(mBGMPlayerObj);

            mBGMPlayerObj = NULL;
            mBGMPlayer = NULL; mBGMPlayerSeek = NULL;
        }
    }
}

SoundSystem::~SoundSystem() {

    _LOGE("Destroying SoundManager.");

    for (int32_t i = 0; i < mSoundCount; ++i) {
        delete mSounds[i];
    }
    mSoundCount = 0;

}

Asset *SoundSystem::registerSound(Asset *pResource) {

    for (int32_t i = 0; i < mSoundCount; ++i) {
        //if (strcmp(pResource->getPath(), mSounds[i]->getPath()) == 0) {
        if(pResource == mSounds[i]){
            return mSounds[i];
        }
    }
    //return nullptr;
    //Sound* sound = new Sound(mApplication, &pResource);
    mSounds[mSoundCount++] = pResource;
    return pResource;
}

void SoundSystem::playSound(Asset *pSound) {
    int32_t currentQueue = ++mCurrentQueue;
    QueueSound& soundQueue = mSoundQueues[currentQueue % QUEUE_COUNT];
    soundQueue.playSound(pSound);
}
