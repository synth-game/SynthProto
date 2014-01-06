//
//  ActorStopMovingEvent.h
//  HelloCpp
//
//  Created by Pierre on 06/01/2014.
//
//

#ifndef HelloCpp_ActorStopMovingEvent_h
#define HelloCpp_ActorStopMovingEvent_h

#include "cocos2d.h"
#include "Actor.h"

class ActorStopMovingEvent : public cocos2d::EventCustom {
    
public:
    ActorStopMovingEvent(Actor* source);
    static const char* eventName;
    inline Actor* getSource() { return _source; }

protected:
    Actor* _source;
    
};

#endif
