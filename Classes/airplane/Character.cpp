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
    
}

void Character::onEnter(){
    Sprite::onEnter();
    _target = Vec2(1000,0);
    goToTarget();
    scheduleUpdate();
}

void Character::createBody(){
    PhysicsMaterial material(100,0.15f,1.1f);
    PhysicsBody* body = PhysicsBody::createBox(this->getContentSize(), material);
    this->setPhysicsBody(body);
}

void Character::setBottom(cocos2d::PhysicsBody* body){
    body->setContactTestBitmask(0xFFFFFFFF);
    this->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
    auto contactListener = EventListenerPhysicsContactWithBodies::create(this->getPhysicsBody(), body);
    contactListener->onContactBegin = CC_CALLBACK_1(Character::onContactBegin, this);
    contactListener->onContactPostSolve = [=](PhysicsContact& contact, const PhysicsContactPostSolve& solve)
    {
        _isContactGround = true;
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void Character::update(float dt){
    if(_isContactGround)
        setColor(Color3B(255,0,0));
    else
        setColor(Color3B(255,255,255));
    goToTarget();
    _isContactGround = false;
}

bool Character::onContactBegin(PhysicsContact& contact){
    log("onContactBegin");
    return true;
}

void Character::setTarget(Vec2 point){
    _target = point;
}

void Character::goToTarget(){
//    Vec2 delta = _target - this->getPosition();
//    delta.normalize();
//    this->setPosition(this->getPosition() + delta * 3);
    if(_isContactGround){
        if()
        Vec2 velocity = this->getPhysicsBody()->getVelocity() + Vec2(10,0);
        this->getPhysicsBody()->setVelocity(velocity);
    }
};


