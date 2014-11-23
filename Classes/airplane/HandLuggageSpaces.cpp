//
//  HandLuggageSpaces.cpp
//  jamPewDiePie
//
//  Created by rustray on 24.11.14.
//
//

#include "HandLuggageSpaces.h"

using namespace cocos2d;

bool HandLuggageSpaces::init(){
    for (int i = 0; i < 4; i++)
    {
        Sprite* handLuggageSpace = Sprite::create("airplane/hand_luggage_spaces.png");
        handLuggageSpace->setPosition(Vec2(i * 225, 45));
        handLuggageSpace->setAnchorPoint(Vec2(0.5,1));
        this->addChild(handLuggageSpace);
    }
    
    scheduleOnce(CC_SCHEDULE_SELECTOR(HandLuggageSpaces::openHandLuggage),  rand() % 20 + 2);
    
    return true;
}

void HandLuggageSpaces::openHandLuggage(float dt){
    int index = rand() % 4;
    Node* obj = getChildren().at(index);
    
    obj->runAction(ScaleTo::create(0.3f, 1, 0));
    
    scheduleOnce(CC_SCHEDULE_SELECTOR(HandLuggageSpaces::openHandLuggage), rand() % 20 + 3);
}