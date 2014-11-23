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
    this->setFlippedX(getDirection() == DIRECTION_LEFT);
    
    _frequencyAnimation = 5;
    
    return true;
}

void Pilot::update(float dt){
    updateAnim();
    Man::update(dt);
}

void Pilot::setAraplaneIsMoved(bool flag){
    if(flag)
        _frequencyAnimation = 1;
    else
        _frequencyAnimation = 6;
}

void Pilot::updateAnim(){
    if (!(getUpdateCounter() % _frequencyAnimation)){
        int currentFrame = (getUpdateCounter() / _frequencyAnimation) % 20;
        if(currentFrame >= 10)
            currentFrame = currentFrame - (currentFrame % 10) * 2 - 1;
        setPicture("airplane/people/pilot", currentFrame);
    }
    
    this->setFlippedX(getDirection() == DIRECTION_LEFT);
}
