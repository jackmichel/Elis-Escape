#include "LevelSelect.h"
#include "MainMenu.h"
#include "Constants.h"
#include "Utils.h"

using namespace cocos2d;

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

	windowSize = CCDirector::sharedDirector()->getWinSize();

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

   /*
    CCSprite* bg = CCSprite::create("HelloWorld.png");
    bg->setPosition(ccp(windowSize.width/2,windowSize.height/2));
    Utils::scaleSprite(bg);
    this->addChild(bg,-1);
	*/



    //Create Menu and Menu Buttons
    CCMenuItemImage *mainMenuButton = CCMenuItemImage::create("button.png", "button.png", this, menu_selector(LevelSelect::mainMenu));
    CCMenu *menu = CCMenu::create(mainMenuButton, NULL);
    menu->setPosition(ccp(windowSize.width - 200, windowSize.height/2 - windowSize.height/4.0f));
    this->addChild(menu,2);

	return true;
}

void LevelSelect::mainMenu() {
    CCDirector::sharedDirector()->replaceScene(MainMenu::scene());
}
