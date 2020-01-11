//
// Created by yanny on 8/1/2020.
//

#include "Rectangle2D.h"
Rectangle2D::~Rectangle2D() {

}

Rectangle2D::Rectangle2D(GLfloat w, GLfloat h) :  Object3D(w,h,0.0){

}
Rectangle2D::Rectangle2D(GLfloat w, GLfloat h, GLfloat d) : Object3D(w, h, d) {

}

Rectangle2D::Rectangle2D(GLfloat w, GLfloat h, GLfloat d, GLfloat x, GLfloat y, GLfloat z)
        : Object3D(w, h, d, x, y, z) {

}



void Rectangle2D::init() {
    sh =  new ShadersManager();
    sh->setVS("shaders/solid_vs.glsl");
    sh->setFS("shaders/solid_fs.glsl");
    sh->addAttrib({0, 3, "vPosition"});
    sh->Program();
    MVPid = sh->getUniformLocation("MVP");
}

void Rectangle2D::render(glm::mat4 MVP) {
    this->MVP = MVP;
    glUseProgram(sh->programObject);

    glUniformMatrix4fv(MVPid, 1, GL_FALSE, &MVP[0][0]);

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
    //glEnableVertexAttribArray(1);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vtxStride, (const void*)offset);
    //offset += 3 * sizeof(GLfloat);
    //glVertexAttribPointer(1, 2,    GL_FLOAT, GL_FALSE, vtxStride, (const void*)offset);

    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0);
}

void Rectangle2D::end() {
    glDeleteBuffers(2, vboIds);
}

void Rectangle2D::setColor(glm::vec4 pColor) {
    color = pColor;
}



