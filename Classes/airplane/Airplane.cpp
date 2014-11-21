#include "Airplane.h"
#include "Helpers.h"
#include "Character.h"

USING_NS_CC;

bool Airplane::init()
{
	// wall
	auto innerRect = Rect(369 + 342, 528, 1170, 526);
	auto wall = Node::create();
	wall->setPhysicsBody(PhysicsBody::createEdgeBox(innerRect.size, PhysicsMaterial(0.1f, 1, 0.0f)));
	wall->setPosition(Vec2());
	this->addChild(wall);
    
    auto bottom = Node::create();
    PhysicsBody* bodyBottom = PhysicsBody::createBox(Size(1170, 10), PhysicsMaterial(0.1f, 1, 0.0f));
    bodyBottom->setDynamic(false);
    bottom->setPhysicsBody(bodyBottom);
    bottom->setPositionX(wall->getPositionX());
    bottom->setPositionY(-526/2 + 10);
    this->addChild(bottom);
    

	auto sprite = Sprite::create("airplane/airplane.png");
	sprite->setPosition(Vec2());
	this->addChild(sprite, 0);

	Character* character = Character::create("airplane/passenger_01.png");
	//character->setPosition(1000, 750);
	helpers::setDesignPosEx(character, 1000, 750);
	this->addChild(character);
    character->createBody();
    character->setBottom(bottom->getPhysicsBody());

	return true;
}
