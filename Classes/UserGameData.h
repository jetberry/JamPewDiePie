//
//  UserGameData.h
//  jamPewDiePie
//
//  Created by rustray on 23.11.14.
//
//

#ifndef __jamPewDiePie__UserGameData__
#define __jamPewDiePie__UserGameData__

#include "cocos2d.h"

class UserGameData : public cocos2d::Ref{
    
public:
    
    static UserGameData* getInstance();
    
    void addScore(int score);
    
    int getScore();
    
    void resetData();
    
private:
    
    int _score;
};


#endif /* defined(__jamPewDiePie__UserGameData__) */
