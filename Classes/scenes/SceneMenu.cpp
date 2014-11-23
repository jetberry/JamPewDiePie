#include "SceneMenu.h"
#include "../Helpers.h"
#include "SceneGame.h"
#include "../SoundManager/SoundManager.h"

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

//	auto background = LayerColor::create(Color4B(255, 255, 255, 255));
//	this->addChild(background, 0);

//	auto sprite = Sprite::create("menu/airplane.png");
//	helpers::setDesignPos(sprite, 766, 49);
//	this->addChild(sprite, 0);

    m_spriteTitle = Sprite::create("title.png");
    m_spriteTitle->setPosition(Director::getInstance()->getWinSize().width / 2,
                               Director::getInstance()->getWinSize().height - m_spriteTitle->getContentSize().height / 3 * 2);
    addChild(m_spriteTitle);
    
    m_labelTutorial = Label::createWithTTF("hello", "UpheavalPro.ttf", 50);
    m_labelTutorial->setPosition(Vec2(200, 200));
    m_labelTutorial->setColor(Color3B::BLACK);
    addChild(m_labelTutorial);
    
    ui::Scale9Sprite* scale = ui::Scale9Sprite::create("menu/main_play.png");
    m_buttonPlay = ControlButton::create(scale);
    m_buttonPlay->addTargetWithActionForControlEvents(this, cccontrol_selector(SceneMenu::menuPlayCallback), cocos2d::extension::Control::EventType::TOUCH_DOWN);
    m_buttonPlay->setPreferredSize(Size(766 / 2, 402 / 2));
    m_buttonPlay->setAnchorPoint(Vec2(0,0));
    m_buttonPlay->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2 - m_buttonPlay->getContentSize().width / 2,
                                   Director::getInstance()->getWinSize().height / 4));
    m_buttonPlay->setZoomOnTouchDown(false);
    
    addChild(m_buttonPlay);
    
    m_labelTutorial->setPosition(m_buttonPlay->getPosition() + m_buttonPlay->getContentSize() / 2);
    m_labelTutorial->setHorizontalAlignment(cocos2d::TextHAlignment::CENTER);
    m_labelTutorial->setOpacity(0);
    
    m_clickCount = 1;
    changeTutorialText();
    m_clickCount = 1;
    
    SoundManager::getInstance()->playSound(sound_best_loop, true, 0.4);
    
	return true;
}

