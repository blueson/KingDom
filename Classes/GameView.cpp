//
//  GameView.cpp
//  KingDom
//
//  Created by gjmac-2 on 15/11/24.
//
//

#include "GameView.h"

Scene* GameView::createScene()
{
    auto scene = Scene::create();
    auto layer = GameView::create();
    scene->addChild(layer);
    return scene;
}

bool GameView::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    return true;
}