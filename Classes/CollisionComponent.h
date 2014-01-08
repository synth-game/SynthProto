#pragma once
#include "SynthComponent.h"
#include "SynthLevelBitmask.h"

class CollisionComponent : public SynthComponent {

public:
	static const char* COMPONENT_TYPE;

	// Members
	SynthLevelBitmask* _pBitmask;
	
	// Methods
	CollisionComponent() : SynthComponent() {};

	virtual bool init();
	static CollisionComponent* create(SynthLevelBitmask* pBitmask);
	

protected:
	// Members
	cocos2d::EventListenerCustom* _pTestCollisionEventListener;

	// Methods
	void initListeners();
    void addListeners();
	virtual void onTestCollision(cocos2d::EventCustom* event);

};
