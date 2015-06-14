//
//  GameScene.cpp
//  
//
//  Created by 孙龙霄 on 6/14/15.
//
//

#include "GameScene.h"



Scene *GameLayer::createScene(){
    
    auto scene = Scene::create();
    auto layer = GameLayer::create();
    
    scene->addChild(layer);
    return scene;
}



bool GameLayer::init(){
    
    
    if (!Layer::init()) {
        return false;
    }
    
    //添加背景A
    auto backgroundA = Sprite::create("ui/shoot_background/background.png");
    backgroundA->setTag(e_BackgroundA);
    backgroundA->setAnchorPoint(Point::ZERO);
    backgroundA->setPosition(Point::ZERO);
    this->addChild(backgroundA);
    
    //添加背景B，与A交替滚动
    auto backgroundB = Sprite::create("ui/shoot_background/background.png");
    backgroundB->setTag(e_BackgroundB);
    backgroundB->setAnchorPoint(Point::ZERO);
    backgroundB->setPosition(Point::ZERO);
    this->addChild(backgroundB);
    
    //背景，每一帧都会调用
    this->schedule(schedule_selector(GameLayer::backgroundMove));

    //添加飞机
    planeLayer = PlaneLayer::create();
    this->addChild(planeLayer);
    
    //飞机子弹
    bulletLayer = BulletLayer::createWithPlane(planeLayer);
    this->addChild(bulletLayer);
    
    enemyLayer = EnemyLayer::create();
    this->addChild(enemyLayer);
    
    //检查现在的游戏状态
    this->schedule(schedule_selector(GameLayer::gameUpdate));

    
    
    return true;
}



void GameLayer::backgroundMove(float dt)
{
    Sprite *pBackgroundA = (Sprite*)this->getChildByTag(EnBackground::e_BackgroundA);
    Sprite *pBackgroundB = (Sprite*)this->getChildByTag(EnBackground::e_BackgroundB);
    
    
    pBackgroundA->setPositionY(pBackgroundA->getPositionY() - 2);
    pBackgroundB->setPositionY(pBackgroundA->getPositionY() + pBackgroundA->getContentSize().height);
    if (0 >= pBackgroundB->getPositionY())
    {
        pBackgroundA->setPositionY(0);
    }
}


void GameLayer::gameUpdate( float dt )
{
    bool bMoveButt = false;
    
    //这种for写法是C++ 11的新特性 子弹和敌机对碰
    for( auto& eButtle : bulletLayer->vecBullet)
    {
        Sprite* pBullet=(Sprite*)eButtle; // 获取子弹
        bMoveButt = bulletCollisionEnemy(pBullet);
        if (bMoveButt)
        {
            // 子弹删除了，无需再遍历
            return;
        }
    }
    
    // 敌机采用传说中的人肉炸弹，与我机同归于尽
    enemyCollisionPlane();
}


bool GameLayer::bulletCollisionEnemy( Sprite* pBullet )
{
    for( auto& eEnemy : enemyLayer->vecEnemy)
    {
        Enemy* pEnemySprite = (Enemy*)eEnemy;
        
        // 是否发生碰撞
        if (pBullet->boundingBox().intersectsRect(pEnemySprite->getBoundingBox()))
        {
            
            // 飞机只剩下一格生命值
            if (1 == pEnemySprite->getLife())
            {
                pEnemySprite->loseLife(); // 知道为什么这里也要loselife吗？你可以试着注释掉看看
                enemyLayer->blowupEnemy(pEnemySprite);
            }
            else
            {
                pEnemySprite->loseLife();
            }
            
            //删除子弹
            bulletLayer->removeBullet(pBullet);
            return true;
        }
    }
    
    return false;
}

bool GameLayer::enemyCollisionPlane()
{
    Sprite* pPlane = (Sprite*)planeLayer->getChildByTag(AIRPLANE);
    for( auto& eEnemy : enemyLayer->vecEnemy)
    {
        Enemy* pEnemySprite = (Enemy*)eEnemy;
        
        // 是否发生碰撞
        if (pPlane->boundingBox().intersectsRect(pEnemySprite->getBoundingBox()) && pEnemySprite->getLife() > 0)
        {
            this->unscheduleAllCallbacks();
            this->bulletLayer->StopBulletShoot();
            this->planeLayer->blowUp();
            return true;
        }
    }
    
    return false;
}
