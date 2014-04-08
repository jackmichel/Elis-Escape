#include "HudLayer.h"
#include "Utils.h"
#include "MainMenu.h"
#include "Tool.h"
#include "Constants.h"
#include "Game.h"
#include "LevelSelect.h"

using namespace cocos2d;

bool HudLayer::init() {
    if (CCLayer::init()) {
        CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
        _movingTool = -1;
        _touches = CCArray::createWithCapacity(10);
        _touches->retain();

        // Create toolbar background
        CCSprite * toolbarBG = CCSprite::create("blank.png");
        toolbarBG->setTextureRect(CCRectMake(0, 0, windowSize.width / 6, windowSize.height));
        toolbarBG->setPosition(ccp(windowSize.width - ((windowSize.width / 6) / 2), windowSize.height / 2));
        toolbarBG->setColor(ccc3(206,171,60));
        this->_toolbarBG = toolbarBG;

        //Level complete modal
    	CCSprite * modal = CCSprite::create("WonGame.png");
        //modal->setTextureRect(CCRectMake(0, 0, windowSize.width / 2, windowSize.height / 2));
        modal->setPosition(ccp(windowSize.width / 2, windowSize.height / 2));
        //modal->setColor(ccc3(206,171,60));
        this->_modal = modal;
        _modal->setVisible(false);

        //level fail modal
        CCSprite * modalF = CCSprite::create("LostGame.png");
        modalF->setPosition(ccp(windowSize.width / 2, windowSize.height / 2));
        this->_modalFail = modalF;
        _modalFail->setVisible(false);


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
        CCMenuItemImage *mainMenuButton = CCMenuItemImage::create("in_game_main_menu.png", "in_game_main_menu.png", this, menu_selector(HudLayer::mainMenu));
        CCMenu *returnMenu = CCMenu::create(mainMenuButton, NULL);
        returnMenu->setPosition(ccp(windowSize.width - (windowSize.width / 12), windowSize.height * .08));
        this->_returnMenu = returnMenu;

        //Create modal menu - on win screen
        CCMenuItemImage *modalMenuButton = CCMenuItemImage::create("MainMenuBtn.png", "MainMenuBtn.png", this, menu_selector(HudLayer::mainMenu));
        CCMenu *modalMenu = CCMenu::create(modalMenuButton, NULL);
        modalMenu->setPosition(ccp(windowSize.width * .4, windowSize.height * .45));
        this->_modalMenu = modalMenu;
        _modalMenu->setVisible(false);


        //Create modal continue button - on win screen
        CCMenuItemImage *modalContButton = CCMenuItemImage::create("ContinueBtn.png", "ContinueBtn.png", this, menu_selector(HudLayer::levelSelect));
        CCMenu *contButton = CCMenu::create(modalContButton, NULL);
        contButton->setPosition(ccp(windowSize.width / 2, windowSize.height * .56));
        this->_modalCont = contButton;
        _modalCont->setVisible(false);

        //create modal replay button - on win screen
        CCMenuItemImage *modalReplay = CCMenuItemImage::create("ReplayBtn.png", "ReplayBtn.png", this, menu_selector(HudLayer::levelSelect));
        CCMenu *modalReplayButton = CCMenu::create(modalReplay, NULL);
        modalReplayButton->setPosition(ccp(windowSize.width * .6, windowSize.height * .45));
        this->_modalReplay = modalReplayButton;
        _modalReplay->setVisible(false);

        //create modal retry button - on lose screen
        CCMenuItemImage *modalRetry = CCMenuItemImage::create("RetryBtn.png", "RetryBtn.png", this, menu_selector(HudLayer::levelSelect));
        CCMenu *modalRetryButton = CCMenu::create(modalRetry, NULL);
        modalRetryButton->setPosition(ccp(windowSize.width / 2, windowSize.height * .47));
        this->_modalRetry = modalRetryButton;
        _modalRetry->setVisible(false);

        //create modal back to basement button - on lose screen
        CCMenuItemImage *modalB2B = CCMenuItemImage::create("b2bBtn.png", "b2bBtn.png", this, menu_selector(HudLayer::levelSelect));
        CCMenu *modalB2BButton = CCMenu::create(modalB2B, NULL);
        modalB2BButton->setPosition(ccp(windowSize.width * .6, windowSize.height * .35));
        this->_modalBack2Basement = modalB2BButton;
        _modalBack2Basement->setVisible(false);

        // Add items associated with toolbar
        this->addChild(_modeMenu);
        this->addChild(_toolbarBG);
        this->addChild(_returnMenu);

        // Add items associated with level complete modal
        this->addChild(_modal);
        this->addChild(_modalMenu);
        this->addChild(_modalCont);
        this->addChild(_modalReplay);

        // Add items associated with level fail modal
        this->addChild(_modalFail);
        this->addChild(_modalRetry);
        this->addChild(_modalBack2Basement);


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

void HudLayer::levelComplete() {
	_modal->setVisible(true);
	_modalMenu->setVisible(true);
	_editMode->setVisible(false);
	_modalCont->setVisible(true);
	_modalReplay->setVisible(true);
}

void HudLayer::levelFail(){
	_modalFail->setVisible(true);
	_modalRetry->setVisible(true);
	_modalMenu->setVisible(true);
	_modalBack2Basement->setVisible(true);
	_editMode->setVisible(false);


}

void HudLayer::mainMenu() {
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5,MainMenu::scene()));
}

void HudLayer::levelSelect() {
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
			toolY = 600;
			tool->setScale(0.5f);
		} else if (tool->getType() == "Spring") {
			toolY = 500;
		} else if (tool->getType() == "Pole") {
			toolY = 400;
		} else if (tool->getType() == "Catapult") {
			toolY = 300;
		} else if (tool->getType() == "Fan") {
			toolY = 200;
		}
		tool->setPosition(ccp(toolX,toolY));
		this->addChild(tool, 11);
	}
}

void HudLayer::hideTools() {
    for (int i = 0; i < _tools->count(); i++) {
		Tool *tool = (Tool *) _tools->objectAtIndex(i);
		this->removeChild(tool);
	}
}

void HudLayer::showTools() {
    for (int i = 0; i < _tools->count(); i++) {
		Tool *tool = (Tool *) _tools->objectAtIndex(i);
		this->addChild(tool);
	}
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
			CCRect box = tool->boundingBox();
			if (box.containsPoint(location)) {
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
			CCPoint newItemLocation = ccp(curTouchPosition.x - screenLocation.x, curTouchPosition.y - screenLocation.y);
			Tool *tool = (Tool *) _tools->objectAtIndex(_movingTool);
			tool->setScale(1.0f);
			tool->setPosition(newItemLocation);
		}
	}
}

void HudLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent) {
	if (Utils::gameLayer()->getState() == kEditMode) {
		if (_movingTool >= 0) {
			Tool *tool = (Tool *) _tools->objectAtIndex(_movingTool);
			CCPoint location = tool->getPosition();
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
