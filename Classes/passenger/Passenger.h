#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include "chipmunk.h"

class Passenger : public cocos2d::Sprite
{
public:

	CREATE_FUNC(Passenger);

	void setSeatPosition(cocos2d::Vec2 pos);

private:

	enum Pictures
	{
		PICTURE_NONE,
		PICTURE_SEAT,
		PICTURE_WALK_0,
		PICTURE_WALK_1
	};

	enum Const
	{
		TOILET_POS = 100,
		MOVING_SPEED = 10,
		WALKING_ANIMATION_SPEED = 5
	};

	enum States
	{
		SEAT,	
		MOVING_TO_TOILET,
		MOVING_TO_SEAT,
	};

	cocos2d::Vec2 seatPos;
	States state;
	Pictures currentPicture;
	int updateCounter;
	int seatTime;
	float target;

	virtual bool init() override;
	virtual void update(float dt) override;

	void setPicture(Pictures picture);
	bool isOnTarget() const;
	void moveToToilet();
	void moveToSeat();
	void seatDown();
	void updateSeat(float dt);
	void updateMovingToToilet(float dt);
	void updateMovingToSeat(float dt);
	void movingToTarget();
};
