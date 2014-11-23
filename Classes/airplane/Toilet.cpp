#include "Toilet.h"

USING_NS_CC;

const int Toilet::openSpeed = 8;

bool Toilet::isFree() const
{
	return !occupied;
}

void Toilet::openDoor()
{
	state = OPENING;
}

void Toilet::closeDoor()
{
	state = CLOSING;
}

void Toilet::occupy()
{
	occupied = true;
}

void Toilet::free()
{
	occupied = false;
}

bool Toilet::isOpen() const
{
	return (openAnglePercent == 100);
}

bool Toilet::isClose() const
{
	return (openAnglePercent == 0);
}

bool Toilet::init()
{
	if (!Sprite::init())
		return false;

	setTexture("airplane/door.png");
	setAnchorPoint(Vec2(0.f, 0.5f));
	setPosition(Vec2(51, 49));
	scheduleUpdate();
	occupied = false;
	openAnglePercent = 0;
	setZOrder(9);

	return true;
}

void Toilet::update(float dt)
{
	switch (state)
	{
	case STILL:
		break;
	case OPENING:
		openAnglePercent += openSpeed;
		if (openAnglePercent >= 100)
		{
			openAnglePercent = 100;
			state = STILL;
		}
		break;
	case CLOSING:
		openAnglePercent -= openSpeed;
		if (openAnglePercent <= 0)
		{
			openAnglePercent = 0;
			state = STILL;
		}
		break;
	}

	setScaleX((100 - openAnglePercent) / 100.f);
}
