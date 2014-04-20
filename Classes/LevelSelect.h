#ifndef __LevelSelect_H__
#define __LevelSelect_H__

#include "cocos2d.h"
#include "AppDelegate.h"

using namespace cocos2d;

class LevelSelect : public cocos2d::CCLayer {
	cocos2d::CCSize windowSize;
	int _levelsUnlocked;

public:
	static CCScene* scene();
	virtual void mainMenu();
	virtual void level1();
	virtual void level2();
	virtual void level3();
	virtual void level4();
	virtual void level5();
	virtual void level6();
	virtual void level7();
	virtual void level8();
	virtual void level9();
	virtual void level10();
	virtual bool init();
	CREATE_FUNC(LevelSelect);
};

#endif

