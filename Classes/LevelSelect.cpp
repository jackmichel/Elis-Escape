#include "LevelSelect.h"
#include "MainMenu.h"
#include "Constants.h"
#include "Utils.h"
#include "Game.h"

using namespace cocos2d;

//Create an area for the Level Select Menu to exist
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

	//Sets the visible area
	windowSize = CCDirector::sharedDirector()->getWinSize();
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    //Create background image and ------ASK JACK HOW "Utils::scaleSprite(bg);" WORKS
    CCSprite* bg = CCSprite::create("Level_Select.png");
    bg->setPosition(ccp(windowSize.width/2,windowSize.height/2));
    Utils::scaleSprite(bg);
    this->addChild(bg,-1);

    //Create Menu Buttons, places them in a Menu function, and positions them on the screen
    CCMenuItemImage *mainMenuButton = CCMenuItemImage::create("main_menu_button.png", "main_menu_button_selected.png", this, menu_selector(LevelSelect::mainMenu));
    CCMenu *menu = CCMenu::create(mainMenuButton, NULL);
    menu->setPosition(ccp(windowSize.width - 1010, windowSize.height/2 - 280));
    this->addChild(menu,2);

    //Create level Buttons, places then in a Menu function, and positions them of the screen
    CCMenuItemImage *levelOne = CCMenuItemImage::create("level1_button.png", "level1_button_selected.png", this, menu_selector(LevelSelect::level1));
    CCMenuItemImage *levelTwo = CCMenuItemImage::create("level1_button.png", "level1_button_selected.png", this, menu_selector(LevelSelect::level2));
    levelTwo->setPosition(200, 0);
    CCMenu *levels = CCMenu::create(levelOne, levelTwo, NULL);
    levels->setPosition(ccp(0 + (windowSize.width / 10), windowSize.height/2 + 80));
    this->addChild(levels,2);

	return true;
}

//Allows for the return to the Main Menu when it's button is tapped
void LevelSelect::mainMenu() {
    CCDirector::sharedDirector()->replaceScene(MainMenu::scene());
}

//The following void functions allow for swithcing between different levels in the game
void LevelSelect::level1() {
	const char *level = "lvl1-1.tmx";
    CCDirector::sharedDirector()->replaceScene(Game::scene(level));
}

void LevelSelect::level2() {
	const char *level = "lvl1-2.tmx";
    CCDirector::sharedDirector()->replaceScene(Game::scene(level));
}
