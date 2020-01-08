//
// Created by yanny on 6/1/2020.
//

#include "Cube.h"



void Cube::init() {

    sh =  new ShadersManager();
    sh->setVS("shaders/solid_vs.glsl");
    sh->setFS("shaders/solid_fs.glsl");
    sh->addAttrib({0, 3, "vPosition"});
    sh->Program();
    mMVPId = sh->getUniformLocation("MVP");

}

void Cube::Render(glm::mat4 MVP) {

    this->MVP = MVP;
    glUseProgram(sh->programObject);

    glUniformMatrix4fv(mMVPId, 1, GL_FALSE, &MVP[0][0]);

    GLint textColor = glGetUniformLocation(sh->programObject, "textColor");
    glUniform4f(textColor, color.x, color.y, color.z, color.w);

    GLfloat vVertices[] = {
            -1.0,  -1.0,  1.0,
             1.0,  -1.0,  1.0,
            -1.0,   1.0,  1.0,
             1.0,   1.0,  1.0,

            -1.0,  -1.0, -1.0,
             1.0,  -1.0, -1.0,
            -1.0,   1.0, -1.0,
             1.0,   1.0, -1.0,
    };

    GLushort  indices[] = {
            // front
            0, 1, 2,
            2, 1, 3,
            // right
            1, 5, 6,
            6, 2, 1,
            // back
            7, 6, 5,
            5, 4, 7,
            // left
            4, 0, 3,
            3, 7, 4,
            // bottom
            4, 5, 1,
            1, 0, 4,
            // top
            3, 2, 6,
            6, 7, 3

    };

    GLint numIndices = 36;
    GLint numVertices = 8;
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

void Cube::end() {
    glDeleteBuffers(2, vboIds);

}

void Cube::setPos(GLfloat x, GLfloat y) {
    posX = x;
    posY = y;

}

void Cube::setColor(glm::vec4 pColor) {
    color = pColor;
}

void Cube::setPosX(GLfloat x) {
    posX = x;
}
void Cube::setPosY(GLfloat y) {
    posY = y;
}
void Cube::setPosZ(GLfloat z) {
    posZ = z;
}

GLfloat Cube::getPosX() {
    return posX;
}
GLfloat Cube::getPosY() {
    return posY;
}
GLfloat Cube::getPosZ() {
    return posZ ;
}



void Cube::setName(char *name) {
    mName = name;
}

const char *Cube::getName() {
    return mName;
}

void Cube::setPos(GLfloat x, GLfloat y, GLfloat z) {
    posX = x;
    posY = y;
    posZ = z;
}