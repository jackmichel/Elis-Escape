#ifndef __Game_H__
#define __Game_H__

#include "cocos2d.h"
#include "AppDelegate.h"

#define kCCLayerPanZoomMultitouchGesturesDetectionDelay 0.5

#ifndef INFINITY
#ifdef _MSC_VER
union MSVC_EVIL_FLOAT_HACK
{
    unsigned __int8 Bytes[4];
    float Value;
};
static union MSVC_EVIL_FLOAT_HACK INFINITY_HACK = {{0x00, 0x00, 0x80, 0x7F}};
#define INFINITY (INFINITY_HACK.Value)
#endif

#ifdef __GNUC__
#define INFINITY (__builtin_inf())
#endif

#ifndef INFINITY
#define INFINITY (1e1000)
#endif
#endif

using namespace cocos2d;

class Game : public cocos2d::CCLayer {

private:
	CCTMXTiledMap *_tileMap;
    CCSprite *eli;
    CCSize windowSize;
    int mapWidth;
    int mapHeight;

public:
	static cocos2d::CCScene* scene();
	void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	void ccTouchesEnded(CCSet *pTouches, CCEvent *event);
	void setPosition(CCPoint  position);
	void setViewPointCenter(CCPoint position);
	void gameLoop(float dt);
	void onEnter();
	void onExit();
	virtual bool init();
	CREATE_FUNC(Game);

	CC_SYNTHESIZE(CCArray*, _touches, touches);
	CC_SYNTHESIZE(float, _touchDistance, touchDistance);
	CC_SYNTHESIZE(float, _maxTouchDistanceToClick, maxTouchDistanceToClick);
	double _singleTouchTimestamp;
	bool _touchMoveBegan;
	bool _running;
};

#endif
