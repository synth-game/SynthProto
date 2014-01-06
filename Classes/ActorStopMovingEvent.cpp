//
//  ActorStopMovingEvent.cpp
//  HelloCpp
//
//  Created by Pierre on 06/01/2014.
//
//

#include "ActorStopMovingEvent.h"

const char* ActorStopMovingEvent::eventName = "actor_stop_moving_event";

ActorStopMovingEvent::ActorStopMovingEvent(Actor* source) : EventCustom(eventName) {
    _source = source;
    const char * c = getType().c_str();
    CCLOG("ActoreStopMovingEvent type = %s", c);
}