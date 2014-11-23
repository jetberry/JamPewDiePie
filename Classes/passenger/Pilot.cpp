//
//  Pilot.cpp
//  jamPewDiePie
//
//  Created by rustray on 23.11.14.
//
//

#include "Pilot.h"
#include "../SoundManager/SoundManager.h"

using namespace cocos2d;

bool Pilot::init()
{
    if (!Man::init())
        return false;
    
    setPicture("airplane/people/pilot/0001.png");
    createBody();
    state = ANIMATION;
    
    _frequencyAnimation = 5;
    
    EventListenerTouchOneByOne* touchListener = EventListenerTouchOneByOne::create();
    CC_SAFE_RETAIN(touchListener);
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(Pilot::onTouchBegan, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    return true;
}

void Pilot::update(float dt){
    updateAnim();
    Man::update(dt);
}

void Pilot::setAraplaneIsMoved(bool flag){
    if(_isAnimation)
        return;
    _isAnimation = flag;
    _frameCounter = 0;
}

void Pilot::updateAnim(){
	if (_isAnimation){
		if (!(getUpdateCounter() % _frequencyAnimation)){
			int currentFrame = _frameCounter;
			if (currentFrame >= 10)
				currentFrame = currentFrame - (currentFrame % 10) * 2 - 1;
			setPicture("airplane/people/pilot", currentFrame);

			_frameCounter++;
			if (_frameCounter >= 20)
				_isAnimation = false;
		}
	}
}

bool Pilot::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unusedEvent){
    if(hitTest(touch->getLocation())){
        SoundManager::getInstance()->playSound(sound_monkey, false, 0.5);
    }
    return false;
}

bool Pilot::hitTest(const Vec2 &pt)
{
    Vec2 nsp = convertToNodeSpace(pt);
    Rect bb;
    bb.size = _contentSize;
    if (bb.containsPoint(nsp))
    {
        return true;
    }
    return false;
}
