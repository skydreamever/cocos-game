//
//  BulletLayer.h
//  
//
//  Created by 孙龙霄 on 6/14/15.
//
//

#ifndef ____BulletLayer__
#define ____BulletLayer__

#include <stdio.h>
#include <cocos2d.h>
#include "PlaneLayer.h"

USING_NS_CC;


class BulletLayer : public Layer{
    
public:
    virtual bool initWithPlane(PlaneLayer *sharePlane);
    static BulletLayer *createWithPlane(PlaneLayer *sharePlane);
    
public:
    void BeginBulletShoot(float dt=0.0f);	// 开启子弹射击
    void StopBulletShoot();					// 停止子弹射击
    void addBullet(float dt);				// 添加子弹
    void removeBullet(Node* pNode);			// 移除子弹
    
public:
    Vector<Sprite*> vecBullet; // 如果没加USING_NS_CC; 则要写成cocos2d::Vector<Sprite*> vecBullet;
    PlaneLayer *sharePlane;

    
};



#endif /* defined(____BulletLayer__) */
