//
//  Pilot.cpp
//  jamPewDiePie
//
//  Created by rustray on 23.11.14.
//
//

#include "Pilot.h"

bool Pilot::init()
{
    if (!Man::init())
        return false;
    
    setPicture("airplane/people/pilot/0001.png");
    createBody();
    state = ANIMATION;
    
    _frequencyAnimation = 5;
    
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
    if(_isAnimation){
    if (!(getUpdateCounter() % _frequencyAnimation)){
        int currentFrame = _frameCounter;
        if(currentFrame >= 10)
            currentFrame = currentFrame - (currentFrame % 10) * 2 - 1;
        setPicture("airplane/people/pilot", currentFrame);
        
        _frameCounter++;
        if(_frameCounter >= 20)
            _isAnimation = false;
    }
    
}
