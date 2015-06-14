//
//  EnemyLayer.h
//  
//
//  Created by 孙龙霄 on 6/14/15.
//
//

#ifndef ____EnemyLayer__
#define ____EnemyLayer__

#include <stdio.h>
#include <cocos2d.h>
#include "Enemy.h"

USING_NS_CC;



class EnemyLayer : public Layer {
    
public:
    virtual bool init();
    CREATE_FUNC(EnemyLayer);
    
public:
    void addEnemy1(float dt); // 添加敌机1
    void addEnemy2(float dt); // 添加敌机2
    void addEnemy3(float dt); // 添加敌机3
    
    void blowupEnemy(Enemy* pEnemySprite);	// 敌机3爆炸
    void removeEnemy(Node *pNode);					// 移除敌机pNode
    
    void setScore(int nScore);						// 设置分数
    int  getScore();								// 获得分数
    void updateScore(int score);					// 更新分数
    
public:
    Vector<Enemy*> vecEnemy;	// 敌机容器，用于遍历碰撞问题
    static int m_score;				// 分数
    Label* scoreItem;			// 分数文本菜单
    
    
};

#endif /* defined(____EnemyLayer__) */
