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
    
    //生成背景图
    void initBackGround();
    //生成logo
    void initLogo();
    //生成记录菜单
    void initMenu_save();
    //生成button_start
    void initButton_start();
    void init_creditBtn();
    void initSoundButton();
    
    void initLogoAnimation();
    void initButton_startAnimation();
    void init_creditBtn_startAnimation();
    void setSaveMenuVisible();
    void setSaveMenuInVisible();
    
    void savemenuCloseCallback(Ref* pSender);
    
    virtual void onEnterTransitionDidFinish();
    
    CREATE_FUNC(WelcomeScene);
    
private:
    Vec2 point_Logo;
    Vec2 point_Menu_Save;
    Vec2 point_Button_Menu_Save_Close;
    Size visibleSize;
    Sprite* sprite_Logo;
    Sprite* button_Start;
    Sprite* button_credit;
    Sprite* menu_Save;
    MenuItemSprite* button_Menu_Save_Close;
};

#endif /* WelcomeScene_h */
