//
// Created by Yanny on 3/1/2020.
//

#ifndef ANDROMEDA_IBUTTON_H
#define ANDROMEDA_IBUTTON_H
#include <glm/glm.hpp>
#include "EventEngine.h"


class iButton{
public:
    iButton();
    virtual ~iButton();
    virtual bool isIn(float a, float b)=0;
    void (*call)(float a, float b);
    void (*callEvent)(ElemEvent Event);
    virtual void AttachEvent(const char * name, void (*call)(float x, float y));
    virtual void AttachEvent(const char * name, void (*call)(ElemEvent Event));
    virtual void bind(iButton *_context)=0;
    virtual iButton * getContext()=0;
    //glm::mat4 MVP;
    static EventEngine * Event;

   // iButton * context;

};


#endif //ANDROMEDA_IBUTTON_H
