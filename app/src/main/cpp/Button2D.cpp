//
// Created by yanny on 8/1/2020.
//

#include "Button2D.h"

bool Button2D::isIn(float x, float y) {

    glm::vec4 V1 = glm::vec4(posX,posY,0.0f,1.0f);
    glm::vec4 V2 = glm::vec4(posX+width,posY+height,0.0f,1.0f);
    V1 = MVP * V1;
    V2 = MVP * V2;

    V1.x = V1.x/2 +0.5;
    V1.y = (V1.y/2 +0.5);
    V2.x = V2.x/2 +0.5;
    V2.y = (V2.y/2 +0.5);

    if(x>=V1.x && x<=V2.x && y>=V1.y && y<=V2.y){
        return true;
    }

    return false;
}

void Button2D::bind(void * pContext) {
    context = pContext;
}

void * Button2D::getContext() {
    return context;
}

Button2D::Button2D(GLfloat w, GLfloat h):Rectangle2D(w, h) {

}

Button2D::Button2D() {

}

Button2D::~Button2D() {

}

