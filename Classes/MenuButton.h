#ifndef _MenuButton_h
#define _MenuButton_h

#include "cocos2d.h"

class MenuButton : public cocos2d::CCSprite
{

    public:
    bool initWithText(const char * text);
    static MenuButton* buttonWithText(const char * text);
};

#endif
