#include "SceneGame.h"
#include "../Helpers.h"
#include "../airplane/Airplane.h"

USING_NS_CC;

SceneGame* SceneGame::createWithPhysics()
{
	SceneGame *ret = new (std::nothrow) SceneGame();
	if (ret && ret->initWithPhysics())
	{
		ret->autorelease();
		return ret;
	}
	else
	{
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}

bool SceneGame::initWithPhysics()
{
	if (!Scene::initWithPhysics())
	{
		return false;
	}

	this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	this->getPhysicsWorld()->setGravity(Point::ZERO);


	auto innerRect = Rect(369 + 342, 528, 1170, 526);

	// wall
	auto wall = Node::create();
	wall->setPhysicsBody(PhysicsBody::createEdgeBox(innerRect.size, PhysicsMaterial(0.1f, 1, 0.0f)));
	helpers::setOnCenter(wall);
	this->addChild(wall);

	auto background = LayerColor::create(Color4B(255, 255, 255, 255));
	this->addChild(background, 0);

	auto airplane = Airplane::create();
	this->addChild(airplane, 0);

	return true;
}
