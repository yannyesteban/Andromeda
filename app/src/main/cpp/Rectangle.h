//
// Created by Yanny on 23/12/2019.
//

#ifndef ANDROMEDA_RECTANGLE_H
#define ANDROMEDA_RECTANGLE_H
#include <EGL/egl.h>
#include <GLES/gl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <glm/glm.hpp>
#include <gl3stub.h>

#include "ShadersManager.h"
#include "World.h"

class Rectangle: public  basicObj {
public:
    GLfloat width = 0.5f;
    GLfloat height = 1.0f;

    //GLfloat posX = 0.0f;
    //GLfloat posY = 0.0f;
    //GLfloat posZ = 0.0f;
    GLfloat acc = 1.0f;
    glm::vec4 color = {0.2f, 0.3f, 0.4f, 1.0f};

    ShadersManager *sh;
    Rectangle();
    Rectangle(GLfloat w, GLfloat h):width(w), height(h){};
    //~Rectangle();

    void init();
    void end();
    void setPos(GLfloat x, GLfloat y);

    void setPosX(GLfloat x);
    void setPosY(GLfloat y);
    void setPosZ(GLfloat z);

    GLfloat getPosX();
    GLfloat getPosY();
    GLfloat getPosZ();

    void setColor(glm::vec4 pColor);
    void Render(glm::mat4 MVP);
    void Reset();
private:
    GLuint vboIds[2];
    GLint mMVPId;

};


#endif //ANDROMEDA_RECTANGLE_H
