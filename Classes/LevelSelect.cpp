#include "LevelSelect.h"
#include "MainMenu.h"
#include "Constants.h"
#include "Utils.h"
#include "Bridge.h"
#include "Spring.h"
#include "Pole.h"
#include "Catapult.h"
#include "Fan.h"
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
    CCMenuItemImage *levelTwo = CCMenuItemImage::create("level2_button.png", "level2_button_selected.png", this, menu_selector(LevelSelect::level2));
    CCMenuItemImage *levelThree = CCMenuItemImage::create("level3_button.png", "level3_button_selected.png", this, menu_selector(LevelSelect::level3));
    CCMenuItemImage *levelFour = CCMenuItemImage::create("level4_button.png", "level4_button_selected.png", this, menu_selector(LevelSelect::level4));
    CCMenuItemImage *levelFive = CCMenuItemImage::create("level5_button.png", "level5_button_selected.png", this, menu_selector(LevelSelect::level5));
    CCMenuItemImage *levelSix = CCMenuItemImage::create("level6_button.png", "level6_button_selected.png", this, menu_selector(LevelSelect::level6));
    CCMenuItemImage *levelSeven = CCMenuItemImage::create("level7_button.png", "level7_button_selected.png", this, menu_selector(LevelSelect::level7));
    CCMenuItemImage *levelEight = CCMenuItemImage::create("level8_button.png", "level8_button_selected.png", this, menu_selector(LevelSelect::level8));
    CCMenuItemImage *levelNine = CCMenuItemImage::create("level9_button.png", "level9_button_selected.png", this, menu_selector(LevelSelect::level9));
    CCMenuItemImage *levelTen = CCMenuItemImage::create("level10_button.png", "level10_button_selected.png", this, menu_selector(LevelSelect::level10));
    levelOne->setPosition(-400, 0);
    levelTwo->setPosition(-200, 0);
    levelThree->setPosition(0, 0);
    levelFour->setPosition(200, 0);
    levelFive->setPosition(400, 0);
    levelSix->setPosition(-400, -200);
    levelSeven->setPosition(-200, -200);
    levelEight->setPosition(0, -200);
    levelNine->setPosition(200, -200);
    levelTen->setPosition(400, -200);
    CCMenu *levels = CCMenu::create(levelOne, levelTwo, levelThree, levelFour, levelFive, levelSix, levelSeven, levelEight, levelNine, levelTen, NULL);
    levels->setPosition(ccp((windowSize.width / 2), windowSize.height / 2 + 80));
    this->addChild(levels,2);

	return true;
}

//Allows for the return to the Main Menu when it's button is tapped
void LevelSelect::mainMenu() {
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInL::create(0.2,MainMenu::scene()));
}

//The following void functions allow for swithcing between different levels in the game
void LevelSelect::level1() {
	const char *level = "lvl1-1.tmx";
	CCArray * tools = CCArray::createWithCapacity(0);
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInT::create(0.5,Game::scene(level, tools)));
}

void LevelSelect::level2() {
	const char *level = "lvl1-2.tmx";
	CCArray * tools = CCArray::createWithCapacity(2);
	Bridge * t1 = Bridge::create();
	Bridge * t2 = Bridge::create();
	tools->addObject(t1);
	tools->addObject(t2);
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInT::create(0.5,Game::scene(level, tools)));
}

void LevelSelect::level3() {
	const char *level = "lvl1-3.tmx";
	CCArray * tools = CCArray::createWithCapacity(5);
	Bridge * t1 = Bridge::create();
	Bridge * t2 = Bridge::create();
	Bridge * t3 = Bridge::create();
	Bridge * t4 = Bridge::create();
	Bridge * t5 = Bridge::create();
	tools->addObject(t1);
	tools->addObject(t2);
	tools->addObject(t3);
	tools->addObject(t4);
	tools->addObject(t5);
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInT::create(0.5,Game::scene(level, tools)));
}

void LevelSelect::level4() {
	const char *level = "lvl1-4.tmx";
	CCArray * tools = CCArray::createWithCapacity(5);
	Bridge * t1 = Bridge::create();
	Bridge * t2 = Bridge::create();
	Bridge * t3 = Bridge::create();
	Bridge * t4 = Bridge::create();
	Bridge * t5 = Bridge::create();
	tools->addObject(t1);
	tools->addObject(t2);
	tools->addObject(t3);
	tools->addObject(t4);
	tools->addObject(t5);
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInT::create(0.5,Game::scene(level, tools)));
}

