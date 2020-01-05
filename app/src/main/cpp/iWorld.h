//
// Created by Yanny on 3/1/2020.
//

#ifndef ANDROMEDA_IWORLD_H
#define ANDROMEDA_IWORLD_H


#include "iObject.h"

class iWorld {
public:
    void add(iObject *pObj);
private:
    iObject * mObject[100];

};


#endif //ANDROMEDA_IWORLD_H
