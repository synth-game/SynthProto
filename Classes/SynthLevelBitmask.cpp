#include "SynthLevelBitmask.h"

USING_NS_CC;

bool SynthLevelBitmask::isOnGround(Point& currentPosition, Size& size) {

		//determine the hero center point on image space
		int ct_pos_x = static_cast<int>(currentPosition.x - _absolutePosition.x);
		int ct_pos_y = static_cast<int>(_absolutePosition.y - currentPosition.y);

		//get the bottom point
		int half_sprite_h = static_cast<int>(floor((size.height/2.f) - 0.5f));
		int bt_pos_x = ct_pos_x;
		int bt_pos_y = ct_pos_y +  half_sprite_h;

		//stop the fall
		bool bGround = false;
		unsigned char value = getAlpha(bt_pos_x, bt_pos_y);
		return value == 255;
}

//move hero sprite when he move lateraly on the ground
//return the Y position to apply to the sprite
Point SynthLevelBitmask::groundLateralTest(Point& currentPosition, Size& size, Point& nextPosition)
{
	//get next available position
	//determine the hero next bottom point on image space
	int half_sprite_h = static_cast<int>(floor((size.height/2.f) - 0.5f));

	int bt_cur_pos_x = static_cast<int>(currentPosition.x - _absolutePosition.x);
	int bt_cur_pos_y = static_cast<int>(_absolutePosition.y - currentPosition.y) +  half_sprite_h;

	int bt_next_pos_x = static_cast<int>(nextPosition.x - _absolutePosition.x);
	int bt_next_pos_y = static_cast<int>(_absolutePosition.y - nextPosition.y) +  half_sprite_h;

	//verify there was a lateral movment
	if(bt_next_pos_x - bt_cur_pos_x != 0)
	{
		unsigned char value = getAlpha(bt_next_pos_x, bt_next_pos_y);

		//case when hitting a wall - growing slope
		if(value == 255)
		{
			//get the upper available pixel (next white px)
			while(value == 255 && bt_next_pos_y>=0)
			{
				bt_next_pos_y -= 1;
				value = getAlpha(bt_next_pos_x, bt_next_pos_y);
			}
		}
		//case when walking on the void - ungrowing slope
		else if(value == 0)
		{
			//get the downer available pixel (next black px)
			while(value == 0 && bt_next_pos_y<getHeight())
			{
				bt_next_pos_y += 1;
				value = getAlpha(bt_next_pos_x, bt_next_pos_y);
			}
			bt_next_pos_y -=1;
		}

		int slopeCoef = (bt_next_pos_y - bt_cur_pos_y)/(bt_next_pos_x - bt_cur_pos_x);
		if(slopeCoef > 3)
		{
			nextPosition = currentPosition;
		}
		else if(-3 < slopeCoef && slopeCoef < 3)
		{
			nextPosition.y = _absolutePosition.y - (bt_next_pos_y - half_sprite_h);
		}
		else {/*do nothing*/}

		return nextPosition;
	}
}

Point SynthLevelBitmask::boundingTest(Size& size, Point nextPosition,  EDirection dir)
{
	int half_sprite_w = static_cast<int>(floor((size.width/2.f) - 0.5f));
	int half_sprite_h = static_cast<int>(floor((size.height/2.f) - 0.5f));

	Point imageSpaceNextPos(nextPosition.x - _absolutePosition.x, _absolutePosition.y - nextPosition.y);

	if(dir == eBottom) {
		imageSpaceNextPos.y += half_sprite_h;
		imageSpaceNextPos = getNextVoidPixelInDirection(imageSpaceNextPos, Point(0.f, -1.f));
		nextPosition.y = _absolutePosition.y - imageSpaceNextPos.y + half_sprite_h;
	} else if (dir == eTop) {
		imageSpaceNextPos.y -= half_sprite_h;
		imageSpaceNextPos = getNextVoidPixelInDirection(imageSpaceNextPos, Point(0.f, 1.f));
		nextPosition.y = _absolutePosition.y - imageSpaceNextPos.y - half_sprite_h;
	} else if (dir == eLeft) {
		imageSpaceNextPos.x -= half_sprite_w;
		imageSpaceNextPos = getNextVoidPixelInDirection(imageSpaceNextPos, Point(1.f, 0.f));
		nextPosition.x = _absolutePosition.x + imageSpaceNextPos.x + half_sprite_w;
	} else if(dir == eRight) {
		imageSpaceNextPos.x += half_sprite_w;
		imageSpaceNextPos = getNextVoidPixelInDirection(imageSpaceNextPos, Point(-1.f, 0.f));
		nextPosition.x = _absolutePosition.x + imageSpaceNextPos.x - half_sprite_w;
	}

	nextPosition.x = floor(nextPosition.x);
	nextPosition.y = floor(nextPosition.y);

	return nextPosition;
}

Point SynthLevelBitmask::getNextVoidPixelInDirection(Point currentPixel, Point direction) {
	Point voidPixel = currentPixel;

	unsigned char ucValue = getAlpha(voidPixel.x, voidPixel.y);
	while(ucValue != 0) {
		voidPixel = voidPixel + direction;
		ucValue =  getAlpha(voidPixel.x, voidPixel.y);
	}

	return voidPixel;
}

unsigned char SynthLevelBitmask::getAlpha(int x, int y)
{
	CCASSERT(x >= 0 , "SynthLevelBitmask : Out of array search for pixel alpha.");
	CCASSERT(x < getWidth() , "SynthLevelBitmask : Out of array search for pixel alpha.");
	CCASSERT(y >= 0 , "SynthLevelBitmask : Out of array search for pixel alpha.");
	CCASSERT(y < getHeight() , "SynthLevelBitmask : Out of array search for pixel alpha.");
	return getData()[4*(x + y*getWidth()) + 3];
}

void SynthLevelBitmask::printData()
{
	unsigned char* pData = getData();

	for(int j=0; j<getHeight(); ++j)
	{
		for(int i=0; i<getWidth(); ++i)
		{
			int idx = i + j*getWidth();
			CCLOG("> pixel : %d \t %d \t %d \t %d", pData[4*idx], pData[4*idx+1], pData[4*idx+2], pData[4*idx+3]);
		}
	}
}