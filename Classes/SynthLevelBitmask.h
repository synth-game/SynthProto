#ifndef __SYNTH_LEVEL_BITMASK_H__
#define __SYNTH_LEVEL_BITMASK_H__

#include "cocos2d.h"

class SynthHero;

class SynthLevelBitmask : public cocos2d::Image {
public:
	virtual ~SynthLevelBitmask() {}

	//void readAlpha(cocos2d::Point position) { CCLOG("ALPHA: %d | POS(%d, %d)", getAlpha(cocos2d::Point(position.x - _absolutePosition.x, _absolutePosition.y - position.y)), static_cast<int>(position.x-_absolutePosition.x), static_cast<int>(_absolutePosition.y-position.y)); }
	void setAbsolutePosition(const cocos2d::Point& absolutePosition) { _absolutePosition = absolutePosition; }
	
	cocos2d::Point bitmaskCollisionTest(cocos2d::Point& currentPosition, cocos2d::Size& size, cocos2d::Point& nextPosition);
	bool	fallTest(cocos2d::Point& currentPosition, cocos2d::Size& size);

	void printData();

private:
	enum EDirection
	{
		eTop,
		eBottom,
		eLeft,
		eRight
	};

	bool	isOnGround(cocos2d::Point& currentPosition, cocos2d::Size& size);
	cocos2d::Point	groundLateralTest(cocos2d::Point& currentPosition, cocos2d::Size& size, cocos2d::Point& nextPosition);
	cocos2d::Point	boundingTest(cocos2d::Point& currentPosition, cocos2d::Size& size, cocos2d::Point& nextPosition,  EDirection dir);
	
	unsigned char getAlpha(int x, int y);

	cocos2d::Point	_absolutePosition;
};

#endif //__SYNTH_LEVEL_BITMASK_H__