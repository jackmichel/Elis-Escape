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
