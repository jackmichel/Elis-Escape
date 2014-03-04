#include "HudLayer.h"
#include "Utils.h"
#include "MainMenu.h"

using namespace cocos2d;

bool HudLayer::init() {
    if (CCLayer::init()) {
        CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

        // Create toolbar background
        CCSprite * toolbarBG = CCSprite::create("blank.png");
        toolbarBG->setTextureRect(CCRectMake(0, 0, windowSize.width / 6, windowSize.height));
        toolbarBG->setPosition(ccp(windowSize.width - ((windowSize.width / 6) / 2), windowSize.height / 2));
        toolbarBG->setColor(ccc3(206,171,60));
        this->_toolbarBG = toolbarBG;

        // Create button to switch to run mode
        CCMenuItemImage *runMode = CCMenuItemImage::create("run_mode.png", "run_mode.png", this, menu_selector(HudLayer::switchMode));
        this->_runMode = runMode;

        // Create button to switch to edit mode
        CCMenuItemImage *editMode = CCMenuItemImage::create("edit_mode.png", "edit_mode.png", this, menu_selector(HudLayer::switchMode));
        editMode->setPosition(ccp((windowSize.width / 6), 0));
        this->_editMode = editMode;

        // Create menu for mode switching
        CCMenu *modeMenu = CCMenu::create(_runMode, _editMode, NULL);
        modeMenu->setPosition(ccp(windowSize.width - (runMode->getContentSize().width / 2) - (windowSize.width / 6), windowSize.height  - (runMode->getContentSize().height / 2)));
        this->_modeMenu = modeMenu;

        //Create button for returning to main menu
        CCMenuItemImage *mainMenuButton = CCMenuItemImage::create("in_game_main_menu.png", "in_game_main_menu.png", this, menu_selector(HudLayer::mainMenu));
        CCMenu *returnMenu = CCMenu::create(mainMenuButton, NULL);
        returnMenu->setPosition(ccp(windowSize.width - (windowSize.width / 12), windowSize.height * .08));
        this->_returnMenu = returnMenu;

        _editMode->setVisible(false);
        this->addChild(_modeMenu);
        this->addChild(_toolbarBG);
        this->addChild(returnMenu);
    }

    return true;
}

void HudLayer::switchMode() {
	if (Utils::gameLayer()->getRunning()) {
		_toolbarBG->setVisible(true);
		_runMode->setVisible(true);
		_editMode->setVisible(false);
		_returnMenu->setVisible(true);
	} else {
		_toolbarBG->setVisible(false);
		_runMode->setVisible(false);
		_editMode->setVisible(true);
		_returnMenu->setVisible(false);
	}
	Utils::gameLayer()->switchMode();
}

void HudLayer::mainMenu() {
    CCDirector::sharedDirector()->replaceScene(MainMenu::scene());
}
