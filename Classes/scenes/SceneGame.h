#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class SceneGame : public cocos2d::Scene
{
public:

	CREATE_FUNC(SceneGame);

	static SceneGame* createWithPhysics();

	virtual bool initWithPhysics();

private:

	cocos2d::Node* airplan;

	void onUp(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    
    void onDown(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
};
