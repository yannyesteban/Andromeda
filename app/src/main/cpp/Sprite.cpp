//
// Created by Yanny on 27/12/2019.
//

#include "Sprite.h"
#include "Log.h"

void Sprite::init() {

    sh =  new ShadersManager();
    //m2->mAssetManager = app->activity->assetManager;

    sh->setVS("shaders/sprite_vs.glsl");
    sh->setFS("shaders/sprite_fs.glsl");


    sh->addAttrib({0, 3, "vPosition"});
    sh->addAttrib({1, 2, "aTexture"});
    sh->Program();

    Texture2D T = Texture2D();

    mTexture = T.bind(mPath);

    _LOGE("mTexture : %d, %s", mTexture, mPath);
    //glBindTexture(GL_TEXTURE_2D, mTexture);

}

void Sprite::Render(glm::mat4 MVP) {


    GLfloat vVertices[] = {
            posX,        posY,         posZ,        0.0f, 0.0f,
            posX+width,  posY,         posZ+0.0f,   1.0f, 0.0f,
            posX+width,  posY+height,  posZ+0.0f,   1.0f, 1.0f,
            posX,        posY+height,  posZ+0.0f,   0.0f, 1.0f,
    };


    GLfloat vVerticesZ[] = {
            0.0f,  0.0f,  0.0f, 0.0f,0.0f,
            0.5f,  0.0f,  0.0f, 1.0f,0.0f,
            0.5f,  0.5f,  0.0f, 1.0f,1.0f,
            0.0f,  0.5f,  0.0f, 0.0f,1.0f,
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



    //glClearColor(1.0f,0.0f,0.1f, 1);
    //glClearColor(1.0f,1.0f,0.5f, 1);
    //glEnable(GL_DEPTH_TEST);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glDepthMask(GL_TRUE);
    //glDepthFunc(GL_LEQUAL);
    //std::list<GLAttrib> lAttrib;
    //std::unordered_map<GLushort , std::string> mAttrib;
    //text_png PNG;
    //return;



    GLuint programObject = sh->programObject;

    //glBindTexture(GL_TEXTURE_2D, mTexture);

    //glViewport(0, 0, 400,400);
    glBindTexture(GL_TEXTURE_2D, mTexture);

    _LOGE("mTexture x 2 : %d, %s", mTexture, mPath);
    GLuint MatrixID = glGetUniformLocation(programObject, "MVP");
    glUseProgram(programObject);


    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0);
}



void Sprite::end() {
    glDeleteBuffers(2, vboIds);

}

void Sprite::setPos(GLfloat x, GLfloat y) {
    posX = x;
    posY = y;

}

void Sprite::setTexture(glm::vec4 pColor) {

}

void Sprite::setPosX(GLfloat x) {
    posX = x;
}
void Sprite::setPosY(GLfloat y) {
    posY += y*acc;
}
void Sprite::setPosZ(GLfloat z) {
    posZ = z;
}

GLfloat Sprite::getPosX() {
    return posX;
}
GLfloat Sprite::getPosY() {
    return posY;
}
GLfloat Sprite::getPosZ() {
    return posZ ;
}

Sprite::Sprite() {

}

