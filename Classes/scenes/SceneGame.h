#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "../sky/Sky.h"
#include "../airplane/Airplane.h"

class SceneGame : public cocos2d::Scene
{
public:

	CREATE_FUNC(SceneGame);

	static SceneGame* createWithPhysics();

	virtual bool initWithPhysics();

private:
    
    enum AirplaneState{
        AirplaneStateNone,
        AirplaneStateUp,
        AirplaneStateDown,
        AirplaneStateShake,
    };

	Airplane* airplan;
	Sky* sky;
    
    AirplaneState _airplaneState;
    
    int _shakeCount;
    
    cocos2d::Vec2 _airplanePosition;

	void onUp(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    void onDown(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    void onShake(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    
    void gravityShakeUp();
    void gravityShakeDown();
    void gravityShakeOff();
    
	void update(float dt);
};
