#include "Spring.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

Spring::~Spring() {

}

Spring::Spring() {
	_screenSize = CCDirector::sharedDirector()->getWinSize();
}

Spring * Spring::create() {
	Spring * spring = new Spring();
	if (spring && spring->initWithFile("spring.png")) {
		spring->autorelease();
		spring->_canJump = true;
		return spring;
	}
	CC_SAFE_DELETE(spring);
	return NULL;
}

const char * Spring::getType() {
	return "Spring";
}

void Spring::checkCollision(Eli * eli) {
	if (_canJump) {
		CCRect box = eli->boundingBox();
		if (box.containsPoint(this->getPosition())) {
			eli->hitSpring();
			_canJump = false;
			CCCallFunc* moveCallback = CCCallFunc::create(this, callfunc_selector(Spring::allowJump));
			CCDelayTime* delayAction = CCDelayTime::create(0.1f);
			this->runAction(CCSequence::create(delayAction, moveCallback, NULL));
		}
	}
}

void Spring::allowJump() {
	_canJump = true;
}

