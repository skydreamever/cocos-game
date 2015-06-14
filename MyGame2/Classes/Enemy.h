//
//  Enemy.h
//  
//
//  Created by 孙龙霄 on 6/14/15.
//
//

#ifndef ____Enemy__
#define ____Enemy__

#include <stdio.h>
#include <cocos2d.h>


USING_NS_CC;

#pragma once

// 敌机生命值
const int ENEMY1_MAXLIFE=1;
const int ENEMY2_MAXLIFE=2;
const int ENEMY3_MAXLIFE=6;

// 敌机分数
const int ENEMY1_SCORE=1;
const int ENEMY2_SCORE=6;
const int ENEMY3_SCORE=30;

// 随着分数上去，游戏难度也随着提升
enum Level
{
    EASY,
    MIDDLE,
    HARD,
    MOREHARD,
};

// 随着分数上去，游戏难度也随着提升
enum EnemyType
{
    Enemy1 = 1,
    Enemy2,
    Enemy3,
    Enemy4,
};


class Enemy: public Node{
    
public:
    virtual bool init();
    CREATE_FUNC(Enemy);
    
public:
    void setEnemyByType(EnemyType enType);
    Sprite* getSprite();
    
    int getLife();
    void loseLife();
    Rect getBoundingBox();
    
private:
    Sprite *pEnemySprite;
    int nLife;
    
    
    
    
};

#endif /* defined(____Enemy__) */
