#include "Options.h"
#include "MainMenu.h"
#include "Constants.h"
#include "Utils.h"

using namespace cocos2d;

CCScene* Options::scene() {
    CCScene *sc = CCScene::create();
    sc->setTag(TAG_OPTIONS_SCENE);
    Options *o = Options::create();
    sc->addChild(o, 0, TAG_OPTIONS_LAYER);

    return sc;
}

bool Options::init() {
	if ( !CCLayer::init() ) {
		return false;
	}

	windowSize = CCDirector::sharedDirector()->getWinSize();

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    CCSprite* bg = CCSprite::create("Options.png");
    bg->setPosition(ccp(windowSize.width/2,windowSize.height/2));
    Utils::scaleSprite(bg);
    this->addChild(bg,-1);

    //Create Menu and Menu Buttons
    CCMenuItemImage *mainMenuButton = CCMenuItemImage::create("main_menu_button.png", "main_menu_button_selected.png", this, menu_selector(Options::mainMenu));
    CCMenu *menu = CCMenu::create(mainMenuButton, NULL);
    menu->setPosition(ccp(windowSize.width - 950, windowSize.height/2 - 230));
    this->addChild(menu,2);

	return true;
}

void Options::mainMenu() {
    CCDirector::sharedDirector()->replaceScene(MainMenu::scene());
}
