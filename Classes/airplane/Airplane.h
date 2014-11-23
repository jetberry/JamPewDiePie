#pragma once

#include "cocos2d.h"
#include "../Passenger/Pilot.h"

class Airplane : public cocos2d::Node
{
public:

	CREATE_FUNC(Airplane);

    ~Airplane();
	virtual bool init();
    
    void setAraplaneIsMoved(bool flag);

    void makeChain();
    
    void dropSomething();
    
    void updateAirplane(float delta);

    void removeJoints();

private:

	void loadBaggage();
    
    void creatHandLuggageSpaces();
    
    void createChair(cocos2d::Vec2 position);
    
    void updateSensor();

    cocos2d::Sprite* _sensor;
    
    int _coutnUpdate = 0;

    Pilot* _pilot;

    cocos2d::__Array* m_arrBananas;
    cocos2d::__Array* m_arrBoobliks;
};
