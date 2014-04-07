#ifndef elisescape_Utils_h
#define elisescape_Utils_h

#include "cocos2d.h"
#include "Game.h"

using namespace cocos2d;

class Utils
{
public:
    static Game* gameLayer();
    static cocos2d::CCLayer* layerWithTag(int tag);
    static cocos2d::CCSize s();
    static cocos2d::CCAnimate* getAnimationWithFrames(int from, int to);
    static void scaleSprite(cocos2d::CCSprite * sprite);
    static float getScale();
    static void setScale(float s);
    static float getArtScaleFactor();
    static void setArtScaleFactor(int s);
    static const char * getLevelMap(int levelNum);
    static CCArray * getLevelTools(int levelNum);
    static bool reverseEliDirection(int levelNum);
};

#endif
