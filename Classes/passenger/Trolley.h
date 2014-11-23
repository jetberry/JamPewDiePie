#pragma once

#include "cocos2d.h"

class Trolley : public cocos2d::Sprite
{
public:

	CREATE_FUNC(Trolley);

protected:

	enum Const
	{
		MOVING_SPEED = 10
	};

	virtual bool init() override;
	virtual void update(float dt) override;

private:

};
