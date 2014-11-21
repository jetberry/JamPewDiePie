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

	auto background = LayerColor::create(Color4B(255, 255, 255, 255));
	this->addChild(background, 0);

	auto sprite = Sprite::create("menu/airplane.png");
	helpers::setDesignPos(sprite, 766, 49);
	this->addChild(sprite, 0);

    auto playItem = MenuItemImage::create(
                                           "menu/play.png",
                                           "menu/play_pressed.png",
										   CC_CALLBACK_1(SceneMenu::menuPlayCallback, this));
    
	helpers::setDesignPos(playItem, 1216, 1078);

	auto menu = Menu::create(playItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

	return true;
}

void SceneMenu::menuPlayCallback(Ref* pSender)
{

}
