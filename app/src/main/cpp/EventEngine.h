//
// Created by Yanny on 29/12/2019.
//

#ifndef ANDROMEDA_EVENTENGINE_H
#define ANDROMEDA_EVENTENGINE_H
#include <android/input.h>
#include <glm/glm.hpp>

struct Area{
    int x;
    int y;
    int width;
    int height;
};
class ElemEvent{
public:
    ElemEvent();
    Area area;
    int x;
    int y;
    int width;
    int height;
    int (*call)(int a, int b);
    glm::mat4 MVP;
};

class EventEngine {
public:
    ElemEvent * obj[100];

    int screenWidth;
    int screenHeight;
    EventEngine();
    ~EventEngine();
    void AttachEvent(Area area, const char * name, int (*call)(int a, int b), glm::mat4 MVP);
    void process(const AInputEvent* motion_event);
    int n = 0;
private:

};


class Button{
public:
    Button();
    Button(int x, int y, int width, int height);
    ~Button();
    void AttachEvent(const char * name, int (*call)(int a, int b), glm::mat4 MVP);

    int x;
    int y;
    int width;
    int height;
    static EventEngine * Event;

};


#endif //ANDROMEDA_EVENTENGINE_H
