//
//  SlotMenu.cpp
//  KingDom
//
//  Created by gjmac-2 on 15/11/23.
//
//

#include "SlotMenu.h"
#include "GameView.h"

#define NEWGAME 7
#define LABEL_HINT 8

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
    setNum(num);
    
    button_Savelot_Delete = MenuItemSprite::create(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mainmenu_saveslot_delete_0001.png")), Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mainmenu_saveslot_delete_0002.png")),CC_CALLBACK_1(SlotMenu::button_Savelot_Delete_callback, this));
    button_Savelot_Delete->setPosition(getContentSize().width - 20,getContentSize().height - 20);
    
    auto menu = Menu::create(button_Savelot_Delete, NULL);
    menu->setPosition(Vec2::ZERO);
    addChild(menu);
    
    label_hint = Label::createWithTTF("DELETE SLOT?", "Comic_Book.ttf", 32,Size::ZERO,TextHAlignment::LEFT,TextVAlignment::TOP);
    label_hint->setColor(Color3B(219,205,139));
    label_hint->setPosition(Vec2(getContentSize().width/2,getContentSize().height/3 * 2));
    
    auto confirm_Delete = MenuItemSprite::create(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mainmenu_saveslot_confirmdelete_0001.png")), Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mainmenu_saveslot_confirmdelete_0001.png")),CC_CALLBACK_1(SlotMenu::conform_delete, this));
    confirm_Delete->setPosition(Vec2(getContentSize().width/4,getContentSize().height/3));
    
    auto cancel_Delete = MenuItemSprite::create(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mainmenu_saveslot_confirmdelete_0002.png")), Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mainmenu_saveslot_confirmdelete_0002.png")),CC_CALLBACK_1(SlotMenu::cancel_delete, this));
    cancel_Delete->setPosition(Vec2(getContentSize().width/4 * 3,getContentSize().height/3));
    
    auto delete_menu = Menu::create(confirm_Delete,cancel_Delete, NULL);
    delete_menu->setPosition(Vec2::ZERO);
    
    auto confirm = Node::create();
    confirm->addChild(label_hint);
    confirm->addChild(delete_menu);
    confirm->setTag(LABEL_HINT);
    confirm->setVisible(false);
    addChild(confirm);
    
    if (UserDefault::getInstance()->getIntegerForKey(StringUtils::format("Slot%d_Star",getNum()).c_str()) != 0 )
    {
        auto node = Sprite::create();
        
        auto label_slot = Label::createWithTTF(StringUtils::format("SLOT %d",num).c_str(),"Comic_Book.ttf",32,Size::ZERO,TextHAlignment::LEFT,TextVAlignment::TOP);
        label_slot->setColor(Color3B(219,205,139));
        label_slot->setPosition(Point(getContentSize().width/2,getContentSize().height/3*2));
        node->addChild(label_slot);
        auto star = Sprite::createWithSpriteFrameName("mainmenu_saveslot_icons_0001.png");
        star->setPosition(Point(getContentSize().width/4,getContentSize().height/3));
        node->addChild(star);
        
        int starCountInt = UserDefault::getInstance()->getIntegerForKey(StringUtils::format("Slot%d_Star",getNum()).c_str(),0);
        
        auto slot = Label::createWithTTF(StringUtils::format("%d/65",starCountInt).c_str(),"Comic_Book.ttf",32,Size::ZERO,TextHAlignment::LEFT,TextVAlignment::TOP);
        slot->setColor(Color3B(219,205,139));
        slot->setPosition(Point(getContentSize().width/4*2.5,getContentSize().height/3));
        node->addChild(slot);
        node->setTag(NEWGAME);
        addChild(node);
    }
    else
    {
        createNewGame();
        button_Savelot_Delete->setVisible(false);
    }
    
    auto savelot_Listener = EventListenerTouchOneByOne::create();
    savelot_Listener->onTouchBegan = [&](Touch* touch,Event* event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        
        auto locationInNode = target->convertToNodeSpace(touch->getLocation());
        
        auto size = target->getContentSize();
        auto rect = Rect(0, 0, size.width, size.height);
        
        if (rect.containsPoint(locationInNode) && !getChildByTag(LABEL_HINT)->isVisible()) {
            target->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mainmenu_saveslot_0002.png"));
            return true;
        }
        
        return false;
    };
    
    savelot_Listener->onTouchEnded = [&](Touch* touch,Event* event){
        UserDefault::getInstance()->setIntegerForKey(StringUtils::format("Slot%d_Star",getNum()).c_str(), 1);
        Director::getInstance()->replaceScene(GameView::createScene());
    };
    savelot_Listener->setSwallowTouches(true);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(savelot_Listener, this);
    
    return true;
}

void SlotMenu::button_Savelot_Delete_callback(Ref* pSender)
{
    getChildByTag(NEWGAME)->setVisible(false);
    button_Savelot_Delete->setVisible(false);
    getChildByTag(LABEL_HINT)->setVisible(true);
}

void SlotMenu::conform_delete(Ref* pSender)
{
    getChildByTag(LABEL_HINT)->setVisible(false);
    removeChildByTag(NEWGAME);
    createNewGame();
    deleteRecord(getNum());
}

void SlotMenu::cancel_delete(Ref* pSender)
{
    getChildByTag(NEWGAME)->setVisible(true);
    button_Savelot_Delete->setVisible(true);
    getChildByTag(LABEL_HINT)->setVisible(false);
}

void SlotMenu::createNewGame()
{
    auto label = Label::createWithTTF("New Game","Comic_Book.ttf",42,Size::ZERO,TextHAlignment::LEFT,TextVAlignment::TOP);
    label->setColor(Color3B(219,205,139));
    label->setPosition(getContentSize().width/2,getContentSize().height/2);
    label->setTag(NEWGAME);
    addChild(label);
}

void SlotMenu::deleteRecord(int num)
{
    UserDefault::getInstance()->setIntegerForKey(StringUtils::format("Slot%d_Star",num).c_str(),0);
}
