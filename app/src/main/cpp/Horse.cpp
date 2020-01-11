//
// Created by yanny on 6/1/2020.
//

#include "Horse.h"

Horse::Horse() {

}

Horse::Horse(const char *pPath) : Sprite2D(pPath) {

}

Horse::Horse(const char *pPath, GLfloat w, GLfloat h) : Sprite2D(pPath, w, h) {

}

void Horse::update() {
    switch(mode){
        case STOP:
            break;
        case RUNNING:
            break;
        case END_RACE:
            break;

    }

}
