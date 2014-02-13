#include "MainMenu.h"
#include "Constants.h"
#include "Game.h"
#include "Options.h"
#include "About.h"
#include "Utils.h"

using namespace cocos2d;

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

	windowSize = CCDirector::sharedDirector()->getWinSize();

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    CCSprite* bg = CCSprite::create("Start_Screen.png");
    bg->setPosition(ccp(windowSize.width/2,windowSize.height/2));
    Utils::scaleSprite(bg);
    this->addChild(bg,-1);

    //Create Menu and Menu Buttons
    CCMenuItemImage *playButton = CCMenuItemImage::create("play_button.png", "play_button_selected.png", this, menu_selector(MainMenu::playGame));
    CCMenuItemImage *optionsButton = CCMenuItemImage::create("options_button.png", "options_button_selected.png", this, menu_selector(MainMenu::options));
    CCMenuItemImage *aboutButton = CCMenuItemImage::create("about_button.png", "about_button_selected.png", this, menu_selector(MainMenu::about));
    playButton->setPosition(-42,250);
    optionsButton->setPosition(-84,100);
    aboutButton->setPosition(-140,-50);
    CCMenu *menu = CCMenu::create(playButton, optionsButton, aboutButton, NULL);
    menu->setPosition(ccp(windowSize.width - 200, windowSize.height/2 - windowSize.height/4.0f));
    this->addChild(menu,2);

    return true;
}

void MainMenu::playGame()
{
    CCDirector::sharedDirector()->replaceScene(Game::scene());
}

void MainMenu::options()
{
    CCDirector::sharedDirector()->replaceScene(Options::scene());
}

void MainMenu::about()
{
    CCDirector::sharedDirector()->replaceScene(About::scene());
}

void MainMenu::mainMenu() {
    CCDirector::sharedDirector()->replaceScene(MainMenu::scene());
}
