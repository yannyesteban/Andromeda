//
// Created by Yanny on 18/1/2020.
//

#ifndef ANDROMEDA_QUEUESOUND_H
#define ANDROMEDA_QUEUESOUND_H
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include "Asset.h"

class QueueSound {
public:
    QueueSound();
    int initialize(SLEngineItf pEngine, SLObjectItf pOutputMixObj);
    void finalize();
    void playSound(Asset* pSound);
private:
    SLObjectItf mPlayerObj;
    SLPlayItf mPlayer;
    SLBufferQueueItf mPlayerQueue;
};


#endif //ANDROMEDA_QUEUESOUND_H
