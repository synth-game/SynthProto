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

MovementComponent* MovementComponent::create()
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
    CCLOG("RECEIVED MOVE EVENT IN COMPONENT = %d", _ID);
    ActorMoveEvent* moveEvent = static_cast<ActorMoveEvent*>(event);
    CCLOG("RECEIVED MOVE EVENT FROM SOURCE = %d", moveEvent->getSource()->getActorID());
    Actor* eventSource = static_cast<Actor*>(moveEvent->getSource());
    Actor* componentOwner = static_cast<Actor*>(_owner);
    CCLOG("COMPONENT OWNER ID = %d", componentOwner->getActorID());
    if (eventSource->getActorID() == componentOwner->getActorID()) {
        CCLOG("MOVE EVENT RECEIVED BY MOVEMENT COMPONENT (ID ARE THE SAME = %d)", eventSource->getActorID());
    }
    else {
        CCLOG("MOVE EVENT RECEIVED BUT ID NOT THE SAME");
    }
    
}

void MovementComponent::update(float delta) {
    //CCLOG("MOVEMENT COMPONENT UPDATE");
}
