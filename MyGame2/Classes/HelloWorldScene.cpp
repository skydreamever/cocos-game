#include "HelloWorldScene.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    //设置menu 退出 按钮
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    Size winSize=Director::getInstance()->getWinSize();

    
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    closeItem->setPosition(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                 origin.y + closeItem->getContentSize().height/2);
    
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu,1);
    
    //预加载图片和音乐
    PreloadMusicAndPicture();
    
    
    //设置背景色
    auto background = Sprite::create("ui/shoot_background/background.png");
    background->setPosition(visibleSize.width /2, visibleSize.height / 2);
    this->addChild(background);
    
    //设置标题
    
    auto copyRight = Sprite::createWithSpriteFrameName("shoot_copyright.png");
    //相当于auto copyRight = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("shoot_copyright.png"));
    copyRight->setAnchorPoint(Point(0.5, 0)); // 描点
    copyRight->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
    this->addChild(copyRight);
    
    //加入加载元素
    auto loading = Sprite::createWithSpriteFrameName("game_loading1.png");
    loading->setAnchorPoint(Point(0.5,1));
    loading->setPosition(visibleSize.width / 2,visibleSize.height / 2);
    this->addChild(loading);
    
    //设置飞行动画帧
    Animation *animation = Animation::create();
    animation->setDelayPerUnit(0.2f);//每一帧间隔时间
    animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_loading1.png"));
    animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_loading2.png"));
    animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_loading3.png"));
    animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_loading4.png"));
    
    //创建动画
    Animate *animate = Animate::create(animation);
    Repeat *repeat = Repeat::create(animate, 3);//重复动画三次
    CallFuncN *repeatdone = CallFuncN::create(CC_CALLBACK_1(HelloWorld::loadingDone, this));
    Sequence *sequence = Sequence::create(repeat, repeatdone, NULL);
    loading->runAction(sequence);
    
    
    this->setKeyboardEnabled(true);//监听键盘，支持android
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::PreloadMusicAndPicture(){
    
    //png加入全局cache中 plist存储了
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui/shoot_background.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui/shoot.plist");
    
    // 音效
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/background-music1.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/bullet.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/enemy1_down.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/enemy2_down.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/enemy3_down.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/game_over.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/get_bomb.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/get_double_laser.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/use_bomb.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/big_spaceship_flying.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/achievement.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/out_porp.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/button.mp3");
    
    // 背景音乐
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/game_music.mp3",true);
    
}

void HelloWorld::loadingDone( Node* pNode ){

    auto scene = GameLayer::createScene();
    TransitionCrossFade *pAnimateScene = TransitionCrossFade::create(1, scene);
    Director::getInstance()->replaceScene(pAnimateScene);
}