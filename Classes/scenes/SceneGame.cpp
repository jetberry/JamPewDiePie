#include "SceneGame.h"
#include "../Helpers.h"
#include "../airplane/Character.h"
#include "../SoundManager/SoundManager.h"
#include "UserGameData.h"

USING_NS_CC;

#define TOTAL_POWER 150

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

SceneGame::~SceneGame() {
    if (!airplan) return;
    airplan->removeJoints();
    airplan->removeFromParent();
    airplan = nullptr;
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
    
    _labelScore = Label::createWithTTF("hello", "UpheavalPro.ttf", 100);
    _labelScore->setPosition(Vec2(2200, 1436));
    _labelScore->setTextColor(Color4B::WHITE);
    onAddScore(nullptr);
    _labelScore->setOpacity(0);
    this->addChild(_labelScore);

    _spriteEnergy = Sprite::create("energy.png");
    addChild(_spriteEnergy);
    _spriteEnergy->setPosition(Vec2(300, 1436));
    _spriteEnergy->setOpacity(0);
    _spriteEnergy->setScale(0.5);
    
    _labelPower = Label::createWithTTF("hello", "UpheavalPro.ttf", 100);
    _labelPower->setPosition(Vec2(500, 1436));
    _labelPower->setTextColor(Color4B::WHITE);
    _labelPower->setOpacity(0);
    this->addChild(_labelPower);
    
	scheduleUpdate();
    
    
    m_popins = __Array::create();
    m_popins->retain();

    char str[100] = {0};
    for(int i = 1; i < 15; i++) {
        sprintf(str, "popins/popins_%d.png", i);
        auto frame = SpriteFrame::create(str, Rect(0, 0, 340, 340)); //we assume that the sprites' dimentions are 40*40 rectangles.
        animFrames.pushBack(frame);
    }
    
    for (int i = 0; i < 10; i++) {
        runAction(Sequence::create(DelayTime::create(CCRANDOM_0_1() * 5), CallFunc::create(CC_CALLBACK_0(SceneGame::createPopins, this)), NULL));
    }
    
    // кнопка рестарт
    ui::Scale9Sprite* scale = ui::Scale9Sprite::create("menu/main_play.png");
    m_buttonRestart = ControlButton::create(scale);
    m_buttonRestart->addTargetWithActionForControlEvents(this, cccontrol_selector(SceneGame::restart), cocos2d::extension::Control::EventType::TOUCH_DOWN);
    m_buttonRestart->setPreferredSize(Size(766 / 2, 402 / 2));
    m_buttonRestart->setAnchorPoint(Vec2(0.5,0.5));
    m_buttonRestart->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2,
                                   Director::getInstance()->getWinSize().height / 4));
    m_buttonRestart->setZoomOnTouchDown(false);
    m_buttonRestart->setPositionY(-500);
    addChild(m_buttonRestart);
    
    m_menu = SceneMenu::create();
    m_menu->setDelegate(this);
    addChild(m_menu);
//    showPlane();
    
	return true;
}

void SceneGame::createPopins() {
    Sprite* pop = Sprite::create("popins/popins_1.png");
    auto animation = Animation::createWithSpriteFrames(animFrames, 0.05f);
    auto animate = Animate::create(animation);
    pop->runAction(RepeatForever::create(animate));
    pop->setPosition(Vec2(0, Director::getInstance()->getWinSize().height * 2));
    addChild(pop);
    m_popins->addObject(pop);
}

void SceneGame::restart(Ref * sender, Control::EventType controlEvent) {
    if (airplan) return;
    showPlane();
}

void SceneGame::runFewPopins(int count) {
    UserGameData::getInstance()->addScore(10 * count);
    for (int i = 0; i < m_popins->count() && count > 0; i++) {
        Sprite* pop = static_cast<Sprite*>(m_popins->getObjectAtIndex(i));
        int actions = pop->getNumberOfRunningActions();
        if (actions > 1) continue;
        
        if (pop->getPositionY() <= -pop->getContentSize().height ||
            pop->getPositionY() > Director::getInstance()->getWinSize().height + pop->getContentSize().height) { // тогда можно трогать
            
            pop->setPositionX(Director::getInstance()->getWinSize().width / 2 + rand() % (int)(Director::getInstance()->getWinSize().width / 2));
            pop->setPositionY(Director::getInstance()->getWinSize().height + pop->getContentSize().height * 1.5);
            
            MoveTo* move = MoveTo::create(6.0, Vec2(Director::getInstance()->getWinSize().width / 2 -
                                                        rand() % (int)(Director::getInstance()->getWinSize().width / 2),
                                                    -pop->getContentSize().height));
            
            pop->runAction(Sequence::create(DelayTime::create(CCRANDOM_0_1() * 10), move, nullptr));
            count--;
        }
    }
}

