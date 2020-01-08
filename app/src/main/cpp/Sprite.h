//
// Created by Yanny on 27/12/2019.
//

#ifndef ANDROMEDA_SPRITE_H
#define ANDROMEDA_SPRITE_H



#include <EGL/egl.h>
#include <GLES/gl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <glm/glm.hpp>
#include <gl3stub.h>
#include "Texture2D.h"
#include "ShadersManager.h"
#include "World.h"


class Sprite: public  basicObj {
public:

    const char * source = "";

    GLfloat width = 1.0f;
    GLfloat height = 1.0f;

    GLfloat posX = 0.0f;
    GLfloat posY = 0.0f;
    GLfloat posZ = 0.0f;
    GLfloat acc = 1.0f;
    ShadersManager *sh;

    Sprite();
    Sprite(const char * pPath):mPath(pPath){};
    Sprite(const char * pPath, GLfloat w, GLfloat h):mPath(pPath),width(w), height(h){};
    Sprite(GLfloat w, GLfloat h):width(w), height(h){};

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

    void setTexture(glm::vec4 pColor);
    void Render(glm::mat4 MVP);


private:
    GLuint vboIds[2];
    GLint mTexture;
    GLint mMVPId;
    const char * mPath = "";
};


#endif //ANDROMEDA_SPRITE_H
