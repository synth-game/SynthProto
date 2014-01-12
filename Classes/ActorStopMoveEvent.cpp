//
//  ActorStopMoveEvent.cpp
//  HelloCpp
//
//  Created by Pierre on 10/01/2014.
//
//

#include "ActorStopMoveEvent.h"

const char* ActorStopMoveEvent::eventName = "actor_stop_move_event";

ActorStopMoveEvent::ActorStopMoveEvent(Actor* source) : EventCustom(eventName) {
    _source = source;
    const char * c = getType().c_str();
    CCLOG("ActorStopMoveEvent type = %s", c);
}