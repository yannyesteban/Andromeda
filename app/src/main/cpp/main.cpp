//
// Created by yanny on 16/12/2019.
//



/*
 *
 *
 * Forward declaration

    A declaration of the following form
    struct name ;
 * hides any previously declared meaning for the name name in the tag name space and declares name as a new struct name in current scope, which will be defined later. Until the definition appears, this struct name has incomplete type.

This allows structs that refer to each other:
*/
 struct prueba ;

#include <android/log.h>
#include "Log.h"
#include "cc.h"
#include <android_native_app_glue.h>
#include <android/asset_manager.h>
#include <EGL/egl.h>
#include <GLES/gl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <png.h>
#include <pngconf.h>
#include "loadpng.h"
#include <jni.h>
#include "types.h"
#include "ShadersManager.h"
#include "Texture2D.h"
#include "Sprite.h"
#include "SpriteText.h"
#include "Frame.h"
#include "EventEngine.h"
#include "Application.h"
#include "Rinconada.h"
#include <NDKHelper.h>

#include <sys/socket.h>
#include <error.h>

int suma(int a, int b){
    _LOGE("AInputEvent ONE");
    return a+b;
}

int resta(int a, int b){
    _LOGE("AInputEvent TWO");
    return a-b;
}

int initDisplay();
int closeDisplay();
void draw_frame();

EGLSurface surface;
EGLContext context;
EGLDisplay display;
int32_t width;
int32_t height;
int band = 0;

struct android_app* app;

void handleCmd(android_app* app, int32_t cmd){
    struct engine* engine = (struct engine*)app->userData;
    _LOGE("ActivityLoop -> %d ", engine->width );
    //Windows& windows = *(Windows*)app->userData;
    switch (cmd) {
        case APP_CMD_SAVE_STATE:
            break;
        case APP_CMD_INIT_WINDOW:
            // The window is being shown, get it ready.
            if (app->window != nullptr) {
                _LOGE("APP_CMD_INIT_WINDOW***");
                //windows.initDisplay();
                initDisplay();
                //windows.init();
                band = 1;
                draw_frame();

            }
            break;
        case APP_CMD_TERM_WINDOW:
            _LOGE("APP_CMD_TERM_WINDOW***");
            // The window is being hidden or closed, clean it up.
            closeDisplay();
            break;
        case APP_CMD_LOST_FOCUS:
            _LOGE("APP_CMD_LOST_FOCUS***");
            draw_frame();
            break;
        default:
            break;
    }
}


