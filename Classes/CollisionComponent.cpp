#include "CollisionComponent.h"
#include "GeometryComponent.h"
#include "MovementComponent.h"
#include "ActorCollisionEvent.h"
#include "ActorStartMoveEvent.h"
#include "ActorChangePositionEvent.h"

USING_NS_CC;

const char* CollisionComponent::COMPONENT_TYPE = "CollisionComponent";

CollisionComponent* CollisionComponent::create(SynthLevelBitmask* pBitmask) {

	 CollisionComponent* pRet = new CollisionComponent();
    if (pRet != NULL && pRet->init())
    {
        CCLOG("CollsionComponent create");
        pRet->autorelease();
		pRet->_pBitmask = pBitmask;
    }
    else
    {
        CCLOG("CollisionComponent create but delete");
        CC_SAFE_DELETE(pRet);
    }
	return pRet;
}

bool CollisionComponent::init() {
	SynthComponent::init(CollisionComponent::COMPONENT_TYPE);
	return true;
}

void CollisionComponent::initListeners() {
    CCLOG("CollisionComponent init listeners");
	_pTestCollisionEventListener = cocos2d::EventListenerCustom::create(ActorCollisionEvent::eventName, CC_CALLBACK_1(CollisionComponent::onTestCollision, this));
}

void CollisionComponent::addListeners() {
    CCLOG("CollisionComponent add listeners");
    auto dispatcher = cocos2d::EventDispatcher::getInstance();
    dispatcher->addEventListenerWithFixedPriority(_pTestCollisionEventListener, 1);
}

void CollisionComponent::onTestCollision(EventCustom* event) {
	ActorCollisionEvent* testCollisionEvent = static_cast<ActorCollisionEvent*>(event);
    Actor* eventSource = static_cast<Actor*>(testCollisionEvent->getSource());
    Actor* componentOwner = static_cast<Actor*>(_owner);
    if (eventSource->getActorID() == componentOwner->getActorID()) {
		CCLOG("COLLISION EVENT RECEIVED");

		// Interesting content of the method
		// Slopes
		Point newPosition = _pBitmask->bitmaskCollisionTest(testCollisionEvent->_currentPosition, testCollisionEvent->_size, testCollisionEvent->_targetPosition);

		if(!newPosition.equals(testCollisionEvent->_currentPosition)) {
			ActorChangePositionEvent* pEvent = new ActorChangePositionEvent(static_cast<Actor*>(_owner));
			pEvent->_currentPosition = newPosition;
			EventDispatcher::getInstance()->dispatchEvent(pEvent);
		}

	} else {
		CCLOG("COLLISION EVENT RECEIVED BUT ID NOT THE SAME");
	}
}

void CollisionComponent::update(float fDt) {
	GeometryComponent* pGeometryComponent = static_cast<GeometryComponent*>(_owner->getComponent(GeometryComponent::COMPONENT_TYPE));
	CCASSERT(pGeometryComponent != NULL, "CollisionComponent need a GeometryComponent added to its owner");

	MovementComponent* pMovementComponent = static_cast<MovementComponent*>(_owner->getComponent(MovementComponent::COMPONENT_TYPE));
	CCASSERT(pGeometryComponent != NULL, "CollisionComponent need a MovementComponent added to its owner");

	if(pMovementComponent->_targetSpeed.y <= 0.) {
		if(_pBitmask->fallTest(pGeometryComponent->_position, pGeometryComponent->_size)) {
			ActorStartMoveEvent* pFallEvent = new ActorStartMoveEvent(static_cast<Actor*>(_owner));
			pFallEvent->_targetSpeed = Point(0, -300.f);
			pFallEvent->_bChangeX = false;
			pFallEvent->_bChangeY = true;

			EventDispatcher::getInstance()->dispatchEvent(pFallEvent);
		}
	}
}