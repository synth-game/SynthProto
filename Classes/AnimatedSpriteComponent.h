//
//  SpriteComponent.h
//  HelloCpp
//
//  Created by Pierre on 06/01/2014.
//
//

#ifndef HelloCpp_SpriteComponent_h
#define HelloCpp_SpriteComponent_h

#include "cocos2d.h"
#include "MovementComponent.h"
#include "GeometryComponent.h"

class AnimatedSpriteComponent : public cocos2d::Component {
    
public:
	static const char* COMPONENT_TYPE;

    AnimatedSpriteComponent(cocos2d::Layer* parent, const char* pvrFile, const char* plistFile, const char* spriteSheetFile);
    static const char* componentName;
    static AnimatedSpriteComponent* create(cocos2d::Layer* parent, const char* pvrFile, const char* plistFile, const char* spriteSheetFile);
    void onEnter();
    void update(float delta);
    
protected:
    cocos2d::Sprite* _sprite;
    cocos2d::Layer* _parent;
    const char* _pvrFile;
    const char* _plistFile;
    const char* _spriteSheetFile;
    GeometryComponent* _geometryComponent;
    cocos2d::SpriteBatchNode* _spriteBatch;
    cocos2d::SpriteFrameCache* _frameCache;
    cocos2d::Animate* _walkAnimation; //normalement il faudrait un array avec comme clé l'enum du type d'animation et en valeur l'objet Animate*
    void initListeners();
    void addListeners();
    void onMoveEvent(cocos2d::EventCustom* event);
    cocos2d::EventListenerCustom* _actorMoveEventListener;
    cocos2d::Array* _animFrames;
    
    
    bool init();
};

#endif
