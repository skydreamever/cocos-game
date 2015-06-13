//
//  Hero.h
//  
//
//  Created by 孙龙霄 on 6/12/15.
//
//

#ifndef ____Hero__
#define ____Hero__

#include <stdio.h>

#include <cocos2d.h>


USING_NS_CC;

class Hero:public Sprite {
    
public:
    virtual bool init();
    CREATE_FUNC(Hero);
};


#endif /* defined(____Hero__) */