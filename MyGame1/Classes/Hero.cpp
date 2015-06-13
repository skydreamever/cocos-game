//
//  Hero.cpp
//  
//
//  Created by 孙龙霄 on 6/12/15.
//
//

#include "Hero.h"
#include "FlashTool.h"


bool Hero::init(){
    
    Sprite::init();
    
    Size heroSize = Size(44,53);

    
    runAction(RepeatForever::create(FlashTool::readJsonSpriteSheet("Hero.json", 0.2f)));
    
    setPhysicsBody(PhysicsBody::createBox(heroSize));
    getPhysicsBody()->setRotationEnable(false);
    getPhysicsBody()->setContactTestBitmask(1);
    setContentSize(heroSize);
        
    return true;
}
