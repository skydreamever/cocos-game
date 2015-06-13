//
//  Block.cpp
//  
//
//  Created by 孙龙霄 on 6/12/15.
//
//

#include "Block.h"

bool Block::init(){
    Sprite::init();
    
    Size boxSize = Size(rand()%20+5,rand()%30+10);
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    setPhysicsBody(PhysicsBody::createBox(boxSize));
    getPhysicsBody()->setDynamic(false);
    getPhysicsBody()->setContactTestBitmask(1);
    setTextureRect(Rect(0, 0, boxSize.width, boxSize.height));
    setColor(Color3B(0, 0, 0));
    setContentSize(boxSize);
    
    setPositionX(visibleSize.width);
    scheduleUpdate();
    
    
    
    
    return true;
}



void Block::update(float dt){
    
    this->setPositionX(getPositionX() - 2);
    
    
    if (getPositionX()<0) {
        unscheduleUpdate();
        removeFromParent();
    }
    
    
}