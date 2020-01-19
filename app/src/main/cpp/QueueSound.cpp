//
// Created by Yanny on 18/1/2020.
//

#include "QueueSound.h"
#include "Log.h"

QueueSound::QueueSound():
        mPlayerObj(NULL),
        mPlayer(NULL),
        mPlayerQueue() {

}

int QueueSound::initialize(SLEngineItf pEngine, SLObjectItf pOutputMixObj) {
    _LOGE("Starting sound player.");
    SLresult result;

    // Set-up sound audio source.
    SLDataLocator_AndroidSimpleBufferQueue dataLocatorIn;
    dataLocatorIn.locatorType = SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE;

    // At most one buffer in the queue.
    dataLocatorIn.numBuffers = 1;


    SLDataFormat_PCM dataFormat;
    dataFormat.formatType = SL_DATAFORMAT_PCM;
    dataFormat.numChannels = 1; // Mono sound.
    dataFormat.samplesPerSec = SL_SAMPLINGRATE_44_1;
    dataFormat.bitsPerSample = SL_PCMSAMPLEFORMAT_FIXED_16;
    dataFormat.containerSize = SL_PCMSAMPLEFORMAT_FIXED_16;
    dataFormat.channelMask = SL_SPEAKER_FRONT_CENTER;
    dataFormat.endianness = SL_BYTEORDER_LITTLEENDIAN;

    SLDataFormat_MIME dataFormat2;
    dataFormat2.formatType = SL_DATAFORMAT_MIME;
    dataFormat2.mimeType = NULL;
    dataFormat2.containerType = SL_CONTAINERTYPE_UNSPECIFIED;

    SLDataSource dataSource;
    dataSource.pLocator = &dataLocatorIn;
    dataSource.pFormat = &dataFormat2;

    SLDataLocator_OutputMix dataLocatorOut;
    dataLocatorOut.locatorType = SL_DATALOCATOR_OUTPUTMIX;
    dataLocatorOut.outputMix = pOutputMixObj;

    SLDataSink dataSink;
    dataSink.pLocator = &dataLocatorOut;
    dataSink.pFormat = NULL;
    const SLuint32 soundPlayerIIDCount = 2;
    const SLInterfaceID soundPlayerIIDs[] = { SL_IID_PLAY, SL_IID_BUFFERQUEUE };
    const SLboolean soundPlayerReqs[] = { SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE };
    result = (*pEngine)->CreateAudioPlayer(pEngine, &mPlayerObj, &dataSource, &dataSink,
            soundPlayerIIDCount, soundPlayerIIDs, soundPlayerReqs);
    if (result != SL_RESULT_SUCCESS) goto ERROR;
    result = (*mPlayerObj)->Realize(mPlayerObj, SL_BOOLEAN_FALSE);
    if (result != SL_RESULT_SUCCESS) goto ERROR;
    result = (*mPlayerObj)->GetInterface(mPlayerObj, SL_IID_PLAY, &mPlayer);
    if (result != SL_RESULT_SUCCESS) goto ERROR;
    result = (*mPlayerObj)->GetInterface(mPlayerObj, SL_IID_BUFFERQUEUE, &mPlayerQueue);
    if (result != SL_RESULT_SUCCESS) goto ERROR;
    result = (*mPlayer)->SetPlayState(mPlayer, SL_PLAYSTATE_PLAYING);
    if (result != SL_RESULT_SUCCESS) goto ERROR;
    return 1;
    ERROR:
    _LOGE("Error while starting SoundQueue");
    return 0;
}

void QueueSound::finalize() {
    if (mPlayerObj != NULL) {
        (*mPlayerObj)->Destroy(mPlayerObj);
        mPlayerObj = NULL; mPlayer = NULL; mPlayerQueue = NULL;
    }
}

void QueueSound::playSound(Asset *pSound) {
    SLresult result;
    SLuint32 playerState;
    (*mPlayerObj)->GetState(mPlayerObj, &playerState);
    if (playerState == SL_OBJECT_STATE_REALIZED) {
        int16_t* buffer = (int16_t*) pSound->getBuffer();
        off_t length = pSound->getLength();
        // Removes any sound from the queue.
        result = (*mPlayerQueue)->Clear(mPlayerQueue);
        if (result != SL_RESULT_SUCCESS) goto ERROR;
        // Plays the new sound.
        result = (*mPlayerQueue)->Enqueue(mPlayerQueue, buffer, length);
        if (result != SL_RESULT_SUCCESS) goto ERROR;
    }
    return;
    ERROR:
    _LOGE("Error trying to play sound");
}
