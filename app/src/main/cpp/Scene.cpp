//
// Created by yanny on 8/1/2020.
//

#include "Scene.h"

void Scene::add(Object3D *obj) {

    obj->init();
    objects[nObjects] = obj;
    nObjects++;
}

void Scene::end() {
    for(int i=0;i < nObjects;i++){
        objects[i]->end();
    }
}

void Scene::render(glm::mat4 pMVP) {
    MVP = pMVP;
    for(int i=0;i < nObjects;i++){
        objects[i]->render(MVP);
    }
}

void Scene::render() {
    render(MVP);
}



