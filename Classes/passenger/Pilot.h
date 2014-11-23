//
//  Pilot.h
//  jamPewDiePie
//
//  Created by rustray on 23.11.14.
//
//

#ifndef __jamPewDiePie__Pilot__
#define __jamPewDiePie__Pilot__

#include "Man.h"
#include "cocos2d.h"

class Pilot : public Man
{
public:
    
    CREATE_FUNC(Pilot);
    
    void setAraplaneIsMoved(bool flag);
    
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unusedEvent);

    
private:

    enum States
    {
        NONE,
        ANIMATION
    };
    
    bool hitTest(const cocos2d::Vec2 &pt);
    
    virtual void update(float dt) override;
    virtual bool init() override;
    
    void updateAnim();
    
    bool _isAnimation;
    
    int _frameCounter;
    
    int _frequencyAnimation;
    
    States state;
};


#endif /* defined(__jamPewDiePie__Pilot__) */
