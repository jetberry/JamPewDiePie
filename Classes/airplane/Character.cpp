 //
//  Character.cpp
//  jamPewDiePie
//
//  Created by rustray on 21.11.14.
//
//

#include "Character.h"

using namespace cocos2d;

Character* Character::create(const std::string& filename)
{
    Character *sprite = new (std::nothrow) Character();
    if (sprite && sprite->initWithFile(filename))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

Character::Character(){
    setState(0);
}

void Character::onEnter(){
    Sprite::onEnter();
    setTargetPoition(Vec2(600,- 257));
    goToTarget();
    scheduleUpdate();
}

void Character::createBody(){
    PhysicsMaterial material(100, 0.15f, 0.1f);
    PhysicsBody* body = PhysicsBody::createBox(this->getContentSize(), material);
    this->setPhysicsBody(body);
}

void Character::setBottom(cocos2d::PhysicsBody* body){
    body->setContactTestBitmask(0xFFFFFFFF);
    this->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
    auto contactListener = EventListenerPhysicsContactWithBodies::create(this->getPhysicsBody(), body);
    
    contactListener->onContactPostSolve = [=](PhysicsContact& contact, const PhysicsContactPostSolve& solve)
    {
        int angle = (int)this->getParent()->getRotation();
        if((angle > -7 && angle < 7)){
            goToTarget();
        }
        _isContactBottom = true;
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void Character::update(float dt){
    if(_isContactBottom)
        setColor(Color3B(255,0,0));
    else
        setColor(Color3B(255,255,255));
    
    _currentBehaviour->update(dt);
    
    _isContactBottom = false;
}

void Character::setStartPosition(Vec2 point){
    _startPosition = point;
}

bool Character::isContactcWithGround(){
    return _isContactBottom;
}

void Character::setTargetPoition(cocos2d::Vec2 point){
    _target = point;
}

void Character::goToTarget(){
    Vec2 velocity = this->getPhysicsBody()->getVelocity();
    Vec2 delta = _target - this->getPosition();
	delta.y = 0;

	float targetSpeed = (delta.x < 1) ? 0 : 300;
    if(delta.x < 1){
        //TODO вызвать колбэк который передаст CharacrerBehaviour 
    }
    
	delta.normalize();
	delta.rotate(Vec2(), CC_DEGREES_TO_RADIANS(-this->getParent()->getRotation()));
	targetSpeed *= delta.x;
	
	float impulse = targetSpeed - velocity.x;
	impulse *= this->getPhysicsBody()->getMass();
	this->getPhysicsBody()->applyImpulse(Vec2(impulse, 0));
	return;
};

void Character::setState(int state){
    switch (state) {
        case 0:
            _currentBehaviour = new CharacrerBehaviour();
            break;
            
        default:
            break;
    }
    _currentBehaviour->setCharacrer(this);
}
