#include "Steward.h"
#include "Helpers.h"

USING_NS_CC;

bool Steward::init()
{
	if (!Man::init())
		return false;

	setPosition(Vec2(RIGHT_POS, 0));
	moveToLeft();

	return true;
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
	}
	
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

	moveToLeft();
}

void Steward::updateMovingAnim()
{
	setPicture("airplane/people/steward", getUpdateCounter() % 14);
}
