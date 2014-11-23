#include "Airplane.h"
#include "Helpers.h"
#include "Character.h"
#include "../passenger/Passenger.h"
#include "../passenger/Steward.h"
#include "../passenger/Trolley.h"
#include "Toilet.h"
#include "json/document.h"
#include "../scenes/SceneGame.h"
#include <iomanip>

USING_NS_CC;

Airplane::~Airplane() {
    m_arrBananas->release();
    m_arrBoobliks->release();
}

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

    float x = 0;
    float y = 0;
    { // кабина пилота
        auto innerRect = Rect(1410, 80, 534, 400);
        auto wall = Node::create();
        wall->setPhysicsBody(PhysicsBody::createEdgeBox(innerRect.size, PhysicsMaterial(0.1f, 1, 0.0f)));
        wall->setPositionY(innerRect.getMinY());
        wall->setPositionX(innerRect.getMinX());
        x = innerRect.getMinX();
        y = innerRect.getMinY() + 400;
        this->addChild(wall);
    }
    { // толстый потолок
        auto bottom = Node::create();
        PhysicsBody* bodyBottom = PhysicsBody::createBox(Size(604, 410), PhysicsMaterial(0.1f, 1, 0.0f));
        bodyBottom->setDynamic(false);
        bottom->setPhysicsBody(bodyBottom);
        bottom->setPositionX(x + 30);
        bottom->setPositionY(y - 800);
        this->addChild(bottom);
    }
    { // толстый пол
        auto bottom = Node::create();
        PhysicsBody* bodyBottom = PhysicsBody::createBox(Size(1204, 410), PhysicsMaterial(0.1f, 1, 0.0f));
        bodyBottom->setDynamic(false);
        bottom->setPhysicsBody(bodyBottom);
        bottom->setPositionX(x + 100);
        bottom->setPositionY(y);
        this->addChild(bottom);
    }
    { // толстая левая стенка пилота
        auto bottom = Node::create();
        PhysicsBody* bodyBottom = PhysicsBody::createBox(Size(50, 480), PhysicsMaterial(0.1f, 1, 0.0f));
        bodyBottom->setDynamic(false);
        bottom->setPhysicsBody(bodyBottom);
        bottom->setPositionX(x - 280);
        bottom->setPositionY(y - 400);
        this->addChild(bottom);
    }
	auto sprite = Sprite::create("airplane/airplane.png");
	sprite->setPosition(Vec2(888,0));
	this->addChild(sprite, -10);

	auto toilet = Toilet::create();
	addChild(toilet);
    
    _sensor = Sprite::create("airplane/sensor/0.png");
    _sensor->setPosition(1307, -210);
    _sensor->setScaleX(1.1f);
    addChild(_sensor);
    

	Steward* steward = Steward::create();
	this->addChild(steward);

	Trolley* trolley = Trolley::create();
	this->addChild(trolley);
	steward->assignTrolley(trolley);

	for (int i = 0; i < 4; i++)
	{
		std::stringstream ss;
		ss << "airplane/people/passengers/" << std::setfill('0') << std::setw(4) << (i % 3) << "/";

		Passenger* passenger = Passenger::create(ss.str(), Vec2(340 + i * 230, 40));
		passenger->assignToilet(toilet);
		passenger->assignTrolley(trolley);
		this->addChild(passenger);
        createChair(passenger->getPosition() + Vec2(25, -75));
	}

    _pilot = Pilot::create();
    _pilot->setPosition(1440, 50);
    addChild(_pilot);

	auto* alarm = Sprite::create("airplane/alarm.png");
	alarm->setPosition(Vec2(1300, 150));
	this->addChild(alarm);
	RotateBy* rotateBy = RotateBy::create(0.7, 360);
	alarm->runAction(RepeatForever::create(rotateBy));

	loadBaggage();
    creatHandLuggageSpaces();
    
	return true;
}

