#pragma once
#include "SynthComponent.h"

class GeometryComponent : public SynthComponent {

public:
	static const char* COMPONENT_TYPE;

	// Members
	cocos2d::Point		_position;
	cocos2d::Size		_size;
	float				_fRotationAngle;
	cocos2d::Point		_anchorPoint;

	// Methods
	GeometryComponent() : SynthComponent() {};

	virtual bool init();
	static GeometryComponent* create(cocos2d::Point position, cocos2d::Size size, float rotationAngle, cocos2d::Point anchorPoint);

protected:
	void onMove(cocos2d::EventCustom* event);

	void initListeners();
    void addListeners();
	cocos2d::EventListenerCustom* _pActorChangePositionListener;
};

