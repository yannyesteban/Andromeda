//
// Created by Yanny on 29/12/2019.
//

#ifndef ANDROMEDA_WORLD_H
#define ANDROMEDA_WORLD_H

#include <glm/glm.hpp>
#include <GLES/gl.h>
#include "EventEngine.h"
#include "Log.h"
class basicObj{
public:
    basicObj();
    virtual ~basicObj();
    //basicObj(GLfloat w, GLfloat h):width(w), height(h){};

    virtual void init() = 0;
    virtual void Render(glm::mat4 MVP) = 0;
    virtual void end() = 0;
    virtual void Reset(){};

    virtual void setPos(GLfloat x, GLfloat y)=0;
    virtual void setPos(GLfloat x, GLfloat y, GLfloat z)=0;


    virtual void setPosX(GLfloat x)=0;
    virtual void setPosY(GLfloat y)=0;
    virtual void setPosZ(GLfloat z)=0;

    virtual GLfloat getPosX()=0;
    virtual GLfloat getPosY()=0;
    virtual GLfloat getPosZ()=0;

    virtual void PosIni(GLfloat x, GLfloat y, GLfloat z);



    GLfloat posX = 0.0f;
    GLfloat posY = 0.0f;
    GLfloat posZ = 0.0f;

    GLfloat iniX = 0.0f;
    GLfloat iniY = 0.0f;
    GLfloat iniZ = 0.0f;
    GLint Id = 0;

};


class World {
public:
    World();
    virtual ~World();
    void add(basicObj *pObj);
    void addButton();
    void addText();

    void Render(glm::mat4 MVP);
    void Reset();
    void End();
private:
    basicObj *obj[100];
    Button *buttons[100];
    int nObj = 0;
    int nButtons = 0;
};


#endif //ANDROMEDA_WORLD_H
