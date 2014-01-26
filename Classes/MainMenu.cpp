#include "MainMenu.h"
#include "Constants.h"
#include "Game.h"
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
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));
    this->addChild(pLabel, 1);

    CCLabelTTF* startLabel = CCLabelTTF::create("Play!", FONT_MAIN, 34);
    startLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height/2 + 6));
    this->addChild(startLabel, 2);

    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("button.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);

    this->setTouchEnabled(true);

    return true;
}

void MainMenu::playGame()
{
    CCDirector::sharedDirector()->replaceScene(Game::scene());
}

void MainMenu::mainMenu() {
    CCDirector::sharedDirector()->replaceScene(MainMenu::scene());
}

void MainMenu::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent) {
    CCTouch *touch = (CCTouch *) pTouches->anyObject();

    if (touch) {
    	CCDirector::sharedDirector()->replaceScene(Game::scene());
    }
}
