//
//  GameOverScene.cpp
//  
//
//  Created by 孙龙霄 on 6/13/15.
//
//

#include "GameOverScene.h"



bool GameOver::init(){
    LayerColor::initWithColor(Color4B::WHITE);
    
    visibleSize = Director::getInstance()->getVisibleSize();
    
    auto label = Label::create();
    label->setString("Game Over");
    label->setSystemFontSize(40);
    label->setColor(Color3B::BLACK);
    addChild(label);
    label->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    
    
    
    return true;
}

Scene* GameOver::createScene(){
    auto scene = Scene::create();
    
    auto layer = GameOver::create();
    scene->addChild(layer);
    
    return scene;
}
