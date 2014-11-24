#include "Nerd.h"
#include "../UserGameData.h"

USING_NS_CC;

bool Nerd::init()
{
	if (!Sprite::init())
		return false;

    isDead = false;
	scheduleUpdate();
	setZOrder(-5);

	this->setTexture("airplane/people/passengers/0003/seating.png");
	this->setPosition(Vec2(340, 40));

	timeToDead = 20; //секунд

	return true;
}

void Nerd::update(float dt)
{
	if (timeToDead > 0) {
		timeToDead -= dt;
		return;
	}
	if (UserGameData::getInstance()->getTotalAngle() < 50)
		return;


    if (!isDead) UserGameData::getInstance()->addScore(200);
    isDead = true;
    
	this->setTexture("airplane/people/passengers/0003/dead.png");
}
