//
//  ActorMoveEvent.h
//  HelloCpp
//
//  Created by Pierre on 18/12/2013.
//
//

#ifndef HelloCpp_ActorMoveEvent_h
#define HelloCpp_ActorStartMoveEvent_h

#include "cocos2d.h"
#include "Actor.h"

enum class MoveDirection { // a priori on ne peut que se diriger dans les 4 directions mais idéalement ce serait bien de rendre ça plus souple en passant par exemple un vecteur de direction normalisé
    TOP,
    RIGHT,
    BOTTOM,
    LEFT
};

class ActorStartMoveEvent : public cocos2d::EventCustom {
    
public:
    ActorStartMoveEvent(Actor* source);
    static const char* eventName;
    inline Actor* getSource() { return _source; }
	cocos2d::Point	_targetSpeed;
	bool			_bChangeX;
	bool			_bChangeY;
    
protected:
    Actor* _source;
    
};

#endif
