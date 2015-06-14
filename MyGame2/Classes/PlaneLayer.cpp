//
//  PlaneLayer.cpp
//  
//
//  Created by 孙龙霄 on 6/14/15.
//
//

#include "PlaneLayer.h"


bool PlaneLayer::init(){
    
    if (!Layer::init()) {
        return false;
    }
    
    //飞机活着
    isAlive = true;
    
    //飞机
    Size visiualSize = Director::getInstance()->getVisibleSize();
    auto sprite = Sprite::create("ui/shoot/hero2.png");
    sprite->setPosition(visiualSize.width / 2,visiualSize.height / 2);
    sprite->setTag(AIRPLANE);
    this->addChild(sprite);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    
    //判断是否点击的是飞机
    listener->onTouchBegan = [=](Touch *t,Event *e){
        Point touchSpritePoint = sprite->convertTouchToNodeSpace(t);//触摸点
        Size s = sprite->getContentSize();
        Rect rect = Rect(0,0,s.width,s.height);//飞机的形状，这里之说以是0，0是因为touchSpritePoint的坐标点的原点也是从飞机的左下角开始计算的，而不是他的父视图
        if (rect.containsPoint(touchSpritePoint)) {
            return true;
        }
        return false;
    };
    
    //飞机随点击移动
    listener->onTouchMoved = [=](Touch* touch, Event *event){
        sprite->setPosition(sprite->getPosition() + touch->getDelta());//位置移动
    };

    //然而并没有什么卵用
    listener->onTouchEnded = [=](Touch* touch, Event* event){
    };
    
    //添加监听
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, sprite);
    
    this->schedule(schedule_selector(PlaneLayer::checkBorder));
    
    return true;
}


void PlaneLayer::checkBorder( float dt )
{
    //进行边界判断,不可超出屏幕
    Point location = this->getChildByTag(AIRPLANE)->getPosition();
    Size visiualSize=Director::getInstance()->getVisibleSize();  // 获取opengl视图窗口大小
    
    Size planeSize=this->getChildByTag(AIRPLANE)->getContentSize();  // 返回的就是这个矩形的大小,只是是逻辑尺寸, 而不是像素的
    if (location.x<planeSize.width/2)
    {
        location.x=planeSize.width/2;
    }
    if (location.x>visiualSize.width-planeSize.width/2)
    {
        location.x=visiualSize.width-planeSize.width/2;
    }
    if (location.y<planeSize.height/2)
    {
        location.y=planeSize.height/2;
    }
    if (location.y>visiualSize.height-planeSize.height/2)
    {
        location.y=visiualSize.height-planeSize.height/2;
    }  
    this->getChildByTag(AIRPLANE)->setPosition(location);  
}

void PlaneLayer::blowUp()
{
    if(isAlive)
    {
        isAlive=false; // 把飞机生命标识设置为死亡
        this->unscheduleAllCallbacks(); // 停止飞机的所有行动
        
        Animation* animation=Animation::create();
        animation->setDelayPerUnit(0.2f); // 下面4个图片切换 每张间隔0.2秒
        animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_blowup_n1.png")); // 数据
        animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_blowup_n2.png"));
        animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_blowup_n3.png"));
        animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_blowup_n4.png"));
        
        Animate* animate=Animate::create(animation);
        auto removePlane = CallFuncN::create(CC_CALLBACK_1(PlaneLayer::removePlane, this));// 移除飞机的回调函数

        Sequence* sequence=Sequence::create(animate,removePlane,NULL); // 当执行完动作，就移除掉飞机
        this->getChildByTag(AIRPLANE)->stopAllActions(); // 停止一切的飞机动作
        this->getChildByTag(AIRPLANE)->runAction(sequence); // 执行
    }
}

void PlaneLayer::removePlane(Node* pNode)
{
    this->removeChildByTag(AIRPLANE,true); // 移除飞机精灵 true子节点上的所有运行行为和回调将清理
//    Scene* pScene=GameOverLayer::createScene();
//    TransitionMoveInT* animateScene=TransitionMoveInT::create(0.8f, pScene);//新场景从上移入覆盖 用时0.8秒
//    Director::getInstance()->replaceScene(animateScene); // 替换场景
}


