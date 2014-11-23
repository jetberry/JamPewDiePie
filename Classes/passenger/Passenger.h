#pragma once

#include "Man.h"
#include "../airplane/Toilet.h"

class Passenger : public Man
{
public:

	CREATE_FUNC(Passenger);

	void setSeatPosition(cocos2d::Vec2 pos);
	void assignToilet(Toilet* toilet);

private:

	enum States
	{
		SEAT,	
		MOVING_TO_TOILET,
		MOVING_TO_SEAT,
		ENTER_TO_TOILET,
		TOILET_SEATING,
		TOILET_EXITING
	};

	cocos2d::Vec2 seatPos;
	States state;
	Toilet* toilet;

	int seatTime;
	int nextActionTime;

	virtual bool init() override;
	virtual void update(float dt) override;

	void enterToToilet();
	void moveToToilet();
	void moveToSeat();
	void seatDown();

	void updateSeat(float dt);
	void updateMovingAnim();
	void updateMovingToToilet(float dt);
	void updateMovingToSeat(float dt);
	void updateEnterToToilet(float dt);
	void updateToiletSeating(float dt);
	void updateToiletExiting(float dt);
	
};
