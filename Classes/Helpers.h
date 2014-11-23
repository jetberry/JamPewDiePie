#pragma once

#include <cocos2d.h>

namespace helpers {

	void setDesignPos(cocos2d::Node* node, int x, int y);
	cocos2d::Vec2 setDesignPosEx(cocos2d::Node* node, int x, int y);
	void setOnCenter(cocos2d::Node* node);

	template <typename T> int sgn(T val) {
		return (T(0) < val) - (val < T(0));
	}
}
