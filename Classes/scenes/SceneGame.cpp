#include "SceneGame.h"
#include "../Helpers.h"

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

	auto sprite = Sprite::create("airplane/airplane.png");
	helpers::setOnCenter(sprite);
	this->addChild(sprite, 0);

	return true;
}
