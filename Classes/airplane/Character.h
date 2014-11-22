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
// класс от которого наследуются пассажиры, стюардесса и может даже тележка стюардессы, если это разные объекты будут
class Character : public cocos2d::Sprite{
  
public:
    
    static Character* create(const std::string& filename);
    
    Character();
    
    virtual void onEnter();
    
    // стартовая позиция объекта, например где сидит пассажир
    void setStartPosition(cocos2d::Vec2 point);
    
    // прердается пол, что бы подписаться на события связанные с ним
    void setBottom(cocos2d::PhysicsBody* body);
    
    void createBody();
    
    // позиция к которой движется объект
    void setTargetPoition(cocos2d::Vec2 point);
    
    // есть ли в данный момент контакт с полом
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
 
    задавать анимацию
 */
class CharacrerBehaviour {
    
public:
    
    virtual void setCharacrer(Character* character){};
    
    virtual void update(float dt){};
    
    //
};


#endif /* defined(__jamPewDiePie__Character__) */
