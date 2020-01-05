//
// Created by Yanny on 29/12/2019.
//

#ifndef ANDROMEDA_GAMEENGINE_H
#define ANDROMEDA_GAMEENGINE_H


class GameEngine {
public:
    virtual void play();
    virtual void pause();
    virtual void stop();


    virtual void render();

private:
    int mPlayers[100];
    int nPlayes = 0;
};


#endif //ANDROMEDA_GAMEENGINE_H
