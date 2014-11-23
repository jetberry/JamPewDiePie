//
//  HandLuggageSpaces.h
//  jamPewDiePie
//
//  Created by rustray on 24.11.14.
//
//

#ifndef __jamPewDiePie__HandLuggageSpaces__
#define __jamPewDiePie__HandLuggageSpaces__

#include "cocos2d.h"

class HandLuggageSpaces : public cocos2d::Node{
  
public:
    
    CREATE_FUNC(HandLuggageSpaces);
    
    virtual bool init();
    
private:
    
    void openHandLuggage(float dt);
};

#endif /* defined(__jamPewDiePie__HandLuggageSpaces__) */
