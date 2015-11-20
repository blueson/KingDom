//
//  WelcomeScene.hpp
//  KingDom
//
//  Created by gjmac-2 on 15/11/20.
//
//

#ifndef WelcomeScene_h
#define WelcomeScene_h

#include "cocos2d.h"

USING_NS_CC;

class WelcomeScene : public Layer{
public:
    virtual bool init();
    static Scene* createScene();
    
    CREATE_FUNC(WelcomeScene);
    
private:
    Sprite* sprite_Logo;
};

#endif /* WelcomeScene_h */
