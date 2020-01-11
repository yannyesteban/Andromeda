//
// Created by yanny on 8/1/2020.
//

#include "Sprite2D.h"
#include "Texture2D.h"

Sprite2D::Sprite2D(const char *pPath):path(pPath) {

}

Sprite2D::Sprite2D(const char *pPath, GLfloat w, GLfloat h):Object3D(w,h,0.0),path(pPath){

}

Sprite2D::Sprite2D() {

}

void Sprite2D::setTexture(const char *pPath) {
    path = pPath;
}

Sprite2D::~Sprite2D() {

}

void Sprite2D::init() {
    sh =  new ShadersManager();
    sh->setVS("shaders/sprite_vs.glsl");
    sh->setFS("shaders/sprite_fs.glsl");
    sh->addAttrib({0, 3, "vPosition"});
    sh->addAttrib({1, 2, "aTexture"});
    sh->Program();

    Texture2D T = Texture2D();
    texture = T.bind(path);
    MVPid = sh->getUniformLocation("MVP");
}

void Sprite2D::render(glm::mat4 MVP) {
    glUseProgram(sh->programObject);
    glUniformMatrix4fv(MVPid, 1, GL_FALSE, &MVP[0][0]);

    GLfloat vVertices[] = {
            posX,        posY,         posZ,   0.0f, 0.0f,
            posX+width,  posY,         posZ,   1.0f, 0.0f,
            posX+width,  posY+height,  posZ,   1.0f, 1.0f,
            posX,        posY+height,  posZ,   0.0f, 1.0f,
    };


    GLushort  indices[] = {0,1,2,0,2,3};

    GLuint vboIds[2];
    GLint numIndices = 6;
    GLint numVertices = 4;
    GLint vtxStride = (5) *sizeof(GLfloat);
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
    glVertexAttribPointer(1, 2,    GL_FLOAT, GL_FALSE, vtxStride,     (const void*)offset);

    glBindTexture(GL_TEXTURE_2D, texture);
    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0);
}

void Sprite2D::end() {
    glDeleteBuffers(2, vboIds);
}
