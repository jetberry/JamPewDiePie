#include "Passenger.h"
#include "Helpers.h"

USING_NS_CC;

bool Passenger::init()
{
	if (!Sprite::init())
		return false;

	scheduleUpdate();

	currentPicture = PICTURE_NONE;
	updateCounter = 0;
	
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
	updateCounter++;
}

bool Passenger::isOnTarget() const
{
	return (abs(target - this->getPositionX()) < 0.5);
}

void Passenger::moveToToilet()
{
	state = MOVING_TO_TOILET;
	target = TOILET_POS;
}

void Passenger::moveToSeat()
{
	state = MOVING_TO_SEAT;
	target = seatPos.x;
}

void Passenger::seatDown()
{
	setPicture(PICTURE_SEAT);
	state = SEAT;
	seatTime = updateCounter;
	setFlipX(false);
}

void Passenger::updateSeat(float dt)
{
	if (updateCounter - seatTime < 60)
		return;

	if (!(rand() % 60))
	{
		moveToToilet();
	}
}

void Passenger::updateMovingToToilet(float dt)
{
	if (!isOnTarget())
	{
		movingToTarget();
		return;
	}
	
	moveToSeat();
}

void Passenger::updateMovingToSeat(float dt)
{
	if (!isOnTarget())
	{
		movingToTarget();
		return;
	}

	seatDown();
}

void Passenger::movingToTarget()
{
	float x = this->getPositionX();
	float delta = target - x;
	float direction = helpers::sgn(delta);

	if ((updateCounter / WALKING_ANIMATION_SPEED) % 2)
		setPicture(PICTURE_WALK_0);
	else
		setPicture(PICTURE_WALK_1);


	setFlipX(direction < 0);

	if (abs(delta) < MOVING_SPEED)
		x = target;
	else
		x += direction * MOVING_SPEED;

	this->setPositionX(x);
}

void Passenger::setSeatPosition(cocos2d::Vec2 pos)
{
	setPosition(pos);
	this->seatPos = pos;
	state = SEAT;
}

void Passenger::setPicture(Pictures picture)
{
	if (currentPicture != picture)
	{
		currentPicture = picture;
		switch (picture)
		{
		case PICTURE_NONE:
			break;
		case PICTURE_SEAT:
			this->setTexture("airplane/passengers/seat.png");
			break;
		case PICTURE_WALK_0:
			this->setTexture("airplane/passengers/stand0.png");
			break;
		case PICTURE_WALK_1:
			this->setTexture("airplane/passengers/stand1.png");
			break;
		}
	}
}
