#ifndef __LevelSelect_H__
#define __LevelSelect_H__

#include "cocos2d.h"
#include "AppDelegate.h"

using namespace cocos2d;

class LevelSelect : public cocos2d::CCLayer {
	cocos2d::CCSize windowSize;

public:
	static CCScene* scene();
	virtual void mainMenu();
	virtual void level1();
	virtual void level2();
	virtual bool init();
	CREATE_FUNC(LevelSelect);
};

#endif

