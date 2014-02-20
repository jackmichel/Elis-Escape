#ifndef __Game_H__
#define __Game_H__

#include "cocos2d.h"
#include "AppDelegate.h"

using namespace cocos2d;

class Game : public cocos2d::CCLayer {
	cocos2d::CCSize windowSize;

private:
	CCTMXTiledMap *_tileMap;
    CCSprite *eli;

public:
	static cocos2d::CCScene* scene();
	void ccTouchesEnded(CCSet *pTouches, CCEvent *event);
	void setViewPointCenter(CCPoint position);
	virtual bool init();
	CREATE_FUNC(Game);
};

#endif