int32_t handleInput(android_app* app, AInputEvent* event){


    struct engine* eng = (struct engine*)app->userData;

    if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {
        _LOGE("AInputEvent II");
        //EventEngine ee = EventEngine();
        eng->Event.process(event);

        return 1;
    }

    return 0;

    //ndk_helper::DragDetector drag;
    //ndk_helper::GESTURE_STATE xxx = drag.Detect(event);
    //ndk_helper::Vec2 v2;
    //drag.GetPointer(v2);
    //v2.Dump();
    //LOGI("iii %d", v2.);
   // _LOGI("gesture xxx %d", xxx);

    //Windows & windows = *(Windows*)app->userData;
    if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {

        ndk_helper::GESTURE_STATE doubleTapState = eng->doubletap_detector_.Detect(event);
        ndk_helper::GESTURE_STATE dragState = eng->drag_detector_.Detect(event);
        ndk_helper::GESTURE_STATE pinchState = eng->pinch_detector_.Detect(event);

        // Double tap detector has a priority over other detectors
        if (doubleTapState == ndk_helper::GESTURE_STATE_ACTION) {
            // Detect double tap
            _LOGE("GESTURE doubleTapState");
            eng->tap_camera_.Reset(true);
        } else {
            // Handle drag state
            if (dragState & ndk_helper::GESTURE_STATE_START) {
                _LOGE("GESTURE start dragging");

                // Otherwise, start dragging
                ndk_helper::Vec2 v;
                eng->drag_detector_.GetPointer(v);
                //eng->TransformPosition(v);
                eng->tap_camera_.BeginDrag(v);
            } else if (dragState & ndk_helper::GESTURE_STATE_MOVE) {
                _LOGE("GESTURE GESTURE_STATE_MOVE");

                ndk_helper::Vec2 v;
                eng->drag_detector_.GetPointer(v);
                //eng->TransformPosition(v);
                eng->tap_camera_.Drag(v);
            } else if (dragState & ndk_helper::GESTURE_STATE_END) {
                _LOGE("GESTURE start end");
                eng->tap_camera_.EndDrag();
            }

            // Handle pinch state
            if (pinchState & ndk_helper::GESTURE_STATE_START) {
                _LOGE("GESTURE Handle pinch state");

                // Start new pinch
                ndk_helper::Vec2 v1;
                ndk_helper::Vec2 v2;
                eng->pinch_detector_.GetPointers(v1, v2);
                //eng->TransformPosition(v1);
                //eng->TransformPosition(v2);
                eng->tap_camera_.BeginPinch(v1, v2);
            } else if (pinchState & ndk_helper::GESTURE_STATE_MOVE) {
                // Multi touch
                // Start new pinch
                ndk_helper::Vec2 v1;
                ndk_helper::Vec2 v2;
                eng->pinch_detector_.GetPointers(v1, v2);
                //eng->TransformPosition(v1);
                //eng->TransformPosition(v2);
                eng->tap_camera_.Pinch(v1, v2);
            }
        }
        int32_t touchX;
        int32_t touchY;
        //windows.touchX = AMotionEvent_getX(event, 0);
        //windows.touchY = AMotionEvent_getY(event, 0);

        touchX = AMotionEvent_getX(event, 0);
        touchY = AMotionEvent_getY(event, 0);

        _LOGE("TOCA AQUI x %d\ty %d\n",touchX, touchY);
        static GLushort mode = 0;
        return 1;
    }
    return 0;
}


int ActivityLoop() {
// Read all pending events.
    //int  eng = *(int*)app->userData;


    while (true) {
        int ident;
        int events;
        struct android_poll_source* source;

        while ((ident=ALooper_pollAll(0, NULL, &events, (void**)&source)) >= 0) {

            // Process this event.
            if (source != NULL) {
                _LOGE("ActivityLoop source");
                //initDisplay();
                source->process(app, source);
                _LOGE("ActivityLoop source2");
            }

            // Check if we are exiting.
            if (app->destroyRequested != 0) {
                _LOGE("ActivityLoop closeDisplay()");
                closeDisplay();
                return 0;
            }
        }

        // Draw the current frame
        if(band == 1){
            _LOGE("ActivityLoop Error");
            draw_frame();
        }

    }
    //return 0;
}





