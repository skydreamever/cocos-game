//
//  Block.h
//  
//
//  Created by 孙龙霄 on 6/12/15.
//
//

#ifndef ____Block__
#define ____Block__

#include <stdio.h>

#include <cocos2d.h>

USING_NS_CC;

class Block:public Sprite {
    
public:
    
    virtual bool init();
    virtual void update(float dt);
    CREATE_FUNC(Block);
    
    
    
};

#endif /* defined(____Block__) */
