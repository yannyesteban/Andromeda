//
// Created by yanny on 6/1/2020.
//

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include "Race.h"
#include "Button2D.h"
#include "Text2D.h"

void Race::init() {
/*
    Cube3D * cube = new Cube3D();

    cube->setPos(-0.05f, -0.5f, -0.5);

    add(cube);
*/
    //return;

    Text2D * mText = new Text2D();
    mText->setColor({(GLfloat)246/255,(GLfloat)22/255,(GLfloat)195/255,1.0});
    mText->setScale(0.01f);
    mText->setText("Andromeda Nov 2021");
    mText->setPos(-3.0f, 6.5f);



    add(mText);



    info = new InfoRace;
    info->maxDistance = 5.0f;

    track = new Sprite2D("png/pista.png", 6.0f, 12.0f);
    track->setPos(-3.0, -6.0, -0.1);

    add(track);

    Sprite2D * meta = new Sprite2D("png/meta.png", 5.8f, 0.5f);
    meta->setPos(-2.9, 5.0);

    add(meta);

    for(int i=0;i<maxHorses;i++){
        Horse *h = new Horse("png/horse2.png", 0.6f, 1.2f);
        h->info = info;
        h->setPos(-2.8+i*(0.87), -5.0);
        addHorse(h);
    }

    Button2D *bStart = new Button2D(1.0, 0.6);
    bStart->setColor({(float)245/255,(float)65/255,(float)218/255,1.0});
    bStart->setPos(-2.5,-5.5);
    bStart->setName("start");
    bStart->bind(this);
    //b1->AttachEvent("click", xx);

    bStart->AttachEvent("click", [](ElemEvent event) -> void {
        Button2D *s = (Button2D*)event.target;
        Race * x = (Race *)event.context;

        //Race *r = (Race *)x->que;
        x->startRace();
       _LOGE("AInputEvent sButton Reset II: %f, %f, status %d", event.x, event.y, x->state);
    });

    add(bStart);


    Button2D *bPause = new Button2D(1.0, 0.6);
    bPause->setColor({(float)185/255,(float)219/255,(float)13/255,1.0});
    bPause->setPos(-1.5,-5.5);
    bPause->setName("start");
    bPause->bind(this);
    //b1->AttachEvent("click", xx);

    bPause->AttachEvent("click", [](ElemEvent event) -> void {
        Button2D *s = (Button2D*)event.target;
        Race * x = (Race *)event.context;

        //Race *r = (Race *)x->que;
        x->stop();
        //x->SS.playSound();
        _LOGE("AInputEvent sButton Reset II: %f, %f, status %d", event.x, event.y, x->state);
    });

    add(bPause);


    Button2D *bReset = new Button2D(1.0, 0.6);
    bReset->setColor({(float)185/255,(float)219/255,(float)13/255,1.0});
    bReset->setPos(0.0,-5.5);
    bReset->setName("start");
    bReset->bind(this);
    //b1->AttachEvent("click", xx);

    bReset->AttachEvent("click", [](ElemEvent event) -> void {
        Button2D *s = (Button2D*)event.target;
        Race * x = (Race *)event.context;

        //Race *r = (Race *)x->que;
        x->reset();
        _LOGE("AInputEvent sButton Reset II: %f, %f, status %d", event.x, event.y, x->state);
    });

    add(bReset);
}

void Race::play() {

}

void Race::stop() {
    state = 0;
}

void Race::pause() {

}

void Race::terminate() {
    setState(0);
    for(int i=0;i<maxHorses;i++){
        delete positions[i];
    }
    nPosition = 0;
}
void Race::setDistance() {

}

void Race::addHorse(Horse *horse) {
    horses[nHorses] = horse;
    nHorses++;
    add(horse);
}

void Race::startRace() {
    _LOGE("AInputEvent sButton start");
    //setState(1);
    state = 1;

}

void Race::setCompetitor(int n) {
    maxHorses = n;

}

void Race::render() {



    Scene::render();
}

void Race::setState(int value) {
    state = value;
}

Race *Race::get() {
    return this;
}

void Race::render(glm::mat4 MVP) {
    _LOGE("AInputEvent Position");
    if(state == 1){
        srand (time(nullptr));
        /* generate secret number between 1 and 10: */
        double Fraction = 500.0;
        GLfloat DX = ((double) rand() / (RAND_MAX)) / Fraction;
        GLfloat DX2 = ((double) rand() / (RAND_MAX)) / Fraction;
        GLfloat DX3 = ((double) rand() / (RAND_MAX)) / Fraction;
        u_short kk = 0;
        for(int i=0;i<maxHorses;i++){


            GLfloat DX = ((double) rand() / (RAND_MAX)) / Fraction;

            horses[i]->setPosY( horses[i]->getPosY()+0.005+DX);
            horses[i]->setPosX( horses[i]->getPosX());
            kk = setPosition(horses[i]);
            _LOGE("AInputEvent Position %d",kk);

        }

        if(kk == maxHorses){
            terminate();
        }
    }

    Scene::render(MVP);
}

void Race::reset() {
    for(int i=0;i<maxHorses;i++){
        horses[i]->setPosY( -5.0);
    }
}

u_short Race::setPosition(Horse *h) {

    if(nPosition<maxHorses){
        float pos =  h->getPosY();
        if(pos>=info->maxDistance){
            positions[nPosition] = h;
            nPosition++;
        }
    }
    return nPosition;
}

