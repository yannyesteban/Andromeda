//
// Created by yanny on 17/12/2019.
//


////////////////////
//https://arm-software.github.io/opengl-es-sdk-for-android/introduction_to_shaders.html
//

#include <ft2build.h>
#include FT_FREETYPE_H

#ifndef ANDROMEDA_FRAME_H
#define ANDROMEDA_FRAME_H
#include <iostream>
#include <string>

#include "Asset.h"
#include <glm/gtc/matrix_transform.hpp>
#include <gl3stub.h>
#include <freetype/ftglyph.h>
#include <freetype/ftstroke.h>

#include "Rectangle.h"

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
ShadersManager *m2;
Rectangle *R;
GLint text[5];
std::list<GLAttrib> lAttrib;
GLfloat fx = 1.0;
GLfloat fy = 1.0;
struct Character {
    GLuint     TextureID;  // ID handle of the glyph texture
    glm::ivec2 Size;       // Size of glyph
    glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
    FT_Pos     Advance;    // Offset to advance to next glyph
};
GLfloat aspect = 1.0f;
std::map<GLchar, Character> Characters;

void RenderText(ShadersManager *s, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
{
    GLuint programObject = s->programObject;

    // Activate corresponding render state



    //glBindVertexArray(VAO);

    // Iterate through all characters
    std::string::const_iterator c;

    glActiveTexture(GL_TEXTURE0);

    GLuint VBO;
    glGenBuffers(1, &VBO);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

    //glUseProgram(programObject);

    GLint vv = glGetUniformLocation(s->programObject, "textColor");


    //_LOGE("COLOR_X *** %d = %d > %f, %f, %f", programObject, vv, color.x, color.y, color.z);
    glUniform3f(vv, color.x, color.y, color.z);


    for (c = text.begin(); c != text.end(); c++)
    {

        Character ch = Characters[*c];

        GLfloat xpos = x + ch.Bearing.x * scale;
        GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;
        GLfloat w = ch.Size.x * scale;
        GLfloat h = ch.Size.y * scale;

        GLfloat vertices2[6*4] = {
                xpos,     ypos + h,   0.0, 0.0 ,
                xpos,     ypos,       0.0, 1.0 ,
                xpos + w, ypos,       1.0, 1.0 ,

                xpos,     ypos + h,   0.0, 0.0 ,
                xpos + w, ypos,       1.0, 1.0 ,
                xpos + w, ypos + h,   1.0, 0.0
        };
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*6*4, vertices2, GL_DYNAMIC_DRAW);

        // Render glyph texture over quad

        // Update content of VBO memory
        //glBindBuffer(GL_ARRAY_BUFFER, VBO);
        //glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        //glBindBuffer(GL_ARRAY_BUFFER, 0);
        // Render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
        //x += (ch.Advance / 64);
    }

    glDisableVertexAttribArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}



