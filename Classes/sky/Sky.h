#pragma once

#include "cocos2d.h"

class Sky : public cocos2d::Node
{
public:

	CREATE_FUNC(Sky);

	virtual bool init();

	void setVector(cocos2d::Vec2 v);

private:

	enum
	{
		CLOWD_COUNT = 10
	};

	cocos2d::Size designResolution;
	cocos2d::Node* plane;
	cocos2d::Vec2 speed;

	void update(float dt);

};
