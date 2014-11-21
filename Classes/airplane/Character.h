//
//  Character.h
//  jamPewDiePie
//
//  Created by rustray on 21.11.14.
//
//

#ifndef __jamPewDiePie__Character__
#define __jamPewDiePie__Character__

#include "cocos2d.h"
#include "cocos-ext.h"

class Character : public cocos2d::Sprite{
  
public:
    
    static Character* create(const std::string& filename);
    
    Character();
    
    virtual void onEnter();
    
    void setTarget(cocos2d::Vec2 point);
    
    void setBottom(cocos2d::PhysicsBody* body);
    
    void createBody();
    
private:

    bool onContactBegin(cocos2d::PhysicsContact& contact);
    
    cocos2d::Vec2 _target;
    
    bool _isContactGround = true;
    
    void update(float dt);
    
    void goToTarget();
    
};


#endif /* defined(__jamPewDiePie__Character__) */
