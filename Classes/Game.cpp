#include "Game.h"
#include "MainMenu.h"
#include "Constants.h"
#include "Utils.h"

using namespace cocos2d;

CCScene* Game::scene() {
    CCScene *sc = CCScene::create();
    sc->setTag(TAG_GAME_SCENE);
    Game *g = Game::create();
    sc->addChild(g, 0, TAG_GAME_LAYER);

    return sc;
}

bool Game::init() {
	if ( !CCLayer::init() ) {
		return false;
	}

	windowSize = CCDirector::sharedDirector()->getWinSize();

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    CCSprite* bg = CCSprite::create("level1.png");
    bg->setPosition(ccp(windowSize.width/2,windowSize.height/2));
    Utils::scaleSprite(bg);
    this->addChild(bg,-1);

    CCLabelTTF* pLabel = CCLabelTTF::create("Game Screen", "Arial", 100);

    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    this->addChild(pLabel, 2);

    //Create Menu and Menu Buttons
        CCMenuItemImage *mainMenuButton = CCMenuItemImage::create("main_menu_button.png", "main_menu_button_selected.png", this, menu_selector(Game::mainMenu));
        CCMenu *menu = CCMenu::create(mainMenuButton, NULL);
        menu->setPosition(ccp(windowSize.width - 1010, windowSize.height/2 - 280));
        this->addChild(menu,3);

	return true;
}

void Game::mainMenu() {
    CCDirector::sharedDirector()->replaceScene(MainMenu::scene());
}
