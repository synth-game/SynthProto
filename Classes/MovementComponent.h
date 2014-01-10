//
//  MovementComponent.h
//  HelloCpp
//
//  Created by Pierre on 06/01/2014.
//
//

#ifndef HelloCpp_MovementComponent_h
#define HelloCpp_MovementComponent_h

#include "cocos2d.h"
#include "Actor.h"
#include "SynthComponent.h"

class MovementComponent : public SynthComponent {
    
public:
	static const char* COMPONENT_TYPE;

	//Members
	cocos2d::Point _speed;
	cocos2d::Point _direction;
	cocos2d::Point _acceleration;
	cocos2d::Point _gravity;
	bool _bStart;
	cocos2d::EventListenerCustom* _pChangeMoveEventListener;

	//Methods
	MovementComponent() : SynthComponent() {}
	virtual bool init();
	static MovementComponent* create(cocos2d::Point& speed, cocos2d::Point& targetSpeed, cocos2d::Point& direction, cocos2d::Point& gravity);
	
protected:
    void initListeners();
    void addListeners();
    void onChangeMove(cocos2d::EventCustom* event);
	virtual void update(float fDt);

	inline float sign(float f) { if(f>0) {return 1.f;} else {return -1.f;} }

};

#endif
