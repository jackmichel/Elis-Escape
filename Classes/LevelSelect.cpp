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

    // Check saved levels unlocked, if this is the first time playing set to level 1
    _levelsUnlocked = CCUserDefault::sharedUserDefault()->getIntegerForKey("levelsUnlocked");
    if (_levelsUnlocked == 0) {
    	_levelsUnlocked = 1;
    	CCUserDefault::sharedUserDefault()->setIntegerForKey("levelsUnlocked", 1);
    	CCUserDefault::sharedUserDefault()->flush();
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

    //Create level Buttons, places them in a Menu function, and positions them of the screen
    CCMenuItemImage *levelOne;
    int gearsl1 = CCUserDefault::sharedUserDefault()->getIntegerForKey("levelOne");
    switch (gearsl1) {
    	case 3:
    	{
    		levelOne = CCMenuItemImage::create("l1_gold.png", "l1_gold_h.png", this, menu_selector(LevelSelect::level1));
    		break;
    	}
    	case 2:
    	{
    		levelOne = CCMenuItemImage::create("l1_silver.png", "l1_silver_h.png", this, menu_selector(LevelSelect::level1));
    		break;
    	}
    	case 1:
    	{
    		levelOne = CCMenuItemImage::create("l1_bronze.png", "l1_bronze_h.png", this, menu_selector(LevelSelect::level1));
    		break;
    	}
    	default:
    	{
    		levelOne = CCMenuItemImage::create("l1_none.png", "l1_none_h.png", this, menu_selector(LevelSelect::level1));
    	}
    }

    CCMenuItemImage *levelTwo;
    int gearsl2 = CCUserDefault::sharedUserDefault()->getIntegerForKey("levelTwo");
    switch (gearsl2) {
    	case 3:
    	{
    		levelTwo = CCMenuItemImage::create("l2_gold.png", "l2_gold_h.png", this, menu_selector(LevelSelect::level2));
    		break;
    	}
    	case 2:
    	{
    		levelTwo = CCMenuItemImage::create("l2_silver.png", "l2_silver_h.png", this, menu_selector(LevelSelect::level2));
    		break;
    	}
    	case 1:
    	{
    		levelTwo = CCMenuItemImage::create("l2_bronze.png", "l2_bronze_h.png", this, menu_selector(LevelSelect::level2));
    		break;
    	}
    	default:
    	{
    		levelTwo = CCMenuItemImage::create("l2_none.png", "l2_none_h.png", this, menu_selector(LevelSelect::level2));
    	}
    }

    CCMenuItemImage *levelThree;
    int gearsl3 = CCUserDefault::sharedUserDefault()->getIntegerForKey("levelThree");
    switch (gearsl3) {
    	case 3:
    	{
    		levelThree = CCMenuItemImage::create("l3_gold.png", "l3_gold_h.png", this, menu_selector(LevelSelect::level3));
    		break;
    	}
    	case 2:
    	{
    		levelThree = CCMenuItemImage::create("l3_silver.png", "l3_silver_h.png", this, menu_selector(LevelSelect::level3));
    		break;
    	}
    	case 1:
    	{
    		levelThree = CCMenuItemImage::create("l3_bronze.png", "l3_bronze_h.png", this, menu_selector(LevelSelect::level3));
    		break;
    	}
    	default:
    	{
    		levelThree = CCMenuItemImage::create("l3_none.png", "l3_none_h.png", this, menu_selector(LevelSelect::level3));
    	}
    }

    CCMenuItemImage *levelFour;
    int gearsl4 = CCUserDefault::sharedUserDefault()->getIntegerForKey("levelFour");
    switch (gearsl4) {
    	case 3:
    	{
    		levelFour = CCMenuItemImage::create("l4_gold.png", "l4_gold_h.png", this, menu_selector(LevelSelect::level4));
    		break;
    	}
    	case 2:
    	{
    		levelFour = CCMenuItemImage::create("l4_silver.png", "l4_silver_h.png", this, menu_selector(LevelSelect::level4));
    		break;
    	}
    	case 1:
    	{
    		levelFour = CCMenuItemImage::create("l4_bronze.png", "l4_bronze_h.png", this, menu_selector(LevelSelect::level4));
    		break;
    	}
    	default:
    	{
    		levelFour = CCMenuItemImage::create("l4_none.png", "l4_none_h.png", this, menu_selector(LevelSelect::level4));
    	}
    }

    CCMenuItemImage *levelFive;
    int gearsl5 = CCUserDefault::sharedUserDefault()->getIntegerForKey("levelFive");
    switch (gearsl5) {
    	case 3:
    	{
    		levelFive = CCMenuItemImage::create("l5_gold.png", "l5_gold_h.png", this, menu_selector(LevelSelect::level5));
    		break;
    	}
    	case 2:
    	{
    		levelFive = CCMenuItemImage::create("l5_silver.png", "l5_silver_h.png", this, menu_selector(LevelSelect::level5));
    		break;
    	}
    	case 1:
    	{
    		levelFive = CCMenuItemImage::create("l5_bronze.png", "l5_bronze_h.png", this, menu_selector(LevelSelect::level5));
    		break;
    	}
    	default:
    	{
    		levelFive = CCMenuItemImage::create("l5_none.png", "l5_none_h.png", this, menu_selector(LevelSelect::level5));
    	}
    }

    CCMenuItemImage *levelSix;
    int gearsl6 = CCUserDefault::sharedUserDefault()->getIntegerForKey("levelSix");
    switch (gearsl6) {
    	case 3:
    	{
    		levelSix = CCMenuItemImage::create("l6_gold.png", "l6_gold_h.png", this, menu_selector(LevelSelect::level6));
    		break;
    	}
    	case 2:
    	{
    		levelSix = CCMenuItemImage::create("l6_silver.png", "l6_silver_h.png", this, menu_selector(LevelSelect::level6));
    		break;
    	}
    	case 1:
    	{
    		levelSix = CCMenuItemImage::create("l6_bronze.png", "l6_bronze_h.png", this, menu_selector(LevelSelect::level6));
    		break;
    	}
    	default:
    	{
    		levelSix = CCMenuItemImage::create("l6_none.png", "l6_none_h.png", this, menu_selector(LevelSelect::level6));
    	}
    }

    CCMenuItemImage *levelSeven;
    int gearsl7 = CCUserDefault::sharedUserDefault()->getIntegerForKey("levelSeven");
    switch (gearsl7) {
    	case 3:
    	{
    		levelSeven = CCMenuItemImage::create("l7_gold.png", "l7_gold_h.png", this, menu_selector(LevelSelect::level7));
    		break;
    	}
    	case 2:
    	{
    		levelSeven = CCMenuItemImage::create("l7_silver.png", "l7_silver_h.png", this, menu_selector(LevelSelect::level7));
    		break;
    	}
    	case 1:
    	{
    		levelSeven = CCMenuItemImage::create("l7_bronze.png", "l7_bronze_h.png", this, menu_selector(LevelSelect::level7));
    		break;
    	}
    	default:
    	{
    		levelSeven = CCMenuItemImage::create("l7_none.png", "l7_none_h.png", this, menu_selector(LevelSelect::level7));
    	}
    }

    CCMenuItemImage *levelEight;
    int gearsl8 = CCUserDefault::sharedUserDefault()->getIntegerForKey("levelEight");
    switch (gearsl8) {
    	case 3:
    	{
    		levelEight = CCMenuItemImage::create("l8_gold.png", "l8_gold_h.png", this, menu_selector(LevelSelect::level8));
    		break;
    	}
    	case 2:
    	{
    		levelEight = CCMenuItemImage::create("l8_silver.png", "l8_silver_h.png", this, menu_selector(LevelSelect::level8));
    		break;
    	}
    	case 1:
    	{
    		levelEight = CCMenuItemImage::create("l8_bronze.png", "l8_bronze_h.png", this, menu_selector(LevelSelect::level8));
    		break;
    	}
    	default:
    	{
    		levelEight = CCMenuItemImage::create("l8_none.png", "l8_none_h.png", this, menu_selector(LevelSelect::level8));
    	}
    }

    CCMenuItemImage *levelNine;
    int gearsl9 = CCUserDefault::sharedUserDefault()->getIntegerForKey("levelNine");
    switch (gearsl9) {
    	case 3:
    	{
    		levelNine = CCMenuItemImage::create("l9_gold.png", "l9_gold_h.png", this, menu_selector(LevelSelect::level9));
    		break;
    	}
    	case 2:
    	{
    		levelNine = CCMenuItemImage::create("l9_silver.png", "l9_silver_h.png", this, menu_selector(LevelSelect::level9));
    		break;
    	}
    	case 1:
    	{
    		levelNine = CCMenuItemImage::create("l9_bronze.png", "l9_bronze_h.png", this, menu_selector(LevelSelect::level9));
    		break;
    	}
    	default:
    	{
    		levelNine = CCMenuItemImage::create("l9_none.png", "l9_none_h.png", this, menu_selector(LevelSelect::level9));
    	}
    }

    CCMenuItemImage *levelTen;
    int gearsl10 = CCUserDefault::sharedUserDefault()->getIntegerForKey("levelTen");
    switch (gearsl10) {
    	case 3:
    	{
    		levelTen = CCMenuItemImage::create("l10_gold.png", "l10_gold_h.png", this, menu_selector(LevelSelect::level10));
    		break;
    	}
    	case 2:
    	{
    		levelTen = CCMenuItemImage::create("l10_silver.png", "l10_silver_h.png", this, menu_selector(LevelSelect::level10));
    		break;
    	}
    	case 1:
    	{
    		levelTen = CCMenuItemImage::create("l10_bronze.png", "l10_bronze_h.png", this, menu_selector(LevelSelect::level10));
    		break;
    	}
    	default:
    	{
    		levelTen = CCMenuItemImage::create("l10_none.png", "l10_none_h.png", this, menu_selector(LevelSelect::level10));
    	}
    }

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
    CCMenu *levels;
    switch (_levelsUnlocked) {
    	case 1:
    	{
    		levels = CCMenu::create(levelOne, NULL);
    		break;
    	}
    	case 2:
    	{
    		levels = CCMenu::create(levelOne, levelTwo, NULL);
    		break;
    	}
    	case 3:
    	{
    		levels = CCMenu::create(levelOne, levelTwo, levelThree, NULL);
    		break;
    	}
    	case 4:
    	{
    		levels = CCMenu::create(levelOne, levelTwo, levelThree, levelFour, NULL);
    		break;
    	}
    	case 5:
    	{
    		levels = CCMenu::create(levelOne, levelTwo, levelThree, levelFour, levelFive, NULL);
    		break;
    	}
    	case 6:
    	{
    		levels = CCMenu::create(levelOne, levelTwo, levelThree, levelFour, levelFive, levelSix, NULL);
    		break;
    	}
    	case 7:
    	{
    		levels = CCMenu::create(levelOne, levelTwo, levelThree, levelFour, levelFive, levelSix, levelSeven, NULL);
    		break;
    	}
    	case 8:
    	{
    		levels = CCMenu::create(levelOne, levelTwo, levelThree, levelFour, levelFive, levelSix, levelSeven, levelEight, NULL);
    		break;
    	}
    	case 9:
    	{
    		levels = CCMenu::create(levelOne, levelTwo, levelThree, levelFour, levelFive, levelSix, levelSeven, levelEight, levelNine, NULL);
    		break;
    	}
    	case 10:
    	{
    		levels = CCMenu::create(levelOne, levelTwo, levelThree, levelFour, levelFive, levelSix, levelSeven, levelEight, levelNine, levelTen, NULL);
    		break;
    	}
    	default:
    	{
    		levels = CCMenu::create(levelOne, levelTwo, levelThree, levelFour, levelFive, levelSix, levelSeven, levelEight, levelNine, levelTen, NULL);
    	}
    }
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
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInT::create(0.5,Game::scene(1)));
}

void LevelSelect::level2() {
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInT::create(0.5,Game::scene(2)));
}

void LevelSelect::level3() {
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInT::create(0.5,Game::scene(3)));
}

void LevelSelect::level4() {
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInT::create(0.5,Game::scene(4)));
}

void LevelSelect::level5() {
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInT::create(0.5,Game::scene(5)));
}

void LevelSelect::level6() {
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInT::create(0.5,Game::scene(6)));
}

void LevelSelect::level7() {
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInT::create(0.5,Game::scene(7)));
}

void LevelSelect::level8() {
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInT::create(0.5,Game::scene(8)));
}

void LevelSelect::level9() {
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInT::create(0.5,Game::scene(9)));
}

void LevelSelect::level10() {
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInT::create(0.5,Game::scene(10)));
}
