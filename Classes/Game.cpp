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




	return true;
}
