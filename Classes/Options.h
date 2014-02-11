#ifndef __Options_H__
#define __Options_H__

#include "cocos2d.h"
#include "AppDelegate.h"

using namespace cocos2d;

class Options : public cocos2d::CCLayer {
	cocos2d::CCSize windowSize;

public:
	static cocos2d::CCScene* scene();
	virtual bool init();
	CREATE_FUNC(Options);
};

#endif

