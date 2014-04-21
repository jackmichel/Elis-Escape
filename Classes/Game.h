#ifndef __Game_H__
#define __Game_H__

#include "cocos2d.h"
#include "AppDelegate.h"
#include "HudLayer.h"
#include "Tool.h"
#include "Eli.h"

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

typedef enum
{
    kRunMode,
    kEditMode,
    kLevelComplete

} GameState;

class Game : public cocos2d::CCLayer {

private:
	CCTMXTiledMap *_tileMap;
	CCTMXLayer *_platform;
	CCTMXLayer *_spikes;
	HudLayer *_hud;
    Eli *eli;
    CCSize windowSize;
    int _level;
    CCArray * _availableTools;
    CCArray * _tools;
    int _movingTool;
    int eliWidth;
    int eliHeight;
    int tileHeight;
    int tileWidth;
    int mapWidthTiles;
    int mapHeightTiles;
    int mapWidth;
    int mapHeight;
    int exitX;
    int exitY;
    CCSprite *gear;
    int gearX;
    int gearY;
    bool _hasGear;

public:
	static cocos2d::CCScene* scene(int level);
	void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	void ccTouchesEnded(CCSet *pTouches, CCEvent *event);
	void setPosition(CCPoint  position);
	void setViewPointCenter(CCPoint position);
	void gameLoop(float dt);
	void switchMode();
	void checkExit();
	void checkGear();
	void checkSpikes();
	//void nextLevel();
	void resetEli();
	void placeTool(int i, CCPoint location);
	void returnTool(int i, Tool * tool);
	void nextLevel();
	void replay();
	void onEnter();
	void onExit();
	CCPoint tileCoordForPosition(CCPoint position);
	void setEliPosition(CCPoint position);
	virtual bool init();
	CREATE_FUNC(Game);

	CC_SYNTHESIZE(GameState, _state, State);
	CC_SYNTHESIZE(CCArray*, _touches, touches);
	CC_SYNTHESIZE(CCArray*, _tiles, tiles);
	CC_SYNTHESIZE(CCArray*, _spiketiles, spiketiles);
	CC_SYNTHESIZE(float, _touchDistance, touchDistance);
	CC_SYNTHESIZE(bool, _shouldPan, ShouldPan);
	CC_SYNTHESIZE(float, _maxTouchDistanceToClick, maxTouchDistanceToClick);
	double _singleTouchTimestamp;
	bool _touchMoveBegan;
};

#endif
