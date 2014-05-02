#include "Game.h"
#include "MainMenu.h"
#include "Constants.h"
#include "Utils.h"
#include "Eli.h"
#include "Tool.h"
#include "Bridge.h"
#include "SimpleAudioEngine.h"
#include "LevelSelect.h"

using namespace cocos2d;
using namespace CocosDenshion;

//Create an area for the Game and Hud to exist, loads corresponding level user selected
CCScene* Game::scene(int level) {
    CCScene *sc = CCScene::create();
    sc->setTag(TAG_GAME_SCENE);
    Game *g = new Game();
    g->_level = level;
    g->_availableTools = Utils::getLevelTools(level);
    g->_tools = CCArray::createWithCapacity(g->_availableTools->count());
    g->init();
    sc->addChild(g, 0, TAG_GAME_LAYER);

    HudLayer *hud = HudLayer::create();
    sc->addChild(hud, 11);
    hud->listTools(g->_availableTools);
    g->_hud = hud;

    return sc;
}

bool Game::init() {
	if ( !CCLayer::init() ) {
		return false;
	}

	//Sets the visible area
	windowSize = CCDirector::sharedDirector()->getWinSize();
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    _musicToggle = CCUserDefault::sharedUserDefault()->getIntegerForKey("music");
    _soundfxToggle = CCUserDefault::sharedUserDefault()->getIntegerForKey("soundfx");

    //Play Background Music
    if(_musicToggle == 0) {
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Audio/Music/BasementTheme.mp3", true);
		SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.1f);
    }

    // create a Tiled TMX map
    _tileMap = new CCTMXTiledMap();
    _tileMap->initWithTMXFile(Utils::getLevelMap(_level));
    _platform = _tileMap->layerNamed("Platform");
    _spikes = _tileMap->layerNamed("Spikes");
    this->addChild(_tileMap, 0);

    // Important inits
    eliWidth = 10;
	eliHeight = 46;
    tileHeight = _tileMap->getTileSize().height;
    tileWidth = _tileMap->getTileSize().width;
    mapHeightTiles = _tileMap->getMapSize().height;
    mapWidthTiles = _tileMap->getMapSize().width;
    mapHeight = mapHeightTiles * tileHeight;
    mapWidth = mapWidthTiles * tileWidth;
    _touches = CCArray::createWithCapacity(10);
    _touches->retain();
    _availableTools->retain();
    _tools->retain();
    _maxTouchDistanceToClick = 315.0f;
    _shouldPan = true;

    //Create array of all platform tiles in map
    _tiles = CCArray::createWithCapacity(mapHeightTiles * mapWidthTiles);
    _tiles->retain();
    //Loop through map rows
    for (int i = 0; i < mapHeightTiles; i++) {
    	//Loop through map columns
    	for (int j = 0; j < mapWidthTiles; j++) {
    		//Check if this is a platform at this coordinate
    		if (_platform->tileGIDAt(ccp(j,i)) > 0) {
    			//It is a platform so add it to the array
    			CCSprite *tile = _platform->tileAt(ccp(j,i));
    			_tiles->addObject(tile);
    		}
    	}
    }

    //Create array of all spike tiles in map
    _spiketiles = CCArray::createWithCapacity(mapHeightTiles * mapWidthTiles);
    _spiketiles->retain();
    for (int i = 0; i < mapHeightTiles; i++) {
    	for (int j = 0; j < mapWidthTiles; j++) {
    		if (_spikes->tileGIDAt(ccp(j,i)) > 0) {
    			CCSprite *tile = _spikes->tileAt(ccp(j,i));
    			_spiketiles->addObject(tile);
    		}
    	}
    }

    _movingTool = -1;

    // Listen for touches
    this->setTouchEnabled(true);

    // This variable is a flag for whether or not the main game loop should fire
    _state = kEditMode;

    // Initialize game loop
    this->schedule(schedule_selector(Game::gameLoop));

    // Reference to the objects in tilemap
    CCTMXObjectGroup *objectGroup = _tileMap->objectGroupNamed("Objects");
    CCDictionary *spawnPoint = objectGroup->objectNamed("SpawnPoint");
    CCDictionary *exitPoint = objectGroup->objectNamed("Exit");
    CCDictionary *gearPoint = objectGroup->objectNamed("Gear");

    int x = ((CCString)*spawnPoint->valueForKey("x")).intValue();
    int y = ((CCString)*spawnPoint->valueForKey("y")).intValue();

    eli = Eli::create();
    eli->setPosition(ccp(x,y));
    eli->setReverseDirection(Utils::reverseEliDirection(_level));
    eli->reset();

    // Create and position gear
    _hasGear = false;
    gear = CCSprite::create("in_level_gear.png");
    gearX = ((CCString)*gearPoint->valueForKey("x")).intValue();
    gearY = ((CCString)*gearPoint->valueForKey("y")).intValue();
    gear->setPosition(ccp(gearX, gearY));

    // Create and position exit
    CCSprite *exit = CCSprite::create("exit.png");
    exitX = ((CCString)*exitPoint->valueForKey("x")).intValue();
    exitY = ((CCString)*exitPoint->valueForKey("y")).intValue();
    exit->setPosition(ccp(exitX,exitY));

    this->addChild(exit);
    this->addChild(gear);
    this->addChild(eli, 10);
    this->setViewPointCenter(eli->getPosition());
    eli->idleAnimation();

	return true;
}

