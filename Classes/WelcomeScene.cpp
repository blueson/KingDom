//
//  WelcomeScene.cpp
//  KingDom
//
//  Created by gjmac-2 on 15/11/20.
//
//

#include "WelcomeScene.h"

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
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mainmenu_spritesheet_32_1-hd.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mainmenu_spritesheet_32_2-hd.plist");
    
    auto sprite_background = Sprite::createWithSpriteFrameName("mainmenu_bg.png");
    
    sprite_background->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    addChild(sprite_background,-1);
    
    
    sprite_Logo = Sprite::createWithSpriteFrameName("logo.png");
    auto point_Logo = Vec2(visibleSize.width/2, visibleSize.height-(sprite_Logo->getContentSize().height/2));
    sprite_Logo->setScale(0.2f);
    sprite_Logo->setPosition(point_Logo);
    addChild(sprite_Logo,1);
    
    auto scaleAction = ScaleTo::create(0.5, 1.5, 1.5);
    sprite_Logo->runAction(scaleAction);
    
    auto sprite = Sprite::createWithSpriteFrameName("logo_brillo_0001.png");
    
    sprite->setPosition(point_Logo);
    
    addChild(sprite,2);
    return true;
}