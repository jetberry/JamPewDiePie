#pragma once

#include "Man.h"
#include "../airplane/Toilet.h"
#include "Trolley.h"

class Passenger : public Man
{
public:

	static Passenger* create(const std::string& pictureDir, cocos2d::Vec2 pos);

	void assignToilet(Toilet* toilet);
	void assignTrolley(Trolley* trolley);

private:

	enum Const
	{
		MOVING_SPEED = 6
	};

	enum States
	{
		SEAT,	
		MOVING_TO_TOILET,
		MOVING_TO_SEAT,
		ENTER_TO_TOILET,
		TOILET_SEATING,
		TOILET_EXITING
	};

	std::string pictureDir;
	cocos2d::Vec2 seatPos;
	States state;
	Toilet* toilet;
	Trolley* trolley;

	int nextActionTime;

	virtual bool init() override;
	virtual void update(float dt) override;


	void checkTrolleyCollision();

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