void Game::gameLoop(float dt) {
	if (_state != kRunMode) { return; }
	eli->update(dt);
	this->setEliPosition(eli->getNextPosition());
	this->checkSpikes();
	this->checkGear();
	this->checkExit();
}

void Game::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent) {
	if (_state == kEditMode && _shouldPan) {
	    CCTouch *pTouch;
	    CCSetIterator setIter;
	    for (setIter = pTouches->begin(); setIter != pTouches->end(); ++setIter) {
	        pTouch = (CCTouch *)(*setIter);
	        _touches->addObject(pTouch);
	    }

	    if (_touches->count() == 1) {
	    	// Check if we are touching a Tool
	    	pTouch = (CCTouch *) _touches->objectAtIndex(0);
	    	CCPoint location = pTouch->getLocation();
	    	CCPoint screenLocation = this->getPosition();
	    	// account for position in tilemap
	    	location = ccp(location.x - screenLocation.x, location.y - screenLocation.y);

	    	for (int i = 0; i < _tools->count(); i++) {
	    		Tool *tool = (Tool *) _tools->objectAtIndex(i);
	    		if (tool->touchingTool(location)) {
	    			_movingTool = i;
	    		}
	    	}

	        _touchMoveBegan = false;
	        time_t seconds;

	        seconds = time (NULL);
	        _singleTouchTimestamp = seconds/60;
	    } else {
	    	 _singleTouchTimestamp = INFINITY;
	    }
	} else if (_state == kRunMode) {
		CCTouch *touch = (CCTouch *)pTouches->anyObject();
		if (touch) {
			eli->jump();
		}
	}
}

