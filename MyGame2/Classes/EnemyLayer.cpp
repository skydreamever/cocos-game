//
//  EnemyLayer.cpp
//  
//
//  Created by 孙龙霄 on 6/14/15.
//
//

#include "EnemyLayer.h"

int EnemyLayer::m_score = 0;


bool EnemyLayer::init(){
    
    if (!Layer::init()) {
        return false;
    }
    
    Vector<SpriteFrame*> vecTemp;
    vecTemp.clear();
    
    //敌机1被打下来，下面是两种编写方式
    Animation* pAnimation1=Animation::create();
    pAnimation1->setDelayPerUnit(0.1f);//每一帧间隔时间
    pAnimation1->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down1.png"));
    pAnimation1->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down2.png"));
    pAnimation1->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down3.png"));
    pAnimation1->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down4.png"));
    
    AnimationCache::getInstance()->addAnimation(pAnimation1, "Enemy1Blowup");
    
  
    // 敌机2被打下来
    vecTemp.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_down1.png"));
    vecTemp.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_down2.png"));
    vecTemp.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_down3.png"));
    vecTemp.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_down4.png"));
    
    Animation *pAnimation2 = Animation::createWithSpriteFrames(vecTemp);
    pAnimation2->setDelayPerUnit(0.1f);
    AnimationCache::getInstance()->addAnimation(pAnimation2, "Enemy2Blowup");
    
    // 敌机3被打爆动作帧
    vecTemp.clear();
    vecTemp.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down1.png"));
    vecTemp.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down2.png"));
    vecTemp.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down3.png"));
    vecTemp.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down4.png"));
    vecTemp.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down5.png"));
    vecTemp.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down6.png"));
    
    Animation *pAnimation3 = Animation::createWithSpriteFrames(vecTemp);
    pAnimation3->setDelayPerUnit(0.1f);
    AnimationCache::getInstance()->addAnimation(pAnimation3, "Enemy3Blowup");
    
    //添加敌机
    this->schedule(schedule_selector(EnemyLayer::addEnemy1), 1.0f); // 每1秒出现一架敌机1
    this->schedule(schedule_selector(EnemyLayer::addEnemy2), 5.0f);
    this->schedule(schedule_selector(EnemyLayer::addEnemy3), 10.0f);

 
    // 分数菜单
    // 加入分数文本菜单
    scoreItem=Label::create();
    scoreItem->setString("0");
    scoreItem->setColor(Color3B(143,146,147));
    scoreItem->setAnchorPoint(Point(0,0.5));
    scoreItem->setPosition(Point(75,767)); // 这个是事先算出来的，为了放在暂停按钮旁边
    this->addChild(scoreItem);

    
    return true;
}




void EnemyLayer::addEnemy1( float dt )
{
    Enemy *pEnemySprite = Enemy::create();
    pEnemySprite->setEnemyByType(Enemy1);
    pEnemySprite->setTag(Enemy1);
    this->addChild(pEnemySprite);
    vecEnemy.pushBack(pEnemySprite);
    
    // 设置运动轨迹 以及到终点时调用的函数
    auto actionMove=MoveTo::create(3.0f,Point(pEnemySprite->getPositionX(), 0 - pEnemySprite->getSprite()->getContentSize().height/2));
    auto actionDone = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::removeEnemy, this));
    Sequence* sequence=Sequence::create(actionMove, actionDone, NULL); // 按顺序执行 敌机飞到边缘，敌机移动结束
    pEnemySprite->runAction(sequence);
}

void EnemyLayer::addEnemy2( float dt )
{
    Enemy *pEnemySprite = Enemy::create();
    pEnemySprite->setEnemyByType(Enemy2);
    pEnemySprite->setTag(Enemy2);
    this->addChild(pEnemySprite);
    vecEnemy.pushBack(pEnemySprite);
    
    // 设置运动轨迹 以及到终点时调用的函数
    auto actionMove=MoveTo::create(4.5f,Point(pEnemySprite->getPositionX(), 0 - pEnemySprite->getSprite()->getContentSize().height/2));
    auto actionDone = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::removeEnemy, this));
    Sequence* sequence=Sequence::create(actionMove, actionDone, NULL); // 按顺序执行 敌机飞到边缘，敌机移动结束
    pEnemySprite->runAction(sequence);
}

void EnemyLayer::addEnemy3( float dt )
{
    Enemy *pEnemySprite = Enemy::create();
    pEnemySprite->setEnemyByType(Enemy3);
    pEnemySprite->setTag(Enemy3);
    this->addChild(pEnemySprite);
    vecEnemy.pushBack(pEnemySprite);
    
    // 设置运动轨迹 以及到终点时调用的函数
    auto actionMove=MoveTo::create(6.0f,Point(pEnemySprite->getPositionX(), 0 - pEnemySprite->getSprite()->getContentSize().height/2));
    auto actionDone = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::removeEnemy, this));
    Sequence* sequence=Sequence::create(actionMove, actionDone, NULL); // 按顺序执行 敌机飞到边缘，敌机移动结束
    pEnemySprite->runAction(sequence);
}

void EnemyLayer::removeEnemy( Node *pNode)
{
    Enemy* enemy=(Enemy*)pNode;
    if (enemy!=NULL)
    {
        this->removeChild(enemy,true);
        vecEnemy.eraseObject(enemy);
    }
}

void EnemyLayer::blowupEnemy( Enemy* pEnemySprite )
{
    Animation *pAnimation = NULL;
    if (Enemy1 == pEnemySprite->getTag())
    {
        // 之前缓存了爆炸的动作数据，以Enemy1Blowup命名
        pAnimation = AnimationCache::getInstance()->getAnimation("Enemy1Blowup");
        setScore(ENEMY1_SCORE);
    }
    else if (Enemy2 == pEnemySprite->getTag())
    {
        pAnimation = AnimationCache::getInstance()->getAnimation("Enemy2Blowup");
        setScore(ENEMY2_SCORE);
    }
    else if (Enemy3 == pEnemySprite->getTag())
    {
        pAnimation = AnimationCache::getInstance()->getAnimation("Enemy3Blowup");
        setScore(ENEMY3_SCORE);
    }
    else
    {
        return;
    }
    
    Animate *pAnimate = Animate::create(pAnimation);
    
    // 爆炸完，要移除敌机
    auto pActionDone = CallFuncN::create(CC_CALLBACK_0(EnemyLayer::removeEnemy,this, pEnemySprite));
    //auto pActionDone = CallFuncN::create(std::bind(&EnemyLayer::removeEnemy, this, pEnemySprite)); 与上面是一样的
    Sequence* pSequence = Sequence::create(pAnimate, pActionDone, NULL);
    pEnemySprite->getSprite()->runAction(pSequence);
    
    updateScore(m_score);
}

void EnemyLayer::setScore( int nScore )
{
    m_score += nScore;
}

int EnemyLayer::getScore()
{
    return m_score;
}

void EnemyLayer::updateScore(int score)
{
    // 更新分数
    if (score>=0)
    {
        scoreItem->setString(StringUtils::format("%d",score));
    }
}
