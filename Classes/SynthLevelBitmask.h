#ifndef __SYNTH_LEVEL_BITMASK_H__
#define __SYNTH_LEVEL_BITMASK_H__

#include "cocos2d.h"

class SynthHero;

class SynthLevelBitmask : public cocos2d::Image {
public:
	virtual ~SynthLevelBitmask() {}

	//void readAlpha(cocos2d::Point position) { CCLOG("ALPHA: %d | POS(%d, %d)", getAlpha(cocos2d::Point(position.x - _absolutePosition.x, _absolutePosition.y - position.y)), static_cast<int>(position.x-_absolutePosition.x), static_cast<int>(_absolutePosition.y-position.y)); }
	void setAbsolutePosition(const cocos2d::Point& absolutePosition) { _absolutePosition = absolutePosition; }
	
	void bitmaskCollisionTest(SynthHero* pHero, cocos2d::Point& nextPosition);

	void printData();

private:
	void	fallTest(SynthHero* pHero, cocos2d::Point& nextPosition);
	void	groundLateralTest(SynthHero* pHero, cocos2d:: Point& nextPosition);
	
	unsigned char getAlpha(int x, int y);

	cocos2d::Point	_absolutePosition;
};

#endif //__SYNTH_LEVEL_BITMASK_H__