//
//  WelcomeScene.cpp
//  KingDom
//
//  Created by gjmac-2 on 15/11/20.
//
//

#include "WelcomeScene.h"
#include "SlotMenu.h"

Scene* WelcomeScene::createScene()
{
    auto scene = Scene::create();
    auto layer = WelcomeScene::create();
    scene->addChild(layer);
    return scene;
}

bool WelcomeScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mainmenu_spritesheet_32_1-hd.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mainmenu_spritesheet_32_2-hd.plist");
    
    //生成背景图
    initBackGround();
    //生成logo
    initLogo();
    //生成记录菜单
    initMenu_save();
    //生成button_start
    initButton_start();
    init_creditBtn();
    initSoundButton();
    
    return true;
}

void WelcomeScene::onEnterTransitionDidFinish()
{
    auto sequence = Sequence::create(ScaleTo::create(0.5, 1.5f,1.5f),
            ScaleTo::create(0.2, 1.0f,1.0f),
            CallFunc::create(CC_CALLBACK_0(WelcomeScene::initLogoAnimation, this)),
            CallFunc::create(CC_CALLBACK_0(WelcomeScene::initButton_startAnimation, this)),
            CallFunc::create(CC_CALLBACK_0(WelcomeScene::init_creditBtn_startAnimation, this)),
            NULL);
    sprite_Logo->runAction(sequence);
}

void WelcomeScene::initBackGround()
{
    auto sprite_background = Sprite::createWithSpriteFrameName("mainmenu_bg.png");
    sprite_background->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    addChild(sprite_background,-1);
}

void WelcomeScene::initLogo()
{
    sprite_Logo = Sprite::createWithSpriteFrameName("logo.png");
    sprite_Logo->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    point_Logo.x = visibleSize.width/2;
    point_Logo.y = visibleSize.height-(sprite_Logo->getContentSize().height/2);
    sprite_Logo->setScale(0.2f);
    sprite_Logo->setPosition(point_Logo);
    addChild(sprite_Logo,9);
}

void WelcomeScene::initMenu_save()
{
    menu_Save = Sprite::createWithSpriteFrameName("mainmenu_saveslot_bg.png");
    //计算位置
    point_Menu_Save.x = point_Logo.x;
    point_Menu_Save.y = point_Logo.y - sprite_Logo->getContentSize().height*1.4/2;
    
    menu_Save->setPosition(Vec2(point_Menu_Save.x,point_Menu_Save.y - 500));
    
    auto slot_1 = SlotMenu::createMenu(1);
    slot_1->setPosition(Vec2(menu_Save->getContentSize().width/2, menu_Save->getContentSize().height/2));
    menu_Save->addChild(slot_1);
    
    auto slot_2 = SlotMenu::createMenu(2);
    slot_2->setPosition(Vec2(menu_Save->getContentSize().width/4 - 30,menu_Save->getContentSize().height/2));
    menu_Save->addChild(slot_2);
    
    auto slot_3 = SlotMenu::createMenu(3);
    slot_3->setPosition(Vec2(menu_Save->getContentSize().width/4*3 + 30,menu_Save->getContentSize().height/2));
    menu_Save->addChild(slot_3);
    
    
    addChild(menu_Save,0);
    
    button_Menu_Save_Close = MenuItemSprite::create(Sprite::createWithSpriteFrameName("mainmenu_saveslot_close_0001.png"), Sprite::createWithSpriteFrameName("mainmenu_saveslot_close_0002.png"),CC_CALLBACK_1(WelcomeScene::savemenuCloseCallback, this));
    
    point_Button_Menu_Save_Close.x = point_Logo.x;
    point_Button_Menu_Save_Close.y = point_Menu_Save.y - menu_Save->getContentSize().height/2 + button_Menu_Save_Close->getContentSize().height + 2 ;
    button_Menu_Save_Close->setPosition(Point(point_Button_Menu_Save_Close.x,point_Button_Menu_Save_Close.y-500));
    
    auto menu = Menu::create(button_Menu_Save_Close, NULL);
    menu->setPosition(Vec2::ZERO);
    
    addChild(menu,0);
}

void WelcomeScene::savemenuCloseCallback(Ref* pSender)
{
    setSaveMenuInVisible();
    initButton_startAnimation();
    init_creditBtn_startAnimation();
}

