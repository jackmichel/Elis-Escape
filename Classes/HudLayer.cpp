#include "HudLayer.h"
#include "Utils.h"
#include "MainMenu.h"
#include "Tool.h"
#include "Constants.h"
#include "Game.h"
#include "LevelSelect.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

bool HudLayer::init() {
    if (CCLayer::init()) {
        CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
        _movingTool = -1;
        _toolLabels = CCArray::createWithCapacity(5);
        _toolLabels->retain();
        _touches = CCArray::createWithCapacity(10);
        _touches->retain();

        _numBridges = 0;
        _numSprings = 0;
        _numPoles = 0;
        _numCatapults = 0;
        _numFans = 0;

        sprintf(_bridges,"x %i",_numBridges);
        _bridgeLabel = CCLabelTTF::create(_bridges,"Arial",20);
        _bridgeLabel->setColor(ccc3(0,0,0));
        _bridgeLabel->setPosition(ccp(windowSize.width - ((windowSize.width / 6) / 2),510));

        sprintf(_springs,"x %i",_numSprings);
        _springLabel = CCLabelTTF::create(_springs,"Arial",20);
        _springLabel->setColor(ccc3(0,0,0));
        _springLabel->setPosition(ccp(windowSize.width - ((windowSize.width / 6) / 2),360));

        sprintf(_poles,"x %i",_numPoles);
        _poleLabel = CCLabelTTF::create(_poles,"Arial",20);
        _poleLabel->setColor(ccc3(0,0,0));
        _poleLabel->setPosition(ccp(windowSize.width - ((windowSize.width / 6) / 2),135));

        sprintf(_catapults,"x %i",_numCatapults);
        _catapultLabel = CCLabelTTF::create(_catapults,"Arial",20);
        _catapultLabel->setPosition(ccp(windowSize.width - ((windowSize.width / 6) / 2),0));

        sprintf(_fans,"x %i",_numFans);
        _fanLabel = CCLabelTTF::create(_fans,"Arial",20);
        _fanLabel->setPosition(ccp(windowSize.width - ((windowSize.width / 6) / 2),0));

        // Create toolbar background
        CCSprite * toolbarBG = CCSprite::create("toolbar.png");
        toolbarBG->setPosition(ccp(windowSize.width - ((windowSize.width / 6) / 2), windowSize.height / 2));
        this->_toolbarBG = toolbarBG;

        //Level complete modal
    	CCSprite * modal = CCSprite::create("won_game.png");
        modal->setPosition(ccp(windowSize.width / 2, windowSize.height / 2));
        this->_modal = modal;
        _modal->setVisible(false);

        // level 10 complete modal
    	CCSprite * endModal = CCSprite::create("won_level10.png");
        endModal->setPosition(ccp(windowSize.width / 2, windowSize.height / 2));
        this->_endModal = endModal;
        _endModal->setVisible(false);

        // Create button to switch to run mode
        CCMenuItemImage *runMode = CCMenuItemImage::create("run_mode.png", "run_mode.png", this, menu_selector(HudLayer::switchMode));
        this->_runMode = runMode;

        // Create button to switch to edit mode
        CCMenuItemImage *editMode = CCMenuItemImage::create("edit_mode.png", "edit_mode.png", this, menu_selector(HudLayer::switchMode));
        editMode->setPosition(ccp((windowSize.width / 6), 0));
        this->_editMode = editMode;
        _editMode->setVisible(false);

        // Create menu for mode switching
        CCMenu *modeMenu = CCMenu::create(_runMode, _editMode, NULL);
        modeMenu->setPosition(ccp(windowSize.width - (runMode->getContentSize().width / 2) - (windowSize.width / 6), windowSize.height  - (runMode->getContentSize().height / 2)));
        this->_modeMenu = modeMenu;

        //Create button for returning to main menu
        CCMenuItemImage *mainMenuButton = CCMenuItemImage::create("MainMenuBtn.png", "MainMenuBtn.png", this, menu_selector(HudLayer::mainMenu));
        CCMenu *returnMenu = CCMenu::create(mainMenuButton, NULL);
        returnMenu->setPosition(ccp(windowSize.width - (windowSize.width / 12), windowSize.height * .08));
        this->_returnMenu = returnMenu;

        //Create modal menu - on win screen
        CCMenuItemImage *modalMenuButton = CCMenuItemImage::create("MainMenuBtn.png", "MainMenuBtn.png", this, menu_selector(HudLayer::mainMenu));
        CCMenu *modalMenu = CCMenu::create(modalMenuButton, NULL);
        modalMenu->setPosition(ccp(windowSize.width * .35, windowSize.height * .35));
        this->_modalMenu = modalMenu;
        _modalMenu->setVisible(false);


        //Create modal continue button - on win screen
        CCMenuItemImage *modalContButton = CCMenuItemImage::create("ContinueBtn.png", "ContinueBtn.png", this, menu_selector(HudLayer::nextLevel));
        CCMenu *contButton = CCMenu::create(modalContButton, NULL);
        contButton->setPosition(ccp(windowSize.width / 2, windowSize.height * .47));
        this->_modalCont = contButton;
        _modalCont->setVisible(false);

        //create modal replay button - on win screen
        CCMenuItemImage *modalReplay = CCMenuItemImage::create("ReplayBtn.png", "ReplayBtn.png", this, menu_selector(HudLayer::replay));
        CCMenu *modalReplayButton = CCMenu::create(modalReplay, NULL);
        modalReplayButton->setPosition(ccp(windowSize.width * .65, windowSize.height * .35));
        this->_modalReplay = modalReplayButton;
        _modalReplay->setVisible(false);

        // Ouch! ~~ when eli hits spikes
        CCSprite * ouch = CCSprite::create("ouch.png");
        ouch->setPosition(ccp(windowSize.width / 2, windowSize.height / 2));
        this->_ouch = ouch;
        _ouch->setVisible(false);
        this->addChild(_ouch);


        // Add items associated with toolbar
        this->addChild(_modeMenu);
        this->addChild(_toolbarBG);
        this->addChild(_returnMenu);

        // Add items associated with level complete modal
        this->addChild(_modal);
        this->addChild(_endModal);
        this->addChild(_modalMenu);
        this->addChild(_modalCont);
        this->addChild(_modalReplay);

        this->setTouchEnabled(true);
    }

    return true;
}

