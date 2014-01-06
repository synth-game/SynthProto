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
#include "ActorStopMovingEvent.h"

const char* MovementComponent::componentName = "MovementComponent";

MovementComponent::MovementComponent() : Component() {}

MovementComponent* MovementComponent::create(float posX, float posY) {
    MovementComponent* pRet = new MovementComponent();
    if (pRet != NULL && pRet->init())
    {
        CCLOG("MovementComponent create");
        pRet->autorelease();
        pRet->_posX = posX;
        pRet->_posY = posY;
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
    _actorStopMovingEventListener = cocos2d::EventListenerCustom::create(ActorStopMovingEvent::eventName, CC_CALLBACK_1(MovementComponent::onStopMovingEvent, this));

}

void MovementComponent::addListeners() {
    CCLOG("MovementComponenet add listeners");
    auto dispatcher = cocos2d::EventDispatcher::getInstance();
    dispatcher->addEventListenerWithFixedPriority(_actorMoveEventListener, 1);
    dispatcher->addEventListenerWithFixedPriority(_actorStopMovingEventListener, 1);
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
        _moveState = MoveState::MOVING;
        switch (moveEvent->getDirection()) {
            case MoveDirection::RIGHT:
                _speedX = 1.0;
                _speedY = 0.0;
                break;
            case MoveDirection::LEFT:
                _speedX = -1.0;
                _speedY = 0.0;
                break;
            default:
                break;
        }
    }
    else {
        CCLOG("MOVE EVENT RECEIVED BUT ID NOT THE SAME");
    }
    
}

void MovementComponent::onStopMovingEvent(cocos2d::EventCustom* event) {
    ActorStopMovingEvent* stopMovingEvent = static_cast<ActorStopMovingEvent*>(event);
    Actor* eventSource = static_cast<Actor*>(stopMovingEvent->getSource());
    Actor* componentOwner = static_cast<Actor*>(_owner);
    if (eventSource->getActorID() == componentOwner->getActorID()) {
        _moveState = MoveState::NOT_MOVING;
    }
}

void MovementComponent::update(float delta) {
    if (_moveState == MoveState::MOVING) {
        _posX += _speedX;
        _posY += _speedY;
    }
}
