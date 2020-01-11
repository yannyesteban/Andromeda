//
// Created by yanny on 8/1/2020.
//

#ifndef ANDROMEDA_OBJECT3D_H
#define ANDROMEDA_OBJECT3D_H
#include <glm/glm.hpp>
#include <GLES/gl.h>
#include "Log.h"


class Object3D {
public:
    Object3D() = default;
    Object3D(GLfloat w, GLfloat h, GLfloat d);
    Object3D(GLfloat w, GLfloat h, GLfloat d, GLfloat x, GLfloat y, GLfloat z);

    virtual ~Object3D()=0;
    virtual void init() = 0;
    virtual void render(glm::mat4 MVP) = 0;
    virtual void end() = 0;
    virtual void reset(){};

    virtual void setPos(GLfloat x, GLfloat y);
    virtual void setPos(GLfloat x, GLfloat y, GLfloat z);

    virtual void setPosX(GLfloat x);
    virtual void setPosY(GLfloat y);
    virtual void setPosZ(GLfloat z);

    //virtual void rotate(GLfloat z);
    //virtual void scale(GLfloat z);

    virtual GLfloat getPosX();
    virtual GLfloat getPosY();
    virtual GLfloat getPosZ();

    virtual void setWidth(GLfloat w);
    virtual void setHeight(GLfloat h);
    virtual void setDepth(GLfloat d);

    virtual GLfloat getWidth();
    virtual GLfloat getHeight();
    virtual GLfloat getDepth();

    virtual void setName(const char * pName);
    virtual const char * getName();


    GLint Id = 0;
private:
    const char * name = nullptr;
protected:
    GLfloat width = 1.0f;
    GLfloat height = 1.0f;
    GLfloat depth = 1.0f;

    GLfloat posX = 0.0f;
    GLfloat posY = 0.0f;
    GLfloat posZ = 0.0f;

    glm::mat4 MVP;
};


#endif //ANDROMEDA_OBJECT3D_H
