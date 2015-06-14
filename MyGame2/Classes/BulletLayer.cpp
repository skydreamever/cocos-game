//
//  BulletLayer.cpp
//  
//
//  Created by 孙龙霄 on 6/14/15.
//
//

#include "BulletLayer.h"


BulletLayer* BulletLayer::createWithPlane(PlaneLayer *sharePlane){
    BulletLayer *pRet = new BulletLayer();
    if (pRet && pRet->initWithPlane(sharePlane)){
        pRet->autorelease();
        return pRet;
    }else {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}


bool BulletLayer::initWithPlane(PlaneLayer *sharePlane){
    
    if (!Layer::init()) {
        return false;
    }
        this->sharePlane = sharePlane;
    
    BeginBulletShoot();
    
    return true;
    
}


void BulletLayer::BeginBulletShoot( float dt )
{
    this->schedule(schedule_selector(BulletLayer::addBullet), 0.2f, kRepeatForever, dt);
}

void BulletLayer::StopBulletShoot()
{
    this->unschedule(schedule_selector(BulletLayer::addBullet));
}

void BulletLayer::addBullet(float dt){
    
    auto bullet = Sprite::createWithSpriteFrameName("bullet1.png");
    this->addChild(bullet);
    
    vecBullet.pushBack(bullet);
    
    //设置子弹的坐标
    Point planePos = sharePlane->getChildByTag(AIRPLANE)->getPosition();
    Size planeSize = sharePlane->getChildByTag(AIRPLANE)->getContentSize();
    Point bulletPos = Point(planePos.x,planePos.y + planeSize.height / 2);
    bullet->setPosition(bulletPos);
    
    //子弹飞行距离
    float flyLen = Director::getInstance()->getVisibleSize().height + bullet->getContentSize().height / 2 - bullet->getPosition().y;//允许子弹冲出窗口
    float flyVelocity = 320 / 1;
    float realFlyDuration = flyLen/flyVelocity; // 飞行时间
    auto actionMove = MoveTo::create(realFlyDuration,Point(bullet->getPosition().x,flyLen+bullet->getPosition().y));//子弹飞行的终点坐标
    auto actionDone = CallFuncN::create(CC_CALLBACK_1(BulletLayer::removeBullet, this));
    
    Sequence* sequence=Sequence::create(actionMove,actionDone,NULL);
    bullet->runAction(sequence);
    
    
}

void BulletLayer::removeBullet( Node* pNode )
{
    if (NULL == pNode)
    {
        return;
    }
    
    Sprite* bullet=(Sprite*)pNode;
    this->removeChild(bullet,true);
    vecBullet.eraseObject(bullet);
}

