//
// Created by yanny on 11/1/2020.
//

#ifndef ANDROMEDA_TEXT2D_H
#define ANDROMEDA_TEXT2D_H
#include <ft2build.h>
#include FT_FREETYPE_H
#include <EGL/egl.h>
#include <GLES/gl.h>
#include <GLES2/gl2.h>
#include "Object3D.h"
#include "ShadersManager.h"

struct iCharacter {
    GLuint     TextureID;  // ID handle of the glyph texture
    glm::ivec2 Size;       // Size of glyph
    glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
    FT_Pos     Advance;    // Offset to advance to next glyph
};

class Text2D : public Object3D {
public:
    Text2D();
    Text2D(std::string text, GLfloat scale);
    Text2D(const char * pFont);
    virtual void init();
    virtual void render(glm::mat4 MVP);
    virtual void end();

    void setColor(glm::vec4 pColor);
    glm::vec4 getColor();
    void setText(std::string text);
    void setText(std::string text, GLfloat scale);

    std::string getText();

    void setScale(GLfloat scale);
    GLfloat getScale();

private:
    GLuint vboIds[2];
    GLint mTexture;
    GLint mMVPId;
    GLint mTextColorId;
    const char * font = "";
    ShadersManager *sh;
    std::map<GLchar, iCharacter> Characters;
    glm::vec4 color;
    std::string text;
    GLfloat scale;
};


#endif //ANDROMEDA_TEXT2D_H
