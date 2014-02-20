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

	this->setTouchEnabled(true);
	windowSize = CCDirector::sharedDirector()->getWinSize();

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    // create a Tiled TMX map

    CCTMXTiledMap *_tileMap = CCTMXTiledMap::create("testsmile.tmx");

    addChild(_tileMap, 0, TAG_LEVEL1);




	return true;
}
void Game::setViewPointCenter(CCPoint position){
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	int x = MAX(position.x, winSize.width/2);
	int y = MAX(position.y, winSize.height/2);
	CCLog("MAX first x and y");

	//x = MIN(x, (_tileMap->getMapSize().width * this->_tileMap->getTileSize().width) - winSize.width/2);
	//y = MIN(y, (_tileMap->getMapSize().height * this->_tileMap->getTileSize().height) - winSize.height/2);
	//CCLog("MIN x and y");

	CCPoint actualPosition = ccp(x,y);
	CCPoint centerOfView = ccp(winSize.width/2, winSize.height/2);
	CCPoint viewPoint = ccpSub(centerOfView, actualPosition);
	this->setPosition(viewPoint);
	CCLog("Set Position");
}

void Game::ccTouchesBegan(CCSet *pTouches, CCEvent *event) {
	//return true;
	CCLog("Touched");
}

void Game::ccTouchesEnded(CCSet *pTouches, CCEvent *event) {
	CCTouch *touch = (CCTouch *)pTouches->anyObject();

	//Get location of event
	CCPoint location = touch->getLocationInView();


	//Convert the location to something useful
	CCPoint convertedLocation = CCDirector::sharedDirector()->convertToGL(location);


	this->setViewPointCenter(convertedLocation);
	CCLog("Set new view point");
}
