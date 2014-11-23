#pragma once

#include "cocos2d.h"

class Toilet : public cocos2d::Sprite
{
public:

	CREATE_FUNC(Toilet);

	bool isFree() const;
	bool isOpen() const;
	bool isClose() const;

	void openDoor();
	void closeDoor();

	void occupy();
	void free();

protected:

	virtual bool init() override;
	virtual void update(float dt) override;

private:

	enum State
	{
		STILL,
		OPENING,
		CLOSING
	};

	static const int openSpeed;

	State state;
	int openAnglePercent;
	bool occupied;
};
