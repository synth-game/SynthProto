//
//  ActorMoveEvent.h
//  HelloCpp
//
//  Created by Pierre on 18/12/2013.
//
//

#ifndef HelloCpp_ActorMoveEvent_h
#define HelloCpp_ActorMoveEvent_h

#include "cocos2d.h"
#include "Actor.h"

enum class MoveDirection { // a priori on ne peut que se diriger dans les 4 directions mais idéalement ce serait bien de rendre ça plus souple en passant par exemple un vecteur de direction normalisé
    TOP,
    RIGHT,
    BOTTOM,
    LEFT
};

class ActorMoveEvent : public cocos2d::EventCustom {
    
public:
    ActorMoveEvent(Actor* source);
    static const char* eventName;
    inline Actor* getSource() { return _source; }
    inline void setMoveDirection(MoveDirection direction) { _direction = direction; }
    inline MoveDirection getDirection() { return _direction; }
    
protected:
    Actor* _source;
    MoveDirection _direction;
    
};

#endif
