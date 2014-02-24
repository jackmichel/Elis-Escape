#include "HudLayer.h"
#include "Utils.h"

using namespace cocos2d;

bool HudLayer::init() {
    if (CCLayer::init()) {
        CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

        CCMenuItemImage *modeToggle = CCMenuItemImage::create("play_button.png", "play_button_selected.png", this, menu_selector(HudLayer::switchMode));
        CCMenu *menu = CCMenu::create(modeToggle, NULL);

        menu->setPosition(ccp(windowSize.width - (modeToggle->getContentSize().width / 2), windowSize.height  - (modeToggle->getContentSize().height / 2)));
        this->addChild(menu);
    }

    return true;
}

void HudLayer::switchMode() {
	Utils::gameLayer()->switchMode();
}
