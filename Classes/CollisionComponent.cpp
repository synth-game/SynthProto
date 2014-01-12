#include "CollisionComponent.h"
#include "GeometryComponent.h"
#include "MovementComponent.h"
#include "ActorCollisionEvent.h"
#include "ActorStartMoveEvent.h"
#include "ActorChangePositionEvent.h"
#include "ActorStopMoveEvent.h"

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
		//CCLOG("COLLISION EVENT RECEIVED");

		// Interesting content of the method
		//boundings collision
		Point bCollisionPosition = _pBitmask->boundingTest(testCollisionEvent->_size, testCollisionEvent->_targetPosition, SynthLevelBitmask::eBottom);
		Point tCollisionPosition = _pBitmask->boundingTest(testCollisionEvent->_size, testCollisionEvent->_targetPosition, SynthLevelBitmask::eTop);
		Point lCollisionPosition = _pBitmask->boundingTest(testCollisionEvent->_size, testCollisionEvent->_targetPosition, SynthLevelBitmask::eLeft);
		Point rCollisionPosition = _pBitmask->boundingTest(testCollisionEvent->_size, testCollisionEvent->_targetPosition, SynthLevelBitmask::eRight);
		
		Point newPosition = testCollisionEvent->_targetPosition;
		bool bVerticalCollision = false;
		if (bCollisionPosition.y != testCollisionEvent->_targetPosition.y) {
			newPosition.y = bCollisionPosition.y;
			bVerticalCollision = true;
		} else if (tCollisionPosition.y != testCollisionEvent->_targetPosition.y) {
			newPosition.y = tCollisionPosition.y;
			bVerticalCollision = true;
		}

		if (lCollisionPosition.x != testCollisionEvent->_targetPosition.x) {
			newPosition.x = lCollisionPosition.x;
		} else if (rCollisionPosition.x != testCollisionEvent->_targetPosition.x) {
			newPosition.x = rCollisionPosition.x;
		}

		if (!newPosition.equals(testCollisionEvent->_currentPosition)) {
			ActorChangePositionEvent* pChangePositionEvent = new ActorChangePositionEvent(static_cast<Actor*>(_owner));
			pChangePositionEvent->_currentPosition = newPosition;
			EventDispatcher::getInstance()->dispatchEvent(pChangePositionEvent);
		}

		if (bVerticalCollision) {
			ActorStopMoveEvent* pStopEvent = new ActorStopMoveEvent(static_cast<Actor*>(_owner));
			pStopEvent->_bHorizontalStop = false;
			pStopEvent->_bVerticalStop = true;
			EventDispatcher::getInstance()->dispatchEvent(pStopEvent);
		}

	} else {
		CCLOG("COLLISION EVENT RECEIVED BUT ID NOT THE SAME");
	}
}