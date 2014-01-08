//
//  ActorMoveEvent.cpp
//  HelloCpp
//
//  Created by Pierre on 06/01/2014.
//
//

#include "ActorStartMoveEvent.h"

const char* ActorStartMoveEvent::eventName = "actor_start_move_event";

ActorStartMoveEvent::ActorStartMoveEvent(Actor* source) : EventCustom(eventName) {
    _source = source;
    const char * c = getType().c_str();
    CCLOG("ActoreMoveEvent type = %s", c);
}