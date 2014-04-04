#include "Bridge.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

Bridge::~Bridge() {

}

Bridge::Bridge() {
	_screenSize = CCDirector::sharedDirector()->getWinSize();
}

Bridge * Bridge::create() {
	Bridge * bridge = new Bridge();
	if (bridge && bridge->initWithFile("bridge.png")) {
		bridge->autorelease();
		return bridge;
	}
	CC_SAFE_DELETE(bridge);
	return NULL;
}
