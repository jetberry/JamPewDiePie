#pragma once

#include "cocos2d.h"
#include "Pilot.h"

class Airplane : public cocos2d::Node
{
public:

	CREATE_FUNC(Airplane);

	virtual bool init();
    
    void setAraplaneIsMoved(bool flag);

private:

	void loadBaggage();
    
    void creatChair(cocos2d::Vec2 position);

    Pilot* _pilot;
};
