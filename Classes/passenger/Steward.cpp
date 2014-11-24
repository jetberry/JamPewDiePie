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

	stayAtKitchen();
	handleTrolley = false;
	movingSpeed = MOVING_SPEED;

	setPicture("airplane/people/steward/go", 0);
	createBody();

	return true;
}

void Steward::stayAtKitchen()
{
	nextAction = getUpdateCounter() + (rand() % 6 + 10) * 60;
	setPosition(Vec2(KITHEN_POS, 40));
	state = STAY_AT_KITCHEN;
}

void Steward::stayAtRight(){
    nextAction = getUpdateCounter() + (rand() % 5 + 1) * 60;
    state = STAY_AT_RIGHT;
}

void Steward::updateTrolley()
{
	if (trolley && handleTrolley)
	{
		trolley->setPositionX(this->getPositionX() + 160);
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
	case STAY_AT_KITCHEN:
		updateStateInKitchen(dt);
		break;
    case STAY_AT_RIGHT:
        updateStateAtRight(dt);
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

    if(handleTrolley)
        stayAtRight();
    else
        goKitchen();
}

void Steward::updateMovingAnim()
{
	setPicture("airplane/people/steward/go", getUpdateCounter() % 15);
	this->setFlippedX(getDirection() == DIRECTION_LEFT);
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
	stayAtKitchen();
}

void Steward::updateStateInKitchen(float dt)
{
	if (getUpdateCounter() < nextAction)
		return;

	moveToRight();
}

void Steward::updateStateAtRight(float dt)
{
    if (getUpdateCounter() < nextAction)
        return;
    
    goKitchen();
}
