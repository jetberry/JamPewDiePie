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
	helpers::setOnCenter(airplan);
	this->addChild(airplan);

	ui::Button* btnBack = ui::Button::create("menu/play.png");
	btnBack->setPosition(Vec2(2000, 200));
	//helpers::setDesignPosEx(btnBack, 2000, 200);
	btnBack->addTouchEventListener(CC_CALLBACK_2(SceneGame::touchEvent, this));
	//btnBack->setZoomScale(0.4f);
	btnBack->setPressedActionEnabled(true);
	this->addChild(btnBack);

    
	return true;
}

void SceneGame::touchEvent(Ref *pSender, ui::Widget::TouchEventType type)
{
	airplan->setRotation(airplan->getRotation() + 10);
}
