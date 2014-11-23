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

    void removeJoints();

private:

	void loadBaggage();
    
    void creatChair(cocos2d::Vec2 position);


    Pilot* _pilot;

    cocos2d::__Array* m_arrBananas;
    cocos2d::__Array* m_arrBoobliks;
};
