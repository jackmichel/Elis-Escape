#include "Game.h"
#include "MainMenu.h"
#include "Constants.h"
#include "Utils.h"
#include "Eli.h"

using namespace cocos2d;

CCScene* Game::scene() {
    CCScene *sc = CCScene::create();
    sc->setTag(TAG_GAME_SCENE);
    Game *g = Game::create();
    sc->addChild(g, 0, TAG_GAME_LAYER);

    HudLayer *hud = HudLayer::create();
    sc->addChild(hud);
    g->_hud = hud;

    return sc;
}

bool Game::init() {
	if ( !CCLayer::init() ) {
		return false;
	}

	windowSize = CCDirector::sharedDirector()->getWinSize();

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    // create a Tiled TMX map
    _tileMap = new CCTMXTiledMap();
    _tileMap->initWithTMXFile("lvl1-1.tmx");
    _platform = _tileMap->layerNamed("Platform");
    this->addChild(_tileMap, 0);

    // Important inits
    mapHeightTiles = _tileMap->getMapSize().height;
    mapWidthTiles = _tileMap->getMapSize().width;
    mapHeight = mapHeightTiles * _tileMap->getTileSize().height;
    mapWidth = mapWidthTiles * _tileMap->getTileSize().width;
    _touches = CCArray::createWithCapacity(10);
    _touches->retain();
    _maxTouchDistanceToClick = 315.0f;

    //Create array of all tiles in map
    _tiles = CCArray::createWithCapacity(mapHeightTiles * mapWidthTiles);
    _tiles->retain();
    //Loop through tilemap rows
    for (int i = 0; i < mapHeightTiles; i++) {
    	//Loop through tilemap columns
    	for (int j = 0; j < mapWidthTiles; j++) {
    		//Check if this is a platform at this coordinate
    		if (_platform->tileGIDAt(ccp(j,i)) == 1) {
    			//It is a platform so add it to the array
    			CCSprite *tile = _platform->tileAt(ccp(j,i));
    			_tiles->addObject(tile);
    		}
    	}
    }

    // Listen for touches
    this->setTouchEnabled(true);

    // This variable is a flag for whether or not the main game loop should fire
    _running = false;

    // Initialize game loop
    this->schedule(schedule_selector(Game::gameLoop));

    // Reference to the objects in tilemap
    CCTMXObjectGroup *objectGroup = _tileMap->objectGroupNamed("Objects");

    if(objectGroup == NULL){
        CCLog("tile map has no objects object layer");
        return false;
    }

    CCDictionary *spawnPoint = objectGroup->objectNamed("SpawnPoint");

    int x = ((CCString)*spawnPoint->valueForKey("x")).intValue();
    int y = ((CCString)*spawnPoint->valueForKey("y")).intValue();

    eli = Eli::create();
    eli->setPosition(ccp(x,y));

    this->addChild(eli);
    this->setViewPointCenter(eli->getPosition());

	return true;
}

void Game::gameLoop(float dt) {
	if (!_running) { return; }
	eli->update(dt);
	this->setEliPosition(eli->getNextPosition());
}

void Game::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent) {
	if (!_running) {
	    CCTouch *pTouch;
	    CCSetIterator setIter;
	    for (setIter = pTouches->begin(); setIter != pTouches->end(); ++setIter) {
	        pTouch = (CCTouch *)(*setIter);
	        _touches->addObject(pTouch);
	    }

	    if (_touches->count() == 1) {
	        _touchMoveBegan = false;
	        time_t seconds;

	        seconds = time (NULL);
	        _singleTouchTimestamp = seconds/60;
	    } else {
	    	 _singleTouchTimestamp = INFINITY;
	    }
	} else {
		CCTouch *touch = (CCTouch *)pTouches->anyObject();
		if (touch) {
			if (eli->getState() != kPlayerDying && !eli->getInAir()) {
				eli->setJumping(true);
				eli->setInAir(true);
			}
		}
	}
}

void Game::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent) {
	if (!_running) {
		bool multitouch = _touches->count() > 1;
		if (multitouch) {
			// Get the two first touches
			CCTouch *touch1 = (CCTouch*)_touches->objectAtIndex(0);
			CCTouch *touch2 = (CCTouch*)_touches->objectAtIndex(1);
			// Get current and previous positions of the touches
			CCPoint curPosTouch1 = CCDirector::sharedDirector()->convertToGL(touch1->getLocationInView());
			CCPoint curPosTouch2 = CCDirector::sharedDirector()->convertToGL(touch2->getLocationInView());

			CCPoint prevPosTouch1 = CCDirector::sharedDirector()->convertToGL(touch1->getPreviousLocationInView());
			CCPoint prevPosTouch2 = CCDirector::sharedDirector()->convertToGL(touch2->getPreviousLocationInView());

			// Calculate current and previous positions of the layer relative the anchor point
			CCPoint curPosLayer = ccpMidpoint(curPosTouch1, curPosTouch2);
			CCPoint prevPosLayer = ccpMidpoint(prevPosTouch1, prevPosTouch2);

			// If current and previous position of the multitouch's center aren't equal -> change position of the layer
			if (!prevPosLayer.equals(curPosLayer))
			{
				this->setPosition(ccp(this->getPosition().x + curPosLayer.x - prevPosLayer.x,
					this->getPosition().y + curPosLayer.y - prevPosLayer.y));
			}
			// Don't click with multitouch
			_touchDistance = INFINITY;
		} else {
			// Get the single touch and it's previous & current position.
			CCTouch *touch = (CCTouch*)_touches->objectAtIndex(0);
			CCPoint curTouchPosition = CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());
			CCPoint prevTouchPosition = CCDirector::sharedDirector()->convertToGL(touch->getPreviousLocationInView());

			this->setPosition(ccp(this->getPosition().x + curTouchPosition.x - prevTouchPosition.x,
				this->getPosition().y + curTouchPosition.y - prevTouchPosition.y));

			// Accumulate touch distance for all modes.
			_touchDistance += ccpDistance(curTouchPosition, prevTouchPosition);
		}
	}
}

