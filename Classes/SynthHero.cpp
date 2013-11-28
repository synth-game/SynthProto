#include "SynthHero.h"

#include "SynthLevelBitmask.h"

#define MAX_HORIZ_SPEED 200.f
#define MAX_JUMP_SPEED 400.f
#define MAX_FALL_SPEED 300.f

USING_NS_CC;

SynthHero::SynthHero()
	: _targetSpeed(Point::ZERO)
	, _currentSpeed(Point::ZERO)
	, _fHorizAcc(20.f)
	, _fVertiAcc(20.f)
	, _bIsLeftMoving(false)
	, _bIsRightMoving(false)
	, _bIsJumping(false)
	, _bIsFalling(false)
	, _pHeroSprite(NULL)
	, _pLevelBitmask(NULL)
{

}

SynthHero::~SynthHero()
{
	if(_pLevelBitmask) delete _pLevelBitmask;
}

void SynthHero::init(Layer* pParent)
{

	// Sprite sheet
	SpriteBatchNode* spritebatch = SpriteBatchNode::create("sprites/megaman.pvr");
	SpriteFrameCache* cache = SpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("sprites/megaman.plist");

	_pHeroSprite = Sprite::createWithSpriteFrameName("walk_1.png");
	spritebatch->addChild(_pHeroSprite);
	spritebatch->setPosition(Point(200.f, 180.f)); 
	_pParent = pParent;
	_pParent->addChild(spritebatch, 1);

	// Sprite animation
	Array* animFrames = Array::createWithCapacity(5);
	char str[100] = {0};
	for(int i = 1; i <= 5; i++) 
	{
	    sprintf(str, "walk_%d.png", i);
	    SpriteFrame* frame = cache->spriteFrameByName( str );
	    animFrames->addObject(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
	_pHeroSprite->runAction( RepeatForever::create( Animate::create(animation) ) );

}

void SynthHero::walkLeft(bool bStart)
{
	if(bStart)
	{
		_bIsLeftMoving = true;
		_targetSpeed.x = -MAX_HORIZ_SPEED;
	}
	else
	{
		_bIsLeftMoving = false;
		if(!_bIsRightMoving) _targetSpeed.x = 0.f;
	}
}

void SynthHero::walkRight(bool bStart)
{
	if(bStart)
	{
		_bIsRightMoving = true;
		_targetSpeed.x = MAX_HORIZ_SPEED;
	}
	else
	{
		_bIsRightMoving = false;
		if(!_bIsLeftMoving) _targetSpeed.x = 0.f;
	}
}

void SynthHero::stop()
{
	_bIsLeftMoving = false;
	_bIsRightMoving = false;
	_targetSpeed.x = 0.f;
	_currentSpeed.x = 0.f;
}

void SynthHero::jump()
{
	_bIsJumping = true;
	_currentSpeed.y = 2.f*MAX_JUMP_SPEED/3.f;
	_targetSpeed.y = MAX_JUMP_SPEED;
	CCLOG("////// JUMP //////");
}

void SynthHero::fall()
{
	_bIsJumping = false;
	_bIsFalling = true;
	_targetSpeed.y = -MAX_FALL_SPEED;
	CCLOG("////// FALL //////");
}

void SynthHero::land()
{
	_bIsFalling = false;
	_targetSpeed.y = 0.f;
	_currentSpeed.y = 0.f;
	CCLOG("////// LAND //////");
}

void SynthHero::move(float fDt)
{
	Point direction(sign(_targetSpeed.x-_currentSpeed.x), sign(_targetSpeed.y-_currentSpeed.y));
	_currentSpeed = _currentSpeed + Point(direction.x*_fHorizAcc, direction.y*_fVertiAcc*static_cast<int>(_bIsFalling || _bIsJumping));

	if(sign(_targetSpeed.x - _currentSpeed.x) != direction.x) _currentSpeed.x = _targetSpeed.x;

	//reach the max vert acceleration -> start falling
	if(sign(_targetSpeed.y - _currentSpeed.y) != direction.y && _bIsJumping)
	{
		_currentSpeed.y = _targetSpeed.y;

		// start falling
		fall();
	}

	Point nextHeroPosition = _pHeroSprite->getPosition() + (_currentSpeed * fDt);
	CCLOG("hero position : (%f, %f)", _pHeroSprite->getPosition().x, _pHeroSprite->getPosition().y);
	//_pLevelBitmask->bitmaskCollisionTest(this, nextHeroPosition);

	/* Hero sprite */
	_pHeroSprite->setPosition(nextHeroPosition);
	

	/* Updating layer position */
	Point nextLayerPosition = Point(-1*(nextHeroPosition.x-450),-1*(nextHeroPosition.y-320));
	Size backgroundSize = _pParent->getChildByTag(1)->getContentSize();

	// Block to the edge of the layer
	if(nextHeroPosition.x < 450 || nextHeroPosition.x > backgroundSize.width-450) 
		nextLayerPosition.x = _pParent->getPosition().x;
	if(nextHeroPosition.y < 320 || nextHeroPosition.y > backgroundSize.height-320) 
		nextLayerPosition.y = _pParent->getPosition().y;

	//CCLOG("Next layer position : (%f, %f)", nextLayerPosition.x, nextLayerPosition.y);

	_pParent->setPosition(nextLayerPosition);

}