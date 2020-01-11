//
// Created by yanny on 8/1/2020.
//

#ifndef ANDROMEDA_BUTTON2D_H
#define ANDROMEDA_BUTTON2D_H


#include "Rectangle2D.h"
#include "iButton.h"
#include "Scene.h"

class Button2D: public Rectangle2D, public iButton {
public:
    Button2D();
    ~Button2D();
    Button2D(GLfloat w, GLfloat h);
    bool isIn(float x, float y);

    void bind(void * _context);
    void * getContext();



private:
    void *context = nullptr;

};


#endif //ANDROMEDA_BUTTON2D_H
