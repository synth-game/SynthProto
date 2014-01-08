#include "SynthLevelBitmask.h"

#include "SynthHero.h"

USING_NS_CC;

Point SynthLevelBitmask::bitmaskCollisionTest(Point& currentPosition, Size& size, Point& nextPosition)
{
	if(isOnGround(currentPosition, size))
	{
		groundLateralTest(currentPosition, size, nextPosition);
	}
	
	nextPosition = boundingTest(currentPosition, size,  nextPosition, eRight);
	nextPosition = boundingTest(currentPosition, size,  nextPosition, eLeft);
	nextPosition = boundingTest(currentPosition, size, nextPosition, eTop);

	return nextPosition;
}

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

//Stop the fall on if there is one
//Start the fall if no ground under the hero
void SynthLevelBitmask::fallTest(SynthHero* pHero, Point& nextPosition) 
{
	if(!pHero->isJumping())
	{
		//determine the hero bottom point on image space
		int ct_pos_x = static_cast<int>(nextPosition.x - _absolutePosition.x);
		int ct_pos_y = static_cast<int>(_absolutePosition.y - nextPosition.y);

		//get the bottom point
		int half_sprite_h = static_cast<int>(floor((pHero->getHeight()/2.f) - 0.5f));
		int bt_pos_x = ct_pos_x;
		int bt_pos_y = ct_pos_y +  half_sprite_h;

		//stop the fall
		if(pHero->isFalling())
		{
			bool bGround = false;
			unsigned char value = getAlpha(bt_pos_x, bt_pos_y);
			while(value == 255 && bt_pos_y>=0)
			{
				bt_pos_y -= 1;
				value = getAlpha(bt_pos_x, bt_pos_y);
				
				bGround = true;
			}

			if(bGround)
			{
				pHero->land();
				nextPosition.y = _absolutePosition.y - (bt_pos_y - half_sprite_h);
			}
		}
		//start the fall
		else
		{
			unsigned char value = getAlpha(bt_pos_x, bt_pos_y+1);
			if(value == 0)
			{
				pHero->fall();
			}
		}
	}
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

Point SynthLevelBitmask::boundingTest(Point& currentPosition, Size& size, Point& nextPosition,  EDirection dir)
{
	int half_sprite_w = static_cast<int>(floor((size.width/2.f) - 0.5f));
	int half_sprite_h = static_cast<int>(floor((size.height/2.f) - 0.5f));

	int next_pos_x = static_cast<int>(nextPosition.x - _absolutePosition.x);
	int	next_pos_y = static_cast<int>(_absolutePosition.y - nextPosition.y);
	if(dir == eTop)
	{
		next_pos_y -= half_sprite_h;
	}
	else if(dir == eLeft)
	{
		next_pos_x -= half_sprite_w;
	}
	else if(dir == eRight)
	{
		next_pos_x += half_sprite_w;
	}

	if(getAlpha(next_pos_x, next_pos_y) == 255)
	{
		if(dir == eTop)
		{
			// fall
			nextPosition.y = currentPosition.y;
		}
		else
		{
			// stop
			nextPosition.x = currentPosition.x;
		}
	}
	return nextPosition;
}

unsigned char SynthLevelBitmask::getAlpha(int x, int y)
{
	if(x >= 0 && x < getWidth() && y >= 0 && y <getHeight())
	{
		return getData()[4*(x + y*getWidth()) + 3];
	}
	return 255;
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