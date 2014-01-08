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

USING_NS_CC;

const char* MovementComponent::COMPONENT_TYPE = "MovementComponent";


bool MovementComponent::init() {
	SynthComponent::init(MovementComponent::COMPONENT_TYPE);
	return true;
}

MovementComponent* MovementComponent::create(Point& speed, Point& targetSpeed, Point& acceleration) {
    MovementComponent* pRet = new MovementComponent();
    if (pRet != NULL && pRet->init())
    {
        CCLOG("MovementComponent create");
        pRet->autorelease();
        pRet->_speed = speed;
        pRet->_targetSpeed = targetSpeed;
		pRet->_acceleration = acceleration;
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
			_targetSpeed.x = startMoveEvent->_targetSpeed.x;
		}
		
		if(startMoveEvent->_bChangeY) {
			_targetSpeed.y = startMoveEvent->_targetSpeed.y;
		}
    }
    else {
        CCLOG("CHANGEMOVE EVENT RECEIVED BUT ID NOT THE SAME");
    }
    
}

void MovementComponent::update(float fDt) {
    //if the hero is moving or has to move
	if(!_targetSpeed.equals(Point::ZERO) || !_speed.equals(Point::ZERO)) {

		//compute next speed
		Point direction(sign(_targetSpeed.x-_speed.x), sign(_targetSpeed.y-_speed.y));
		_speed = _speed + Point(direction.x*_acceleration.x, direction.y*_acceleration.y);

		//cap the next speed
		if(sign(_targetSpeed.x - _speed.x) != direction.x) _speed.x = _targetSpeed.x;
		if(sign(_targetSpeed.y - _speed.y) != direction.y) _speed.y = _targetSpeed.y;

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

		//determine jump end
		if(_targetSpeed.y == _speed.y && _targetSpeed.y > 0)
		{
			ActorStartMoveEvent* pFallEvent = new ActorStartMoveEvent(static_cast<Actor*>(_owner));
			pFallEvent->_targetSpeed = Point(0, -300.f);
			pFallEvent->_bChangeX = false;
			pFallEvent->_bChangeY = true;

			EventDispatcher::getInstance()->dispatchEvent(pFallEvent);
		}
	}
}
