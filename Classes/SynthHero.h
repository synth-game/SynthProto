#ifndef __SYNTH_HERO_H__
#define __SYNTH_HERO_H__

#include "cocos2d.h"

class SynthLevelBitmask;

class SynthHero
{
public:
	SynthHero();
	~SynthHero();

	void init(cocos2d::Layer* pParent);

	void walkLeft(bool bStart);
	void walkRight(bool bStart);
	void stop(); //stop moving laterally
	void jump();
	void fall();
	void land();
	void move(float fDt);

	bool isJumping() { return _bIsJumping; }
	bool isFalling() { return _bIsFalling; }
	bool isMovingLaterally() { if(_currentSpeed.x != 0.f) { return true; } return false; }
	float  getWidth() { return _pHeroSprite->getTextureRect().size.width; }
	float  getHeight() { return _pHeroSprite->getTextureRect().size.height; }

	cocos2d::Point getPosition() { return _pHeroSprite->getPosition(); }
	cocos2d::Point getSpeed() { return _currentSpeed; }

	void setLevelBitmask(SynthLevelBitmask* pLevelBitmask) { _pLevelBitmask = pLevelBitmask; }

private:
	inline float sign(float f) { if(f>0) {return 1.f;} else {return -1.f;} }

	cocos2d::Point	_targetSpeed;
	cocos2d::Point	_currentSpeed;
	float			_fHorizAcc;
	float			_fVertiAcc;
	bool			_bIsLeftMoving;
	bool			_bIsRightMoving;
	bool			_bIsJumping;
	bool			_bIsFalling;
	
	cocos2d::Sprite* _pHeroSprite;
	SynthLevelBitmask* _pLevelBitmask;
	cocos2d::Layer* _pParent;
};

#endif //__SYNTH_HERO_H__