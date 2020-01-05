//
// Created by Yanny on 3/1/2020.
//

#ifndef ANDROMEDA_IOBJECT_H
#define ANDROMEDA_IOBJECT_H


class iObject {
public:
    iObject();
    virtual ~iObject();
    virtual void init()=0;
    virtual void end()=0;
    virtual void render()=0;

private:
    bool visible = true;
    float posX;
    float posY;
    float posZ;

    float width;
    float heigt;
    float depth;

};


#endif //ANDROMEDA_IOBJECT_H
