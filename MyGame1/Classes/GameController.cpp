//
//  GameController.cpp
//  
//
//  Created by 孙龙霄 on 6/13/15.
//
//

#include "GameController.h"


GameController *GameController::create(cocos2d::Layer *layer, float position){
    auto _ins = new GameController();
    if (_ins && _ins->init(layer, position)) {
        _ins->autorelease();
        return _ins;
    }else{
        delete _ins;
        _ins = NULL;
        return NULL;
    }
}


bool GameController::init(cocos2d::Layer *layer, float positionY){

    _layer = layer;
    _positionY = positionY;
    
    visblesize = Director::getInstance()->getVisibleSize();

    
    edge = Edge::create();
    edge->setPosition(visblesize.width / 2, visblesize.height / 2 + positionY);
    edge->setContentSize(visblesize);
    layer->addChild(edge);
    
    auto ground = Sprite::create();
    ground->setColor(Color3B(0, 0, 0));
    ground->setTextureRect(Rect(0, 0, visblesize.width, 3));
    ground->setPosition(visblesize.width / 2,1.5+positionY);
    layer->addChild(ground);
    
    hero = Hero::create();
    hero->setPosition(50, hero->getContentSize().height / 2 + positionY + 20);
    layer->addChild(hero);
    
    resetFrames();
    
    
    return true;
}

void GameController::addBlock(){
    auto block = Block::create();
    _layer->addChild(block);
    block->setPositionY(block->getContentSize().height/2 + _positionY);
}

void GameController::resetFrames(){
    currentFrameIndex = 0;
    nextFrameCount = rand() % 120 + 100;
}

bool GameController::hitTestPoint(cocos2d::Vec2 point){
    
    return (edge->getBoundingBox().containsPoint(point));
    
}

void GameController::onUserTouch(){
    
    hero->getPhysicsBody()->setVelocity(Vec2(0,400));
    
    
}

void GameController::onUpdate(float dt) {
    
    currentFrameIndex++;
    if (currentFrameIndex>= nextFrameCount) {
        resetFrames();
        addBlock();
    }

}