//
// Created by Yanny on 23/12/2019.
//

#include <glm/gtc/matrix_transform.hpp>
#include "Rectangle.h"
#include "Log.h"

Rectangle::Rectangle() {


}
void Rectangle::init() {

    sh =  new ShadersManager();
    sh->setVS("shaders/solid_vs.glsl");
    sh->setFS("shaders/solid_fs.glsl");
    sh->addAttrib({0, 3, "vPosition"});
    sh->Program();
    mMVPId = sh->getUniformLocation("MVP");

}

void Rectangle::Render(glm::mat4 MVP) {

    this->MVP = MVP;
    glUseProgram(sh->programObject);

    glUniformMatrix4fv(mMVPId, 1, GL_FALSE, &MVP[0][0]);

    GLint textColor = glGetUniformLocation(sh->programObject, "textColor");
    glUniform4f(textColor, color.x, color.y, color.z, color.w);

    GLfloat vVertices[] = {
            posX,       posY,         posZ,
            posX+width, posY,         posZ,
            posX+width, posY+height,  posZ,
            posX,       posY+height,  posZ,
    };

    GLushort  indices[] = {0,1,2,0,2,3};

    GLint numIndices = 6;
    GLint numVertices = 4;
    GLint vtxStride = (3)*sizeof(GLfloat);
    GLuint offset = 0;

    // vboIds[0] – used to store vertex attribute data
    // vboIds[1] – used to store element indices
    glGenBuffers(2, vboIds);

    glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
    glBufferData(GL_ARRAY_BUFFER, vtxStride * numVertices, vVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * numIndices, indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vtxStride, (const void*)offset);
    offset += 3 * sizeof(GLfloat);
    glVertexAttribPointer(1, 2,    GL_FLOAT, GL_FALSE, vtxStride, (const void*)offset);

    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0);

}

void Rectangle::end() {
    glDeleteBuffers(2, vboIds);

}

void Rectangle::setPos(GLfloat x, GLfloat y) {
    posX = x;
    posY = y;

}

void Rectangle::setColor(glm::vec4 pColor) {
    color =pColor;
}

void Rectangle::setPosX(GLfloat x) {
    posX = x;
}
void Rectangle::setPosY(GLfloat y) {
    posY = y;
}
void Rectangle::setPosZ(GLfloat z) {
    posZ = z;
}

GLfloat Rectangle::getPosX() {
    return posX;
}
GLfloat Rectangle::getPosY() {
    return posY;
}
GLfloat Rectangle::getPosZ() {
    return posZ ;
}

void Rectangle::Reset() {
    posX = 0.0f;
    posY = -2.0f;
    posZ = 0.0f;


}

void Rectangle::setName(char *name) {
    mName = name;
}

const char *Rectangle::getName() {
    return mName;
}
