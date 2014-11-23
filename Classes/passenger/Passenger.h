#pragma once

#include "Man.h"
#include "../airplane/Toilet.h"
#include "Trolley.h"

class Passenger : public Man
{
public:

	static Passenger* create(const std::string& pictureDir, cocos2d::Vec2 pos);

	void assignToilet(Toilet* toilet);
	void assignTrolley(Trolley* trolley);
    
private:
    
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unusedEvent);
    bool hitTest(const cocos2d::Vec2 &pt);
    
	enum Const
	{
		MOVING_SPEED = 4
	};

	enum States
	{
		SEAT,	
		MOVING_TO_TOILET,
		MOVING_TO_SEAT,
		ENTER_TO_TOILET,
		TOILET_SEATING,
		TOILET_EXITING,
		BARF
	};

	std::string pictureDir;
	cocos2d::Vec2 seatPos;
	States state;
	Toilet* toilet;
	Trolley* trolley;
	bool angryFlag;
	bool dirty;

	int nextActionTime;
    int count_tap;
    
	virtual bool init() override;
	virtual void update(float dt) override;


	void checkTrolleyCollision();

	void enterToToilet();
	void moveToToilet();
	void moveToSeat();
	void seatDown();
	void setAngry(bool value);
	void doBarf();

	void updateSeat(float dt);
	void updateMovingAnim();
	void updateSittingAnim();
	void updateBarfAnim();
	void updateMovingToToilet(float dt);
	void updateMovingToSeat(float dt);
	void updateEnterToToilet(float dt);
	void updateToiletSeating(float dt);
	void updateToiletExiting(float dt);
	void updateBarf(float dt);
	
	
};
