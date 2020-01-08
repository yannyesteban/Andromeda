//
// Created by yanny on 6/1/2020.
//

#ifndef ANDROMEDA_CUBE_H
#define ANDROMEDA_CUBE_H

#include "ShadersManager.h"
#include "World.h"

class Cube: public basicObj {
public:
    glm::mat4 MVP;
    glm::vec4 color = {0.2f, 0.3f, 0.4f, 1.0f};
    Cube(GLfloat w, GLfloat h, GLfloat d):width(w), height(h), depth(d){};
    GLfloat width = 0.5f;
    GLfloat height = 1.0f;
    GLfloat depth = 0.0f;

    void init();
    void end();
    void setPos(GLfloat x, GLfloat y);
    void setPos(GLfloat x, GLfloat y, GLfloat z);

    void setPosX(GLfloat x);
    void setPosY(GLfloat y);
    void setPosZ(GLfloat z);

    GLfloat getPosX();
    GLfloat getPosY();
    GLfloat getPosZ();
    void setName(char * name);
    const char * getName();
    void setColor(glm::vec4 pColor);
    void Render(glm::mat4 MVP);

    void Reset(){};

private:
    GLuint vboIds[2];
    GLint mMVPId;
    const char * mName = nullptr;
    ShadersManager *sh;

};


#endif //ANDROMEDA_CUBE_H
