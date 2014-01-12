//
//  ActorJumpEvent.h
//  HelloCpp
//
//  Created by Jiji on 10/01/2013.
//
//

#ifndef __ACTOR_JUMP_EVENT_H__
#define __ACTOR_JUMP_EVENT_H__

#include "cocos2d.h"
#include "Actor.h"

class ActorJumpEvent : public cocos2d::EventCustom {
    
public:
    ActorJumpEvent(Actor* source);
    static const char* eventName;
    inline Actor* getSource() { return _source; }
	bool _bStart;
    
protected:
    Actor* _source;
    
};

#endif
