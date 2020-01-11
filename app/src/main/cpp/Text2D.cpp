//
// Created by yanny on 11/1/2020.
//

#include "Text2D.h"

Text2D::Text2D(std::string text, GLfloat scale) : text(text), scale(scale) {

}

Text2D::Text2D(const char *pFont) {

}

void Text2D::init() {
    FT_Library ft;
    FT_Face face;
    if (FT_Init_FreeType(&ft)){
        _LOGE("ERROR::FREETYPE: Could not init FreeType Library");
    }

    Asset *asset = new Asset("fonts/arial.ttf", AASSET_MODE_BUFFER);

    if(asset->open()){
        _LOGE("PNG - cool");
    }else{
        _LOGE("PNG - error 1");
    }

    /*
    AAsset* fontFile = AAssetManager_open(Asset::_assetManager, "fonts/arial.ttf", AASSET_MODE_BUFFER);
    off_t fontDataSize = AAsset_getLength(fontFile);
    FT_Byte* fontData = new FT_Byte[fontDataSize];
    AAsset_read(fontFile, fontData, (size_t) fontDataSize);
    AAsset_close(fontFile);
    */

    off_t fontDataSize = asset->getLength();
    FT_Byte* fontData = new FT_Byte[fontDataSize];
    asset->read(fontData, (size_t) fontDataSize);
    asset->close();
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
        iCharacter character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                face->glyph->advance.x
        };

        Characters.insert(std::pair<GLchar, iCharacter>(c, character));
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

    sh =  new ShadersManager();
    sh->setVS("shaders/font_vs.glsl");
    sh->setFS("shaders/font_fs.glsl");
    sh->addAttrib({0, 4, "vertex"});
    sh->Program();
    mMVPId = sh->getUniformLocation("projection");
    mTextColorId = glGetUniformLocation(sh->programObject, "textColor");
}

void Text2D::render(glm::mat4 MVP) {
    GLfloat x = posX;
    GLfloat y = posY;
    glUseProgram(sh->programObject);
    glUniform3f(mTextColorId, color.x, color.y, color.z);
    glUniformMatrix4fv(mMVPId, 1, GL_FALSE, &MVP[0][0]);

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

    for (c = text.begin(); c != text.end(); c++)
    {
        iCharacter ch = Characters[*c];

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

void Text2D::end() {
    glDeleteBuffers(2, vboIds);
}

void Text2D::setColor(glm::vec4 pColor) {
    color = pColor;

}

glm::vec4 Text2D::getColor() {
    return color;
}

void Text2D::setText(std::string pText) {
    text = pText;
}

std::string Text2D::getText() {
    return text;
}

void Text2D::setText(std::string pText, GLfloat pScale) {
    text = pText;
    scale = pScale;

}

Text2D::Text2D() {

}

void Text2D::setScale(GLfloat pScale) {
    scale = pScale;
}

GLfloat Text2D::getScale() {
    return scale;
}
