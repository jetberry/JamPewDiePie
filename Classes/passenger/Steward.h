#pragma once

#include "Man.h"


class Steward : public Man
{
public:

	CREATE_FUNC(Steward);


private:

	enum Const
	{
		LEFT_POS = 0,
		RIGHT_POS = 1000
	};

	enum States
	{
		MOVING_TO_LEFT,
		MOVING_TO_RIGHT,
	};

	States state;

	virtual bool init() override;
	virtual void update(float dt) override;

	void moveToLeft();
	void moveToRight();
	void updateMovingToLeft(float dt);
	void updateMovingToRight(float dt);
	void updateMovingAnim();
};
