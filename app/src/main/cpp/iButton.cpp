//
// Created by Yanny on 3/1/2020.
//

#include "iButton.h"
#include "Log.h"

EventEngine * iButton::Event = nullptr;
iButton::iButton() {

}

iButton::~iButton() {

}

void iButton::AttachEvent(const char *name, void (*callFunction)(float, float)) {

    call = callFunction;
    //iButton *X = new iButton();
   // Event->is(X);
    //iButton *x = new iButton(2.0,2.0);

   Event->AttachEvent(this, name);

}

void iButton::AttachEvent(const char *name, void (*callFunction)(ElemEvent)) {
    callEvent = callFunction;
    //iButton *X = new iButton();
    // Event->is(X);
    //iButton *x = new iButton(2.0,2.0);

    Event->AttachEvent(this, name);
}


/*
void iButton::isIn(float a, float b) {

}
*/


