#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "../sky/Sky.h"
#include "SceneMenu.h"
#include "../airplane/Airplane.h"

class SceneGame : public cocos2d::Scene
{
public:

	static SceneGame* createWithPhysics();

	virtual bool initWithPhysics();
    
    void showPlane();
private:
    
    enum AirplaneState{
        AirplaneStateNone,
        AirplaneStateUp,
        AirplaneStateDown,
        AirplaneStateShake,
    };

	void onUp(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    void onDown(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    void onShake(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    
    void onAddScore(Ref* obj);
    
    void setState(AirplaneState state);
    
    void gravityShakeUp();
    void gravityShakeDown();
    void gravityShakeOff();
    
	void update(float dt);
    
    void runTint();
    
    Airplane* airplan;
    Sky* sky;
    
    AirplaneState _airplaneState;
    
    int _shakeCount;
    
    cocos2d::Label* _labelScore;
    
    cocos2d::Vec2 _airplanePosition;
    
    bool _tumbler;
    int _countUpdate;

    SceneMenu* m_menu;
    
    ui::Button* btnUp;
    ui::Button* btnDown;
    ui::Button* btnShake;
    
    LayerColor* background;
    float tintDelay;
};
