#pragma once

#include "Man.h"
#include "Trolley.h"


class Steward : public Man
{
public:

	CREATE_FUNC(Steward);

	void assignTrolley(Trolley* trolley);

private:
	
	enum Const
	{
		MOVING_SPEED = 6,
		LEFT_POS = 0,
		RIGHT_POS = 700,
		KITHEN_POS = -500
	};

	enum States
	{
		STAY_AT_KITCHEN,
		GOTO_KITCHEN,
		MOVING_TO_LEFT,
		MOVING_TO_RIGHT,
	};

	States state;
	Trolley* trolley;
	bool handleTrolley;
	int nextAction;

	Steward();

	virtual bool init() override;
	void updateTrolley();
	virtual void update(float dt) override;

	// Запуск действий.
	void moveToLeft();
	void moveToRight();
	void goKitchen();
	void stayAtKitchen();


	// Обработка действий в update().
	void updateMovingToLeft(float dt);
	void updateMovingToRight(float dt);
	void updateMovingAnim();
	void updateGotoKitchen(float dt);
	void updateStateInKitchen(float dt);
};
