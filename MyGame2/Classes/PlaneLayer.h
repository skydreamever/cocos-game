//
//  PlaneLayer.h
//  
//
//  Created by 孙龙霄 on 6/14/15.
//
//

#ifndef ____PlaneLayer__
#define ____PlaneLayer__

#include <stdio.h>
#include <cocos2d.h>

USING_NS_CC;

enum Enum_Plane
{
    AIRPLANE = 1,
};

class PlaneLayer : public Layer{
    
public:
    virtual bool init();
    CREATE_FUNC(PlaneLayer);
    
public:
    void checkBorder(float dt); // 边界检测
    void blowUp();				// 飞机爆炸
    void removePlane(Node* pNode);			// 移除飞机
    
public:
    bool isAlive; // 飞机是否活着
    
};



#endif /* defined(____PlaneLayer__) */
