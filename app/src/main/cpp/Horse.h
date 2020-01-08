//
// Created by yanny on 6/1/2020.
//

#ifndef ANDROMEDA_HORSE_H
#define ANDROMEDA_HORSE_H


#include "Rectangle.h"

class Horse: public Rectangle  {
    Horse(){};
    ~Horse(){};
    Horse(GLfloat w, GLfloat h):Rectangle(w, h){};
};


#endif //ANDROMEDA_HORSE_H