void Init0 (android_app* app){

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
void Frame1(android_app* app, EGLDisplay display, EGLSurface surface){
    glClearColor(1.0f,0.0f,0.5f, 1);
    //glClearColor(1.0f,1.0f,0.5f, 1);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glDepthMask(GL_FALSE);
    glDepthFunc(GL_ALWAYS);
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

void Init2 (android_app* app){
    Asset::setAssetManager(app->activity->assetManager);
    m =  new ShadersManager();
    m->mAssetManager = app->activity->assetManager;

    m2 =  new ShadersManager();
    m2->mAssetManager = app->activity->assetManager;

    FT_Library ft;
    FT_Face face;
    if (FT_Init_FreeType(&ft)){
        _LOGE("ERROR::FREETYPE: Could not init FreeType Library");
    }



    AAsset* fontFile = AAssetManager_open(app->activity->assetManager, "fonts/baily.ttf", AASSET_MODE_BUFFER);
    off_t fontDataSize = AAsset_getLength(fontFile);
    FT_Byte* fontData = new FT_Byte[fontDataSize];
    AAsset_read(fontFile, fontData, (size_t) fontDataSize);
    AAsset_close(fontFile);
    if (FT_New_Memory_Face(ft, (const FT_Byte*)fontData, (FT_Long)fontDataSize, 0, &face)) {
        _LOGE("ERROR::FREETYPE:Load memory failed");
    }

    FT_Set_Pixel_Sizes(face, 0, 48);
    if (FT_Load_Char(face, 'X', FT_LOAD_RENDER)){
        _LOGE("ERROR::FREETYPE:Failed to load Glyph");
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

    for (GLubyte c = 0; c < 128; c++)
    {
        // Load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            _LOGE("ERROR::FREETYPE:Failed to load Glyph");
            continue;
        }
        // Generate texture
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RGB

                ,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RGB

                ,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
        );
        // Set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // Now store character for later use
        Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                face->glyph->advance.x
        };

        //_LOGE("ERROR::FREETYPE: %s", c);
        Characters.insert(std::pair<GLchar, Character>(c, character));
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    /*
    FT_Face face;

    if (FT_New_Face(ft, "/assets/fonts/baily.ttf", 0, &face)){
        _LOGE("ERROR::FREETYPE: Failed to load font");
    }
     */







    m->setVS("shaders/b_vs.glsl");
    m->setFS("shaders/b_fs.glsl");


    lAttrib.push_back({0, 3, "aPosition"});
    lAttrib.push_back({1, 2, "aColor"});

    m->Program3(lAttrib);
    //lProgram[0] = m->programObject;

    text[0] = Texture(app->activity->assetManager, "png/mario.png");
    text[1] = Texture(app->activity->assetManager, "png/instagram.png");
    text[2] = Texture(app->activity->assetManager, "png/mickey.png");



}
void Frame2(android_app* app, EGLDisplay display, EGLSurface surface){


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



    glClearColor(1.0f,0.0f,0.1f, 1);
    //glClearColor(1.0f,1.0f,0.5f, 1);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
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

    GLuint MatrixID = glGetUniformLocation(programObject, "MVP");
    glUseProgram(programObject);

    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 4.0f, 0.1f, 100.0f);
    // Camera matrix
    glm::mat4 View       = glm::lookAt(
            glm::vec3(0,0,2), // Camera is at (4,3,-3), in World Space
            glm::vec3(0,0,0), // and looks at the origin
            glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );
    // Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 Model      = glm::mat4(1.0f);
    //LOGI("aspect1 %d", aspect);

    float aspect = 0.5;
    float radians = 180;
    Model = glm::scale(Model,glm::vec3(1.0f,1.0f*aspect,1.0f));
    Model = glm::rotate(Model,glm::radians(radians),glm::vec3(0.0,0.0,1.0));
    float left = -0.3f, up = 0.0f;
    Model = glm::translate(Model, glm::vec3(0+left,0+up,0));
    // Our ModelViewProjection : multiplication of our 3 matrices
    glm::mat4 MVP        = Projection * View * Model ; // Remember, matrix multiplication is the other way around

    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
    glBindTexture(GL_TEXTURE_2D, text[0]);
    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0);



    // Model matrix : an identity matrix (model will be at the origin)
    Model      = glm::mat4(1.0f);
    //LOGI("aspect1 %d", aspect);

    aspect = 0.5;
    radians = 170;
    Model = glm::scale(Model,glm::vec3(1.0f,1.0f*aspect,1.0f));
    Model = glm::rotate(Model,glm::radians(radians),glm::vec3(0.0,0.0,1.0));
    left = 0.1f, up = 0.0f;
    Model = glm::translate(Model, glm::vec3(0+left,0+up,-1.2));
    // Our ModelViewProjection : multiplication of our 3 matrices
    MVP        = Projection * View * Model ; // Remember, matrix multiplication is the other way around

    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
    glBindTexture(GL_TEXTURE_2D, text[1]);
    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0);



    eglSwapBuffers(display, surface);
    glDeleteBuffers(2, vboIds);
}


