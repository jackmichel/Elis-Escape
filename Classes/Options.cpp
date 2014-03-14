#include "Options.h"
#include "MainMenu.h"
#include "Constants.h"
#include "Utils.h"

using namespace cocos2d;

//Create an area for the Options Menu to exist
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

	//Sets the visible area
	windowSize = CCDirector::sharedDirector()->getWinSize();
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    //Create background image and ------ASK JACK HOW "Utils::scaleSprite(bg);" WORKS
    CCSprite* bg = CCSprite::create("Options.png");
    bg->setPosition(ccp(windowSize.width/2,windowSize.height/2));
    Utils::scaleSprite(bg);
    this->addChild(bg,-1);

    //Create Menu Buttons, places them in a Menu function, and positions them on the screen
    CCMenuItemImage *mainMenuButton = CCMenuItemImage::create("main_menu_button.png", "main_menu_button_selected.png", this, menu_selector(Options::mainMenu));
    CCMenu *menu = CCMenu::create(mainMenuButton, NULL);
    menu->setPosition(ccp(windowSize.width - 1010, windowSize.height/2 - 280));
    this->addChild(menu,2);

	return true;
}

//Allows for the return to the Main Menu when it's button is tapped
void Options::mainMenu() {
    CCDirector::sharedDirector()->replaceScene(MainMenu::scene());
}
