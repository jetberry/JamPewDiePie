#include "Steward.h"
#include "Helpers.h"

USING_NS_CC;

Steward::Steward() : trolley( nullptr )
{
}

void Steward::assignTrolley(Trolley* trolley)
{
	this->trolley = trolley;
}

bool Steward::init()
{
	if (!Man::init())
		return false;

	setPosition(Vec2(RIGHT_POS, 0));
	goKitchen();
	handleTrolley = false;

	return true;
}

void Steward::updateTrolley()
{
	if (trolley && handleTrolley)
	{
		trolley->setPositionX(this->getPositionX() - 160);
		this->setFlippedX(false);
	}
}

void Steward::update(float dt)
{
	switch (state)
	{
	case MOVING_TO_LEFT:
		updateMovingToLeft(dt);
		break;
	case MOVING_TO_RIGHT:
		updateMovingToRight(dt);
		break;
	case GOTO_KITCHEN:
		updateGotoKitchen(dt);
		break;
	}

	updateTrolley();
	Man::update(dt);
}

void Steward::moveToLeft()
{
	state = MOVING_TO_LEFT;
	setTarget(LEFT_POS);
}

void Steward::moveToRight()
{
	state = MOVING_TO_RIGHT;
	setTarget(RIGHT_POS);
}

void Steward::goKitchen()
{
	state = GOTO_KITCHEN;
	setTarget(KITHEN_POS);
}

void Steward::updateMovingToLeft(float dt)
{
	if (!isOnTarget())
	{
		movingToTarget();
		updateMovingAnim();
		return;
	}

	moveToRight();
}

void Steward::updateMovingToRight(float dt)
{
	if (!isOnTarget())
	{
		movingToTarget();
		updateMovingAnim();
		return;
	}

	goKitchen();
}

void Steward::updateMovingAnim()
{
	setPicture("airplane/people/steward", getUpdateCounter() % 14);
	this->setFlippedX(getDirection() == DIRECTION_RIGHT);
}

void Steward::updateGotoKitchen(float dt)
{
	if (!isOnTarget())
	{
		movingToTarget();
		updateMovingAnim();
		return;
	}

	handleTrolley = !handleTrolley;
	moveToRight();
}
