//
// Created by Yanny on 29/12/2019.
//

#include "World.h"


basicObj::basicObj() {

}

basicObj::~basicObj() {

}

void basicObj::Reset() {
    posX = 0.0f;
    posY = -2.0f;
    posZ = 0.0f;


}

World::World(){

}
World::~World(){

}
void World::add(basicObj *pObj) {
    pObj->init();
    obj[nButtons] = pObj;
    nButtons++;
}

void World::Render(glm::mat4 MVP) {

    for(int i=0;i<nButtons;i++){
        obj[i]->Render(MVP);
    }

}

void World::End() {

    for(int i=0;i<nButtons;i++){
        obj[i]->end();
    }

}

void World::Reset() {
    for(int i=0;i<nButtons;i++){

        obj[i]->Reset();
    }
}
