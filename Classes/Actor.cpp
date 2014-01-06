//
//  Actor.cpp
//  HelloCpp
//
//  Created by Pierre on 06/01/2014.
//
//

#include "Actor.h"

int Actor::actorCount = 0;

Actor::Actor() : Node() {
    Actor::actorCount++;
    _actorID = Actor::actorCount;
    CCLOG("ACTOR ID = %d", _actorID);
}

int Actor::getActorID() {
    return _actorID;
}