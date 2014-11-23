#pragma once

#include "cocos2d.h"

class Man : public cocos2d::Sprite
{
public:

	CREATE_FUNC(Man);

protected:

	enum Const
	{
		TOILET_POS = 100,
		MOVING_SPEED = 10,
		WALKING_ANIMATION_SPEED = 5
	};

	virtual bool init() override;
	virtual void update(float dt) override;

	void setPicture(const std::string& fileName);
	void setPicture(const std::string& dirName, int index);
	void setTarget(float target);
	bool isOnTarget() const;
	void movingToTarget();
	int getUpdateCounter() const;

private:

	// Счетчик update-ов, с момента инициализации человека.
	int updateCounter;

	// Позиция по горизонтали, куда будет перемещаться человек.
	float target;

	// Текущая картинка.
	std::string currentPicture;
};
