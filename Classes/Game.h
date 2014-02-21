#ifndef __Game_H__
#define __Game_H__

#include "cocos2d.h"
#include "AppDelegate.h"
#include "CCLayerPanZoom.h"

using namespace cocos2d;

class Game : public CCLayerPanZoom {
	cocos2d::CCSize windowSize;

private:
	CCTMXTiledMap *_tileMap;
    CCSprite *eli;

public:
	static cocos2d::CCScene* scene();
	void setViewPointCenter(CCPoint position);
	virtual bool init();
	CREATE_FUNC(Game);
};

#endif
