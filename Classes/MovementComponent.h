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

enum class MoveState {
    NOT_MOVING,
    MOVING,
    JUMPING
};

class MovementComponent : public cocos2d::Component {
    
public:
    inline bool init() { CCLOG("MovementComponent init"); _posX = 0.0; _posY = 0.0; _moveState = MoveState::NOT_MOVING; initListeners(); addListeners(); setName(componentName); return true;};
    static const char* componentName;
    static MovementComponent* create();
    
protected:
    MovementComponent();
    float _posX;
    float _posY;
    MoveState _moveState;
    void initListeners();
    void addListeners();
    void onMoveEvent(cocos2d::EventCustom* event);
    cocos2d::EventListenerCustom* _actorMoveEventListener;
};

#endif
