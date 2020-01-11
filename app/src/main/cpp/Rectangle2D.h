//
// Created by yanny on 8/1/2020.
//

#ifndef ANDROMEDA_RECTANGLE2D_H
#define ANDROMEDA_RECTANGLE2D_H


#include "Object3D.h"
#include "ShadersManager.h"

class Rectangle2D: public Object3D {
public:


    Rectangle2D() = default;
    Rectangle2D(GLfloat w, GLfloat h);
    Rectangle2D(GLfloat w, GLfloat h, GLfloat d);
    Rectangle2D(GLfloat w, GLfloat h, GLfloat d, GLfloat x, GLfloat y, GLfloat z);

    ~Rectangle2D();

    virtual void init();
    virtual void render(glm::mat4 MVP);
    virtual void end();

    virtual void setColor(glm::vec4 pColor);

private:



protected:
    glm::vec4 color = {0.2f, 0.3f, 0.4f, 1.0f};
    ShadersManager *sh;
    GLuint vboIds[2];
    GLint MVPid;
};


#endif //ANDROMEDA_RECTANGLE2D_H
