//
// Created by yanny on 6/1/2020.
//

#ifndef ANDROMEDA_HORSE_H
#define ANDROMEDA_HORSE_H



#include "Sprite2D.h"
enum{
    STOP,
    RUNNING,
    END_RACE
};

struct InfoRace{
    GLfloat maxDistance;
    u_short status = 0;
};
class Horse: public Sprite2D  {
public:
    Horse();
    Horse(const char * pPath);
    Horse(const char * pPath, GLfloat w, GLfloat h);
    ~Horse(){};
    Horse(GLfloat w, GLfloat h):Sprite2D(nullptr, w, h){};
    InfoRace *info = nullptr;

    void update();
private:
    int mode = STOP;

};


#endif //ANDROMEDA_HORSE_H
