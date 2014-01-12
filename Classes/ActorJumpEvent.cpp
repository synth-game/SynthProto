//
//  ActorJumpEvent.cpp
//  HelloCpp
//
//  Created by Pierre on 10/01/2014.
//
//

#include "ActorJumpEvent.h"

const char* ActorJumpEvent::eventName = "actor_jump_event";

ActorJumpEvent::ActorJumpEvent(Actor* source) : EventCustom(eventName) {
    _source = source;
    const char * c = getType().c_str();
    CCLOG("ActorJumpEvent type = %s", c);
}