//
//  Actor.h
//  HelloCpp
//
//  Created by Pierre on 06/01/2014.
//
//

#ifndef HelloCpp_Actor_h
#define HelloCpp_Actor_h

#include "cocos2d.h"

class Actor : public cocos2d::Node {
    
public:
    Actor();
    static int actorCount;
    int getActorID();
    
protected:
    int _actorID;
};

#endif
