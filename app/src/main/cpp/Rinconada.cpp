//
// Created by yanny on 6/1/2020.
//

#include "Rinconada.h"
#include "iEvent.h"

void myCall3(ElemEvent event){
    sButton *s = (sButton*)event.context;




    _LOGE("AInputEvent sButton Reset III: %f, %f, width:%f", event.x, event.y,s->width);
    _LOGE("AInputEvent sButton Reset III: name %s", s->getName());

}

Rinconada::Rinconada(struct android_app *app) : Application(app) {
    _LOGE("xxxxx000");
}

void Rinconada::init() {
    //Application::init();




    _LOGE("xxxxx111");
    Sprite *S = new Sprite("png/Rinconada.png", 4.0f, 3.0f);
    S->setPos(-2.0, -1.0);
    //S = new Sprite("png/barcelona.png");

    sButton *b1 = new sButton(1.0, 1.0);
    b1->setColor({1.0,1.0,0.0,1.0});
    b1->setPos(-0.5,-3);
    b1->setName("start");

    b1->AttachEvent("click", [](ElemEvent event) -> void {
        sButton *s = (sButton*)event.context;
        _LOGE("AInputEvent sButton Reset II: %f, %f", event.x, event.y);
    });

    //S->init();
    world.add(S);
    world.add(b1);
}

int Rinconada::play() {

    _LOGE("xxxxx");



    glClearColor(1.0f,0.354f,0.2f, 1);
    //glClearColor(0.0f,0.3f,0.4f, 1);
    glClearColor((GLfloat)178/255,(GLfloat)240/255,(GLfloat)255/255, 1);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glDisable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    getMVP();
    world.Render(MVP);

    //S->Render(MVP);
    swap();
    //S->end();
    world.End();
    return 1;
    //return Application::play();
}

void Rinconada::terminate() {}

void Rinconada::getMVP() {
    _LOGE("xxxxx2");
    glm::mat4 projection;
    projection = glm::ortho(-4.0f, 4.0f, -4.0f, 4.0f, -5.0f, 5.0f);
    // Camera matrix
    glm::mat4 View       = glm::lookAt(
            glm::vec3(0,0,5), // Camera is at (4,3,-3), in World Space
            glm::vec3(0,0,0), // and looks at the origin
            glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );
    // Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 Model      = glm::mat4(1.0f);
    Model = glm::scale(Model,glm::vec3(1.0f * aspectX, 1.0f * aspectY, 1.0f));
    //Model = glm::rotate(Model,glm::radians(radians),glm::vec3(0.0,0.0,1.0));
    float left = -0.0f, up = 0.0;
    Model = glm::translate(Model, glm::vec3(0+left,0+up,0));
    // Our ModelViewProjection : multiplication of our 3 matrices
    MVP        = projection * View * Model ; // Remember, matrix multiplication is the other way around
}

void Rinconada::iniApp() {
    //int h = Rinconada::ff();
    //_LOGE("ggg ff %d",h);


    _app->userData = this;
    _app->onAppCmd = handleCmd;
    _app->onInputEvent = handleInput;


    mainLoop();
}
