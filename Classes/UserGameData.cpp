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
}