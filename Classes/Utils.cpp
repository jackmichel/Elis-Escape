#include "Utils.h"
#include "Constants.h"
#include "Bridge.h"
#include "Spring.h"
#include "Pole.h"
#include "Catapult.h"
#include "Fan.h"

using namespace cocos2d;

static float scale = 1.0f;
static int artScaleFactor = 1;

Game* Utils::gameLayer() {
    return (Game *)Utils::layerWithTag(TAG_GAME_LAYER);
}

CCLayer* Utils::layerWithTag(int tag) {
    CCScene *sc = CCDirector::sharedDirector()->getRunningScene();
    if (sc->getTag() == TAG_GAME_SCENE) {
        CCLayer *layer = (CCLayer *)sc->getChildByTag(tag);
        return layer;
    }
    return NULL;
}

CCSize Utils::s() {
    return CCDirector::sharedDirector()->getWinSize();
}

cocos2d::CCAnimate* Utils::getAnimationWithFrames(int from, int to) {
	CCArray* frames = CCArray::create();
	for (int i = from; i <= to; i++) {
	     CCString *str = CCString::createWithFormat("a%04d.png", i);
	     frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str->getCString()));
	}
	CCAnimation *animation = CCAnimation::create(frames, 1.0f/24.0f);
	CCAnimate *a = CCAnimate::create(animation);
	return a;
}

void Utils::scaleSprite(CCSprite* sprite) {
    float rX = Utils::s().width / sprite->getContentSize().width;
	float rY = Utils::s().height / sprite->getContentSize().height;
	sprite->setScaleX(rX);
	sprite->setScaleY(rY);
}

float Utils::getScale() {
    return scale;
}

void Utils::setScale(float s) {
    scale = s;
}

float Utils::getArtScaleFactor() {
    return artScaleFactor;
}

void Utils::setArtScaleFactor(int s) {
    artScaleFactor = s;
}

const char * Utils::getLevelMap(int levelNum) {
	const char * levelMap;
	switch (levelNum) {
		case 1:
			levelMap = "lvl1-1.tmx";
			break;
		case 2:
			levelMap = "lvl1-2.tmx";
			break;
		case 3:
			levelMap = "lvl1-3.tmx";
			break;
		case 4:
			levelMap = "lvl1-4.tmx";
			break;
		case 5:
			levelMap = "lvl1-5.tmx";
			break;
		case 6:
			levelMap = "lvl1-6.tmx";
			break;
		case 7:
			levelMap = "lvl1-7.tmx";
			break;
		case 8:
			levelMap = "lvl1-8.tmx";
			break;
		case 9:
			levelMap = "lvl1-9.tmx";
			break;
		case 10:
			levelMap = "lvl1-10.tmx";
			break;
	}
	return levelMap;
}

const char * Utils::getLevelKey(int levelNum) {
	const char * levelKey;
	switch (levelNum) {
		case 1:
			levelKey = "levelOne";
			break;
		case 2:
			levelKey = "levelTwo";
			break;
		case 3:
			levelKey = "levelThree";
			break;
		case 4:
			levelKey = "levelFour";
			break;
		case 5:
			levelKey = "levelFive";
			break;
		case 6:
			levelKey = "levelSix";
			break;
		case 7:
			levelKey = "levelSeven";
			break;
		case 8:
			levelKey = "levelEight";
			break;
		case 9:
			levelKey = "levelNine";
			break;
		case 10:
			levelKey = "levelTen";
			break;
	}
	return levelKey;
}