void HudLayer::switchMode() {
	if (Utils::gameLayer()->getState() == kRunMode) {
		_toolbarBG->setVisible(true);
		_runMode->setVisible(true);
		_editMode->setVisible(false);
		_returnMenu->setVisible(true);
		this->showTools();
	} else if (Utils::gameLayer()->getState() == kEditMode) {
		_toolbarBG->setVisible(false);
		_runMode->setVisible(false);
		_editMode->setVisible(true);
		_returnMenu->setVisible(false);
		this->hideTools();
	}
	Utils::gameLayer()->switchMode();
}

void HudLayer::levelComplete(int toolsLeft, bool gotGear, int level) {
	_modalMenu->setVisible(true);
	_editMode->setVisible(false);
	if (level < 10) {
		_modalCont->setVisible(true);
		_modal->setVisible(true);
	} else {
		_endModal->setVisible(true);
	}
	_modalReplay->setVisible(true);

	const char * levelKey = Utils::getLevelKey(level);
	int previousGears = CCUserDefault::sharedUserDefault()->getIntegerForKey(levelKey);

	int width = CCDirector::sharedDirector()->getWinSize().width;
	CCSprite *gears;
	if (toolsLeft > 0 && gotGear) {
		gears = CCSprite::create("gold.png");
		if (3 > previousGears) {
			CCUserDefault::sharedUserDefault()->setIntegerForKey(levelKey, 3);
			CCUserDefault::sharedUserDefault()->flush();
		}
	} else if (toolsLeft > 0 || gotGear) {
		gears = CCSprite::create("silver.png");
		if (2 > previousGears) {
			CCUserDefault::sharedUserDefault()->setIntegerForKey(levelKey, 2);
			CCUserDefault::sharedUserDefault()->flush();
		}
	} else {
		gears = CCSprite::create("bronze.png");
		if (1 > previousGears) {
			CCUserDefault::sharedUserDefault()->setIntegerForKey(levelKey, 1);
			CCUserDefault::sharedUserDefault()->flush();
		}
	}
	gears->setPosition(ccp(width / 2, 150));
	this->addChild(gears);
}

