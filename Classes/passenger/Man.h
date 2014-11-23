#pragma once

#include "cocos2d.h"

class Man : public cocos2d::Sprite
{
public:

	CREATE_FUNC(Man);

protected:

	enum Direction
	{
		DIRECTION_UNKNOW,
		DIRECTION_LEFT,
		DIRECTION_RIGHT
	};

	enum Const
	{
		TOILET_POS = 115,
		DEFAULT_MOVING_SPEED = 10,
		WALKING_ANIMATION_SPEED = 5
	};

	virtual bool init() override;
	virtual void update(float dt) override;

	void createBody();
	void setPicture(const std::string& fileName);
	void setPicture(const std::string& dirName, int index);
	void setTarget(float target);
	bool isOnTarget() const;
	void movingToTarget();
	int getUpdateCounter() const;
	Direction getDirection() const;

	float movingSpeed;
	bool shakeState;

private:

	void onShakeOn(Ref* obj);
	void onShakeOff(Ref* obj);

	// Счетчик update-ов, с момента инициализации человека.
	int updateCounter;

	// Позиция по горизонтали, куда будет перемещаться человек.
	float target;

	// Текущая картинка.
	std::string currentPicture;
};
