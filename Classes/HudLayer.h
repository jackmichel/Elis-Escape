#ifndef __HUDLAYER_H__
#define __HUDLAYER_H__

#include "cocos2d.h"

using namespace cocos2d;

class HudLayer : public cocos2d::CCLayer
{
private:
	CCSize windowSize;
	CCMenuItemImage *_runMode;
	CCMenuItemImage *_editMode;
    CCSprite *_toolbarBG;
    CCSprite *_modal;
    CCMenu *_modeMenu;
    CCMenu *_returnMenu;
    CCMenu *_modalMenu;
    CCLabelTTF *_niceJob;
    CCArray * _tools;
    int _movingTool;

public:
    virtual bool init();
    static CCScene* scene();
    void switchMode();
    void levelComplete();
    void mainMenu();
    void listTools(CCArray * tools);
    void hideTools();
    void showTools();
    void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	void ccTouchesEnded(CCSet *pTouches, CCEvent *event);
    CC_SYNTHESIZE(CCArray*, _touches, touches);
    CREATE_FUNC(HudLayer);
};

#endif // __HUDLAYER_H__
