#include "Airplane.h"
#include "Helpers.h"
#include "Character.h"
#include "../passenger/Passenger.h"
#include "../passenger/Steward.h"
#include "../passenger/Trolley.h"
#include "Toilet.h"
#include "json/document.h"

USING_NS_CC;

bool Airplane::init()
{
	// wall
	auto innerRect = Rect(667 - 192, 528, 1334, 556);
	auto wall = Node::create();
	wall->setPhysicsBody(PhysicsBody::createEdgeBox(innerRect.size, PhysicsMaterial(0.1f, 1, 0.0f)));
	wall->setPosition(Vec2());
    wall->setPositionX(innerRect.getMinX());
	this->addChild(wall);
    
    auto bottom = Node::create();
    PhysicsBody* bodyBottom = PhysicsBody::createBox(Size(1334, 10), PhysicsMaterial(0.1f, 1, 0.0f));
    bodyBottom->setDynamic(false);
    bottom->setPhysicsBody(bodyBottom);
    bottom->setPositionX(wall->getPositionX());
    bottom->setPositionY(-300/2 + 10);
    this->addChild(bottom);
    

	auto sprite = Sprite::create("airplane/airplane.png");
	sprite->setPosition(Vec2(888,0));
	this->addChild(sprite, 0);

	auto toilet = Toilet::create();
	addChild(toilet);

	for (int i = 0; i < 4; i++)
	{
		Passenger* passenger = Passenger::create();
		passenger->setSeatPosition(Vec2(350 + i * 230, 4));
		passenger->assignToilet(toilet);
		this->addChild(passenger);
	}

	Steward* steward = Steward::create();
	this->addChild(steward);

	Trolley* trolley = Trolley::create();
	this->addChild(trolley);
	steward->assignTrolley(trolley);


	auto* part0 = Sprite::create("airplane/passengers/part.png");
	part0->setPosition(Vec2(1042, -28));
	this->addChild(part0);


	auto* alarm = Sprite::create("airplane/alarm.png");
	alarm->setPosition(Vec2(1250, 150));
	this->addChild(alarm);
	RotateBy* rotateBy = RotateBy::create(0.5, 360);
	alarm->runAction(RepeatForever::create(rotateBy));


	loadBaggage();

	return true;
}

void Airplane::loadBaggage()
{
	std::string content = FileUtils::getInstance()->getStringFromFile("json/luggage.json");

	rapidjson::Document doc;
	doc.Parse<0>(content.c_str());
	if (doc.HasParseError())
		return;

	const rapidjson::Value& luggage = doc["luggage"];
	for (rapidjson::Value::ConstValueIterator i = luggage.onBegin(); i != luggage.onEnd(); ++i)
	{
		double x = (*i)["x"].GetDouble();
		double y = (*i)["y"].GetDouble();
		std::string file = (*i)["file"].GetString();

		CCLOG("create luggage: %f, %f, %s", x, y, file.c_str());
		auto l = Sprite::create(file);
		PhysicsMaterial material(0.1f, 0.15f, 0.1f);
		PhysicsBody* body = PhysicsBody::createBox(l->getContentSize(), material);
		l->setPhysicsBody(body);
		l->setPosition(x, y);
		this->addChild(l);
	}
}




