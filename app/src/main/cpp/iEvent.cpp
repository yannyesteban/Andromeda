//
// Created by Yanny on 3/1/2020.
//

#include "iEvent.h"


bool sButton::isIn(float x, float y){

    //_LOGE("AInputEvent sButton AA: %f, BB: %f x-> %f", x, y, width) ;




    glm::vec4 V1 = glm::vec4(posX,posY,0.0f,1.0f);
    glm::vec4 V2 = glm::vec4(posX+width,posY+height,0.0f,1.0f);
    V1 = MVP * V1;
    V2 = MVP * V2;
    //_LOGE("AInputEvent (1) C:(%f, %f), p1:(%f, %f), p2:(%f, %f)", x, y,  V1.x,V1.y, V2.x, V2.y);
    V1.x = V1.x/2 +0.5;
    V1.y = (V1.y/2 +0.5);
    V2.x = V2.x/2 +0.5;
    V2.y = (V2.y/2 +0.5);


    //_LOGE("AInputEvent (2) C:(%f, %f), p1:(%f, %f), p2:(%f, %f)", x, y,  V1.x,V1.y, V2.x, V2.y);

    if(x>=V1.x && x<=V2.x && y>=V1.y && y<=V2.y){
        //int s = obj[i]->call(1, 1);
        _LOGE("AInputEvent sButton YESSS" );

        return true;
    }else{
        //_LOGE("AInputEvent sButton NOPPP" );
    }

    return false;

};
sButton::sButton(GLfloat w, GLfloat h):Rectangle(w, h){
    _context = this;
};

void sButton::bind(void * context) {
   _context = context;
}

sButton::~sButton() {

}

void *sButton::getContext() {
    return _context;
}



iEvent::iEvent() {

}

iEvent::~iEvent() {

}

void iEvent::AttachEvent(EEvent area, const char *name, int (*call)(int, int), glm::mat4 MVP) {

}

void iEvent::process(const AInputEvent *motion_event) {

}
