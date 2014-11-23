#include "Passenger.h"
#include "Helpers.h"
#include "SoundManager.h"

USING_NS_CC;

bool Passenger::init()
{
	if (!Man::init())
		return false;
	
	setPicture("airplane/passengers/stand0.png");
	createBody();
	toilet = nullptr;
	nextActionTime = 0;
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
	case ENTER_TO_TOILET:
		updateEnterToToilet(dt);
		break;
	case TOILET_SEATING:
		updateToiletSeating(dt);
		break;
	case TOILET_EXITING:
		updateToiletExiting(dt);
		break;
	}

	Man::update(dt);
}

void Passenger::enterToToilet()
{
	state = ENTER_TO_TOILET;
	toilet->occupy();
	toilet->openDoor();
}

void Passenger::moveToToilet()
{
    setZOrder(10);
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
    setZOrder(-5);
	setPicture("airplane/passengers/seat.png");
	state = SEAT;
	nextActionTime = getUpdateCounter() + (((rand() % 10) + 5) * 60);
	this->setFlippedX(false);
}

void Passenger::updateSeat(float dt)
{
	if (getUpdateCounter() < nextActionTime)
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

	// Дошел до туалета. Если закрыто, идем назад.
	if (toilet && toilet->isFree())
	{
		enterToToilet();
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

void Passenger::updateEnterToToilet(float dt)
{
    SoundManager::getInstance()->playSound(sound_toilet_open, false, 14.0);
    
	// Ждем пока дверь откроется.
	if (!toilet->isOpen())
		return;

	// Переходим в туалет.

	setZOrder(8);
	toilet->closeDoor();
	state = TOILET_SEATING;
	nextActionTime = getUpdateCounter() + 140;
    
    SoundManager::getInstance()->playSound(sound_toilet, false, 0.4);
	//moveToSeat();
}

void Passenger::setSeatPosition(cocos2d::Vec2 pos)
{
	setPosition(pos);
	this->seatPos = pos;
	state = SEAT;
}

void Passenger::assignToilet(Toilet* toilet)
{
	this->toilet = toilet;
}

void Passenger::updateToiletSeating(float dt)
{
	// Пока посидим, попердим.
	if (getUpdateCounter() < nextActionTime)
		return;

	// Выходим из туалета.
	toilet->openDoor();
	state = TOILET_EXITING;
}

void Passenger::updateToiletExiting(float dt)
{
	// Ждем пока дверь откроется.
	if (!toilet->isOpen())
		return;

	setZOrder(10);
	toilet->closeDoor();
	toilet->free();
	moveToSeat();
}
