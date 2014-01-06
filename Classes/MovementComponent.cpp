//
//  MovementComponent.cpp
//  HelloCpp
//
//  Created by Pierre on 06/01/2014.
//
//

#include "cocos2d.h"
#include "MovementComponent.h"
#include "ActorMoveEvent.h"

const char* MovementComponent::componentName = "MovementComponent";

MovementComponent::MovementComponent() : Component() {}

MovementComponent* MovementComponent::create(void)
{
    MovementComponent* pRet = new MovementComponent();
    if (pRet != NULL && pRet->init())
    {
        CCLOG("MovementComponent create");
        pRet->autorelease();
    }
    else
    {
        CCLOG("MovementComponent create but delete");
        CC_SAFE_DELETE(pRet);
    }
	return pRet;
}

void MovementComponent::initListeners() {
    CCLOG("MovementComponent init listeners");
    _actorMoveEventListener = cocos2d::EventListenerCustom::create(ActorMoveEvent::eventName, CC_CALLBACK_1(MovementComponent::onMoveEvent, this));
}

void MovementComponent::addListeners() {
    CCLOG("MovementComponenet add listeners");
    auto dispatcher = cocos2d::EventDispatcher::getInstance();
    dispatcher->addEventListenerWithFixedPriority(_actorMoveEventListener, 1);
}

void MovementComponent::onMoveEvent(cocos2d::EventCustom* event) {
    CCLOG("MOVE EVENT RECEIVED BY MOVEMENT COMPONENT");
}

