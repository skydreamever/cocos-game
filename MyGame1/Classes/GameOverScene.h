//
//  GameOverScene.h
//  
//
//  Created by 孙龙霄 on 6/13/15.
//
//

#ifndef ____GameOverScene__
#define ____GameOverScene__

#include <stdio.h>
#include <cocos2d.h>
USING_NS_CC;



class GameOver:public LayerColor {
    
    
private:
    Size visibleSize;
    
public:
    virtual bool init();
    CREATE_FUNC(GameOver);
    
    static Scene* createScene();
};


#endif /* defined(____GameOverScene__) */
