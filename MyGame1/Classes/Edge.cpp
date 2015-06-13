//
//  Edge.cpp
//  
//
//  Created by 孙龙霄 on 6/11/15.
//
//

#include "Edge.h"


bool Edge::init(){
    
    Node::init();
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    setPhysicsBody(PhysicsBody::createEdgeBox(visibleSize));
    
    
    return true;
}