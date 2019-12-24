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
    //m2->mAssetManager = app->activity->assetManager;

    sh->setVS("shaders/solid_vs.glsl");
    sh->setFS("shaders/solid_fs.glsl");


    sh->addAttrib({0, 3, "vPosition"});
    //sh->addAttrib({1, 2, "aColor"});
    sh->Program();

}

void Rectangle::Render(glm::mat4 MVP) {
    glUseProgram(sh->programObject);

    GLint vv = glGetUniformLocation(sh->programObject, "textColor");


    static GLfloat x= 0;


    color.x = x;
    x = x +0.001f;
    _LOGE("COLOR_X *** %d = %d > %f, %f, %f, %f", sh->programObject, vv, color.x, color.y, color.z, color.w);
    glUniform4f(vv, color.x, color.y, color.z, color.w);

    GLfloat vVertices[] = {
            0.0f,  0.0f,  0.0f,
            0.5f,  0.0f,  0.0f,
            0.5f,  0.5f,  0.0f,
            0.0f,  0.5f,  0.0f,
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
    glVertexAttribPointer(1, 2,    GL_FLOAT, GL_FALSE, vtxStride,     (const void*)offset);

    _LOGE(" FRAME -a-  draw_frame");

    GLuint programObject = sh->programObject;

    GLuint MatrixID = glGetUniformLocation(programObject, "MVP");


    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0);

}

void Rectangle::end() {
    glDeleteBuffers(2, vboIds);

}
