#include "GeometryComponent.h"
#include "ActorCollisionEvent.h"

USING_NS_CC;

const char* GeometryComponent::COMPONENT_TYPE = "GeometryComponent";

GeometryComponent* GeometryComponent::create(cocos2d::Point& position, cocos2d::Size& size, float rotationAngle, cocos2d::Point& anchorPoint) {
	 GeometryComponent* pRet = new GeometryComponent();
    if (pRet != NULL && pRet->init())
    {
        CCLOG("GeometryComponent create");
        pRet->autorelease();
		pRet->_position = position;
		pRet->_size = size;
		pRet->_fRotationAngle = rotationAngle;
		pRet->_anchorPoint = anchorPoint;
    }
    else
    {
        CCLOG("GeometryComponent create but delete");
        CC_SAFE_DELETE(pRet);
    }
	return pRet;
}

bool GeometryComponent::init() {
	SynthComponent::init(GeometryComponent::COMPONENT_TYPE);
	return true;
}

void GeometryComponent::initListeners() {
    CCLOG("GeometryComponent init listeners");
	_pActorFakeTestCollisionEventListener = cocos2d::EventListenerCustom::create(ActorCollisionEvent::eventName, CC_CALLBACK_1(GeometryComponent::onMove, this));
}

void GeometryComponent::addListeners() {
    CCLOG("GeometryComponent add listeners");
    auto dispatcher = cocos2d::EventDispatcher::getInstance();
    dispatcher->addEventListenerWithFixedPriority(_pActorFakeTestCollisionEventListener, 1);
}

void GeometryComponent::onMove(EventCustom* event) {
	ActorCollisionEvent* fakeEvent = static_cast<ActorCollisionEvent*>(event);
    Actor* eventSource = static_cast<Actor*>(fakeEvent->getSource());
    Actor* componentOwner = static_cast<Actor*>(_owner);
    if (eventSource->getActorID() == componentOwner->getActorID()) {
		CCLOG("FAKE EVENT RECEIVED");
		_position = fakeEvent->_targetPosition;
	} else {
		CCLOG("FAKE EVENT RECEIVED BUT ID NOT THE SAME");
	}
}