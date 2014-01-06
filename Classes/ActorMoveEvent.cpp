//
//  ActorMoveEvent.cpp
//  HelloCpp
//
//  Created by Pierre on 06/01/2014.
//
//

#include "ActorMoveEvent.h"

const char* ActorMoveEvent::eventName = "actor_move_event";

ActorMoveEvent::ActorMoveEvent(Actor* source) : EventCustom(eventName) {
    _source = source;
    const char * c = getType().c_str();
    CCLOG("ActoreMoveEvent type = %s", c);
}