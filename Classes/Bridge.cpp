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

void Bridge::setGridPosition(CCPoint location, int offsetX, int offsetY) {
	int height = (int) this->getContentSize().height % 50;
	int width = (int) this->getContentSize().width % 50;
	int xMod = (int) location.x % 50;
	int yMod = (int) location.y % 50;
	int newX;
	int newY;

	if (xMod > 25) {
		newX = location.x - xMod + 50;
	} else {
		newX = location.x - xMod;
	}

	if (yMod > 25) {
		newY = location.y - yMod + 50;
	} else {
		newY = location.y - yMod;
	}

	newX = newX + width / 2 + offsetX;
	newY = newY + height / 2 + 10 + offsetY;
	this->setPosition(ccp(newX, newY));
}
