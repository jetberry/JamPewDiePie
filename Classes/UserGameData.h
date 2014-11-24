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
    
    void setAngle(float);
    
    float getAngle() const;
	float getTotalAngle() const;
    
    void resetData();
    
private:
    
	float _angle = 0.f;
	float _totalAngle = 0.f;
    
    int _score = 0;
};


#endif /* defined(__jamPewDiePie__UserGameData__) */
