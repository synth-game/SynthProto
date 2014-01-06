//
//  TestObject.cpp
//  HelloCpp
//
//  Created by Pierre on 06/01/2014.
//
//

#include "TestObject.h"
#include "ActorMoveEvent.h"


TestObject::TestObject(int pID) : id(pID) {
    initListeners();
}

void TestObject::initListeners() {
    _actorMoveEventListener = cocos2d::EventListenerCustom::create(ActorMoveEvent::eventName, CC_CALLBACK_1(TestObject::onMoveEvent, this));
    auto dispatcher = cocos2d::EventDispatcher::getInstance();
    dispatcher->addEventListenerWithFixedPriority(_actorMoveEventListener, 1);
}

void TestObject::onMoveEvent(cocos2d::EventCustom* event) {
    CCLOG("RECEVEID MOVE EVENT IN TEST OBJECT %d", id);
}