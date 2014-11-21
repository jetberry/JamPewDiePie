#include "SceneFinish.h"

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

	return true;
}
