#pragma once

#include "cocos2d.h"

class Nerd : public cocos2d::Sprite
{
public:

	CREATE_FUNC(Nerd);

protected:

	virtual bool init() override;
	virtual void update(float dt) override;

	float timeToDead;

    bool isDead;
};