void Game::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent) {
	if (_state == kEditMode && _shouldPan) {
		if (_movingTool >= 0) {
			CCTouch *touch = (CCTouch*)_touches->objectAtIndex(0);
			CCPoint curTouchPosition = CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());
			CCPoint screenLocation = this->getPosition();
			CCPoint newItemLocation = ccp(curTouchPosition.x - screenLocation.x, curTouchPosition.y - screenLocation.y);
			Tool *tool = (Tool *) _tools->objectAtIndex(_movingTool);
			tool->setGridPosition(newItemLocation, 0, 0);
		} else {
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
}

void Game::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent) {
	if (_state == kEditMode && _shouldPan) {
		_singleTouchTimestamp = INFINITY;

		if (_movingTool >= 0) {
			Tool *tool = (Tool *) _tools->objectAtIndex(_movingTool);
			CCPoint location = tool->getPosition();
			if (location.x + this->getPosition().x >= windowSize.width - (windowSize.width / 6)) {
				returnTool(_movingTool, tool);
			}
			_movingTool = -1;
		}

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
	if (this->getPosition().x < windowSize.width - mapWidth - (windowSize.width / 6)) {
		CCNode::setPosition(ccp(windowSize.width - mapWidth - (windowSize.width / 6), this->getPosition().y));
	}
	if (this->getPosition().y < windowSize.height - mapHeight) {
		CCNode::setPosition(ccp(this->getPosition().x, windowSize.height - mapHeight));
	}
}

void Game::setViewPointCenter(CCPoint position) {
	int x;
	int y = MAX(position.y, windowSize.height/2);
	y = MIN(y, mapHeight - windowSize.height/2);

	if (_state == kEditMode) {
		x = MAX(position.x, windowSize.width/2 - (windowSize.width / 6));
		x = MIN(x, mapWidth + (windowSize.width / 6) - windowSize.width / 2);
	} else {
	    x = MAX(position.x, windowSize.width/2);
	    x = MIN(x, mapWidth - windowSize.width / 2);
	}

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
	// Eli's current x and y
	int currentX = eli->getPosition().x;
	int currentY = eli->getPosition().y;

	// Desired x and y
	int newX = position.x;
	int newY = position.y;

	for (int i = 0; i < _tiles->count(); i++) {
		// Get the current tile and compute its bounds
		CCSprite *tile = (CCSprite *) _tiles->objectAtIndex(i);
		CCPoint location = tile->getPosition();
		int left = location.x - 2; // subtract and add a few pixels to left and right so that there is absolutely no void between tiles
		int right = location.x + tileWidth + 2;
		int bottom = location.y;
		int top = location.y + tileHeight;

		if (position.x + eliWidth > left && position.x - eliWidth < right) {
			if (currentY >= top + eliHeight && position.y < top + eliHeight) {
				newY = top + eliHeight;
				if (eli->numberOfRunningActions() == 0) {
					eli->startRunAnimation();
				}
				eli->setInAir(false);
				eli->setState(kPlayerMoving);
				break;
			}
			if (currentY <= bottom - eliHeight && position.y > bottom - eliHeight) {
				newY = bottom - eliHeight;
				eli->setJumping(false);
				break;
			}
		}
	}

	for (int i = 0; i < _tiles->count(); i++) {
		// Get the current tile and compute its bounds
		CCSprite *tile = (CCSprite *) _tiles->objectAtIndex(i);
		CCPoint location = tile->getPosition();
		int left = location.x;
		int right = location.x + tileWidth;
		int bottom = location.y;
		int top = location.y + tileHeight;
		int offset = eliHeight / 2; // used to check collision with walls in both his top and bottom half

		// Because Eli is essentially the size of two tiles we need to check for collision in both his top and bottom half
		// Check for collision in lower half
		if (position.y - offset < top && position.y - offset > bottom) {
			if (currentX >= right && position.x <= right) {
				newX = right;
				eli->changeDirection();
				break;
			}
			if (currentX <= left && position.x >= left) {
				newX = left;
				eli->changeDirection();
				break;
			}
		}
		// Check for collision in upper half
		if (position.y + offset < top && position.y + offset > bottom) {
			if (currentX >= right && position.x <= right) {
				newX = right;
				eli->changeDirection();
				break;
			}
			if (currentX <= left && position.x >= left) {
				newX = left;
				eli->changeDirection();
				break;
			}
		}
	}

	// Check bridge and tool Collision
    for (int i = 0; i < _tools->count(); i++) {
		Tool *tool = (Tool *) _tools->objectAtIndex(i);
		if (tool->getType() == "Bridge") {
			int bridgeHeight = tool->getContentSize().height;
			int bridgeWidth = tool->getContentSize().width;
			int bridgeLeft = tool->getPosition().x - (bridgeWidth / 2);
			int bridgeRight = bridgeLeft + bridgeWidth;
			int bridgeBottom = tool->getPosition().y - (bridgeHeight / 2);
			int bridgeTop = bridgeBottom + 15;

			if (position.x + eliWidth >= bridgeLeft && position.x - eliWidth < bridgeRight) {
				if (currentY >= bridgeTop + eliHeight && position.y < bridgeTop + eliHeight) {
					newY = bridgeTop + eliHeight;
					if (eli->numberOfRunningActions() == 0) {
						eli->startRunAnimation();
					}
					eli->setInAir(false);
					eli->setState(kPlayerMoving);
					break;
				}
				if (currentY <= bridgeBottom - eliHeight && position.y > bridgeBottom - eliHeight) {
					newY = bridgeBottom - eliHeight;
					eli->setJumping(false);
					break;
				}
			}
		} else {
			tool->checkCollision(eli);
		}
	}

	eli->setPosition(ccp(newX, newY));
	this->setViewPointCenter(ccp(newX, newY));
}

void Game::switchMode() {
	if (_state == kEditMode) {
		_state = kRunMode;
		eli->startRunAnimation();
	} else if (_state == kRunMode) {
		_state = kEditMode;
		this->resetEli();
		eli->idleAnimation();
	}
}

void Game::checkExit() {
	CCRect box = eli->boundingBox();
	if (box.containsPoint(ccp(exitX,exitY))) {
		_state = kLevelComplete;
		eli->stopAllActions();
		eli->setVisible(false);

	    if(SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying()) {
	        SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	    }

		if (_soundfxToggle == 0) {
			if (_level < 10) {
				SimpleAudioEngine::sharedEngine()->playEffect("Audio/Sound Effects/tada.wav", false);
			} else {
				SimpleAudioEngine::sharedEngine()->playEffect("Audio/Sound Effects/cheers.wav", false);
			}

		}

		_hud->levelComplete(_availableTools->count(), _hasGear, _level);
		int levelsUnlocked = CCUserDefault::sharedUserDefault()->getIntegerForKey("levelsUnlocked");
		if (_level + 1 > levelsUnlocked) {
			CCUserDefault::sharedUserDefault()->setIntegerForKey("levelsUnlocked", _level + 1);
			CCUserDefault::sharedUserDefault()->flush();
		}
	}
}

void Game::checkGear() {
	CCRect box = eli->boundingBox();
	if (!_hasGear && box.containsPoint(ccp(gearX,gearY))) {
		gear->setVisible(false);
		_hasGear = true;
		if (_soundfxToggle == 0) {
			SimpleAudioEngine::sharedEngine()->playEffect("Audio/Sound Effects/powerUp.wav", false);
		}
	}
}

void Game::checkSpikes() {
	CCRect box = eli->boundingBox();
	for (int i = 0; i < _spiketiles->count(); i++) {
		CCSprite *tile = (CCSprite *) _spiketiles->objectAtIndex(i);
		CCPoint location = tile->getPosition();
		if (box.containsPoint(ccp(location.x + (tileWidth / 2), location.y + (tileHeight / 2)))) {
			_state = kEliHitSpike;
			if (_soundfxToggle == 0) {
				SimpleAudioEngine::sharedEngine()->playEffect("Audio/Sound Effects/clang.wav", false);
			}
			_hud->showOuch();
			eli->stopAllActions();
			CCCallFunc* moveCallback = CCCallFunc::create(this, callfunc_selector(Game::eliHitSpikes));
			CCDelayTime* delayAction = CCDelayTime::create(0.5f);
			this->runAction(CCSequence::create(delayAction, moveCallback, NULL));
		}
	}
}

void Game::eliHitSpikes() {
	_state = kRunMode;
	_hud->hideOuch();
	this->resetEli();
	// this->setViewPointCenter(eli->getPosition());
}

void Game::resetEli() {
	if (_hasGear) {
		gear->setVisible(true);
		_hasGear = false;
	}
	CCTMXObjectGroup *objectGroup = _tileMap->objectGroupNamed("Objects");
    CCDictionary *spawnPoint = objectGroup->objectNamed("SpawnPoint");
    int x = ((CCString)*spawnPoint->valueForKey("x")).intValue();
    int y = ((CCString)*spawnPoint->valueForKey("y")).intValue();
    eli->setPosition(ccp(x,y));
    eli->reset();
}

void Game::placeTool(int i, CCPoint location) {
	CCPoint screenLocation = this->getPosition();
	// account for position in tilemap
	location = ccp(location.x - screenLocation.x, location.y - screenLocation.y);
	Tool *tool = (Tool *) _availableTools->objectAtIndex(i);
	_availableTools->removeObjectAtIndex(i, false);
	_tools->addObject(tool);
	tool->setPosition(location);
	this->addChild(tool, 11);
	checkToolsOnScreen();
}

void Game::checkToolsOnScreen() {
    for (int i = 0; i < _tools->count(); i++) {
		Tool *tool = (Tool *) _tools->objectAtIndex(i);
		CCPoint location = tool->getPosition();
		if (location.x > mapWidth) {
			returnTool(i, tool);
		}
    }
}

void Game::returnTool(int i, Tool * tool) {
	_availableTools->addObject(tool);
	_tools->removeObjectAtIndex(i, false);
	_hud->addTool();
	this->removeChild(tool);
}

void Game::nextLevel() {
	if (_level != 10) {
	    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5,Game::scene(_level + 1)));
	}
}

void Game::replay() {
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5,Game::scene(_level)));
}

void Game::onEnter() {
    CCLayer::onEnter();
    CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(this, 0, false);
}

void Game::onExit() {
    CCDirector::sharedDirector()->getScheduler()->unscheduleUpdateForTarget(this);
    CCLayer::onExit();
}
