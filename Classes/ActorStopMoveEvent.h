//
//  ActorStopMoveEvent.h
//  HelloCpp
//
//  Created by Jiji on 10/01/2013.
//
//

#ifndef __ACTOR_STOP_MOVE_EVENT_H__
#define __ACTOR_STOP_MOVE_EVENT_H__

#include "cocos2d.h"
#include "Actor.h"

class ActorStopMoveEvent : public cocos2d::EventCustom {
    
public:
    ActorStopMoveEvent(Actor* source);
    static const char* eventName;
    inline Actor* getSource() { return _source; }
	bool _bHorizontalStop;
	bool _bVerticalStop;
    
protected:
    Actor* _source;
    
};

#endif
