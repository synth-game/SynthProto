//
//  TestObject.h
//  HelloCpp
//
//  Created by Pierre on 06/01/2014.
//
//

#ifndef HelloCpp_TestObject_h
#define HelloCpp_TestObject_h

#include "cocos2d.h"
#include "Actor.h"

class TestObject : public Actor {
    
public:
    TestObject(int id);
    int id;
    void initListeners();
    void onMoveEvent(cocos2d::EventCustom* event);
    cocos2d::EventListenerCustom* _actorMoveEventListener;
    
};

#endif
