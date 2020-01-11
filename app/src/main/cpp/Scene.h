//
// Created by yanny on 8/1/2020.
//

#ifndef ANDROMEDA_SCENE_H
#define ANDROMEDA_SCENE_H


#include "Object3D.h"

class Scene {
public:

    Scene()= default;
    virtual ~Scene(){};
    virtual void add(Object3D * obj);

    virtual void render(glm::mat4 MVP);
    virtual void render();
    virtual void end();

    int state = 44;
private:

protected:
    Object3D * objects[100];
    int nObjects = 0;

    glm::mat4 MVP;
};


#endif //ANDROMEDA_SCENE_H
