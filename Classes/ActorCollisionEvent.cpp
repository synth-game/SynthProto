//
//  ActorMoveEvent.cpp
//  HelloCpp
//
//  Created by Pierre on 06/01/2014.
//
//

#include "ActorCollisionEvent.h"

const char* ActorCollisionEvent::eventName = "actor_collision_event";

ActorCollisionEvent::ActorCollisionEvent(Actor* source) : EventCustom(eventName) {
    _source = source;
    const char * c = getType().c_str();
    CCLOG("ActorCollisionEvent type = %s", c);
}