CCArray * Utils::getLevelTools(int levelNum) {
	CCArray * tools = CCArray::createWithCapacity(14);
	switch (levelNum) {
		case 1:
			{
				Bridge * t1 = Bridge::create();
				tools->addObject(t1);
			}
			break;
		case 2:
			{
				Bridge * t1 = Bridge::create();
				Bridge * t2 = Bridge::create();
				tools->addObject(t1);
				tools->addObject(t2);
			}
			break;
		case 3:
			{
				Bridge * t1 = Bridge::create();
				Bridge * t2 = Bridge::create();
				Bridge * t3 = Bridge::create();
				Bridge * t4 = Bridge::create();
				Bridge * t5 = Bridge::create();
				tools->addObject(t1);
				tools->addObject(t2);
				tools->addObject(t3);
				tools->addObject(t4);
				tools->addObject(t5);
			}
			break;
		case 4:
			{
				Bridge * t1 = Bridge::create();
				Bridge * t2 = Bridge::create();
				Bridge * t3 = Bridge::create();
				Bridge * t4 = Bridge::create();
				tools->addObject(t1);
				tools->addObject(t2);
				tools->addObject(t3);
				tools->addObject(t4);
			}
			break;
		case 5:
			{
				Spring * t1 = Spring::create();
				Spring * t2 = Spring::create();
				tools->addObject(t1);
				tools->addObject(t2);
			}
			break;
		case 6:
			{
				Bridge * t1 = Bridge::create();
				Bridge * t2 = Bridge::create();
				Spring * t3 = Spring::create();
				Spring * t4 = Spring::create();
				Spring * t5 = Spring::create();
				Spring * t6 = Spring::create();
				tools->addObject(t1);
				tools->addObject(t2);
				tools->addObject(t3);
				tools->addObject(t4);
				tools->addObject(t5);
				tools->addObject(t6);
			}
			break;
		case 7:
			{
				Bridge * t1 = Bridge::create();
				Bridge * t2 = Bridge::create();
				Spring * t3 = Spring::create();
				Spring * t4 = Spring::create();
				tools->addObject(t1);
				tools->addObject(t2);
				tools->addObject(t3);
				tools->addObject(t4);
			}
			break;
		case 8:
			{
				Pole * t1 = Pole::create();
				Pole * t2 = Pole::create();
				Pole * t3 = Pole::create();
				Pole * t4 = Pole::create();
				Pole * t5 = Pole::create();
				Pole * t6 = Pole::create();
				Pole * t7 = Pole::create();
				Pole * t8 = Pole::create();
				Pole * t9 = Pole::create();
				Pole * t10 = Pole::create();
				Pole * t11 = Pole::create();
				Pole * t12 = Pole::create();
				Pole * t13 = Pole::create();
				Pole * t14 = Pole::create();
				tools->addObject(t1);
				tools->addObject(t2);
				tools->addObject(t3);
				tools->addObject(t4);
				tools->addObject(t5);
				tools->addObject(t6);
				tools->addObject(t7);
				tools->addObject(t8);
				tools->addObject(t9);
				tools->addObject(t10);
				tools->addObject(t11);
				tools->addObject(t12);
				tools->addObject(t13);
				tools->addObject(t14);
			}
			break;
		case 9:
			{
				Bridge * t1 = Bridge::create();
				Bridge * t2 = Bridge::create();
				Spring * t3 = Spring::create();
				Pole * t4 = Pole::create();
				Pole * t5 = Pole::create();
				Pole * t6 = Pole::create();
				tools->addObject(t1);
				tools->addObject(t2);
				tools->addObject(t3);
				tools->addObject(t4);
				tools->addObject(t5);
				tools->addObject(t6);
			}
			break;
		case 10:
			{
				Bridge * t1 = Bridge::create();
				Bridge * t2 = Bridge::create();
				Bridge * t3 = Bridge::create();
				Spring * t4 = Spring::create();
				Spring * t5 = Spring::create();
				Spring * t6 = Spring::create();
				Spring * t7 = Spring::create();
				Pole * t8 = Pole::create();
				tools->addObject(t1);
				tools->addObject(t2);
				tools->addObject(t3);
				tools->addObject(t4);
				tools->addObject(t5);
				tools->addObject(t6);
				tools->addObject(t7);
				tools->addObject(t8);
			}
			break;
	}
	return tools;
}

bool Utils::reverseEliDirection(int levelNum) {
	bool reverseDirection = false;
	if (levelNum == 5 || levelNum == 6 || levelNum == 8 || levelNum == 9) {
		reverseDirection = true;
	}
	return reverseDirection;
}
