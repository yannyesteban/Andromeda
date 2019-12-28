//
// Created by Yanny on 27/12/2019.
//

#ifndef ANDROMEDA_SPRITETEXT_H
#define ANDROMEDA_SPRITETEXT_H

#include <ft2build.h>
#include FT_FREETYPE_H

#include <EGL/egl.h>
#include <GLES/gl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <glm/glm.hpp>
#include <gl3stub.h>
#include "Texture2D.h"
#include "ShadersManager.h"
struct Character2 {
    GLuint     TextureID;  // ID handle of the glyph texture
    glm::ivec2 Size;       // Size of glyph
    glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
    FT_Pos     Advance;    // Offset to advance to next glyph
};


class SpriteText {


public:


    std::map<GLchar, Character2> Characters;
    const char * source = "";

    GLfloat width = 4.0f;
    GLfloat height = 1.0f;

    GLfloat posX = 0.0f;
    GLfloat posY = 0.0f;
    GLfloat posZ = 0.0f;
    GLfloat acc = 1.0f;
    ShadersManager *sh;

    SpriteText();
    SpriteText(const char * pPath):mPath(pPath){};
    SpriteText(const char * pPath, GLfloat w, GLfloat h):mPath(pPath),width(w), height(h){};
    SpriteText(GLfloat w, GLfloat h):width(w), height(h){};

    void init();
    void end();
    void setPos(GLfloat x, GLfloat y);

    void setPosX(GLfloat x);
    void setPosY(GLfloat y);
    void setPosZ(GLfloat z);

    GLfloat getPosX();
    GLfloat getPosY();
    GLfloat getPosZ();

    void setTexture(glm::vec4 pColor);
    void Render(glm::mat4 MVP, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);


private:
    GLuint vboIds[2];
    GLint mTexture;

const char * mPath = "";
};


#endif //ANDROMEDA_SPRITETEXT_H
