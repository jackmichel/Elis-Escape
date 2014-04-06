#include "Pole.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

Pole::~Pole() {

}

Pole::Pole() {
	_screenSize = CCDirector::sharedDirector()->getWinSize();
}

Pole * Pole::create() {
	Pole * pole = new Pole();
	if (pole && pole->initWithFile("pole.png")) {
		pole->_canTurn = true;
		pole->autorelease();
		return pole;
	}
	CC_SAFE_DELETE(pole);
	return NULL;
}

const char * Pole::getType() {
	return "Pole";
}

void Pole::checkCollision(Eli * eli) {
	if (_canTurn) {
		CCRect box = eli->boundingBox();
		if (box.containsPoint(this->getPosition())) {
			eli->changeDirection();
			_canTurn = false;
			CCCallFunc* moveCallback = CCCallFunc::create(this, callfunc_selector(Pole::allowTurn));
			CCDelayTime* delayAction = CCDelayTime::create(0.1f);
			this->runAction(CCSequence::create(delayAction, moveCallback, NULL));
		}
	}
}

void Pole::allowTurn() {
	_canTurn = true;
}
