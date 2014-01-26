#include "Utils.h"
#include "Constants.h"

using namespace cocos2d;

static float scale = 1.0f;
static int artScaleFactor = 1;

Game* Utils::gameLayer()
{
    return (Game *)Utils::layerWithTag(TAG_GAME_LAYER);
}
CCLayer* Utils::layerWithTag(int tag)
{
    CCScene *sc = CCDirector::sharedDirector()->getRunningScene();
    if (sc->getTag() == TAG_GAME_SCENE) {
        CCLayer *layer = (CCLayer *)sc->getChildByTag(tag);
        return layer;
    }
    return NULL;
}

CCSize Utils::s()
{
    return CCDirector::sharedDirector()->getWinSize();
}

cocos2d::CCAnimate* Utils::getAnimationWithFrames(int from, int to)
{
	CCArray* frames = CCArray::create();
	for (int i = from; i <= to; i++) {
	     CCString *str = CCString::createWithFormat("a%04d.png", i);
	     frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str->getCString()));
	}
	CCAnimation *animation = CCAnimation::create(frames, 1.0f/24.0f);
	CCAnimate *a = CCAnimate::create(animation);
	return a;
}

void Utils::scaleSprite(CCSprite* sprite)
{
    float rX = Utils::s().width / sprite->getContentSize().width;
	float rY = Utils::s().height / sprite->getContentSize().height;
	sprite->setScaleX(rX);
	sprite->setScaleY(rY);
}

float Utils::getScale()
{
    return scale;
}

void Utils::setScale(float s)
{
    scale = s;
}

float Utils::getArtScaleFactor()
{
    return artScaleFactor;
}

void Utils::setArtScaleFactor(int s)
{
    artScaleFactor = s;
}
