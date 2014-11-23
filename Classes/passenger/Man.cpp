#include "Man.h"
#include "Helpers.h"
#include <iomanip>

USING_NS_CC;

bool Man::init()
{
	if (!Sprite::init())
		return false;

	scheduleUpdate();

	currentPicture.clear();
	updateCounter = 0;
	setZOrder(10);

	return true;
}

void Man::createBody()
{
	return;
	PhysicsMaterial material(100, 0.15f, 0.1f);
	PhysicsBody* body = PhysicsBody::createBox(this->getContentSize(), material);
	this->setPhysicsBody(body);
}

void Man::update(float dt)
{
	updateCounter++;
}

void Man::setPicture(const std::string& fileName)
{
	// Промежучтоная ф-ия, чтобы не дергать часто setTexture (на случай, если setTexture затратна¤ операция).
	// Можно дергать каждый кадр, и не переживать. Если картинка не мен¤лась, то setTexture не будет вызываться.

	if (fileName == currentPicture)
		return;

	currentPicture = fileName;
	this->setTexture(fileName);
}

void Man::setPicture(const std::string& dirName, int index)
{
	std::stringstream ss;
	ss << dirName << "/" << std::setfill('0') << std::setw(4) << index << ".png";
	setPicture(ss.str());
}

void Man::setTarget(float target)
{
	this->target = target;
}

bool Man::isOnTarget() const
{
	return (abs(target - this->getPositionX()) < 0.5);
}

void Man::movingToTarget()
{
	float x = this->getPositionX();
	float delta = target - x;
	float direction = helpers::sgn(delta);

	this->setFlippedX(direction < 0);

	if (abs(delta) < MOVING_SPEED)
		x = target;
	else
		x += direction * MOVING_SPEED;

	this->setPositionX(x);
}

int Man::getUpdateCounter() const
{
	return updateCounter;
}

Man::Direction Man::getDirection() const
{
	float x = this->getPositionX();
	float delta = target - x;
	float direction = helpers::sgn(delta);

	if (abs(delta) < MOVING_SPEED)
		return DIRECTION_UNKNOW;

	if (direction < 0)
		return DIRECTION_LEFT;

	return DIRECTION_RIGHT;
}
