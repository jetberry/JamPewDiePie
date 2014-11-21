#include "SceneMenu.h"
#include "../Helpers.h"

USING_NS_CC;

Scene* SceneMenu::createScene()
{
	auto scene = Scene::create();
	auto layer = SceneMenu::create();
	scene->addChild(layer);
	return scene;
}

bool SceneMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto sprite = Sprite::create("menu/airplane.png");
	helpers::setDesignPos(sprite, 766, 49);
	this->addChild(sprite, 0);

	return true;
}