void Game::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent) {
	if (!_running) {
		_singleTouchTimestamp = INFINITY;

		// Process click event in single touch.
		if (  (_touchDistance < _maxTouchDistanceToClick) && (_touches->count() == 1)) {
			CCTouch *touch = (CCTouch*)_touches->objectAtIndex(0);
			CCPoint curPos = CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());
		}

		CCTouch *pTouch;
		CCSetIterator setIter;
		for (setIter = pTouches->begin(); setIter != pTouches->end(); ++setIter) {
			pTouch = (CCTouch *)(*setIter);
			_touches->removeObject(pTouch);
		}

		if (_touches->count() == 0) {
			_touchDistance = 0.0f;
		}
	}
}

void Game::setPosition(CCPoint  position) {
    CCPoint prevPosition = this->getPosition();
    CCNode::setPosition(position);

	if (this->getPosition().x > 0) {
		CCNode::setPosition(ccp(0, this->getPosition().y));
	}
	if (this->getPosition().y > 0) {
		CCNode::setPosition(ccp(this->getPosition().x, 0));
	}
	if (this->getPosition().x < -mapWidth + windowSize.width) {
		CCNode::setPosition(ccp(-mapWidth + windowSize.width, this->getPosition().y));
	}
	if (this->getPosition().y < -mapHeight + windowSize.height) {
		CCNode::setPosition(ccp(this->getPosition().x, -mapHeight + windowSize.height));
	}
}

void Game::setViewPointCenter(CCPoint position) {
    int x = MAX(position.x, windowSize.width/2);
    int y = MAX(position.y, windowSize.height/2);
    x = MIN(x, mapWidth - windowSize.width / 2);
    y = MIN(y, mapHeight - windowSize.height/2);
    CCPoint actualPosition = ccp(x, y);

    CCPoint centerOfView = ccp(windowSize.width/2, windowSize.height/2);
    CCPoint viewPoint = ccpSub(centerOfView, actualPosition);
    this->setPosition(viewPoint);
}

CCPoint Game::tileCoordForPosition(CCPoint position) {
    int x = position.x / _tileMap->getTileSize().width;
    int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - position.y) / _tileMap->getTileSize().height;
    return ccp(x, y);
}

void Game::setEliPosition(CCPoint position) {
    CCPoint top = this->tileCoordForPosition(ccp(position.x, position.y + 45));
    CCPoint topLeft = this->tileCoordForPosition(ccp(position.x - 10, position.y + 25));
    CCPoint topRight = this->tileCoordForPosition(ccp(position.x + 10, position.y + 25));
    CCPoint bottom = this->tileCoordForPosition(ccp(position.x, position.y - 45));
    CCPoint bottomLeft = this->tileCoordForPosition(ccp(position.x - 10, position.y - 25));
    CCPoint bottomRight = this->tileCoordForPosition(ccp(position.x + 10, position.y - 25));
    CCPoint middleLeft = this->tileCoordForPosition(ccp(position.x - 10, position.y));
    CCPoint middleRight = this->tileCoordForPosition(ccp(position.x + 10, position.y));

    int tileTop = _platform->tileGIDAt(top);
    int tileTopLeft = _platform->tileGIDAt(topLeft);
    int tileTopRight = _platform->tileGIDAt(topRight);
    int tileBottom = _platform->tileGIDAt(bottom);
    int tileBottomLeft = _platform->tileGIDAt(bottomLeft);
    int tileBottomRight = _platform->tileGIDAt(bottomRight);
    int tileMiddleLeft = _platform->tileGIDAt(middleLeft);
    int tileMiddleRight = _platform->tileGIDAt(middleRight);

    if (eli->getJumping()) {
    	CCLog("Eli is Jumping");
    }

    if (tileBottom == 1) {
    	eli->setInAir(false);
    	if (tileTopRight == 1 || tileMiddleRight == 1 || tileBottomRight == 1) {
    		eli->changeDirection();
    		return;
    	} else if (tileTopLeft == 1 || tileMiddleLeft == 1 || tileBottomRight == 1) {
    		eli->changeDirection();
    		return;
    	} else {
    		eli->setPosition(ccp(position.x, (mapHeightTiles - bottom.y + 1) * 50));
    	}
    } else if (tileTop == 1) {
    	eli->setJumping(false);
    	if (tileTopRight == 1 || tileMiddleRight == 1 || tileBottomRight == 1) {
    		eli->changeDirection();
    		return;
    	} else if (tileTopLeft == 1 || tileMiddleLeft ==1 || tileBottomRight == 1) {
    		eli->changeDirection();
    		return;
    	} else {
    		eli->setPosition(ccp(position.x, (mapHeightTiles - top.y - 2) * 50));
    	}
    } else {
    	eli->setPosition(position);
    }
    this->setViewPointCenter(eli->getPosition());
}

void Game::switchMode() {
	_running = !_running;
}

void Game::onEnter() {
    CCLayer::onEnter();
    CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(this, 0, false);
}

void Game::onExit() {
    CCDirector::sharedDirector()->getScheduler()->unscheduleUpdateForTarget(this);
    CCLayer::onExit();
}