void SceneGame::onUp(Ref *pSender, ui::Widget::TouchEventType type)
{
    if(type == ui::Widget::TouchEventType::BEGAN){
        planeMoves.pushBack(__Integer::create(1));
        checkActions();
        setState(AirplaneStateUp);
        SoundManager::getInstance()->playSound(sound_power_up, false, 0.5);
        _power -= 2;
    }else if(type ==  ui::Widget::TouchEventType::ENDED ||
             type ==  ui::Widget::TouchEventType::CANCELED){
        setState(AirplaneStateNone);
        SoundManager::getInstance()->pauseSound(sound_power_up);
        _power -= 2;
    }
    onChangePower(nullptr);
}

void SceneGame::onDown(Ref *pSender, ui::Widget::TouchEventType type)
{
    if(type == ui::Widget::TouchEventType::BEGAN){
        planeMoves.pushBack(__Integer::create(2));
        checkActions();
        setState(AirplaneStateDown);
        SoundManager::getInstance()->playSound(sound_power_down, false, 0.5);
        _power -= 2;
    }else if(type ==  ui::Widget::TouchEventType::ENDED||
             type ==  ui::Widget::TouchEventType::CANCELED){
        setState(AirplaneStateNone);
        SoundManager::getInstance()->pauseSound(sound_power_down);
        _power -= 2;
    }
    onChangePower(nullptr);
}

