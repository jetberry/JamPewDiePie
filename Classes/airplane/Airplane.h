#pragma once

#include "cocos2d.h"
#include "Pilot.h"

class Airplane : public cocos2d::Node
{
public:

	CREATE_FUNC(Airplane);

	virtual bool init();
    
    void setAraplaneIsMoved(bool flag);

    void makeChain();
    
    void dropSomething();
    
    void updateAirplane(float delta);

private:

	void loadBaggage();
    
    void creatChair(cocos2d::Vec2 position);
    
    void updateSensor();

    cocos2d::Sprite* _sensor;
    
    int _coutnUpdate;

    Pilot* _pilot;

    cocos2d::__Array* m_arrBananas;
    cocos2d::__Array* m_arrBoobliks;
};
