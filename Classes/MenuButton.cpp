#include "MenuButton.h"
#include "Constants.h"
#include "Utils.h"

using namespace cocos2d;

bool MenuButton::initWithText(const char * text)
{
    if (!CCSprite::init()) {
        return false;
    }

}

MenuButton* MenuButton::buttonWithText(const char * text)
{
    MenuButton *btn = new MenuButton();
    btn->initWithText(text);
    btn->autorelease();
    return btn;
}