void SceneGame::onShake(Ref *pSender, ui::Widget::TouchEventType type) {
    _power -= 15;
    onChangePower(nullptr);
    
    if(type == ui::Widget::TouchEventType::BEGAN){
        planeMoves.pushBack(__Integer::create(3));
        checkActions();
        setState(AirplaneStateShake);
        
        UserGameData::getInstance()->addScore(30);
        
        SoundManager::getInstance()->pauseSound(sound_best_loop);
        SoundManager::getInstance()->playSound(sound_harkem_shake, false, 0.8);
        
//        airplan->stopAllActions();
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

void SceneGame::checkActions() {
    if (planeMoves.size() > 4) { // проверить на попинс и маски
        if (planeMoves.at(planeMoves.size() - 1)->getValue() == 2 && // маски
            planeMoves.at(planeMoves.size() - 2)->getValue() == 1 &&
            planeMoves.at(planeMoves.size() - 3)->getValue() == 2 &&
            planeMoves.at(planeMoves.size() - 4)->getValue() == 1) {
            airplan->dropMasks();
        } else if (planeMoves.at(planeMoves.size() - 1)->getValue() == 1 && // попинс
                   planeMoves.at(planeMoves.size() - 2)->getValue() == 1 &&
                   planeMoves.at(planeMoves.size() - 3)->getValue() == 2 &&
                   planeMoves.at(planeMoves.size() - 4)->getValue() == 2) {
            runFewPopins(2);
        } else if (planeMoves.at(planeMoves.size() - 1)->getValue() == 3 && // куча попинсов
                   planeMoves.at(planeMoves.size() - 2)->getValue() == 2 &&
                   planeMoves.at(planeMoves.size() - 3)->getValue() == 2 &&
                   planeMoves.at(planeMoves.size() - 4)->getValue() == 1) {
            runFewPopins(8);
        } else {
            
        }
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
    airplan->deattachOneMask();
    
    SoundManager::getInstance()->playSound(sound_drop_item, false, 1.0);
	NotificationCenter::getInstance()->postNotification("shake-off");
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

void SceneGame::onChangePower(Ref* obj){
    if (_power < 0) _power = 0;
    
    _labelPower->setString(__String::createWithFormat("%d",_power)->getCString());
    if (_power <= 0 && !_isGameOver) {
        _isGameOver = true;
        // скрыть кнопки
        {
            MoveTo* move = MoveTo::create(0.25, Vec2(btnUp->getPositionX(), -500));
            EaseBackOut* back = EaseBackOut::create(move);
            btnUp->runAction(Sequence::create(DelayTime::create(0.3), back, nullptr));
        }
        {
            MoveTo* move = MoveTo::create(0.25, Vec2(btnDown->getPositionX(), -500));
            EaseBackOut* back = EaseBackOut::create(move);
            btnDown->runAction(Sequence::create(DelayTime::create(0.15), back, nullptr));
        }
        {
            MoveTo* move = MoveTo::create(0.25, Vec2(btnShake->getPositionX(), -500));
            EaseBackOut* back = EaseBackOut::create(move);
            btnShake->runAction(back);
        }
        
        // скрыть топливо
        _labelPower->runAction(FadeTo::create(3.0, 0));
        _spriteEnergy->runAction(FadeTo::create(3.0, 0));
        
        // выкатить в центр очки
        _labelScore->runAction(Sequence::create(MoveTo::create(2.5, Vec2(Director::getInstance()->getWinSize().width / 2,
                                                                         _labelScore->getPositionY())),
                                                MoveTo::create(2.5, Vec2(Director::getInstance()->getWinSize().width / 2,
                                                                         Director::getInstance()->getWinSize().height / 2)),
                                                ScaleTo::create(0.5, 2.5),
                                                NULL));
        // направить самолёт вниз
        RotateTo* rotate = RotateTo::create(5.0, 45);
        airplan->runAction(rotate);
        
        // начать двигать самолёт вниз
        MoveTo* move = MoveTo::create(7.0, Vec2(airplan->getPositionX() - 300, -400));
        airplan->runAction(move);
        runAction(Sequence::create(DelayTime::create(5.0), CallFunc::create(CC_CALLBACK_0(SceneGame::showFinish, this)), nullptr));
        
        m_menu->showTitle(true);
        
        // проиграть звук быдыщ
        SoundManager::getInstance()->pauseSound(sound_best_loop);
        SoundManager::getInstance()->playSound(sound_plane_crash, false, 1.0);
    }
}

void SceneGame::showFinish() {
    if (airplan) {
        airplan->removeJoints();
        airplan->removeFromParent();
        airplan = nullptr;
    }
    
    {
        MoveTo* move = MoveTo::create(0.25, Vec2(m_buttonRestart->getPositionX(), 200));
        EaseBackOut* back = EaseBackOut::create(move);
        m_buttonRestart->stopAllActions();
        m_buttonRestart->runAction(back);
    }
}

void SceneGame::update(float dt)
{
    _countUpdate++;
    Scene::update(dt);
    
    if (airplan) {
        airplan->updateAirplane(dt);
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
    }
    
//    if (_isGameOver) return;
    
    Vec2 airplaneVector = Vec2(1, 0);
    if (airplan) airplaneVector = Vec2::forAngle(CC_DEGREES_TO_RADIANS(airplan->getRotation()));
    airplaneVector.x = -airplaneVector.x;
    airplaneVector *= 30;
    sky->setVector(airplaneVector);
}

void SceneGame::showPlane() {
    if (airplan) {
        airplan->removeJoints();
        airplan->removeFromParent();
        airplan = nullptr;
    }
    
    _isGameOver = false;
    UserGameData::getInstance()->resetData();
    _power = TOTAL_POWER;
    onAddScore(nullptr);
    onChangePower(nullptr);
    
    airplan = Airplane::create();
    this->addChild(airplan);
    helpers::setDesignPosEx(airplan, 1650, 0);
    airplan->makeChain();
    
    _labelScore->runAction(FadeTo::create(0.2, 255));
    _labelPower->runAction(FadeTo::create(0.2, 255));
    _spriteEnergy->runAction(FadeTo::create(0.2, 255));
    
    
    auto pDirector = Director::getInstance();
    auto glview = pDirector->getOpenGLView();
    Size screenSize = glview->getFrameSize();
    int width = screenSize.width / CC_CONTENT_SCALE_FACTOR();
    int delta = (width - 2048) / 2;
    Vec2 pos = helpers::setDesignPosEx(airplan, 1650 - delta, 0);
    _airplanePosition = pos;
    airplan->setPositionX(-3000);
    
    MoveTo* move = MoveTo::create(2.0, pos);
    airplan->runAction(move);
    
    _labelScore->runAction(MoveTo::create(0.5, Vec2(2200, 1436)));
    _labelScore->runAction(ScaleTo::create(0.5, 1.0));
    {
        MoveTo* move = MoveTo::create(0.25, Vec2(m_buttonRestart->getPositionX(), -500));
        EaseBackOut* back = EaseBackOut::create(move);
        m_buttonRestart->runAction(back);
    }
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
    
    setState(AirplaneStateNone);
    tintDelay = 7.0;
    runTint();
    
    m_menu->showTitle(false);
    
    SoundManager::getInstance()->resumeSound(sound_best_loop);
}

void SceneGame::setState(AirplaneState state){

	if (state == AirplaneStateShake)
		NotificationCenter::getInstance()->postNotification("shake-on");

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




