#ifndef __About_H__
#define __About_H__

#include "cocos2d.h"
#include "AppDelegate.h"

using namespace cocos2d;

class About : public cocos2d::CCLayer {
	cocos2d::CCSize windowSize;

public:
	static cocos2d::CCScene* scene();
	virtual bool init();
	CREATE_FUNC(About);
};

#endif
