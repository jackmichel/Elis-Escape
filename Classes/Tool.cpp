#include "Tool.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

Tool::~Tool() {

}

Tool::Tool() {
	_screenSize = CCDirector::sharedDirector()->getWinSize();
}

const char * Tool::getType() {
	return "Tool";
}

void Tool::checkCollision(Eli * eli) {

}

// Switched to bounding box method, this is essentially the same as CCrect's containsPoint() method
bool Tool::touchingTool(CCPoint location) {
	bool isTouching = false;
	int height = this->getContentSize().height;
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
