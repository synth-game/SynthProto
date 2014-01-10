//
//  MovementComponent.cpp
//  HelloCpp
//
//  Created by Pierre on 06/01/2014.
//
//

#include "cocos2d.h"
#include "MovementComponent.h"
#include "GeometryComponent.h"
#include "ActorStartMoveEvent.h"
#include "ActorCollisionEvent.h"

#define MAX_X_SPEED 200.f
#define MAX_Y_SPEED 300.f

USING_NS_CC;

const char* MovementComponent::COMPONENT_TYPE = "MovementComponent";


bool MovementComponent::init() {
	SynthComponent::init(MovementComponent::COMPONENT_TYPE);
	return true;
}

MovementComponent* MovementComponent::create(Point& speed, Point& direction, Point& acceleration, cocos2d::Point& gravity) {
    MovementComponent* pRet = new MovementComponent();
    if (pRet != NULL && pRet->init())
    {
        CCLOG("MovementComponent create");
        pRet->autorelease();
        pRet->_speed = speed;
        pRet->_direction = direction;
		pRet->_acceleration = acceleration;
		pRet->_gravity = gravity;
		pRet->_bStart = false;
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
	_pChangeMoveEventListener = cocos2d::EventListenerCustom::create(ActorStartMoveEvent::eventName, CC_CALLBACK_1(MovementComponent::onChangeMove, this));
}

void MovementComponent::addListeners() {
    CCLOG("MovementComponenet add listeners");
    auto dispatcher = cocos2d::EventDispatcher::getInstance();
    dispatcher->addEventListenerWithFixedPriority(_pChangeMoveEventListener, 1);
}

void MovementComponent::onChangeMove(cocos2d::EventCustom* event) {
    ActorStartMoveEvent* startMoveEvent = static_cast<ActorStartMoveEvent*>(event);
    Actor* eventSource = static_cast<Actor*>(startMoveEvent->getSource());
    Actor* componentOwner = static_cast<Actor*>(_owner);
    if (eventSource->getActorID() == componentOwner->getActorID()) {
		CCLOG("CHANGEMOVE EVENT RECEIVED IN MOVEMEMENT COMPONENT");
		if(startMoveEvent->_bChangeX) {
			_direction.x = startMoveEvent->_direction.x;
		}
		
		if(startMoveEvent->_bChangeY) {
			_direction.y = startMoveEvent->_direction.y;
		}

		_bStart = startMoveEvent->_bStart;
    }
    else {
        CCLOG("CHANGEMOVE EVENT RECEIVED BUT ID NOT THE SAME");
    }
    
}

void MovementComponent::update(float fDt) {
	//compute next speed
	_speed = _speed + Point(_direction.x*_acceleration.x, _direction.y*_acceleration.y) + _gravity;

	//cap the next speed
	if (_bStart) {
		if(abs(_speed.x) > MAX_X_SPEED) _speed.x = _direction.x * MAX_X_SPEED;
		if(abs(_speed.y) > MAX_Y_SPEED) _speed.x = _direction.y * MAX_Y_SPEED;
	} else {
		if(_speed.x * _direction.x > 0.f) _speed.x = 0.f;
		if(_speed.y * _direction.y > 0.f) _speed.y = 0.f;
	}
	

	//compute next position
	GeometryComponent* pGeometryComponent = static_cast<GeometryComponent*>(_owner->getComponent(GeometryComponent::COMPONENT_TYPE));
	CCASSERT(pGeometryComponent != NULL, "MovementComponent need a GeometryComponent added to its owner");

	Point nextPosition = pGeometryComponent->_position + (_speed * fDt);

	//send event for collision
	ActorCollisionEvent* pNeedTestCollisionEvent = new ActorCollisionEvent(static_cast<Actor*>(_owner));
	pNeedTestCollisionEvent->_currentPosition = pGeometryComponent->_position;
	pNeedTestCollisionEvent->_targetPosition = nextPosition;
	pNeedTestCollisionEvent->_size = pGeometryComponent->_size;
	EventDispatcher::getInstance()->dispatchEvent(pNeedTestCollisionEvent);
}
