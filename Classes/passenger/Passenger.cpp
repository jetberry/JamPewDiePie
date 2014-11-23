#include "Passenger.h"
#include "Helpers.h"
#include "../SoundManager/SoundManager.h"

USING_NS_CC;

Passenger* Passenger::create(const std::string& pictureDir, cocos2d::Vec2 pos)
{
	Passenger *passenger = new (std::nothrow) Passenger();
	if (passenger)
	{
		passenger->pictureDir = pictureDir;
		if (passenger->init())
		{
			passenger->seatPos = pos;
			passenger->setPosition(pos);
			passenger->autorelease();
			return passenger;
		}
	}
	CC_SAFE_DELETE(passenger);
	return nullptr;
}


bool Passenger::init()
{
	if (!Man::init())
		return false;
	
	createBody();
	toilet = nullptr;
	trolley = nullptr;
	nextActionTime = 0;
	angryFlag = false;
	seatDown();
	movingSpeed = MOVING_SPEED;
	setAngry(true);

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
	case BARF:
		updateBarf(dt);
		break;
	}

	setAngry(shakeState);
	Man::update(dt);
}

void Passenger::assignTrolley(Trolley* trolley)
{
	this->trolley = trolley;
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
	setPicture(pictureDir + "sitting/0000.png");
	state = SEAT;
	nextActionTime = getUpdateCounter() + (((rand() % 10) + 5) * 60);
	this->setFlippedX(false);
}

void Passenger::updateSeat(float dt)
{
	updateSittingAnim();

	if (getUpdateCounter() < nextActionTime)
		return;

	if (rand() % 2)
	{
		doBarf();
		return;
	}

	if (toilet && !toilet->isFree())
	{
		nextActionTime = getUpdateCounter() + (((rand() % 10) + 5) * 60);
		return;
	}

	//toilet->occupy();
	moveToToilet();
}

void Passenger::updateMovingAnim()
{
	setPicture(pictureDir + "go", getUpdateCounter() % 14);
	//this->setFlippedX(getDirection() == DIRECTION_RIGHT);
}

void Passenger::updateSittingAnim()
{
	if (!angryFlag)
	{
		setPicture(pictureDir + "sitting/0000.png");
		return;
	}

	setPicture(pictureDir + "angry_seating", (getUpdateCounter() / 4) % 15);
}

void Passenger::updateBarfAnim()
{
	setPicture(pictureDir + "barf_sitting", (getUpdateCounter() / 4) % 15);
}

void Passenger::updateMovingToToilet(float dt)
{
	if (!isOnTarget())
	{
		movingToTarget();
		checkTrolleyCollision();
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
		checkTrolleyCollision();
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

void Passenger::updateBarf(float dt)
{
	updateBarfAnim();

	if (getUpdateCounter() < nextActionTime)
		return;

	seatDown();
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

void Passenger::setAngry(bool value)
{
	angryFlag = value;
}

void Passenger::doBarf()
{
	if (state != SEAT)
		return;

	state = BARF;
	nextActionTime = getUpdateCounter() + 120;
}

void Passenger::checkTrolleyCollision()
{
	if (!trolley)
		return;

	float trolleyPos = trolley->getPositionX();
	float trolleyWidth = trolley->getContentSize().width;

	if (trolleyPos < -250)
		return;

	float delta = trolleyPos - getPositionX();
	float distance = abs(delta);

	if (distance > trolleyWidth)
		return;

	if (delta > 0)
		setPositionX(trolleyPos - trolleyWidth);
	else
		setPositionX(trolleyPos + trolleyWidth);

}
