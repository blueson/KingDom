//
//  GameView.hpp
//  KingDom
//
//  Created by gjmac-2 on 15/11/24.
//
//

#ifndef GameView_h
#define GameView_h

#include "cocos2d.h"

USING_NS_CC;

class GameView : public Layer{
public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameView);
};

#endif /* GameView_h */
