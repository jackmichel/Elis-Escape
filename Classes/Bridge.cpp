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

const char * Bridge::getType() {
	return "Bridge";
}

bool Bridge::touchingTool(CCPoint location) {
	bool isTouching = false;
	int height = this->getContentSize().height * 2;
	int width = this->getContentSize().width;
	int left = this->getPosition().x - (width / 2);
	int right = left + width;
	int bottom = this->getPosition().y - (height / 2);
	int top = bottom + height;

	if ((location.x >= left && location.x <= right) && (location.y >= bottom && location.y <= top)) {
		isTouching = true;
	}

	return isTouching;
}
