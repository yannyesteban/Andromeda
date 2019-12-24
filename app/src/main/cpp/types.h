//
// Created by yanny on 1/8/2019.
//

#ifndef RINCONADA_TYPES_H
#define RINCONADA_TYPES_H
//#include <GLES/gl.h>
//#include <GLES2/gl2.h>

#include <string>
#include <glm/glm.hpp>

struct GMv6{
    glm::vec3 v;
    glm::vec3 c;
};
struct GMv8{
    glm::vec3 a;
    glm::vec3 b;
    glm::vec2 c;

};
struct GMv5{
    GLfloat x[5];
};
struct GLAttrib{
    GLushort index;
    GLushort size;
    std::string name;
};

struct engine {
    struct android_app* app;


    int animating;
    EGLDisplay display;
    EGLSurface surface;
    EGLContext context;
    int32_t width;
    int32_t width2;
    int32_t height;

};



#endif //RINCONADA_TYPES_H
