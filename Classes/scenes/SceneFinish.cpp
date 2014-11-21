#include "SceneFinish.h"
#include "../Helpers.h"

USING_NS_CC;

Scene* SceneFinish::createScene()
{
	auto scene = Scene::create();
	auto layer = SceneFinish::create();
	scene->addChild(layer);
	return scene;
}

bool SceneFinish::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto background = LayerColor::create(Color4B(255, 255, 255, 255));
	this->addChild(background, 0);

	auto sprite = Sprite::create("menu/game_over.png");
	helpers::setDesignPos(sprite, 792, 422);
	this->addChild(sprite, 0);

	return true;
}
