//
// Created by yanny on 6/1/2020.
//

#ifndef ANDROMEDA_RACE_H
#define ANDROMEDA_RACE_H


#include "Horse.h"

class Race {

    void init();
    void play();
    void stop();
    void pause();
    void terminate();
    void setDistance();
    void addHorse(Horse* horse);

    void startRace();

};


#endif //ANDROMEDA_RACE_H
