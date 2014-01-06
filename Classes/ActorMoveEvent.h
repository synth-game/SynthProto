//
//  ActorMoveEvent.h
//  HelloCpp
//
//  Created by Pierre on 18/12/2013.
//
//

#ifndef HelloCpp_ActorMoveEvent_h
#define HelloCpp_ActorMoveEvent_h

#include "cocos2d.h"

class ActorMoveEvent : public cocos2d::EventCustom {
    
public:
    ActorMoveEvent();
    static const char* eventName;
    
};

#endif
