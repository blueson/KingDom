//
//  SlotMenu.cpp
//  KingDom
//
//  Created by gjmac-2 on 15/11/23.
//
//

#include "SlotMenu.h"

SlotMenu* SlotMenu::createMenu(int num)
{
    auto slotMenu = new SlotMenu();
    if (slotMenu && slotMenu->initWithNum(num)) {
        slotMenu->autorelease();
        return slotMenu;
    }
    
    CC_SAFE_DELETE(slotMenu);
    slotMenu = NULL;
    return nullptr;
}

SlotMenu::SlotMenu()
{
    
}

SlotMenu::~SlotMenu()
{
    
}

bool SlotMenu::initWithNum(int num)
{
    if (!Sprite::initWithSpriteFrameName("mainmenu_saveslot_0001.png")) {
        return false;
    }
    this->num = num;
    
    if (UserDefault::getInstance()->getBoolForKey(Value(num).asString().c_str()))
    {
        
    }
    else
    {
        label_hint = Label::createWithTTF("New Game", "Comic_Book.ttf", 30);
        label_hint->setPosition(Vec2(getContentSize().width/2,getContentSize().height/2));
        addChild(label_hint);
    }
    
    return true;
}

void SlotMenu::button_Savelot_Delete_callback(Ref* pSender)
{
    
}

void SlotMenu::conform_delete(Ref* pSender)
{
    
}

void SlotMenu::cancel_delete(Ref* pSender)
{
    
}

void SlotMenu::createNewGame()
{
    
}
