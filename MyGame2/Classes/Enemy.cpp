//
//  Enemy.cpp
//  
//
//  Created by 孙龙霄 on 6/14/15.
//
//

#include "Enemy.h"


bool Enemy::init(){
    

    if (!Node::init())
    {
        return false;
    }
    
    return true;
}

void Enemy::setEnemyByType( EnemyType enType )
{
    switch (enType)
    {
        case Enemy1:
            pEnemySprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1.png"));
            nLife = ENEMY1_MAXLIFE;
            break;
        case Enemy2:
            pEnemySprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2.png"));
            nLife = ENEMY2_MAXLIFE;
            break;
        case Enemy3:
            pEnemySprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_n1.png"));
            nLife = ENEMY3_MAXLIFE;
            break;
        case Enemy4:
            pEnemySprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_n2.png"));
            nLife = ENEMY3_MAXLIFE;
            break;
        default:
            return;
            break;
    }
    
    this->addChild(pEnemySprite);
    Size visiualSize = Director::getInstance()->getVisibleSize();
    Size enemySize = pEnemySprite->getContentSize();
    
    int minX = enemySize.width / 2;
    int maxX = visiualSize.width - minX;

    
    int rangeX = maxX - minX;
    
    int actualX = (rand() % rangeX) + minX;
    
    this->setPosition(Point(actualX,visiualSize.height + enemySize.height / 2));
    
}


Sprite* Enemy::getSprite()
{
    return pEnemySprite;
}

int Enemy::getLife()
{
    return nLife;
}

void Enemy::loseLife()
{
    --nLife;
}

Rect Enemy::getBoundingBox()
{
    Rect rect=pEnemySprite->boundingBox();
    Point pos=this->convertToWorldSpace(rect.origin);
    Rect enemyRect(pos.x, pos.y, rect.size.width, rect.size.height);
    return enemyRect;
}
