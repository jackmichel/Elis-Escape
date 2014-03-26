#include "About.h"
#include "MainMenu.h"
#include "Constants.h"
#include "Utils.h"

using namespace cocos2d;

//Create an area for the About Menu to exist
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

	//Sets the visible area
	windowSize = CCDirector::sharedDirector()->getWinSize();
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    //Create background image and ------ASK JACK HOW "Utils::scaleSprite(bg);" WORKS
    CCSprite* bg = CCSprite::create("Credits.png");
    bg->setPosition(ccp(windowSize.width/2,windowSize.height/2));
    Utils::scaleSprite(bg);
    this->addChild(bg,-1);

    //Create Menu Buttons, places them in a Menu function, and positions them on the screen
    CCMenuItemImage *mainMenuButton = CCMenuItemImage::create("main_menu_button.png", "main_menu_button_selected.png", this, menu_selector(About::mainMenu));
    CCMenu *menu = CCMenu::create(mainMenuButton, NULL);
    menu->setPosition(ccp(windowSize.width - 1010, windowSize.height/2 - 280));
    this->addChild(menu,2);

	return true;
}

//Allows for the return to the Main Menu when it's button is tapped
void About::mainMenu() {
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInB::create(0.2,MainMenu::scene()));
}
