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

   /*
    CCSprite* bg = CCSprite::create("HelloWorld.png");
    bg->setPosition(ccp(windowSize.width/2,windowSize.height/2));
    Utils::scaleSprite(bg);
    this->addChild(bg,-1);
	*/

    CCLabelTTF* pLabel = CCLabelTTF::create("Options", "Arial", 100);

    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    this->addChild(pLabel, 1);

    //Create Menu and Menu Buttons
    CCMenuItemImage *mainMenuButton = CCMenuItemImage::create("button.png", "button.png", this, menu_selector(Options::mainMenu));
    CCMenu *menu = CCMenu::create(mainMenuButton, NULL);
    menu->setPosition(ccp(windowSize.width - 200, windowSize.height/2 - windowSize.height/4.0f));
    this->addChild(menu,2);

	return true;
}

void Options::mainMenu() {
    CCDirector::sharedDirector()->replaceScene(MainMenu::scene());
}
