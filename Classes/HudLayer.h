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
    CCMenu *_modeMenu;

public:
    virtual bool init();
    static CCScene* scene();
    void switchMode();
    CREATE_FUNC(HudLayer);
};

#endif // __HUDLAYER_H__
