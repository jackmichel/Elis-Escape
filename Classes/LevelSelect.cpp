#include "LevelSelect.h"
#include "MainMenu.h"
#include "Constants.h"
#include "Utils.h"
#include "Game.h"

using namespace cocos2d;

CCScene* LevelSelect::scene() {
    CCScene *sc = CCScene::create();
    sc->setTag(TAG_LEVELSELECT_SCENE);
    LevelSelect *l = LevelSelect::create();
    sc->addChild(l, 0, TAG_LEVELSELECT_LAYER);

    return sc;
}

bool LevelSelect::init() {
	if ( !CCLayer::init() ) {
		return false;
	}

	windowSize = CCDirector::sharedDirector()->getWinSize();

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    CCSprite* bg = CCSprite::create("Level_Select.png");
    bg->setPosition(ccp(windowSize.width/2,windowSize.height/2));
    Utils::scaleSprite(bg);
    this->addChild(bg,-1);

    //Create Menu and Menu Buttons
    CCMenuItemImage *mainMenuButton = CCMenuItemImage::create("main_menu_button.png", "main_menu_button_selected.png", this, menu_selector(LevelSelect::mainMenu));
    CCMenu *menu = CCMenu::create(mainMenuButton, NULL);
    menu->setPosition(ccp(windowSize.width - 1010, windowSize.height/2 - 280));
    this->addChild(menu,2);

    //Create level Buttons
    CCMenuItemImage *levelOne = CCMenuItemImage::create("level1_button.png", "level1_button_selected.png", this, menu_selector(LevelSelect::level1));
    CCMenuItemImage *levelTwo = CCMenuItemImage::create("level1_button.png", "level1_button_selected.png", this, menu_selector(LevelSelect::level2));
    levelTwo->setPosition(200, 0);
    CCMenu *levels = CCMenu::create(levelOne, levelTwo, NULL);
    levels->setPosition(ccp(0 + (windowSize.width / 10), windowSize.height/2 + 80));
    this->addChild(levels,2);

	return true;
}

void LevelSelect::mainMenu() {
    CCDirector::sharedDirector()->replaceScene(MainMenu::scene());
}

void LevelSelect::level1() {
	const char *level = "lvl1-1.tmx";
    CCDirector::sharedDirector()->replaceScene(Game::scene(level));
}

void LevelSelect::level2() {
	const char *level = "lvl1-2.tmx";
    CCDirector::sharedDirector()->replaceScene(Game::scene(level));
}
