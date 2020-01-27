//
// Created by yanny on 23/1/2020.
//

#ifndef ANDROMEDA_CUBE3D_H
#define ANDROMEDA_CUBE3D_H

#include <glm/gtc/matrix_transform.hpp>
#include "Object3D.h"
#include "ShadersManager.h"

class Cube3D: public Object3D{
public:
    Cube3D();
    ~Cube3D();


    virtual void init();
    virtual void render(glm::mat4 MVP);
    virtual void end();
protected:
    glm::vec4 color = {0.9f, 0.122f, 0.122f, 1.0f};
    ShadersManager *sh;
    GLuint vboIds[4];
    GLint MVPid;
    GLint Mid;
    GLint Vid;
    GLint Pid;
};


#endif //ANDROMEDA_CUBE3D_H
