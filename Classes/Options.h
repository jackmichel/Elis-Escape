#ifndef __Options_H__
#define __Options_H__

#include "cocos2d.h"
#include "AppDelegate.h"

using namespace cocos2d;

class Options : public cocos2d::CCLayer {
	cocos2d::CCSize windowSize;
	CCMenuItemImage *musicOn;
	CCMenuItemImage *musicOff;
	CCMenuItemImage *soundfxOn;
	CCMenuItemImage *soundfxOff;

public:
	static CCScene* scene();
	virtual bool init();
	virtual void mainMenu();
	void fmusicOff();
	void fmusicOn();
	void fsoundfxOff();
	void fsoundfxOn();
	CREATE_FUNC(Options);
};

#endif

