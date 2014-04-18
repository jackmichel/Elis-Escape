#include "MainMenu.h"
#include "Constants.h"
#include "Game.h"
#include "Options.h"
#include "LevelSelect.h"
#include "About.h"
#include "Utils.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

//Create an area for the Main Menu to exist
CCScene* MainMenu::scene() {
	CCScene *sc = CCScene::create();
	MainMenu *m = MainMenu::create();
	sc->addChild(m, 0);
	return sc;
}

bool MainMenu::init() {
	if ( !CCLayer::init() ) {
		return false;
	}

	//Sets the visible area
	windowSize = CCDirector::sharedDirector()->getWinSize();
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    //Play Background Music
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Audio/Music/Menu.mp3", true);

    //Create background image and ------ASK JACK HOW "Utils::scaleSprite(bg);" WORKS
    CCSprite* bg = CCSprite::create("Start_Screen_Alt.png");
    bg->setPosition(ccp(windowSize.width/2,windowSize.height/2));
    Utils::scaleSprite(bg);
    this->addChild(bg,-1);

    //Create Menu Buttons, places them in a Menu function, and positions them on the screen
    CCMenuItemImage *levelButton = CCMenuItemImage::create("play_button.png", "play_button_selected.png", this, menu_selector(MainMenu::levelSelect));
    CCMenuItemImage *optionsButton = CCMenuItemImage::create("options_button.png", "options_button_selected.png", this, menu_selector(MainMenu::options));
    CCMenuItemImage *aboutButton = CCMenuItemImage::create("about_button.png", "about_button_selected.png", this, menu_selector(MainMenu::about));
    levelButton->setPosition(-42,250);
    optionsButton->setPosition(-84,100);
    aboutButton->setPosition(-140,-50);
    CCMenu *menu = CCMenu::create(levelButton, optionsButton, aboutButton, NULL);
    menu->setPosition(ccp(windowSize.width - 200, windowSize.height/2 - windowSize.height/4.0f));
    this->addChild(menu,2);

    return true;
}

//The next four void functions allow for switching between menu screens when buttons are tapped
void MainMenu::levelSelect()
{
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInR::create(0.2,LevelSelect::scene()));
}

void MainMenu::options()
{
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInB::create(0.2,Options::scene()));
}

void MainMenu::about()
{
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInT::create(0.2,About::scene()));
}

void MainMenu::mainMenu() {
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.2,MainMenu::scene()));
}
