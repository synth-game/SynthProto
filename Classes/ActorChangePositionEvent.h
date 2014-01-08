//
//  ActorMoveEvent.h
//  HelloCpp
//
//  Created by Pierre on 18/12/2013.
//
//

#ifndef __ACTOR_CHANGE_POSITION_EVENT_H__
#define __ACTOR_CHANGE_POSITION_EVENT_H__

#include "cocos2d.h"
#include "Actor.h"

class ActorChangePositionEvent : public cocos2d::EventCustom {
    
public:
    ActorChangePositionEvent(Actor* source);
    static const char* eventName;
    inline Actor* getSource() { return _source; }
	cocos2d::Point _currentPosition;
	cocos2d::Point _targetPosition;
	cocos2d::Size _size;
    
protected:
    Actor* _source;
    
};

#endif