#pragma once

#include "Man.h"

class Passenger : public Man
{
public:

	CREATE_FUNC(Passenger);

	void setSeatPosition(cocos2d::Vec2 pos);

private:


	enum States
	{
		SEAT,	
		MOVING_TO_TOILET,
		MOVING_TO_SEAT,
	};

	cocos2d::Vec2 seatPos;
	States state;

	int seatTime;

	virtual bool init() override;
	virtual void update(float dt) override;

	void moveToToilet();
	void moveToSeat();
	void seatDown();
	void updateSeat(float dt);
	void updateMovingAnim();
	void updateMovingToToilet(float dt);
	void updateMovingToSeat(float dt);
};
