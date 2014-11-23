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
		LEFT_POS = 0,
		RIGHT_POS = 800,
		KITHEN_POS = -100
	};

	enum States
	{
		GOTO_KITCHEN,
		MOVING_TO_LEFT,
		MOVING_TO_RIGHT,
	};

	States state;
	Trolley* trolley;
	bool handleTrolley;

	Steward();

	virtual bool init() override;
	void updateTrolley();
	virtual void update(float dt) override;

	// Запуск действий.
	void moveToLeft();
	void moveToRight();
	void goKitchen();


	// Обработка действий в update().
	void updateMovingToLeft(float dt);
	void updateMovingToRight(float dt);
	void updateMovingAnim();
	void updateGotoKitchen(float dt);
};
