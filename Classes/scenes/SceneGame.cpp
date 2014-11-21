#include "SceneGame.h"
#include "../Helpers.h"
#include "../airplane/Airplane.h"
#include "../airplane/Character.h"

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
	this->getPhysicsWorld()->setGravity(Point::UNIT_Y * -1000);
    this->getPhysicsWorld()->setAutoStep(true);

	auto background = LayerColor::create(Color4B(100, 100, 255, 255));
	this->addChild(background, 0);

	airplan = Airplane::create();
//	helpers::setOnCenter(airplan);
    helpers::setDesignPosEx(airplan, 1366, 0);
	this->addChild(airplan);

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

    
	return true;
}

void SceneGame::onUp(Ref *pSender, ui::Widget::TouchEventType type)
{
    if(airplan->getRotation() > - 15)
        airplan->setRotation(airplan->getRotation() - 1);
}

void SceneGame::onDown(Ref *pSender, ui::Widget::TouchEventType type)
{
    if(airplan->getRotation() <  15)
        airplan->setRotation(airplan->getRotation() + 1);
}
