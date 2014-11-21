#include "SceneGame.h"
#include "../Helpers.h"
#include "airplane/Airplane.h"

USING_NS_CC;

Scene* SceneGame::createScene()
{
	auto scene = Scene::create();
	auto layer = SceneGame::create();
	scene->addChild(layer);
	return scene;
}

bool SceneGame::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto background = LayerColor::create(Color4B(255, 255, 255, 255));
	this->addChild(background, 0);

	auto airplane = Airplane::create();
	this->addChild(airplane, 0);

	return true;
}
