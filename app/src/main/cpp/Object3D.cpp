//
// Created by yanny on 8/1/2020.
//

#include "Object3D.h"



Object3D::Object3D(GLfloat w, GLfloat h, GLfloat d):
    width(w),
    height(h),
    depth(d){
}

Object3D::Object3D(GLfloat w, GLfloat h, GLfloat d, GLfloat x, GLfloat y, GLfloat z):
    width(w),
    height(h),
    depth(d),
    posX(x),
    posY(y),
    posZ(z){
}

void Object3D::setName(const char *pName) {
    name = pName;
}

const char *Object3D::getName() {
    return name;
}

void Object3D::setPos(GLfloat x, GLfloat y) {
    posX = x;
    posY = y;
}

void Object3D::setPos(GLfloat x, GLfloat y, GLfloat z) {
    posX = x;
    posY = y;
    posZ = z;
}

void Object3D::setPosX(GLfloat x) {
    posX = x;
}

void Object3D::setPosY(GLfloat y) {
    posY = y;
}

void Object3D::setPosZ(GLfloat z) {
    posZ = z;
}

GLfloat Object3D::getPosX() {
    return posX;
}

GLfloat Object3D::getPosY() {
    return posY;
}

GLfloat Object3D::getPosZ() {
    return posZ;
}

void Object3D::setWidth(GLfloat w) {
    width = w;
}

void Object3D::setHeight(GLfloat h) {
    height = h;
}

void Object3D::setDepth(GLfloat d) {
    depth = d;
}

GLfloat Object3D::getWidth() {
    return width;
}

GLfloat Object3D::getHeight() {
    return height;
}

GLfloat Object3D::getDepth() {
    return depth;
}

Object3D::~Object3D() {

}

glm::mat4 Object3D::getProjection() {
    return projection;
}

glm::mat4 Object3D::getView() {
    return view;
}

glm::mat4 Object3D::getModel() {
    return model;
}

void Object3D::setProjection(glm::mat4 pProjection) {
    projection = pProjection;
}

void Object3D::setView(glm::mat4 pView) {
    view = pView;
}

void Object3D::setModel(glm::mat4 pModel) {
    model = pModel;
}
