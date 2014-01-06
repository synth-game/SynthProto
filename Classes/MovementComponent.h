//
//  MovementComponent.h
//  HelloCpp
//
//  Created by Pierre on 06/01/2014.
//
//

#ifndef HelloCpp_MovementComponent_h
#define HelloCpp_MovementComponent_h

#include "cocos2d.h"
#include "ActorMoveEvent.h"
#include "Actor.h"

#define MAX_HORIZ_SPEED 200.f
#define MAX_JUMP_SPEED 400.f
#define MAX_FALL_SPEED 300.f

enum class MoveState {
    NOT_MOVING,
    MOVING,
    JUMPING,
    FALLING
};

class MovementComponent : public cocos2d::Component {
    
public:
    inline bool init() { CCLOG("MovementComponent init"); _posX = 0.0; _posY = 0.0; _speedX = 0.0; _speedY = 0.0; _moveState = MoveState::NOT_MOVING; initListeners(); addListeners(); setName(componentName); return true;};
    static const char* componentName;
    static MovementComponent* create(float posX = 0.0, float posY = 0.0);
    void update(float delta);
    inline float getPosX() { return _posX; }
    inline float getPosY() { return _posY; }
    
protected:
    MovementComponent();
    bool isSameOwner();
    inline float sign(float f) { if(f>0) {return 1.f;} else {return -1.f;} }
    
	float _speedX;
    float _speedY;
    float _posX;
    float _posY;
    MoveState _moveState;
    void initListeners();
    void addListeners();
    void onMoveEvent(cocos2d::EventCustom* event);
    void onStopMovingEvent(cocos2d::EventCustom* event);
    cocos2d::EventListenerCustom* _actorMoveEventListener;
    cocos2d::EventListenerCustom* _actorStopMovingEventListener;

};

#endif
