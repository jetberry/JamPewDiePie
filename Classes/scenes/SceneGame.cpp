#include "SceneGame.h"
#include "../Helpers.h"
#include "../airplane/Character.h"
#include "UserGameData.h"

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
    
    NotificationCenter::getInstance()->addObserver(this, CC_CALLFUNCO_SELECTOR(SceneGame::onAddScore), "MSG_UPDATE_SCORE", nullptr);
    
    _airplaneState = AirplaneStateNone;

//	this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	this->getPhysicsWorld()->setGravity(Point::UNIT_Y * -1000);
    this->getPhysicsWorld()->setAutoStep(true);

	// Blue background (sky).
	auto background = LayerColor::create(Color4B(100, 100, 255, 255));
	this->addChild(background, 0);

	sky = Sky::create();
	this->addChild(sky);

	airplan = Airplane::create();
    helpers::setDesignPosEx(airplan, 1366, 0);
//    helpers::setDesignPosEx(airplan, 1566, 0);
	this->addChild(airplan);
    _airplanePosition = airplan->getPosition();

	ui::Button* btnUp = ui::Button::create("menu/play.png");
    btnUp->setRotation(-90);
	btnUp->setPosition(Vec2(1800, 200));
	btnUp->addTouchEventListener(CC_CALLBACK_2(SceneGame::onUp, this));
	btnUp->setPressedActionEnabled(true);
	this->addChild(btnUp);
    
    ui::Button* btnDown = ui::Button::create("menu/play.png");
    btnDown->setRotation(90);
    btnDown->setPosition(Vec2(2200, 200));
    btnDown->addTouchEventListener(CC_CALLBACK_2(SceneGame::onDown, this));
    btnDown->setPressedActionEnabled(true);
    this->addChild(btnDown);
    
    ui::Button* btnShake = ui::Button::create("menu/shake.png");
    btnShake->setPosition(Vec2(1400, 200));
    btnShake->addTouchEventListener(CC_CALLBACK_2(SceneGame::onShake, this));
    btnShake->setPressedActionEnabled(true);
    this->addChild(btnShake);

    _labelScore = Label::create();
    _labelScore->setPosition(Vec2(2200, 1436));
    _labelScore->setTextColor(Color4B::BLACK);
    _labelScore->setSystemFontSize(100);
    onAddScore(nullptr);
    
    this->addChild(_labelScore);
    

	scheduleUpdate();
    
	return true;
}

void SceneGame::onUp(Ref *pSender, ui::Widget::TouchEventType type)
{
    if(type == ui::Widget::TouchEventType::BEGAN){
        _airplaneState = AirplaneStateUp;
    }else if(type ==  ui::Widget::TouchEventType::ENDED ||
             type ==  ui::Widget::TouchEventType::CANCELED){
        _airplaneState = AirplaneStateNone;
    }
}

void SceneGame::onDown(Ref *pSender, ui::Widget::TouchEventType type)
{
    if(type == ui::Widget::TouchEventType::BEGAN){
        _airplaneState = AirplaneStateDown;
    }else if(type ==  ui::Widget::TouchEventType::ENDED||
             type ==  ui::Widget::TouchEventType::CANCELED){
        _airplaneState = AirplaneStateNone;
    }
}

void SceneGame::onShake(Ref *pSender, ui::Widget::TouchEventType type)
{
    if(type == ui::Widget::TouchEventType::BEGAN){
        UserGameData::getInstance()->addScore(500);
        
        airplan->stopAllActions();
        airplan->setPosition(_airplanePosition);
        float _time = 0.08f;
        
        MoveBy* moveUp = MoveBy::create(_time, Vec2(0,200));
        CallFunc* chageGravityUp = CallFunc::create(CC_CALLBACK_0(SceneGame::gravityShakeUp, this));

        MoveBy* moveDown = MoveBy::create(_time, Vec2(0,-200));
        CallFunc* chageGravityDown = CallFunc::create(CC_CALLBACK_0(SceneGame::gravityShakeDown, this));
        Sequence* squence = Sequence::create(moveUp,chageGravityUp,moveDown,chageGravityDown, NULL);
        
        Repeat* repeat = Repeat::create(squence, 10);
        
        MoveTo* moveTo = MoveTo::create(_time, _airplanePosition);
        CallFunc* chageGravityOff = CallFunc::create(CC_CALLBACK_0(SceneGame::gravityShakeOff, this));
        Sequence* squenceAll = Sequence::create(repeat,moveTo,chageGravityOff,NULL);

        airplan->runAction(squenceAll);
    }
}

void SceneGame::gravityShakeUp(){
    this->getPhysicsWorld()->setGravity(Point::UNIT_Y * 35000);
}

void SceneGame::gravityShakeDown(){
    this->getPhysicsWorld()->setGravity(Point::UNIT_Y * -35000);
}

void SceneGame::gravityShakeOff(){
    this->getPhysicsWorld()->setGravity(Point::UNIT_Y * -1000);
}

void SceneGame::onAddScore(Ref* obj){
    int score = UserGameData::getInstance()->getScore();
    _labelScore->setString(__String::createWithFormat("%d",score)->getCString());
}

void SceneGame::update(float dt)
{
    if(_airplaneState == AirplaneStateUp){
        if(airplan->getRotation() > - 15)
            airplan->setRotation(airplan->getRotation() - 0.5f);
    }else if(_airplaneState == AirplaneStateDown){
        if(airplan->getRotation() <  15)
            airplan->setRotation(airplan->getRotation() + 0.5f);
    }else if(_airplaneState == AirplaneStateShake){
        
    }
	Scene::update(dt);

	Vec2 airplaneVector = Vec2::forAngle(CC_DEGREES_TO_RADIANS(airplan->getRotation()));
	airplaneVector.x = -airplaneVector.x;
	airplaneVector *= 30;
	sky->setVector(airplaneVector);
}

