#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include "chipmunk.h"

class Airplane : public cocos2d::Node
{
public:

	CREATE_FUNC(Airplane);

	virtual bool init();

private:

	cpSpace* _space;
	cpShape* _walls[4];
	cocos2d::extension::PhysicsDebugNode* _debugLayer;

	void initPhysics();

	//cocos2d::extension::PhysicsSprite;

};
