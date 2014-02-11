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

    CCLabelTTF* pLabel = CCLabelTTF::create("Eli's Escape", FONT_MAIN, 64);
    pLabel->setPosition(ccp(origin.x + pLabel->getContentSize().width,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));
    this->addChild(pLabel, 1);

    //Create Menu and Menu Buttons
    CCMenuItemImage *playButton = CCMenuItemImage::create("button.png", "button.png", this, menu_selector(MainMenu::playGame));
    CCMenuItemImage *optionsButton = CCMenuItemImage::create("button.png", "button.png", this, menu_selector(MainMenu::options));
    CCMenuItemImage *aboutButton = CCMenuItemImage::create("button.png", "button.png", this, menu_selector(MainMenu::about));
    playButton->setPosition(0,400);
    optionsButton->setPosition(0,200);
    aboutButton->setPosition(0,0);
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
