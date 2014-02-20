#include "GameReturnButton.h"
#include "Constants.h"
#include "Game.h"
#include "Utils.h"
#include "MainMenu.h"

using namespace cocos2d;

bool GameReturnButton::init()
{
    if (!CCSprite::init()) {
        return false;
    }

    CCSprite* backbutton = CCSprite::create("testreturnbutton.jpg");
    this->addChild(backbutton,1);

}

GameReturnButton* GameReturnButton::button()
{
    GameReturnButton *btn = new GameReturnButton();
    btn->init();
    btn->autorelease();
    return btn;
}