void SceneMenu::menuPlayCallback(Ref * sender, Control::EventType controlEvent)
{
    switch (m_clickCount) {
        case 1: { // откатить кнопку, наверх
            MoveTo* move = MoveTo::create(0.25, m_buttonPlay->getPosition() + Vec2(0, 600));
            EaseBackOut* back = EaseBackOut::create(move);
            m_buttonPlay->stopAllActions();
            m_buttonPlay->runAction(back);
            m_labelTutorial->runAction(FadeTo::create(0.1, 255));
            break;
        }
        case 2: {
            RotateTo* rotate = RotateTo::create(0.25, 180);
            EaseBackOut* back = EaseBackOut::create(rotate);
            m_buttonPlay->stopAllActions();
            m_buttonPlay->runAction(back);
            
            m_labelTutorial->runAction(Sequence::create(FadeTo::create(0.1, 0),
                                                        CallFunc::create(CC_CALLBACK_0(SceneMenu::changeTutorialText, this)),
                                                        MoveTo::create(1.0 / 60.0, m_buttonPlay->getPosition() + m_buttonPlay->getContentSize() / 2),
                                                        FadeTo::create(0.1, 255), NULL));
            break;
        }
        case 3: {
            m_buttonPlay->stopAllActions();
            {
                MoveTo* move = MoveTo::create(0.25, Vec2(400, 400));
                EaseBackOut* back = EaseBackOut::create(move);
                m_buttonPlay->runAction(back);
            }
            {
                RotateTo* rotate = RotateTo::create(0.25, 0);
                EaseBackOut* back = EaseBackOut::create(rotate);
                m_buttonPlay->runAction(back);
            }
            {
                m_labelTutorial->runAction(Sequence::create(FadeTo::create(0.1, 0),
                                                            CallFunc::create(CC_CALLBACK_0(SceneMenu::changeTutorialText, this)),
                                                            MoveTo::create(1.0 / 60.0, m_buttonPlay->getPosition() - m_buttonPlay->getContentSize() / 2),
                                                            FadeTo::create(0.1, 255), NULL));
            }
            break;
        }
        case 4: {
            m_buttonPlay->stopAllActions();
            {
                MoveTo* move = MoveTo::create(0.25, Vec2(Director::getInstance()->getWinSize().width - 2 * m_buttonPlay->getPosition().x,
                                                         400));
                EaseBackOut* back = EaseBackOut::create(move);
                m_buttonPlay->runAction(back);
            }
            {
                m_labelTutorial->runAction(Sequence::create(FadeTo::create(0.1, 0),
                                                            CallFunc::create(CC_CALLBACK_0(SceneMenu::changeTutorialText, this)),
                                                            MoveTo::create(1.0 / 60.0, m_buttonPlay->getPosition() + m_buttonPlay->getContentSize() / 2),
                                                            FadeTo::create(0.1, 255), NULL));
            }
            break;
        }
        case 5: {
            m_buttonPlay->stopAllActions();
            {
                MoveTo* move = MoveTo::create(0.25, Vec2(Vec2(Director::getInstance()->getWinSize().width / 2 - m_buttonPlay->getContentSize().width / 2,
                                                              Director::getInstance()->getWinSize().height / 4)));
                EaseBackOut* back = EaseBackOut::create(move);
                m_buttonPlay->runAction(back);
            }
            {
                m_labelTutorial->runAction(Sequence::create(FadeTo::create(0.1, 0),
                                                            CallFunc::create(CC_CALLBACK_0(SceneMenu::changeTutorialText, this)),
                                                            MoveTo::create(1.0 / 60.0, m_buttonPlay->getPosition() + m_buttonPlay->getContentSize() / 2),
                                                            FadeTo::create(0.1, 255), NULL));
            }
            break;
        }
        case 6: {
            m_buttonPlay->stopAllActions();
            {
                MoveTo* move = MoveTo::create(0.25, Vec2(Vec2(m_buttonPlay->getPositionX(),
                                                              -Director::getInstance()->getWinSize().height / 2)));
                EaseBackOut* back = EaseBackOut::create(move);
                m_buttonPlay->runAction(back);
            }
            m_labelTutorial->runAction(FadeTo::create(0.1, 0));
            m_spriteTitle->runAction(FadeTo::create(0.1, 0));
            m_delegate->showPlane();
            SoundManager::getInstance()->playSound(sound_noise_loop, true, 0.4);
            break;
        }
        default:
            break;
    }
    m_clickCount++;
}

void SceneMenu::changeTutorialText() {
    __String* tutorial = nullptr;
    switch (m_clickCount) {
        case 1:
            tutorial = __String::createWithFormat("hey, dude!\nlet's learn to play");
            break;
        case 3:
            tutorial = __String::createWithFormat("so, the main goal here\nis ruffle the passengers");
            break;
        case 4:
            tutorial = __String::createWithFormat("you should watch at them\nand make some actions");
            break;
        case 5:
            tutorial = __String::createWithFormat("remember!\ndifferent combinations\ngenerate different actions!");
            break;
        case 6:
            tutorial = __String::createWithFormat("you have to see them all!\nhave a fun game!");
            break;
            
        default:
            break;
    }
    if (tutorial) m_labelTutorial->setString(tutorial->getCString());
}

void SceneMenu::setDelegate(SceneGame* delegate) {
    m_delegate = delegate;
}

void SceneMenu::showTitle(bool is_show) {
    if (is_show) {
        m_spriteTitle->runAction(FadeTo::create(4.0, 255));
    } else {
        m_spriteTitle->runAction(FadeTo::create(1.0, 0));
    }
}