void WelcomeScene::initButton_start()
{
    button_Start = Sprite::createWithSpriteFrameName("menu_startchain_0001.png");
    button_Start->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    button_Start->setVisible(false);
    button_Start->setPosition(point_Logo);
    addChild(button_Start,1);
    
    auto button_Start_listener = EventListenerTouchOneByOne::create();
    button_Start_listener->onTouchBegan = [&](Touch* touch,Event* event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        
        Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size size = target->getContentSize();
        Rect rect = Rect(0+40, 0+30, size.width-80, size.height/3 +15);
        
        if (rect.containsPoint(locationInNode) && target->isVisible())
        {
            target->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("menu_startchain_0002.png"));
            return true;
        }
        return false;
    };
    
    button_Start_listener->onTouchEnded = [&](Touch* touch,Event* event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        target->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("menu_startchain_0001.png"));
        button_credit->setVisible(false);
        button_credit->runAction(MoveTo::create(0.3f, Point(point_Logo.x,point_Logo.y - 180)));
        target->runAction(Sequence::create(DelayTime::create(0.3f),MoveTo::create(0.3f, Point(point_Logo.x,point_Logo.y)),NULL));
        target->setVisible(false);
        
        setSaveMenuVisible();
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(button_Start_listener, button_Start);
}

void WelcomeScene::initLogoAnimation()
{
    auto sprite = Sprite::createWithSpriteFrameName("logo_brillo_0001.png");
    sprite->setPosition(point_Logo);
    SpriteFrame* frame = NULL;
    Vector<SpriteFrame*> aFrames(20);
    
    for (int len = 1; len <= 21; len++) {
        char str[100];
        sprintf(str, "logo_brillo_00%02d.png",len);
        frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
        if (frame != nullptr) {
            aFrames.pushBack(frame);
        }
    }
    addChild(sprite,10);
    auto animation = Animation::createWithSpriteFrames(aFrames,0.1);
    sprite->runAction(RepeatForever::create(Animate::create(animation)));
    
}

void WelcomeScene::initButton_startAnimation()
{
    button_Start->setVisible(true);
    button_Start->runAction(MoveTo::create(0.3f, Vec2(point_Logo.x,point_Logo.y - 180)));
}

void WelcomeScene::init_creditBtn_startAnimation()
{
    button_credit->runAction(Sequence::create(
        DelayTime::create(0.3f),
        CallFuncN::create(CC_CALLBACK_0(Sprite::setVisible, button_credit,true)),
        MoveTo::create(0.3f, Vec2(point_Logo.x,point_Logo.y - 360)),NULL));
}

void WelcomeScene::init_creditBtn()
{
    button_credit = Sprite::createWithSpriteFrameName("menu_creditschain_0001.png");
    button_credit->setVisible(false);
    
    button_credit->setPosition(point_Logo.x,point_Logo.y - 180);
    addChild(button_credit,0);
    
    auto button_credit_listener = EventListenerTouchOneByOne::create();
    button_credit_listener->onTouchBegan = [&](Touch* touch,Event* event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        
        auto locationInNode = target->convertToNodeSpace(touch->getLocation());
        auto size = target->getContentSize();
        auto rect = Rect(0+40, 0+30, size.width - 80, size.height/3+15);
        
        if (rect.containsPoint(locationInNode) && target->isVisible()) {
            target->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("menu_creditschain_0002.png"));
            return true;
        }
        
        return false;
    };
    
    button_credit_listener->onTouchEnded = [&](Touch* touch,Event* event){
        static_cast<Sprite*>(event->getCurrentTarget())->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("menu_creditschain_0001.png"));
        
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(button_credit_listener, button_credit);
}

void WelcomeScene::initSoundButton()
{
    
}

void WelcomeScene::setSaveMenuInVisible()
{
    //移出屏幕外
    menu_Save->runAction(MoveBy::create(0.3f,Point(0,-500)));
    button_Menu_Save_Close->runAction(MoveBy::create(0.3f,Point(0,-500)));
}

void WelcomeScene::setSaveMenuVisible()
{
    menu_Save->runAction(MoveTo::create(0.3f,point_Menu_Save));
    button_Menu_Save_Close->runAction(MoveTo::create(0.3f, point_Button_Menu_Save_Close));
}

