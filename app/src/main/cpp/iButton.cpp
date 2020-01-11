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
    Event->AttachEvent(this, name);

}

void iButton::AttachEvent(const char *name, void (*callFunction)(ElemEvent)) {
    callEvent = callFunction;
    Event->AttachEvent(this, name);
}

