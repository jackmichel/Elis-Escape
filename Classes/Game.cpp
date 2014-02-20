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

    CCTMXTiledMap *map = CCTMXTiledMap::create("lvl1-1.tmx");

    addChild(map, 0, TAG_LEVEL1);

    eli = new CCSprite();
    eli->initWithFile("eli.png");
    eli->setPosition(ccp(100,600));

    this->addChild(eli, 1);
   // this->setViewPointCenter(eli->getPosition());

	return true;
}

void Game::setViewPointCenter(CCPoint position) {

    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    int x = MAX(position.x, winSize.width/2);
    int y = MAX(position.y, winSize.height/2);
    x = MIN(x, (map->getMapSize().width * this->map->getTileSize().width) - winSize.width / 2);
    y = MIN(y, (map->getMapSize().height * map->getTileSize().height) - winSize.height/2);
    CCPoint actualPosition = ccp(x, y);

    CCPoint centerOfView = ccp(winSize.width/2, winSize.height/2);
    CCPoint viewPoint = ccpSub(centerOfView, actualPosition);
    this->setPosition(viewPoint);
}
