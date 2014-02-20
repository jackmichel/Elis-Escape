#ifndef __Game_H__
#define __Game_H__

#include "cocos2d.h"
#include "AppDelegate.h"

using namespace cocos2d;

class Game : public cocos2d::CCLayer {
	cocos2d::CCSize windowSize;
	//virtual bool ccTouchesBegan(CCSet *pTouches, CCEvent *event);
private:
	CCTMXTiledMap *_tileMap;

public:
	static cocos2d::CCScene* scene();
	virtual bool init();
	CREATE_FUNC(Game);
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *event);
	//virtual void ccTouchesMoved(CCSet* ptouches, CCEvent* event);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *event);
	virtual void setViewPointCenter(CCPoint position);
};

#endif
