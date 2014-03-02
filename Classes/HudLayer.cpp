#include "HudLayer.h"
#include "Utils.h"

using namespace cocos2d;

bool HudLayer::init() {
    if (CCLayer::init()) {
        CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

        // Create toolbar background
        CCSprite * toolbarBG = CCSprite::create("blank.png");
        toolbarBG->setTextureRect(CCRectMake(0, 0, windowSize.width / 5, windowSize.height));
        toolbarBG->setPosition(ccp(windowSize.width - ((windowSize.width / 5) / 2), windowSize.height / 2));
        toolbarBG->setColor(ccc3(206,171,60));
        this->_toolbarBG = toolbarBG;

        // Create button to switch between game modes
        CCMenuItemImage *runMode = CCMenuItemImage::create("play_button.png", "play_button_selected.png", this, menu_selector(HudLayer::switchMode));
        this->_runMode = runMode;

        CCMenuItemImage *editMode = CCMenuItemImage::create("main_menu_button.png", "main_menu_selected.png", this, menu_selector(HudLayer::switchMode));
        editMode->setPosition(ccp((windowSize.width / 5), 0));
        this->_editMode = editMode;

        CCMenu *modeMenu = CCMenu::create(_runMode, _editMode, NULL);
        modeMenu->setPosition(ccp(windowSize.width - (runMode->getContentSize().width / 2) - (windowSize.width / 5), windowSize.height  - (runMode->getContentSize().height / 2)));
        this->_modeMenu = modeMenu;

        _editMode->setVisible(false);
        this->addChild(_modeMenu);
        this->addChild(_toolbarBG);
    }

    return true;
}

void HudLayer::switchMode() {
	if (Utils::gameLayer()->getRunning()) {
		_toolbarBG->setVisible(true);
		_runMode->setVisible(true);
		_editMode->setVisible(false);
	} else {
		_toolbarBG->setVisible(false);
		_runMode->setVisible(false);
		_editMode->setVisible(true);
	}
	Utils::gameLayer()->switchMode();
}
