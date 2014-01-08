//
//  ActorMoveEvent.cpp
//  HelloCpp
//
//  Created by Pierre on 06/01/2014.
//
//

#include "ActorChangePositionEvent.h"

const char* ActorChangePositionEvent::eventName = "actor_change_position_event";

ActorChangePositionEvent::ActorChangePositionEvent(Actor* source) : EventCustom(eventName) {
    _source = source;
    const char * c = getType().c_str();
    CCLOG("ActorChangePositionEvent type = %s", c);
}