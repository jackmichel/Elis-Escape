#ifndef __MAINMENU_H__
#define __MAINMENU_H__

#include "cocos2d.h"

using namespace cocos2d;

class MainMenu : public cocos2d::CCLayer {
	cocos2d::CCSize windowSize;

public:
    virtual bool init();
    virtual void levelSelect();
    virtual void options();
    virtual void about();
    static void mainMenu();
    static CCScene* scene();
    CREATE_FUNC(MainMenu);
};

#endif
