//
// Created by yanny on 6/1/2020.
//

#ifndef ANDROMEDA_RINCONADA_H
#define ANDROMEDA_RINCONADA_H
#include <ft2build.h>
#include FT_FREETYPE_H
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Application.h"
#include "World.h"
#include "Sprite.h"

class Rinconada: public Application {
public:
    Rinconada(struct android_app* app);
    ~Rinconada(){};
    //template<class T>
    virtual void iniApp();

    void init();
    int play();
    void terminate();

    void getMVP();
private:
    World world;
    glm::mat4 MVP;
    GLfloat screenRel = 1.0f;
    Sprite *S;
protected:

};


#endif //ANDROMEDA_RINCONADA_H
