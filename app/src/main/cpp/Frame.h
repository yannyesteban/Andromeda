//
// Created by yanny on 17/12/2019.
//

#ifndef ANDROMEDA_FRAME_H
#define ANDROMEDA_FRAME_H

#include "Asset.h"

#define VERTEX_POS_INDX 0
#define VERTEX_NORMAL_INDX 1
#define VERTEX_COLOR_INDEX 1
#define VERTEX_TEXCOORD0_INDX 2


#define VERTEX_POS_INDEX 0
#define VERTEX_POS_SIZE 3 // x, y and z

#define VERTEX_COLOR_INDEX 1
#define VERTEX_COLOR_SIZE 3 // x, y and z

#define VERTEX_NORMAL_INDEX 8
#define VERTEX_NORMAL_SIZE 3 // x, y and z


#define VERTEX_TEXCOORD0_INDEX 3
#define VERTEX_TEXCOORD0_SIZE 2 // s and t


#define VERTEX_TEXCOORD1_INDEX 4
#define VERTEX_TEXCOORD2_INDEX 5

ShadersManager *m;
GLint text[5];
std::list<GLAttrib> lAttrib;
void Init (android_app* app){

    Asset::setAssetManager(app->activity->assetManager);
    m =  new ShadersManager();
    m->mAssetManager = app->activity->assetManager;



    m->setVS("shaders/a_vs.glsl");
    m->setFS("shaders/a_fs.glsl");


    lAttrib.push_back({0, 3, "aPosition"});
    lAttrib.push_back({1, 2, "aColor"});

    m->Program3(lAttrib);
    //lProgram[0] = m->programObject;

    text[0] = Texture(app->activity->assetManager, "png/mario.png");
    //text[1] = Texture(app->activity->assetManager, "png/instagram.png");
    //text[2] = Texture(app->activity->assetManager, "png/mickey.png");


    glBindTexture(GL_TEXTURE_2D, text[0]);
}
void Frame(android_app* app, EGLDisplay display, EGLSurface surface){
    glClearColor(1.0f,0.0f,0.5f, 1);
    //glClearColor(1.0f,1.0f,0.5f, 1);
    //glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glDepthMask(GL_FALSE);
    //glDepthFunc(GL_ALWAYS);
    //std::list<GLAttrib> lAttrib;
    //std::unordered_map<GLushort , std::string> mAttrib;
    //text_png PNG;
    //return;
    _LOGE(" FRAME -a-  draw_frame");
    // No display.
    if (display == NULL) {
        _LOGE("************************ CLOSE");
        return;
    }


    GLuint programObject = m->programObject;

    //glBindTexture(GL_TEXTURE_2D, text[1]);

    //glViewport(0, 0, 400,400);


    glUseProgram(programObject);


    GLfloat vVertices1[] = {
            0.0f,  0.0f,  0.0f, 1.0f,1.0f,0.5f,
            0.5f,  0.0f,  0.0f, 1.0f,1.0f,0.5f,
            0.5f,  0.5f,  0.0f, 1.0f,1.0f,0.5f,
            0.0f,  0.5f,  0.0f, 1.0f,1.0f,0.5f,
    };

    GLfloat vVertices[] = {
            0.0f,  0.0f,  0.0f, 0.0f,0.0f,
            0.5f,  0.0f,  0.0f, 1.0f,0.0f,
            0.5f,  0.5f,  0.0f, 1.0f,1.0f,
            0.0f,  0.5f,  0.0f, 0.0f,1.0f,
    };
    GLushort  indices[] = {0,1,2,0,2,3};

    GLuint vboIds[2];

    GLint numIndices = 6;
    GLint numVertices = 4;
    GLint vtxStride = (5)*sizeof(GLfloat);
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



    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0);



    //return;

    //LOGE("ancho = %d, alto = %d",width, height);
    //glClearColor(100, 0, 0, 1);
    //glClear(GL_COLOR_BUFFER_BIT);
    //init();
    eglSwapBuffers(display, surface);

    glDeleteBuffers(2, vboIds);
}

#endif //ANDROMEDA_FRAME_H
