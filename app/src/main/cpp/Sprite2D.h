//
// Created by yanny on 8/1/2020.
//

#ifndef ANDROMEDA_SPRITE2D_H
#define ANDROMEDA_SPRITE2D_H
#include <EGL/egl.h>
#include <GLES/gl.h>
#include <GLES2/gl2.h>
#include "Object3D.h"
#include "ShadersManager.h"

class Sprite2D : public Object3D{
public:
    Sprite2D();
    Sprite2D(const char * pPath);
    Sprite2D(const char * pPath, GLfloat w, GLfloat h);
    virtual ~Sprite2D();
    //Sprite2D(GLfloat w, GLfloat h):width(w), height(h){};

    virtual void init();
    virtual void render(glm::mat4 MVP);
    virtual void end();
    void setTexture(const char * pPath);
private:

protected:
    ShadersManager *sh;
    GLuint vboIds[2];
    GLint texture;
    GLint MVPid;
    const char * path = "";
};


#endif //ANDROMEDA_SPRITE2D_H
