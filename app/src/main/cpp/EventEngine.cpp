//
// Created by Yanny on 29/12/2019.
//



#include "EventEngine.h"
#include "Log.h"
#include "iEvent.h"
//#include "iButton.h"

EventEngine * Button::Event = nullptr;

ElemEvent::ElemEvent() {}
Button::Button() {

}






void Button::AttachEvent(const char *name, int (*call)(int a, int b), glm::mat4 MVP) {

    Area aa = {x,y,width,height};
    Event->AttachEvent(aa, name,call, MVP);

}

Button::~Button() {

}

Button::Button(int xx, int yy, int pwidth, int pheight) {
    x =xx;
    y=yy;
    width=pwidth;
    height=pheight;

}

void EventEngine::process(const AInputEvent* event) {
    int32_t touchX;
    int32_t touchY;
    //windows.touchX = AMotionEvent_getX(event, 0);
    //windows.touchY = AMotionEvent_getY(event, 0);

    touchX = AMotionEvent_getX(event, 0);
    touchY = AMotionEvent_getY(event, 0);

    float x = (float)touchX/screenWidth;
    float y =  1-(float)touchY/screenHeight;


    for(int i =0;i<nButtons;i++){
        _LOGE("AInputEvent sButton Reset II: %f, %f", x, y);
        iButton *B = (iButton*)buttons[i];
        if(B->isIn(x, y)){
            ElemEvent ev;
            ev.x= x;
            ev.y= y;
            ev.index = i;
            ev.context = B->getContext();
            ev.target = B;
            //ev.dataUser = buttons[i]->_ctx;
            B->callEvent(ev);
            //B->call(x, y);
        }

    }

    return;
    _LOGE("AInputEvent Width %f", x);
    for(int i =0;i<n;i++){
        _LOGE("AInputEvent (i) %d",i);
        glm::vec4 V1 = glm::vec4(obj[i]->area.x,obj[i]->area.y,0.0f,1.0f);
        glm::vec4 V2 = glm::vec4(obj[i]->area.x+obj[i]->area.width,obj[i]->area.y+obj[i]->area.height,0.0f,1.0f);
        V1 = obj[i]->MVP * V1;
        V2 = obj[i]->MVP * V2;
        _LOGE("AInputEvent (1) C:(%f, %f), p1:(%f, %f), p2:(%f, %f)", x, y,  V1.x,V1.y, V2.x, V2.y);
        V1.x = V1.x/2 +0.5;
        V1.y = (V1.y/2 +0.5);
        V2.x = V2.x/2 +0.5;
        V2.y = (V2.y/2 +0.5);


        _LOGE("AInputEvent (2) C:(%f, %f), p1:(%f, %f), p2:(%f, %f)", x, y,  V1.x,V1.y, V2.x, V2.y);

        if(x>=V1.x && x<=V2.x && y>=V1.y && y<=V2.y){
            int s = obj[i]->call(1, 1);
            _LOGE("AInputEvent YESSS" );
        }else{
            _LOGE("AInputEvent NOPPP" );
        }

        /*
        if(touchX >= obj[i]->area.x && touchX <= obj[i]->area.x +obj[i]->area.width &&
                touchY >= obj[i]->area.y && touchY <= obj[i]->area.y +obj[i]->area.height){
            int s = obj[i]->call(obj[i]->area.x, obj[i]->area.y);
            _LOGE("AInputEvent CLICK" );
            _LOGE("AInputEvent touchX: %d, touchY: %d -> SUMA(%d)", obj[i]->area.x, obj[i]->area.y,s);

        }
        */


        //_LOGE("AInputEvent touchX: %d, touchY: %d -> SUMA(%d)", obj[i]->area.x, obj[i]->area.y,s);
    }

    _LOGE("AInputEvent touchX: %d, touchY: %d ", touchX, touchY);


}

EventEngine::EventEngine() {

}

EventEngine::~EventEngine() {

}

void EventEngine::AttachEvent(Area area, const char *name, int (*call)(int a, int b), glm::mat4 MVP) {
    _LOGE("AInputEvent area: %d, touchY: %d ", area.x, area.y);
    obj[n] = new ElemEvent();

    obj[n]->area = area;
    obj[n]->call = call;
    obj[n]->MVP = MVP;
    n++;
    _LOGE("AInputEvent n: %d", n);
}

void EventEngine::AttachEvent(iButton * iButton, const char *name) {


    //_LOGE("AInputEvent xxx: %d", nButtons);
    buttons[nButtons] = iButton;

    //obj[n]->area = area;
    //obj[n]->call = call;
   // buttons[nButtons]->MVP = MVP;
    nButtons++;


}

void EventEngine::is(iButton * B) {
    //_LOGE("AInputEvent U3: %d", B);
    nButtons++;
    //buttons[nButtons] = B;
    //b=B;
    //obj[n]->area = area;
    //obj[n]->call = call;
    // buttons[nButtons]->MVP = MVP;
    nButtons++;
}



