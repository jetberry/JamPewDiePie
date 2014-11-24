//
//  UserGameData.cpp
//  jamPewDiePie
//
//  Created by rustray on 23.11.14.
//
//

#include "UserGameData.h"


static UserGameData *s_instance = nullptr;

UserGameData* UserGameData::getInstance()
{
    if (!s_instance)
    {
        s_instance = new UserGameData();
        s_instance->resetData();
    }
    
    return s_instance;
}

void UserGameData::addScore(int score){
    _score += score;
    cocos2d::__NotificationCenter::getInstance()->postNotification("MSG_UPDATE_SCORE");
}

int UserGameData::getScore(){
    return _score;
}

void UserGameData::resetData(){
    _score = 0;
	_totalAngle = 0;
}

void UserGameData::setAngle(float angle){
	_totalAngle += fabs(_angle - angle);
    _angle = angle;
    cocos2d::NotificationCenter::getInstance()->postNotification("change-angle");
}

float UserGameData::getAngle() const {
	return _angle;
}

float UserGameData::getTotalAngle() const {
	return _totalAngle;
}
