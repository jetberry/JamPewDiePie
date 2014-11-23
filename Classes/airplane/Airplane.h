#pragma once

#include "cocos2d.h"

class Airplane : public cocos2d::Node
{
public:

	CREATE_FUNC(Airplane);

	virtual bool init();

private:

	void loadBaggage();

};
