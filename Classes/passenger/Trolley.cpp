#include "Trolley.h"
#include "Helpers.h"
#include <iomanip>

USING_NS_CC;

bool Trolley::init()
{
	if (!Sprite::init())
		return false;

	scheduleUpdate();

	this->setTexture("airplane/trolley.png");
	this->setPosition(Vec2(300, -60));

	return true;
}

void Trolley::update(float dt)
{

}
