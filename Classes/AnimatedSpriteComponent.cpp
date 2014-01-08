//
//  SpriteComponent.cpp
//  HelloCpp
//
//  Created by Pierre on 06/01/2014.
//
//

#include "cocos2d.h"
#include "AnimatedSpriteComponent.h"
#include "ActorStartMoveEvent.h"
#include "GeometryComponent.h"

const char* AnimatedSpriteComponent::componentName = "AnimatedSpriteComponent";

AnimatedSpriteComponent::AnimatedSpriteComponent(cocos2d::Layer* parent, const char* pvrFile, const char* plistFile, const char *spriteSheetFile) : Component(), _parent(parent), _pvrFile(pvrFile), _plistFile(plistFile), _spriteSheetFile(spriteSheetFile) {}

AnimatedSpriteComponent* AnimatedSpriteComponent::create(cocos2d::Layer* parent, const char* pvrFile, const char* plistFile, const char* spriteSheetFile)
{
    AnimatedSpriteComponent* pRet = new AnimatedSpriteComponent(parent, pvrFile, plistFile, spriteSheetFile);
    if (pRet != NULL && pRet->init())
    {
        CCLOG("SpriteComponent create");
        pRet->autorelease();
    }
    else
    {
        CCLOG("SpriteComponent create but delete");
        CC_SAFE_DELETE(pRet);
    }
	return pRet;
}

bool AnimatedSpriteComponent::init() {
    // Sprite sheet
    setName(componentName);
	_spriteBatch = cocos2d::SpriteBatchNode::create("sprites/megaman.pvr");
	_frameCache = cocos2d::SpriteFrameCache::sharedSpriteFrameCache();
	_frameCache->addSpriteFramesWithFile("sprites/megaman.plist");
	_frameCache->retain();
    
	_sprite = cocos2d::Sprite::createWithSpriteFrameName("walk_3.png");
	_spriteBatch->addChild(_sprite);
	_spriteBatch->setPosition(cocos2d::Point(0.f, 0.f));

	_parent->addChild(_spriteBatch, 1);
    
    // Sprite animation
    _animFrames = cocos2d::Array::create();
	char str[100] = {0};
	for(int i = 1; i <= 5; i++)
	{
	    sprintf(str, "walk_%d.png", i);
        cocos2d::SpriteFrame* frame = _frameCache->spriteFrameByName( str );
        frame->retain();
	    _animFrames->addObject(frame);
	}
	_walkAnimation = cocos2d::Animate::create(cocos2d::Animation::createWithSpriteFrames(_animFrames, 0.1f));
    _walkAnimation->retain();
    
    initListeners();
    addListeners();
    
    return true;
}

void AnimatedSpriteComponent::onEnter() { //Appelée après l'ajout dans le componentContainer par la classe Node (avant le owner n'est pas défini)
	_geometryComponent = static_cast<GeometryComponent*>(_owner->getComponent(GeometryComponent::COMPONENT_TYPE));
    CCASSERT(_geometryComponent != NULL, "SpriteComponent need a GeometryComponent added to its owner"); //Ici ça sous-entend qu'on ne peut pas créer de sprite qui n'ait pas besoin de bouger, ce qui est donc injuste. D'où la nécessité de passer plutôt par un PositionComponent par la suite qui se charge simplement de la position de l'objet.
	_spriteBatch->setPosition(_geometryComponent->_position);
}

void AnimatedSpriteComponent::initListeners() {
    CCLOG("SpriteComponent init listeners");
	_actorMoveEventListener = cocos2d::EventListenerCustom::create(ActorStartMoveEvent::eventName, CC_CALLBACK_1(AnimatedSpriteComponent::onMoveEvent, this));    
}

void AnimatedSpriteComponent::addListeners() {
    CCLOG("SpriteComponent add listeners");
    auto dispatcher = cocos2d::EventDispatcher::getInstance();
    dispatcher->addEventListenerWithFixedPriority(_actorMoveEventListener, 1);
}

void AnimatedSpriteComponent::onMoveEvent(cocos2d::EventCustom* event) {
    ActorStartMoveEvent* moveEvent = static_cast<ActorStartMoveEvent*>(event);
    Actor* eventSource = static_cast<Actor*>(moveEvent->getSource());
    Actor* componentOwner = static_cast<Actor*>(_owner);
    if (eventSource->getActorID() == componentOwner->getActorID()) {
		if (moveEvent->_targetSpeed.x < 0) {
            _sprite->setFlippedX(true);
            _sprite->runAction(cocos2d::RepeatForever::create( _walkAnimation ));
        }
        else if(moveEvent->_targetSpeed.x > 0) {
            _sprite->setFlippedX(false);
            _sprite->runAction(cocos2d::RepeatForever::create( _walkAnimation ));
        }
		else {
			_sprite->stopAllActions();
		}
    }
    else {
        CCLOG("MOVE EVENT RECEIVED BUT ID NOT THE SAME");
    }
    
}

void AnimatedSpriteComponent::update(float delta) {
    CCLOG("SPRITE SIZE : %f, %f", _sprite->getContentSize().width, _sprite->getContentSize().height);
	_spriteBatch->setPosition(_geometryComponent->_position);
}



