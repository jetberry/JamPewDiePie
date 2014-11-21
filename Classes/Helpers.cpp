#include "Helpers.h"

USING_NS_CC;

void helpers::setDesignPos(Node* node, int x, int y)
{
	float dh = Director::getInstance()->getOpenGLView()->getDesignResolutionSize().height;
	auto s = node->getContentSize();
	float rx = static_cast<float>(x)+s.width / 2.0;
	float ry = (dh - static_cast<float>(y)-1) - s.height / 2.0;
	node->setPosition(Vec2(rx, ry));
}

void helpers::setOnCenter(Node* node)
{
	float dw = Director::getInstance()->getOpenGLView()->getDesignResolutionSize().width;
	float dh = Director::getInstance()->getOpenGLView()->getDesignResolutionSize().height;

	node->setPosition(Vec2(dw/2, dh/2));
}
