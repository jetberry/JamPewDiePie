#include "Airplane.h"
#include "Helpers.h"

USING_NS_CC;

bool Airplane::init()
{
	auto sprite = Sprite::create("airplane/airplane.png");
	helpers::setOnCenter(sprite);
	this->addChild(sprite, 0);

	return true;
}
