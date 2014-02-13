#include "About.h"
#include "MainMenu.h"
#include "Constants.h"
#include "Utils.h"

using namespace cocos2d;

CCScene* About::scene() {
    CCScene *sc = CCScene::create();
    sc->setTag(TAG_ABOUT_SCENE);
    About *a = About::create();
    sc->addChild(a, 0, TAG_ABOUT_LAYER);

    return sc;
}

bool About::init() {
	if ( !CCLayer::init() ) {
		return false;
	}

	windowSize = CCDirector::sharedDirector()->getWinSize();

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    CCSprite* bg = CCSprite::create("Credits.png");
    bg->setPosition(ccp(windowSize.width/2,windowSize.height/2));
    Utils::scaleSprite(bg);
    this->addChild(bg,-1);

    //Create Menu and Menu Buttons
    CCMenuItemImage *mainMenuButton = CCMenuItemImage::create("main_menu_button.png", "main_menu_button_selected.png", this, menu_selector(About::mainMenu));
    CCMenu *menu = CCMenu::create(mainMenuButton, NULL);
    menu->setPosition(ccp(windowSize.width - 1010, windowSize.height/2 - 280));
    this->addChild(menu,2);

	return true;
}

void About::mainMenu() {
    CCDirector::sharedDirector()->replaceScene(MainMenu::scene());
}
