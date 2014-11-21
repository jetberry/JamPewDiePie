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
    
private:
    
};


#endif /* defined(__jamPewDiePie__Character__) */
