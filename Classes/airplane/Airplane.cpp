#include "Airplane.h"
#include "Helpers.h"
#include "Character.h"

USING_NS_CC;

bool Airplane::init()
{
	// wall
	auto innerRect = Rect(369 + 342, 528, 1270, 556);
	auto wall = Node::create();
	wall->setPhysicsBody(PhysicsBody::createEdgeBox(innerRect.size, PhysicsMaterial(0.1f, 1, 0.0f)));
	wall->setPosition(Vec2());
    wall->setPositionX(innerRect.getMinX());
	this->addChild(wall);
    
    auto bottom = Node::create();
    PhysicsBody* bodyBottom = PhysicsBody::createBox(Size(1270, 10), PhysicsMaterial(0.1f, 1, 0.0f));
    bodyBottom->setDynamic(false);
    bottom->setPhysicsBody(bodyBottom);
    bottom->setPositionX(wall->getPositionX());
    bottom->setPositionY(-326/2 + 10);
    this->addChild(bottom);
    

	auto sprite = Sprite::create("airplane/airplane.png");
    helpers::setDesignPosEx(sprite, 1366, 0);
//	sprite->setPosition(Vec2());
	this->addChild(sprite, 0);

	Character* character = Character::create("airplane/passenger_01.png");
	helpers::setDesignPosEx(character, 1500, 750);
	this->addChild(character);
    character->createBody();
    character->setBottom(bottom->getPhysicsBody());

	return true;
}
