#ifndef __MAINMENU_H__
#define __MAINMENU_H__

#include "cocos2d.h"

using namespace cocos2d;

class MainMenu : public cocos2d::CCLayer {
	cocos2d::CCSize windowSize;

public:
    virtual bool init();
    virtual void playGame();
    static void mainMenu();
    static CCScene* scene();
    void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    CREATE_FUNC(MainMenu);
};

#endif
