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

class CharacrerBehaviour;

class Character : public cocos2d::Sprite{
  
public:
    
    static Character* create(const std::string& filename);
    
    Character();
    
    virtual void onEnter();
    
    void setStartPosition(cocos2d::Vec2 point);
    
    void setBottom(cocos2d::PhysicsBody* body);
    
    void createBody();
    
    void setTargetPoition(cocos2d::Vec2 point);
    
    bool isContactcWithGround();
    
private:

    bool onContactBegin(cocos2d::PhysicsContact& contact);
    
    void update(float dt);
    
    void setState(int state);
    
    void goToTarget();
    
    int _currentState;
    
    CharacrerBehaviour* _currentBehaviour;
    
    cocos2d::Vec2 _startPosition;
    
    cocos2d::Vec2 _target;
    
    bool _isContactBottom = true;
    
};

/* класс от которого наследуются поведенческие классы, например пойти в туалет, и он будет полностью управлять объектом пока объект не дойдет до туалета и не сделает в нем все дела, после чего в зависимости от состояния, влючается новый поведенческий класс

    класс может передать колбэк на событие, когда объет дойдет то таргета, узнать косается ли объет пола и прк
 */
class CharacrerBehaviour {
    
public:
    
    virtual void setCharacrer(Character* character){};
    
    virtual void update(float dt){};
    
    //
};


#endif /* defined(__jamPewDiePie__Character__) */