void Airplane::loadBaggage()
{
    auto hillock = Node::create();
    PhysicsBody* body = PhysicsBody::createCircle(30);
    body->setDynamic(false);
    hillock->setPhysicsBody(body);
    hillock->setPosition(830,-302);
    this->addChild(hillock);
    
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


void Airplane::setAraplaneIsMoved(bool flag){
    _pilot->setAraplaneIsMoved(flag);
}

void Airplane::createChair(Vec2 passengetPosition){
    auto* chair = Sprite::create("airplane/chair.png");
    chair->setPosition(passengetPosition);
	chair->setColor(Color3B(255, 255, 255));
    this->addChild(chair,1);
}
    
void Airplane::makeChain() {
    
    {
        m_arrBananas = __Array::create();
        m_arrBananas->retain();
        
        Vec2 start_banan = Vec2(1230, 290);
        auto sprite = Sprite::create("airplane/alpha_pixel.png");
        PhysicsMaterial material(0.1f, 0.15f, 0.1f);
        PhysicsBody* body = PhysicsBody::createBox(sprite->getContentSize(), material);
        body->setDynamic(false);
        sprite->setPhysicsBody(body);
        this->addChild(sprite);
        sprite->setPosition(start_banan);

        PhysicsBody* prev_body = body;
        for ( int i = 1; i < 6; i++) {
            auto sprite = Sprite::create("airplane/banana.png");
            PhysicsMaterial material(0.1f, 0.15f, 0.1f);
            PhysicsBody* body = PhysicsBody::createBox(sprite->getContentSize(), material);
            sprite->setPhysicsBody(body);
            body->setDynamic(true);
            PhysicsJointLimit* joint = PhysicsJointLimit::construct(prev_body, body, Vec2(0.5, 0.5), Vec2(0.5, 0.5), 10, 50);
            SceneGame* game = static_cast<SceneGame*>(getParent());
            game->getPhysicsWorld()->addJoint(joint);
            
            prev_body = body;
            this->addChild(sprite);
            sprite->setPosition(start_banan.x, start_banan.y - 10 * i);
            
            m_arrBananas->addObject((Ref*)joint);
        }
    }
    /////////////////////////////////////////////////////////////////////////////////////////
    {
        m_arrBoobliks = __Array::create();
        m_arrBoobliks->retain();
        
        Vec2 start_banan = Vec2(1400, 290);
        auto sprite = Sprite::create("airplane/alpha_pixel.png");
        PhysicsMaterial material(0.1f, 0.15f, 0.1f);
        PhysicsBody* body = PhysicsBody::createBox(sprite->getContentSize(), material);
        body->setDynamic(false);
        sprite->setPhysicsBody(body);
        this->addChild(sprite);
        sprite->setPosition(start_banan);
        
        PhysicsBody* prev_body = body;
        for ( int i = 1; i < 5; i++) {
            auto sprite = Sprite::create("airplane/booblik.png");
            PhysicsMaterial material(0.1f, 0.15f, 0.1f);
            PhysicsBody* body = PhysicsBody::createBox(sprite->getContentSize(), material);
            sprite->setPhysicsBody(body);
            body->setDynamic(true);
            PhysicsJointLimit* joint = PhysicsJointLimit::construct(prev_body, body, Vec2(0.5, 0.5), Vec2(0.5, 0.5), 10, 50);
            SceneGame* game = static_cast<SceneGame*>(getParent());
            game->getPhysicsWorld()->addJoint(joint);
            
            prev_body = body;
            this->addChild(sprite);
            sprite->setPosition(start_banan.x, start_banan.y - 10 * i);
            m_arrBoobliks->addObject((Ref*)joint);
        }
    }
}

void Airplane::dropSomething() {
    PhysicsJointLimit* joint = nullptr;
    if (rand() % 2 == 0) { // уронить баранку
        if (m_arrBoobliks && m_arrBoobliks->count() > 0) {
            joint = (PhysicsJointLimit*)m_arrBoobliks->getLastObject();
            m_arrBoobliks->removeLastObject();
        }
    } else { // уронить банан
        if (m_arrBananas && m_arrBananas->count() > 0) {
            joint = (PhysicsJointLimit*)m_arrBananas->getLastObject();
            m_arrBananas->removeLastObject();
        }
    }
    if (joint) {
        SceneGame* game = static_cast<SceneGame*>(getParent());
        game->getPhysicsWorld()->removeJoint(joint);
    }
}

void Airplane::updateAirplane(float dt){
    updateSensor();
}

void Airplane::updateSensor(){
    if(!(_coutnUpdate % 5)){
        std::string dirName = "airplane/sensor";
        std::stringstream ss;
        int index = (_coutnUpdate / 5) % 3;
        ss << dirName << "/"  << index << ".png";
        _sensor->setTexture(ss.str());
    }
    _coutnUpdate++;
}

void Airplane::removeJoints() {
    for (int i = 0; i < 15; i++) {
        if (m_arrBoobliks && m_arrBoobliks->count() > 0) {
            PhysicsJointLimit* joint = (PhysicsJointLimit*)m_arrBoobliks->getLastObject();
            m_arrBoobliks->removeLastObject();
            if (joint) {
                SceneGame* game = static_cast<SceneGame*>(getParent());
                game->getPhysicsWorld()->removeJoint(joint);
            }
        }
        if (m_arrBananas && m_arrBananas->count() > 0) {
            PhysicsJointLimit* joint = (PhysicsJointLimit*)m_arrBananas->getLastObject();
            m_arrBananas->removeLastObject();
            if (joint) {
                SceneGame* game = static_cast<SceneGame*>(getParent());
                game->getPhysicsWorld()->removeJoint(joint);
            }
        }
    }
}


void Airplane::creatHandLuggageSpaces(){
    for (int i = 0; i < 4; i++)
    {
        Sprite* handLuggageSpace = Sprite::create("airplane/hand_luggage_spaces.png");
        handLuggageSpace->setPosition(Vec2(350 + i * 225, 200 ));
        this->addChild(handLuggageSpace);
    }
}