int initDisplay() {
// Setup OpenGL ES 2
    // http://stackoverflow.com/questions/11478957/how-do-i-create-an-opengl-es-2-context-in-a-native-activity
    _LOGE("initDisplay()");
    const EGLint attribs[] = {
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT, //important
            EGL_BLUE_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_RED_SIZE, 8,
            EGL_NONE
    };

    EGLint attribList[] =
            {
                    EGL_CONTEXT_CLIENT_VERSION, 2,
                    EGL_NONE
            };

    EGLint w, h, dummy, format;
    EGLint numConfigs;
    EGLConfig config;




    display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

    eglInitialize(display, 0, 0);
    _LOGE("initDisplay(2)");
    /* Here, the application chooses the configuration it desires. In this
     * sample, we have a very simplified selection process, where we pick
     * the first EGLConfig that matches our criteria */
    eglChooseConfig(display, attribs, &config, 1, &numConfigs);
    _LOGE("initDisplay(3)");
    /* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
     * guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
     * As soon as we picked a EGLConfig, we can safely reconfigure the
     * ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */
    eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);
    _LOGE("initDisplay(4)");
    ANativeWindow_setBuffersGeometry(app->window, 0, 0, format);
    _LOGE("initDisplay(5)");
    surface = eglCreateWindowSurface(display, config, app->window, NULL);
    _LOGE("initDisplay(6)");
    context = eglCreateContext(display, config, NULL, attribList);
    _LOGE("initDisplay(7)");
    if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE) {
        _LOGE("Unable to eglMakeCurrent");
        return -1;
    }
    _LOGE("initDisplay(8)");
    // Grab the width and height of the surface
    eglQuerySurface(display, surface, EGL_WIDTH, &width);
    eglQuerySurface(display, surface, EGL_HEIGHT, &height);

    struct engine* engine = (struct engine*)app->userData;
    engine->width = width;
    engine->height = height;
    engine->Event.screenWidth = width;
    engine->Event.screenHeight = height;

    // Initialize GL state.
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
    glEnable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    //glViewport(100, 100, width, height);
    glViewport(0, 0, width, height);
    //glViewport(100, 100, 200, 200);
    Main(app);
    return 0;
}
int closeDisplay() {
    _LOGE("closeDisplay");
    if (display != EGL_NO_DISPLAY) {
        eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if (context != EGL_NO_CONTEXT) {
            eglDestroyContext(display, context);
        }
        if (surface != EGL_NO_SURFACE) {
            eglDestroySurface(display, surface);
        }
        eglTerminate(display);
    }
    display = EGL_NO_DISPLAY;
    context = EGL_NO_CONTEXT;
    surface = EGL_NO_SURFACE;
    //LOGE("BYE!!!!!!!!!!!!!!!!");
    band = 0;
    return 1;
}

void draw_frame() {

    Frame(app, display, surface);

    return;
    _LOGE("draw_frame");
    // No display.
    if (display == NULL) {
        _LOGE("************************ CLOSE");
        return;
    }

    //glViewport(0, 0, 400,400);
    glClearColor(1.0f,0.1f,0.0f, 1);


    //glEnable(GL_DEPTH_TEST);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glDepthMask(GL_FALSE);
    //glDepthFunc(GL_ALWAYS);

    //return;

    //LOGE("ancho = %d, alto = %d",width, height);
    //glClearColor(100, 0, 0, 1);
    //glClear(GL_COLOR_BUFFER_BIT);
    //init();
    eglSwapBuffers(display, surface);




}


void android_main(struct android_app* app1) {

    Rinconada V = Rinconada(app1);
    V.iniApp();
    //V.init();

    return;



    struct engine eng;
    app = app1;
    //memset(&eng, 0, sizeof(engine));

    _LOGE("HOLA MUNDO");
    //const char* suma = "yanny";
    eng.Event = EventEngine();

    Button::Event = &eng.Event;
    iButton::Event = &eng.Event;


    /*
    Button *b2 = new Button(0,400, 300, 300);
    b2->AttachEvent("click", suma);

    Button *b = new Button(0,0, 300, 300);
    b->AttachEvent("click", resta);
    */

    app1->userData = &eng;
    app1->onAppCmd = handleCmd;
    app1->onInputEvent = handleInput;


    //eng.app = app;
    //Init(app);
    ActivityLoop();
    return;
    while (true) {
        int ident;
        int events;
        struct android_poll_source* source;

        while ((ident=ALooper_pollAll(0, NULL, &events, (void**)&source)) >= 0) {

            // Process this event.
            if (source != NULL) {
                _LOGE("ActivityLoop source");
                //initDisplay();
                source->process(app, source);
                _LOGE("ActivityLoop source2");
            }

            // Check if we are exiting.
            if (app->destroyRequested != 0) {
                _LOGE("ActivityLoop closeDisplay()");
                closeDisplay();

                return;
            }
        }

        // Draw the current frame
        if(band == 1){
            _LOGE("ActivityLoop Ok");
            draw_frame();
        }

    }

}