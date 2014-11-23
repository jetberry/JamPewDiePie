#include "Passenger.h"
#include "Helpers.h"

USING_NS_CC;

bool Passenger::init()
{
	if (!Man::init())
		return false;
	
	seatDown();

	return true;
}

void Passenger::update(float dt)
{
	switch (state)
	{
	case SEAT:
		updateSeat(dt);
		break;
	case MOVING_TO_TOILET:
		updateMovingToToilet(dt);
		break;
	case MOVING_TO_SEAT:
		updateMovingToSeat(dt);
		break;
	}

	Man::update(dt);
}

void Passenger::moveToToilet()
{
	state = MOVING_TO_TOILET;
	setTarget(TOILET_POS);
}

void Passenger::moveToSeat()
{
	state = MOVING_TO_SEAT;
	setTarget(seatPos.x);
}

void Passenger::seatDown()
{
	setPicture("airplane/passengers/seat.png");
	state = SEAT;
	seatTime = getUpdateCounter();
	this->setFlippedX(false);
}

void Passenger::updateSeat(float dt)
{
	if (getUpdateCounter() - seatTime < 60)
		return;

	if (!(rand() % 60))
	{
		moveToToilet();
	}
}

void Passenger::updateMovingAnim()
{
	if ((getUpdateCounter() / WALKING_ANIMATION_SPEED) % 2)
		setPicture("airplane/passengers/stand0.png");
	else
		setPicture("airplane/passengers/stand1.png");
}

void Passenger::updateMovingToToilet(float dt)
{
	if (!isOnTarget())
	{
		movingToTarget();
		updateMovingAnim();
		return;
	}
	
	moveToSeat();
}

void Passenger::updateMovingToSeat(float dt)
{
	if (!isOnTarget())
	{
		movingToTarget();
		updateMovingAnim();
		return;
	}

	seatDown();
}

void Passenger::setSeatPosition(cocos2d::Vec2 pos)
{
	setPosition(pos);
	this->seatPos = pos;
	state = SEAT;
}
