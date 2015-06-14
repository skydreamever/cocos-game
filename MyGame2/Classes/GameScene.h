//
//  GameScene.h
//  
//
//  Created by 孙龙霄 on 6/14/15.
//
//

#ifndef ____GameScene__
#define ____GameScene__

#include <stdio.h>
#include <cocos2d.h>
#include "PlaneLayer.h"
#include "BulletLayer.h"
#include "EnemyLayer.h"

USING_NS_CC;


enum EnBackground
{
    e_BackgroundA = 1, // 背景A
    e_BackgroundB = 2, // 背景B 与A交替滚动
};


class GameLayer : public Layer{
    
public:
    static Scene *createScene();
    virtual bool init();
    CREATE_FUNC(GameLayer);
    
public:
    void backgroundMove(float dt); // 背景移动
    void gameUpdate(float dt);     // 碰撞检测
    bool bulletCollisionEnemy(Sprite* pBullet);   // 子弹和敌机碰撞
    bool enemyCollisionPlane();    // 我机和敌机碰撞

    
private:
    PlaneLayer *planeLayer;
    BulletLayer *bulletLayer;
    EnemyLayer *enemyLayer;
    
};



#endif /* defined(____GameScene__) */