void LevelSelect::level5() {
	const char *level = "lvl1-5.tmx";
	CCArray * tools = CCArray::createWithCapacity(2);
	Spring * t1 = Spring::create();
	Spring * t2 = Spring::create();
	tools->addObject(t1);
	tools->addObject(t2);
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInT::create(0.5,Game::scene(level, tools)));
}

void LevelSelect::level6() {
	const char *level = "lvl1-6.tmx";
	CCArray * tools = CCArray::createWithCapacity(6);
	Bridge * t1 = Bridge::create();
	Bridge * t2 = Bridge::create();
	Spring * t3 = Spring::create();
	Spring * t4 = Spring::create();
	Spring * t5 = Spring::create();
	Spring * t6 = Spring::create();
	tools->addObject(t1);
	tools->addObject(t2);
	tools->addObject(t3);
	tools->addObject(t4);
	tools->addObject(t5);
	tools->addObject(t6);
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInT::create(0.5,Game::scene(level, tools)));
}

void LevelSelect::level7() {
	const char *level = "lvl1-7.tmx";
	CCArray * tools = CCArray::createWithCapacity(4);
	Bridge * t1 = Bridge::create();
	Bridge * t2 = Bridge::create();
	Spring * t3 = Spring::create();
	Spring * t4 = Spring::create();
	tools->addObject(t1);
	tools->addObject(t2);
	tools->addObject(t3);
	tools->addObject(t4);
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInT::create(0.5,Game::scene(level, tools)));
}

void LevelSelect::level8() {
	const char *level = "lvl1-8.tmx";
	CCArray * tools = CCArray::createWithCapacity(14);
	Pole * t1 = Pole::create();
	Pole * t2 = Pole::create();
	Pole * t3 = Pole::create();
	Pole * t4 = Pole::create();
	Pole * t5 = Pole::create();
	Pole * t6 = Pole::create();
	Pole * t7 = Pole::create();
	Pole * t8 = Pole::create();
	Pole * t9 = Pole::create();
	Pole * t10 = Pole::create();
	Pole * t11 = Pole::create();
	Pole * t12 = Pole::create();
	Pole * t13 = Pole::create();
	Pole * t14 = Pole::create();
	tools->addObject(t1);
	tools->addObject(t2);
	tools->addObject(t3);
	tools->addObject(t4);
	tools->addObject(t5);
	tools->addObject(t6);
	tools->addObject(t7);
	tools->addObject(t8);
	tools->addObject(t9);
	tools->addObject(t10);
	tools->addObject(t11);
	tools->addObject(t12);
	tools->addObject(t13);
	tools->addObject(t14);
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInT::create(0.5,Game::scene(level, tools)));
}

void LevelSelect::level9() {
	const char *level = "lvl1-9.tmx";
	CCArray * tools = CCArray::createWithCapacity(6);
	Bridge * t1 = Bridge::create();
	Bridge * t2 = Bridge::create();
	Spring * t3 = Spring::create();
	Pole * t4 = Pole::create();
	Pole * t5 = Pole::create();
	Pole * t6 = Pole::create();
	tools->addObject(t1);
	tools->addObject(t2);
	tools->addObject(t3);
	tools->addObject(t4);
	tools->addObject(t5);
	tools->addObject(t6);
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInT::create(0.5,Game::scene(level, tools)));
}

void LevelSelect::level10() {
	const char *level = "lvl1-10.tmx";
	CCArray * tools = CCArray::createWithCapacity(8);
	Bridge * t1 = Bridge::create();
	Bridge * t2 = Bridge::create();
	Bridge * t3 = Bridge::create();
	Spring * t4 = Spring::create();
	Spring * t5 = Spring::create();
	Spring * t6 = Spring::create();
	Spring * t7 = Spring::create();
	Pole * t8 = Pole::create();
	tools->addObject(t1);
	tools->addObject(t2);
	tools->addObject(t3);
	tools->addObject(t4);
	tools->addObject(t5);
	tools->addObject(t6);
	tools->addObject(t7);
	tools->addObject(t8);
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInT::create(0.5,Game::scene(level, tools)));
}
