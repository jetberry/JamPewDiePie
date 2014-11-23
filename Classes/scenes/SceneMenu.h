#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"

using namespace cocos2d;
using namespace extension;
using namespace ui;

class SceneGame;
class SceneMenu : public cocos2d::Layer
{
public:

	static cocos2d::Scene* createScene();
	virtual bool init();

	CREATE_FUNC(SceneMenu);

    void setDelegate(SceneGame* delegate);
private:
    void menuPlayCallback(Ref * sender, Control::EventType controlEvent);
    void changeTutorialText();
    
    int m_clickCount;
    ControlButton* m_buttonPlay;
    Label* m_labelTutorial;
    
    SceneGame* m_delegate;
    
    Sprite* m_spriteTitle;
};

