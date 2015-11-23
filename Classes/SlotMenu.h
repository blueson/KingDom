//
//  SlotMenu.hpp
//  KingDom
//
//  Created by gjmac-2 on 15/11/23.
//
//

#ifndef SlotMenu_h
#define SlotMenu_h

#include "cocos2d.h"

USING_NS_CC;

class SlotMenu : public Sprite{
public:
    SlotMenu();
    ~SlotMenu();
    virtual bool initWithNum(int num);
    CREATE_FUNC(SlotMenu);
    void button_Savelot_Delete_callback(Ref* pSender);
    void conform_delete(Ref* pSender);
    void cancel_delete(Ref* pSender);
    void createNewGame();
    static SlotMenu* createMenu(int num);
protected:
    Label* label_hint;
    MenuItemSprite* button_Savelot_Delete;
    Sprite* savelot;
    CC_SYNTHESIZE(int, num, Num);
};

#endif /* SlotMenu_h */
