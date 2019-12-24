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

#include "ShadersManager.h"

class Rectangle {
public:
    GLfloat width = 1.0f;
    GLfloat height = 1.0f;

    GLfloat posX = 0.0f;
    GLfloat posY = 0.0f;
    GLfloat posZ = 0.0f;

    glm::vec4 color = {0.2f, 0.3f, 0.4f, 1.0f};

    ShadersManager *sh;
    Rectangle();
    //~Rectangle();

    void init();
    void end();
    void Render(glm::mat4 MVP);
private:
    GLuint vboIds[2];

};


#endif //ANDROMEDA_RECTANGLE_H
