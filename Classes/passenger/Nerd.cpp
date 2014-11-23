#include "Nerd.h"

USING_NS_CC;

bool Nerd::init()
{
	if (!Sprite::init())
		return false;

	scheduleUpdate();
	setZOrder(-5);

	this->setTexture("airplane/people/passengers/0003/seating.png");
	this->setPosition(Vec2(340, 40));

	timeToDead = 12 * 60;

	return true;
}

void Nerd::update(float dt)
{
	if (timeToDead)
	{
		timeToDead--;
		return;
	}

	this->setTexture("airplane/people/passengers/0003/dead.png");
}
