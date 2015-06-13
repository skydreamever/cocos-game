//
//  GameController.h
//  
//
//  Created by 孙龙霄 on 6/13/15.
//
//

#ifndef ____GameController__
#define ____GameController__

#include <stdio.h>
#include <cocos2d.h>
#include "Edge.h"
#include "Hero.h"
#include "Block.h"

USING_NS_CC;

class GameController:public Ref{
    
private:
    Layer *_layer;
    float _positionY;
    Size visblesize;
    int currentFrameIndex;
    int nextFrameCount;
    Edge *edge;
    Hero *hero;

private:
    void resetFrames();
    void addBlock();
    
public:
    virtual bool init(Layer *layer,float positionY);
    void onUpdate(float dt);
    bool hitTestPoint(Vec2 point);
    void onUserTouch();
    static GameController *create(Layer *layer,float position);
    
    
    
};

#endif /* defined(____GameController__) */
