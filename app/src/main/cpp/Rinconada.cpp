//
// Created by yanny on 6/1/2020.
//

#include "Rinconada.h"
#include "iEvent.h"
#include "Sprite2D.h"
#include "Button2D.h"
#include "Race.h"

void myCall3(ElemEvent event){
    sButton *s = (sButton*)event.context;




    _LOGE("AInputEvent sButton Reset III: %f, %f, width:%f", event.x, event.y,s->width);
    _LOGE("AInputEvent sButton Reset III: name %s", s->getName());

}

Rinconada::Rinconada(struct android_app *app) : Application(app),SSystem(app) {
    _LOGE("xxxxx000");
}

void Rinconada::init() {
    //Application::init();

    Asset *s1 = new Asset("sounds/airplane.wav");
    //Asset * s2 = new Asset("sounds/airplane.mp3");
    SSystem.registerSound(s1);
    //SSystem.registerSound(s2);

     if(SSystem.start()){
        _LOGE("SSystem April 2020");
    }
    //Asset mBGM("sounds/piano.mp3");
    //SSystem.playBGM(mBGM);
    //SSystem.playSound(s1);
    Race * R = new Race();
    R->setCompetitor(7);

    scene = R;

    R->init();
    //SSystem.playSound(s1);
    _LOGE("xxxxx111");


   //Sprite2D *S2 = new Sprite2D("png/horse2.png", 0.6f, 1.2f);
    //S->setPos(-3.0, -6.0);

    //S = new Sprite("png/barcelona.png");
/*
    Button2D *b1 = new Button2D(1.0, 1.0);
    b1->setColor({1.0,1.0,0.0,1.0});
    b1->setPos(-0.5,-3);
    b1->setName("start");

    b1->AttachEvent("click", [](ElemEvent event) -> void {
        sButton *s = (sButton*)event.context;
        _LOGE("AInputEvent sButton Reset II: %f, %f", event.x, event.y);
    });
*/
    //S->init();
    //scene.add(S);
    //scene.add(S2);
    //scene.add(b1);
}

int Rinconada::play() {

    _LOGE("xxxxx");


    //glClearColor(1.0f,0.354f,0.2f, 1);
    glClearColor(0.2f,0.2f,0.2f, 1);    //glClearColor((GLfloat)178/255,(GLfloat)240/255,(GLfloat)255/255, 1);
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
    scene->render(MVP);

    //S->Render(MVP);
    swap();
    //S->end();
    scene->end();
    return 1;
    //return Application::play();
}

void Rinconada::terminate() {}

void Rinconada::getMVP() {
    _LOGE("xxxxx2");
    glm::mat4 projection;
    projection = glm::ortho(-4.0f, 4.0f, -4.0f, 4.0f, -10.0f, 10.0f);
    // Camera matrix
    glm::mat4 View       = glm::lookAt(
            glm::vec3(0,0,5), // Camera is at (4,3,-3), in World Space
            glm::vec3(0,0,0), // and looks at the origin
            glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );
    // Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 Model      = glm::mat4(1.0f);
    Model = glm::scale(Model,glm::vec3(1.0f * aspectX, 1.0f * aspectY, 1.0f));

    static GLfloat dd= 0;

    if(dd>360){
        dd = 0;
    }
    dd=dd+2.0;
    float radians = dd;
    Model = glm::rotate(Model,glm::radians(360-dd),glm::vec3(1.0,0.0,0.0));
    Model = glm::rotate(Model,glm::radians(radians),glm::vec3(0.0,1.0,1.0));
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


