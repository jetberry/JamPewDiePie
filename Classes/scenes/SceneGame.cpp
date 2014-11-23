#include "SceneGame.h"
#include "../Helpers.h"
#include "../airplane/Character.h"
#include "../SoundManager/SoundManager.h"
#include "UserGameData.h"

USING_NS_CC;

SceneGame* SceneGame::createWithPhysics()
{
	SceneGame *ret = new (std::nothrow) SceneGame();
	if (ret && ret->initWithPhysics())
	{
		ret->autorelease();
		return ret;
	}
	else
	{
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}

bool SceneGame::initWithPhysics()
{
	if (!Scene::initWithPhysics())
	{
		return false;
	}
    airplan = nullptr;
    NotificationCenter::getInstance()->addObserver(this, CC_CALLFUNCO_SELECTOR(SceneGame::onAddScore), "MSG_UPDATE_SCORE", nullptr);

//	this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	this->getPhysicsWorld()->setGravity(Point::UNIT_Y * -1000);
    this->getPhysicsWorld()->setAutoStep(true);

	// Blue background (sky).
	background = LayerColor::create(Color4B(223, 247, 248, 255));
	this->addChild(background, 0);
    tintDelay = 7.0;
    runTint();
    
	sky = Sky::create();
	this->addChild(sky);
    
    btnShake = ui::Button::create("gamebuttons/button_shake.png", "gamebuttons/button_shake_h.png");
    btnShake->setPosition(Vec2(Director::getInstance()->getOpenGLView()->getDesignResolutionSize().width - btnShake->getContentSize().width - 50,
                               btnShake->getContentSize().height / 2));
    btnShake->addTouchEventListener(CC_CALLBACK_2(SceneGame::onShake, this));
    btnShake->setPressedActionEnabled(true);
    btnShake->setZoomScale(false);
    btnShake->setZOrder(1);
    this->addChild(btnShake);

    btnDown = ui::Button::create("gamebuttons/button_up.png", "gamebuttons/button_up_h.png");
    btnDown->setPosition(Vec2(btnShake->getPositionX() - btnShake->getContentSize().width,
                              btnDown->getContentSize().height / 2));
    btnDown->addTouchEventListener(CC_CALLBACK_2(SceneGame::onDown, this));
    btnDown->setPressedActionEnabled(true);
    btnDown->setZoomScale(false);
    btnDown->setZOrder(1);
    this->addChild(btnDown);
    btnDown->setFlippedY(true);
    
	btnUp = ui::Button::create("gamebuttons/button_up.png", "gamebuttons/button_up_h.png");
	btnUp->setPosition(Vec2(btnDown->getPositionX() - btnShake->getContentSize().width,
                            btnUp->getContentSize().height / 2));
	btnUp->addTouchEventListener(CC_CALLBACK_2(SceneGame::onUp, this));
	btnUp->setPressedActionEnabled(true);
    btnUp->setZoomScale(false);
	btnUp->setZOrder(1);
    this->addChild(btnUp);
    
    btnUp->setPositionY(-500);
    btnShake->setPositionY(-500);
    btnDown->setPositionY(-500);
    
    _labelScore = Label::createWithTTF("hello", "HelveticaNeue-Bold.ttf", 100);
    _labelScore->setPosition(Vec2(2200, 1436));
    _labelScore->setTextColor(Color4B::BLACK);
    onAddScore(nullptr);
    _labelScore->setOpacity(0);
    this->addChild(_labelScore);
    
//    m_menu = SceneMenu::create();
//    m_menu->setDelegate(this);
//    addChild(m_menu);
    showPlane();
    
	scheduleUpdate();
    
    setState(AirplaneStateNone);
    
	return true;
}

void SceneGame::onUp(Ref *pSender, ui::Widget::TouchEventType type)
{
    if(type == ui::Widget::TouchEventType::BEGAN){
        setState(AirplaneStateUp);
        SoundManager::getInstance()->playSound(sound_power_up, false, 0.5);
    }else if(type ==  ui::Widget::TouchEventType::ENDED ||
             type ==  ui::Widget::TouchEventType::CANCELED){
        setState(AirplaneStateNone);
        SoundManager::getInstance()->pauseSound(sound_power_up);
    }
}

void SceneGame::onDown(Ref *pSender, ui::Widget::TouchEventType type)
{
    if(type == ui::Widget::TouchEventType::BEGAN){
        setState(AirplaneStateDown);
        SoundManager::getInstance()->playSound(sound_power_down, false, 0.5);
    }else if(type ==  ui::Widget::TouchEventType::ENDED||
             type ==  ui::Widget::TouchEventType::CANCELED){
        setState(AirplaneStateNone);
        SoundManager::getInstance()->pauseSound(sound_power_down);
    }
}

void SceneGame::onShake(Ref *pSender, ui::Widget::TouchEventType type)
{
//    // code for RESTART !!!!!!!!!!!!!!!!!!!!!!!
//    if (!airplan) return;
//    airplan->removeJoints();
//    airplan->removeFromParent();
//    airplan = nullptr;
//    auto scene = SceneGame::createWithPhysics();
//    Director::getInstance()->replaceScene(scene);
//    return;
    
    if(type == ui::Widget::TouchEventType::BEGAN){
        UserGameData::getInstance()->addScore(500);
        
        SoundManager::getInstance()->pauseSound(sound_best_loop);
        SoundManager::getInstance()->playSound(sound_harkem_shake, false, 0.8);
        
        airplan->stopAllActions();
        airplan->setPosition(_airplanePosition);
        float _time = 0.09f;
        
        MoveBy* moveUp = MoveBy::create(_time, Vec2(0,200));
        CallFunc* chageGravityUp = CallFunc::create(CC_CALLBACK_0(SceneGame::gravityShakeUp, this));

        MoveBy* moveDown = MoveBy::create(_time, Vec2(0,-200));
        CallFunc* chageGravityDown = CallFunc::create(CC_CALLBACK_0(SceneGame::gravityShakeDown, this));
        Sequence* squence = Sequence::create(moveUp, chageGravityUp, moveDown, chageGravityDown, NULL);
        
        Repeat* repeat = Repeat::create(squence, 20);
        
        MoveTo* moveTo = MoveTo::create(_time, _airplanePosition);
        CallFunc* chageGravityOff = CallFunc::create(CC_CALLBACK_0(SceneGame::gravityShakeOff, this));
        Sequence* squenceAll = Sequence::create(DelayTime::create(2.2), repeat,moveTo,chageGravityOff,NULL);

        airplan->runAction(squenceAll);

        tintDelay = 0.1;
        airplan->runAction(Sequence::create(DelayTime::create(2.0), CallFunc::create(CC_CALLBACK_0(SceneGame::runTint, this)), nullptr));
        airplan->runAction(Sequence::create(DelayTime::create(2.2), CallFunc::create(CC_CALLBACK_0(SceneGame::playScream, this)), nullptr));
    }
}

void SceneGame::gravityShakeUp(){
    this->getPhysicsWorld()->setGravity(Point::UNIT_Y * 35000);
}

void SceneGame::gravityShakeDown(){
    this->getPhysicsWorld()->setGravity(Point::UNIT_Y * -35000);
}

void SceneGame::gravityShakeOff(){
    this->getPhysicsWorld()->setGravity(Point::UNIT_Y * -1000);
    SoundManager::getInstance()->pauseSound(sound_scream_1);
    SoundManager::getInstance()->pauseSound(sound_scream_2);
    SoundManager::getInstance()->resumeSound(sound_best_loop);
    tintDelay = 8.0;
    runTint();
    airplan->dropSomething();
}

void SceneGame::playScream() {
    int t = rand() % 3;
    if (t == 0) {
        SoundManager::getInstance()->playSound(sound_scream_1, false, 1.0);
    } else if (t == 1) {
        SoundManager::getInstance()->playSound(sound_scream_2, false, 1.0);
    } else {
        SoundManager::getInstance()->playSound(sound_haha, false, 1.0);
    }
}

void SceneGame::onAddScore(Ref* obj){
    int score = UserGameData::getInstance()->getScore();
    _labelScore->setString(__String::createWithFormat("%d",score)->getCString());
}

void SceneGame::update(float dt)
{
    if(_airplaneState == AirplaneStateUp){
        if(airplan->getRotation() > - 15){
            airplan->stopActionByTag(10);
            airplan->setRotation(airplan->getRotation() - 0.5f);
        }else{
            setState(AirplaneStateNone);
        }
    }else if(_airplaneState == AirplaneStateDown){
        if(airplan->getRotation() <  15){
            airplan->stopActionByTag(10);
            airplan->setRotation(airplan->getRotation() + 0.5f);
        }else{
            setState(AirplaneStateNone);
        }
    }else if(_airplaneState == AirplaneStateShake){
        
    }else{
        if(!(_countUpdate % 25)){
        _tumbler = !_tumbler;
        if(_tumbler){
            RotateBy* action = RotateBy::create(0.4, 0.5);
            action->setTag(10);
            airplan->runAction(action);
        }else{
            RotateBy* action = RotateBy::create(0.4, -0.5);
            action->setTag(10);
            airplan->runAction(action);
        }
        }
    }
    _countUpdate++;
    airplan->updateAirplane(dt);
	Scene::update(dt);

	Vec2 airplaneVector = Vec2::forAngle(CC_DEGREES_TO_RADIANS(airplan->getRotation()));
	airplaneVector.x = -airplaneVector.x;
	airplaneVector *= 30;
	sky->setVector(airplaneVector);

    Scene::update(dt);
    if (airplan) {
        if(_airplaneState == AirplaneStateUp){
            if(airplan->getRotation() > - 15)
                airplan->setRotation(airplan->getRotation() - 0.5f);
        }else if(_airplaneState == AirplaneStateDown){
            if(airplan->getRotation() <  15)
                airplan->setRotation(airplan->getRotation() + 0.5f);
        }else if(_airplaneState == AirplaneStateShake){
            
        }
        
        Vec2 airplaneVector = Vec2::forAngle(CC_DEGREES_TO_RADIANS(airplan->getRotation()));
        airplaneVector.x = -airplaneVector.x;
        airplaneVector *= 30;
        sky->setVector(airplaneVector);
    }
}

void SceneGame::showPlane() {
    airplan = Airplane::create();
    this->addChild(airplan);
    helpers::setDesignPosEx(airplan, 1650, 0);
    _airplanePosition = airplan->getPosition();
    airplan->makeChain();
    
    _labelScore->runAction(FadeTo::create(0.2, 255));
    Vec2 pos = helpers::setDesignPosEx(airplan, 1650, 0);
    airplan->setPositionX(-3000);
    
    MoveTo* move = MoveTo::create(2.0, pos);
    airplan->runAction(move);
    
    {
        MoveTo* move = MoveTo::create(0.25, Vec2(btnUp->getPositionX(), btnUp->getContentSize().height / 2));
        EaseBackOut* back = EaseBackOut::create(move);
        btnUp->runAction(Sequence::create(DelayTime::create(0.3), back, nullptr));
    }
    {
        MoveTo* move = MoveTo::create(0.25, Vec2(btnDown->getPositionX(), btnDown->getContentSize().height / 2));
        EaseBackOut* back = EaseBackOut::create(move);
        btnDown->runAction(Sequence::create(DelayTime::create(0.15), back, nullptr));
    }
    {
        MoveTo* move = MoveTo::create(0.25, Vec2(btnShake->getPositionX(), btnShake->getContentSize().height / 2));
        EaseBackOut* back = EaseBackOut::create(move);
        btnShake->runAction(back);
    }
}

void SceneGame::setState(AirplaneState state){
    if(state == AirplaneStateNone){
        airplan->setAraplaneIsMoved(false);
    }else{
        airplan->setAraplaneIsMoved(true);
    }
    _airplaneState = state;
}

void SceneGame::runTint() {
    float time = tintDelay;
    TintTo* tint_1 = TintTo::create(time, 123, 126, 241);
    TintTo* tint_2 = TintTo::create(time, 42, 44, 111);
    TintTo* tint_3 = TintTo::create(time, 66, 218, 245);
    TintTo* tint_4 = TintTo::create(time, 245, 176, 55);
    TintTo* tint_5 = TintTo::create(time, 223, 247, 248);
    TintTo* tint_6 = TintTo::create(time, 50, 236, 98);
    TintTo* tint_7 = TintTo::create(time, 243, 54, 241);
    TintTo* tint_8 = TintTo::create(time, 22, 22, 100);
    
    background->stopAllActions();
    background->runAction(RepeatForever::create(Sequence::create(tint_1, tint_2, tint_3, tint_4, tint_5, tint_6, tint_7, tint_8, NULL)));
}




