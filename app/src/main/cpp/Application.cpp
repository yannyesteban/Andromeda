//
// Created by yanny on 6/1/2020.
//

#include "Application.h"
#include "Log.h"
#include "EventEngine.h"
#include "iButton.h"

GLfloat Application::XAspect = 1.0;
GLfloat Application::YAspect = 1.0;


//template <class T>
void Application::handleCmd(android_app *app, int32_t cmd) {

    _LOGE("xxx");
    auto* engine = (Application*)app->userData;
    //Windows& windows = *(Windows*)app->userData;
    switch (cmd) {
        case APP_CMD_SAVE_STATE:
            break;
        case APP_CMD_INIT_WINDOW:
            // The window is being shown, get it ready.
            if (app->window != nullptr) {
                _LOGE("APP_CMD_INIT_WINDOW***");
                engine->displayInit();
                engine->_focus = true;
                engine->init();
                engine->play();
            }
            break;
        case APP_CMD_TERM_WINDOW:
            // The window is being hidden or closed, clean it up.
            engine->_focus = false;
            engine->displayClose();
            break;
        case APP_CMD_STOP:
            break;
        case APP_CMD_LOST_FOCUS:
            engine->_focus = false;
            engine->play();
            break;
        case APP_CMD_CONFIG_CHANGED:
            if (app->window != NULL){
                int w= ANativeWindow_getWidth(app->window);

                _LOGE("APP_CMD_CONFIG_CHANGED %d", w);
                engine->log("APP_CMD_CONFIG_CHANGED");
            }

            break;
        case APP_CMD_LOW_MEMORY:
            // Free up GL resources
            //eng->TrimMemory();
            break;
        default:
            break;
    }
}

//template <class T>
int32_t Application::handleInput(android_app *app, AInputEvent *event) {

    auto * engine = (Application*)app->userData;

    if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {
        engine->systemEvent.process(event);
        return 1;
    }

    return 0;
}

void Application::init() {

    AConfiguration* _config = AConfiguration_new();
    if (_config != NULL){
        AConfiguration_fromAssetManager(_config,
                                        _app->activity->assetManager);
        int32_t result;
        char i18NBuffer[] = "__";
        static const char* orientation[] = {
                "Unknown", "Portrait", "Landscape", "Square"
        };
        static const char* screenSize[] = {
                "Unknown", "Small", "Normal", "Large", "X-Large"
        };
        static const char* screenLong[] = {
                "Unknown", "No", "Yes"
        };
        //AConfiguration_fromAssetManager(_config, _app->activity->assetManager);

        result = AConfiguration_getOrientation(_config);
        _LOGE("Orientation : %s (%d)", orientation[result], result);

        result = AConfiguration_getScreenSize(_config);
        _LOGE("Orientation Screen Size : %s (%d)", screenSize[result], result);
        result = AConfiguration_getScreenLong(_config);
        _LOGE("Orientation Long Screen : %s (%d)", screenLong[result], result);
        AConfiguration_delete(_config);
    }
    _LOGE("xxxxxYANNY");
}

int Application::mainLoop() {
    //g_engine.InitSensors();
    // Read all pending events.

    while (true) {
        int ident;
        int events;
        struct android_poll_source* source;

        while ((ident=ALooper_pollAll(0, NULL, &events, (void**)&source)) >= 0) {
            // Process this event.
            if (source != NULL) {
                //g_engine.ProcessSensors(id);
                //initDisplay();
                source->process(_app, source);
            }

            // Check if we are exiting.
            if (_app->destroyRequested != 0) {
                displayClose();
                return 0;
            }
        }
        // Draw the current frame
        if(isReady()){
            play();
        }
    }
}

int Application::play() {
    glClearColor(1.0f,0.354f,0.2f, 1);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glDisable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    swap();
    _LOGE("PLAY2020");
    return 1;
}

Application::Application(struct android_app *app) {
    _app = app;

    Asset::setAssetManager(app->activity->assetManager);

    systemEvent = EventEngine();

    Button::Event = &systemEvent;
    iButton::Event = &systemEvent;

    //_app->userData = this;
    //_app->onAppCmd = handleCmd;
    //_app->onInputEvent = handleInput;
    //mainLoop();
    _LOGE("INIT");


}


int Application::displayInit() {
    // Setup OpenGL ES 2
    // http://stackoverflow.com/questions/11478957/how-do-i-create-an-opengl-es-2-context-in-a-native-activity

    const EGLint attribs[] = {
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT, //important
        EGL_BLUE_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_RED_SIZE, 8,
        EGL_NONE
    };

    EGLint attribList[] = {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE
    };

    EGLint w, h, dummy, format;
    EGLint numConfigs;
    EGLConfig config;

    display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

    eglInitialize(display, 0, 0);
    /* Here, the application chooses the configuration it desires. In this
     * sample, we have a very simplified selection process, where we pick
     * the first EGLConfig that matches our criteria */
    eglChooseConfig(display, attribs, &config, 1, &numConfigs);
    /* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
     * guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
     * As soon as we picked a EGLConfig, we can safely reconfigure the
     * ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */
    eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);

    ANativeWindow_setBuffersGeometry(_app->window, 0, 0, format);

    surface = eglCreateWindowSurface(display, config, _app->window, NULL);

    context = eglCreateContext(display, config, NULL, attribList);

    if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE) {
        _LOGE("Unable to eglMakeCurrent");
        return -1;
    }
    // Grab the width and height of the surface
    int32_t width;
    int32_t height;

    eglQuerySurface(display, surface, EGL_WIDTH, &width);
    eglQuerySurface(display, surface, EGL_HEIGHT, &height);
    _LOGE("xxxxx WIDTH %d, HEIGHT %d", width, height);


    // Initialize GL state.
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
    glEnable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    //glViewport(100, 100, width, height);
    glViewport(0, 0, width, height);
    //glViewport(100, 100, 200, 200);
    aspect = (float)width/(float)height;

    if(aspect > 1){
        aspectX = aspect;
    }else{
        aspectY = aspect;
    }

    XAspect = aspectX;
    XAspect = aspectY;

    screenWidth = width;
    screenHeight = height;
    /*
     *  assing width a our systemEvent
     *
     */
    systemEvent.screenWidth = width;
    systemEvent.screenHeight = height;

    return 0;
}

int Application::displayClose() {

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
    //band = 0;
    return 1;
}

bool Application::isReady() {
    return _focus;
}

void Application::swap() {
    eglSwapBuffers(display, surface);
}

void Application::iniApp() {
    _app->userData = this;
    _app->onAppCmd = Application::handleCmd;
    _app->onInputEvent = Application::handleInput;

    mainLoop();
}

int Application::ff() {
    return 6666;
}

void Application::log(const char *msg) {
    _LOGE("APP-> %s", msg);
}


