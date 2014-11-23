#pragma once

#include "cocos2d.h"

class Airplane : public cocos2d::Node
{
public:

	CREATE_FUNC(Airplane);

    ~Airplane();
	virtual bool init();
    
    void makeChain();
    
    void dropSomething();
    
    void removeJoints();
private:

	void loadBaggage();

    cocos2d::__Array* m_arrBananas;
    cocos2d::__Array* m_arrBoobliks;
};
