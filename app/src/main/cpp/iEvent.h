//
// Created by Yanny on 3/1/2020.
//

#ifndef ANDROMEDA_IEVENT_H
#define ANDROMEDA_IEVENT_H
#include <android/input.h>
#include <glm/glm.hpp>
#include "Rectangle.h"
#include "iButton.h"

class sButton: public Rectangle, public iButton{
public:
    sButton();
    ~sButton();
    sButton(GLfloat w, GLfloat h);
    bool isIn(float a, float b);

    void bind(void * _context);
    void * getContext();

private:
    void *_context;
};






struct EEvent{

};

class iEvent {
public:
    EEvent * obj[100];

    int screenWidth;
    int screenHeight;
    iEvent();
    ~iEvent();
    void AttachEvent(EEvent area, const char * name, int (*call)(int a, int b), glm::mat4 MVP);
    void process(const AInputEvent* motion_event);
    int n = 0;
private:
};


#endif //ANDROMEDA_IEVENT_H
