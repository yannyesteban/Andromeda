//
// Created by yanny on 6/1/2020.
//

#ifndef ANDROMEDA_APPLICATION_H
#define ANDROMEDA_APPLICATION_H
#include <android/log.h>
#include "Log.h"

#include <android_native_app_glue.h>
#include <android/asset_manager.h>
#include <android/configuration.h>
#include <EGL/egl.h>
#include <GLES/gl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "Asset.h"
#include "EventEngine.h"
/*
template <class T>
void handleCmd(android_app* app, int32_t cmd);
template <class T>
int32_t handleInput(android_app* app, AInputEvent* event);
*/


class Application {
public:
    Application(struct android_app* app);
    virtual ~Application(){};
    //template<class T>
    virtual void iniApp();

    int mainLoop();
    int displayInit();
    int displayClose();
    virtual void init();
    virtual int play();
    virtual void terminate(){};
    bool isReady();
    EventEngine systemEvent;

    void swap();

    //void handleCmd(void * engine, android_app* app, int32_t cmd);
    //int32_t handleInput(void * engine, android_app* app, AInputEvent* event);

    //template <class T>
    static void handleCmd(android_app* app, int32_t cmd);
    //template <class T>
    static int32_t handleInput(android_app* app, AInputEvent* event);

    static int ff();

    void log(const char * msg);

    int32_t screenWidth;
    int32_t screenHeight;
    bool _focus =  false;
private:


    EGLSurface surface;
    EGLContext context;
    EGLDisplay display;

protected:
    struct android_app* _app;
    GLfloat aspect = 1.0f;
    GLfloat aspectX = 1.0f;
    GLfloat aspectY = 1.0f;

};


#endif //ANDROMEDA_APPLICATION_H