void HudLayer::mainMenu() {
    if(SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying()) {
        SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    }
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5,MainMenu::scene()));
}

void HudLayer::levelSelect() {
    if(SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying()) {
        SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    }
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5,LevelSelect::scene()));
}

void HudLayer::listTools(CCArray * tools) {
	_tools = tools;
	_tools->retain();
	int width = CCDirector::sharedDirector()->getWinSize().width;
	int toolX = width - ((width / 6) / 2);
	int toolY;
    for (int i = 0; i < tools->count(); i++) {
		Tool *tool = (Tool *) tools->objectAtIndex(i);
		if (tool->getType() == "Bridge") {
			toolY = 550;
			tool->setScale(0.5f);
			_numBridges++;
		} else if (tool->getType() == "Spring") {
			toolY = 400;
			_numSprings++;
		} else if (tool->getType() == "Pole") {
			toolY = 220;
			_numPoles++;
		} else if (tool->getType() == "Catapult") {
			toolY = 0;
			_numCatapults++;
		} else if (tool->getType() == "Fan") {
			toolY = 0;
			_numFans++;
		}
		tool->setPosition(ccp(toolX,toolY));
		this->addChild(tool, 11);
	}
    if (_numBridges > 0) {
		sprintf(_bridges,"x %i",_numBridges);
		_bridgeLabel->setString(_bridges);
		this->addChild(_bridgeLabel);
		_toolLabels->addObject(_bridgeLabel);
    }
    if (_numSprings > 0) {
		sprintf(_springs,"x %i",_numSprings);
		_springLabel->setString(_springs);
		this->addChild(_springLabel);
		_toolLabels->addObject(_springLabel);
    }
    if (_numPoles > 0) {
		sprintf(_poles,"x %i",_numPoles);
		_poleLabel->setString(_poles);
		this->addChild(_poleLabel);
		_toolLabels->addObject(_poleLabel);
    }
    if (_numCatapults > 0) {
		sprintf(_catapults,"x %i",_numCatapults);
		_catapultLabel->setString(_catapults);
		this->addChild(_catapultLabel);
		_toolLabels->addObject(_catapultLabel);
    }
    if (_numFans > 0) {
		sprintf(_fans,"x %i",_numFans);
		_fanLabel->setString(_fans);
		this->addChild(_fanLabel);
		_toolLabels->addObject(_fanLabel);
    }
}

void HudLayer::hideTools() {
    for (int i = 0; i < _tools->count(); i++) {
		Tool *tool = (Tool *) _tools->objectAtIndex(i);
		this->removeChild(tool);
	}
    for (int i = 0; i < _toolLabels->count(); i++) {
    	CCLabelTTF * label = (CCLabelTTF *) _toolLabels->objectAtIndex(i);
    	label->setVisible(false);
    }
}

void HudLayer::showTools() {
    for (int i = 0; i < _tools->count(); i++) {
		Tool *tool = (Tool *) _tools->objectAtIndex(i);
		this->addChild(tool);
	}
    for (int i = 0; i < _toolLabels->count(); i++) {
    	CCLabelTTF * label = (CCLabelTTF *) _toolLabels->objectAtIndex(i);
    	label->setVisible(true);
    }
}

void HudLayer::showOuch() {
	_ouch->setVisible(true);
}

void HudLayer::hideOuch() {
	_ouch->setVisible(false);
}

void HudLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent) {
	if (Utils::gameLayer()->getState() == kEditMode) {
	    CCTouch *pTouch;
	    CCSetIterator setIter;
	    for (setIter = pTouches->begin(); setIter != pTouches->end(); ++setIter) {
	        pTouch = (CCTouch *)(*setIter);
	        _touches->addObject(pTouch);
	    }
	    pTouch = (CCTouch *) _touches->objectAtIndex(0);
		CCPoint location = pTouch->getLocation();

		for (int i = 0; i < _tools->count(); i++) {
			Tool *tool = (Tool *) _tools->objectAtIndex(i);
			if (tool->touchingTool(location)) {
				_movingTool = i;
				Utils::gameLayer()->setShouldPan(false);
			}
		}
	}
}

void HudLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent) {
	if (Utils::gameLayer()->getState() == kEditMode) {
		if (_movingTool >= 0) {
			CCTouch *touch = (CCTouch*)_touches->objectAtIndex(0);
			CCPoint curTouchPosition = CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());
			CCPoint screenLocation = this->getPosition();
			int gridX = (int) Utils::gameLayer()->getPosition().x % 50;
			int gridY = (int) Utils::gameLayer()->getPosition().y % 50;
			CCPoint newItemLocation = ccp(curTouchPosition.x - screenLocation.x, curTouchPosition.y - screenLocation.y);
			Tool *tool = (Tool *) _tools->objectAtIndex(_movingTool);
			tool->setScale(1.0f);
			tool->setGridPosition(newItemLocation, gridX, gridY);
		}
	}
}

void HudLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent) {
	if (Utils::gameLayer()->getState() == kEditMode) {
		if (_movingTool >= 0) {
			Tool *tool = (Tool *) _tools->objectAtIndex(_movingTool);
			CCPoint location = tool->getPosition();
			subtractTool(tool->getType());
			this->removeChild(tool);
			Utils::gameLayer()->placeTool(_movingTool, location);
			_movingTool = -1;
		}

		CCTouch *pTouch;
		CCSetIterator setIter;
		for (setIter = pTouches->begin(); setIter != pTouches->end(); ++setIter) {
			pTouch = (CCTouch *)(*setIter);
			_touches->removeObject(pTouch);
		}

		Utils::gameLayer()->setShouldPan(true);
	}
}

void HudLayer::subtractTool(const char * type) {
	if (type == "Bridge") {
		_numBridges--;
		sprintf(_bridges,"x %i",_numBridges);
		_bridgeLabel->setString(_bridges);
	} else if (type == "Spring") {
		_numSprings--;
		sprintf(_springs,"x %i",_numSprings);
		_springLabel->setString(_springs);
	} else if (type == "Pole") {
		_numPoles--;
		sprintf(_poles,"x %i",_numPoles);
		_poleLabel->setString(_poles);
	} else if (type == "Fan") {
		_numFans--;
		sprintf(_fans,"x %i",_numFans);
		_fanLabel->setString(_fans);
	} else if (type == "Catapult") {
		_numCatapults--;
		sprintf(_catapults,"x %i",_numCatapults);
		_catapultLabel->setString(_catapults);
	}
}

void HudLayer::addTool() {
	Tool *tool = (Tool *) _tools->objectAtIndex(_tools->count() - 1);
	int width = CCDirector::sharedDirector()->getWinSize().width;
	int toolX = width - ((width / 6) / 2);
	int toolY;
	if (tool->getType() == "Bridge") {
		toolY = 550;
		tool->setScale(0.5f);
		_numBridges++;
		sprintf(_bridges,"x %i",_numBridges);
		_bridgeLabel->setString(_bridges);
	} else if (tool->getType() == "Spring") {
		toolY = 400;
		_numSprings++;
		sprintf(_springs,"x %i",_numSprings);
		_springLabel->setString(_springs);
	} else if (tool->getType() == "Pole") {
		toolY = 220;
		_numPoles++;
		sprintf(_poles,"x %i",_numPoles);
		_poleLabel->setString(_poles);
	} else if (tool->getType() == "Catapult") {
		toolY = 0;
		_numCatapults++;
		sprintf(_catapults,"x %i",_numCatapults);
		_catapultLabel->setString(_catapults);
	} else if (tool->getType() == "Fan") {
		toolY = 0;
		_numFans++;
		sprintf(_fans,"x %i",_numFans);
		_fanLabel->setString(_fans);
	}
	tool->setPosition(ccp(toolX,toolY));
	this->addChild(tool, 11);
}

void HudLayer::nextLevel() {
	Utils::gameLayer()->nextLevel();
}

void HudLayer::replay() {
	Utils::gameLayer()->replay();
}
