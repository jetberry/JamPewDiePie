#include "Airplane.h"
#include "Helpers.h"

USING_NS_CC;
USING_NS_CC_EXT;

bool Airplane::init()
{
	initPhysics();

	auto sprite = Sprite::create("airplane/airplane.png");
	helpers::setOnCenter(sprite);
	this->addChild(sprite, 0);

	return true;
}

void Airplane::initPhysics()
{
	_space = cpSpaceNew();

	_space->gravity = cpv(0, -100);


	auto innerRect = Rect( 369 + 342,  528, 1170, 526 );


	// bottom
	_walls[0] = cpSegmentShapeNew(_space->staticBody,
		cpv(innerRect.getMinX(), innerRect.getMinY()),
		cpv(innerRect.getMaxX(), innerRect.getMinY()), 0.0f);

	// top
	_walls[1] = cpSegmentShapeNew(_space->staticBody,
		cpv(innerRect.getMinX(), innerRect.getMaxY()),
		cpv(innerRect.getMaxX(), innerRect.getMaxY()), 0.0f);

	// left
	_walls[2] = cpSegmentShapeNew(_space->staticBody,
		cpv(innerRect.getMinX(), innerRect.getMinY()),
		cpv(innerRect.getMinX(), innerRect.getMaxY()), 0.0f);

	// right
	_walls[3] = cpSegmentShapeNew(_space->staticBody,
		cpv(innerRect.getMaxX(), innerRect.getMinY()),
		cpv(innerRect.getMaxX(), innerRect.getMaxY()), 0.0f);

	for (int i = 0; i<4; i++) {
		_walls[i]->e = 1.0f;
		_walls[i]->u = 1.0f;
		cpSpaceAddStaticShape(_space, _walls[i]);
	}

	// Physics debug layer
	_debugLayer = PhysicsDebugNode::create(_space);
	this->addChild(_debugLayer, 100);
}
