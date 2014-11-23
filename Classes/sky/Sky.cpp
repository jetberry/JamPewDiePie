#include "Sky.h"
#include "Helpers.h"

USING_NS_CC;

bool Sky::init()
{
	designResolution = Size(4000, 2000);

	plane = Node::create();

	for (int i = 0; i < CLOWD_COUNT; ++i)
	{
		float x = rand() % static_cast< int >(designResolution.width);
		float y = rand() % static_cast< int >(designResolution.height);
		float scale = ((rand() % 8) + 2) / 10.0;

		auto sprite0 = Sprite::create("sky_1.png");
		sprite0->setPosition(Vec2(x, y));
		sprite0->setScale(scale);
		plane->addChild(sprite0, 0);

		auto sprite1 = Sprite::create("sky_1.png");
		sprite1->setPosition(Vec2(x + designResolution.width, y));
		sprite1->setScale(scale);
		plane->addChild(sprite1, 0);

		auto sprite2 = Sprite::create("sky_1.png");
		sprite2->setPosition(Vec2(x, y + designResolution.height));
		sprite2->setScale(scale);
		plane->addChild(sprite2, 0);

		auto sprite3 = Sprite::create("sky_1.png");
		sprite3->setPosition(Vec2(x + designResolution.width, y + designResolution.height));
		sprite3->setScale(scale);
		plane->addChild(sprite3, 0);
        
	}

	this->addChild(plane);

	scheduleUpdate();

	return true;
}

void Sky::update(float dt)
{
	Vec2 pos = plane->getPosition();
	pos += speed;

	if (pos.x > 0)
		pos.x -= designResolution.width;

	if (pos.x < -designResolution.width)
		pos.x += designResolution.width;

	if (pos.y > 0)
		pos.y -= designResolution.height;

	if (pos.y < -designResolution.height)
		pos.y += designResolution.height;

	plane->setPosition(pos);
}

void Sky::setVector(Vec2 v)
{
	speed = v;
}
