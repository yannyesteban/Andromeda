//
// Created by yanny on 6/1/2020.
//

#ifndef ANDROMEDA_RACE_H
#define ANDROMEDA_RACE_H


#include "Horse.h"
#include "Object3D.h"
#include "Scene.h"

class Race: public Scene        {
public:
    void init();
    void play();
    void stop();
    void pause();
    void reset();
    void terminate();
    void setDistance();
    void addHorse(Horse* horse);

    void setCompetitor(int n);

    void render(glm::mat4 MVP);
    void render();
    void startRace();
    void setState(int value);
    int state = 8;

    Race * get();

    u_short setPosition(Horse * h);



private:
    Horse * horses[20];
    int nHorses = 0;
    int maxHorses = 20;
    float distance = 20.0;

    Sprite2D * track = nullptr;
    InfoRace *info = nullptr;

    Horse  * positions[20];
    u_short nPosition = 0;


};


#endif //ANDROMEDA_RACE_H