void Init (android_app* app){
    struct engine* engine = (struct engine*)app->userData;

    aspect = (float)engine->width/(float)engine->height;

    if(aspect > 1){
        fx = aspect;
    }else{
        fy = aspect;
    }

    _LOGE("aspect %f fx=%f, fy=%f", aspect, fx, fy);
    R = new Rectangle();

    Asset::setAssetManager(app->activity->assetManager);
    m =  new ShadersManager();
    m->mAssetManager = app->activity->assetManager;

    m2 =  new ShadersManager();
    m2->mAssetManager = app->activity->assetManager;

    FT_Library ft;
    FT_Face face;
    if (FT_Init_FreeType(&ft)){
        _LOGE("ERROR::FREETYPE: Could not init FreeType Library");
    }



    AAsset* fontFile = AAssetManager_open(app->activity->assetManager, "fonts/arial.ttf", AASSET_MODE_BUFFER);
    off_t fontDataSize = AAsset_getLength(fontFile);
    FT_Byte* fontData = new FT_Byte[fontDataSize];
    AAsset_read(fontFile, fontData, (size_t) fontDataSize);
    AAsset_close(fontFile);
    if (FT_New_Memory_Face(ft, (const FT_Byte*)fontData, (FT_Long)fontDataSize, 0, &face)) {
        _LOGE("ERROR::FREETYPE:Load memory failed");
    }

    //FT_Set_Char_Size(face, 0 )
    FT_Set_Pixel_Sizes(face, 0, 48*1);
    //FT_Set_Char_Size(face, 0, 16*64*2, 600, 600 );
    if (FT_Load_Char(face, 'X', FT_LOAD_RENDER)){
        _LOGE("ERROR::FREETYPE:Failed to load Glyph");
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction
/*
    // initialize stroker, so you can create outline font
    FT_Stroker stroker;
    FT_Stroker_New(ft, &stroker);
    FT_Stroker_Set(stroker, 4 * 64, FT_STROKER_LINECAP_ROUND, FT_STROKER_LINEJOIN_ROUND, 0);
  */

    for (GLubyte c = 0; c < 128; c++)
    {
        // Load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            _LOGE("ERROR::FREETYPE:Failed to load Glyph");
            continue;
        }
        // Generate texture
/*
        FT_UInt glyphIndex = FT_Get_Char_Index(face, c);
        FT_Load_Glyph(face, glyphIndex, FT_LOAD_DEFAULT);

        FT_Glyph glyph;
        FT_Get_Glyph(face->glyph, &glyph);
        FT_Glyph_StrokeBorder(&glyph, stroker, false, true);
        FT_Glyph_To_Bitmap(&glyph, FT_RENDER_MODE_NORMAL, nullptr, true);
        FT_BitmapGlyph bitmapGlyph = reinterpret_cast<FT_BitmapGlyph>(glyph);
*/
        //FT_Load_Glyph(face, FT_Get_Char_Index(face,c), FT_LOAD_TARGET_LIGHT);

        //FT_Glyph_To_Bitmap(&glyph, FT_RENDER_MODE_NORMAL, 0, 1);

        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_R8,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
        );
        // Set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



        // Now store character for later use
        Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                face->glyph->advance.x
        };

        //_LOGE("ERROR::FREETYPE: %s", c);
        Characters.insert(std::pair<GLchar, Character>(c, character));
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    /*
    FT_Face face;

    if (FT_New_Face(ft, "/assets/fonts/baily.ttf", 0, &face)){
        _LOGE("ERROR::FREETYPE: Failed to load font");
    }
     */

    m->setVS("shaders/font_vs.glsl");
    m->setFS("shaders/font_fs.glsl");


    lAttrib.push_back({0, 4, "vertex"});

    m->Program3(lAttrib);
    //lProgram[0] = m->programObject;

    //text[0] = Texture(app->activity->assetManager, "png/mario.png");
    //text[1] = Texture(app->activity->assetManager, "png/instagram.png");
    //text[2] = Texture(app->activity->assetManager, "png/mickey.png");


    R->init();
}
void Frame(android_app* app, EGLDisplay display, EGLSurface surface){





    //glClearColor(1.0f,0.2f,0.1f, 1);
    glClearColor(1.0f,1.0f,0.5f, 1);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT);

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

    GLuint MatrixID = glGetUniformLocation(programObject, "projection");
    glm::mat4 projection;
    projection = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, -5.0f, 5.0f);

    glm::mat4 projection1 = glm::ortho(
            0.0f,
            static_cast<float>(5),
            static_cast<float>(10),
            0.0f,
            0.0f,
            10.0f
    );

    glUseProgram(programObject);
    //GLuint MatrixID2 = glGetUniformLocation(programObject, "textColor");
    //LOGE("COLOR_XX *** %d = %d ", programObject, MatrixID2);
    //_LOGE("MatrixID2 %d", MatrixID2);
    //glUniform3f(MatrixID2, 0.8f, 0.0f, 0.5f);

    //glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 4.0f, 0.1f, 100.0f);
    //projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
    //Projection = glm::ortho(0.0f, 500.0f, 0.0f, 400.0f);

    // Camera matrix
    glm::mat4 View       = glm::lookAt(
            glm::vec3(0,0,3), // Camera is at (4,3,-3), in World Space
            glm::vec3(0,0,0), // and looks at the origin
            glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );
    // Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 Model      = glm::mat4(1.0f);
    //LOGI("aspect1 %d", aspect);

    float aspect = 0.5f;
    float radians = 0;
    Model = glm::scale(Model,glm::vec3(1.0f,1.0f*fy,1.0f));
    //Model = glm::rotate(Model,glm::radians(radians),glm::vec3(0.0,0.0,1.0));
    float left = -0.5f, up = 0.0;
    Model = glm::translate(Model, glm::vec3(0+left,0+up,0));
    // Our ModelViewProjection : multiplication of our 3 matrices
    glm::mat4 MVP        = projection * View * Model ; // Remember, matrix multiplication is the other way around
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

    /*
    GLint vv = glGetUniformLocation(programObject, "textColor");
    _LOGE("COLOR_X __ %d = %d > %f, %f, %f", programObject, vv, 0.2f, 0.0f, 0.5f);

    */


    static GLfloat ii = 0;
    ii = ii +0.001f;
    if(ii>=1.0f){
        ii=0.0f;
    }

    static GLfloat ee = 0;
    ee = ee +0.001f;
    if(ee>=1.0f){
        ee=0.0f;
    }
    std::string str= std::to_string(ee);

    RenderText(m, "Yanny "+str, -0.3f, -0.5f, 0.005, glm::vec3(0.1, ee, ii));
    R->Render(MVP);
    eglSwapBuffers(display, surface);
    R->end();

}
#endif //ANDROMEDA_FRAME_H
