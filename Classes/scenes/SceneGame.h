#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "../sky/Sky.h"
#include "SceneMenu.h"
#include "../airplane/Airplane.h"

class SceneGame : public cocos2d::Scene
{
public:
    ~SceneGame();
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
    void onChangePower(Ref* obj);
    
    void setState(AirplaneState state);
    
    void gravityShakeUp();
    void gravityShakeDown();
    void gravityShakeOff();
    
	void update(float dt);
    
    void runTint();
    void playScream();
    
    void createPopins();
    void runFewPopins(int count);
    
    void restart(Ref * sender, Control::EventType controlEvent);
    
    void showFinish();
    
    void checkActions();
    Airplane* airplan;
    Sky* sky;
    
    AirplaneState _airplaneState;
    
    int _shakeCount;
    
    bool _isGameOver;
    int _power;
    cocos2d::Label* _labelScore;
    cocos2d::Label* _labelPower;
    Sprite* _spriteEnergy;
    
    cocos2d::Vec2 _airplanePosition;
    
    bool _tumbler;
    int _countUpdate;

    SceneMenu* m_menu;
    
    ui::Button* btnUp;
    ui::Button* btnDown;
    ui::Button* btnShake;
    
    
    ControlButton* m_buttonRestart;
    
    LayerColor* background;
    float tintDelay;
    
    __Array* m_popins;
    Vector<SpriteFrame*> animFrames;
    Vector<__Integer*> planeMoves;
};
