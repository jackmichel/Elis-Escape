#include "Eli.h"

Eli::~Eli() {

}

Eli::Eli() {
	_screenSize = CCDirector::sharedDirector()->getWinSize();
	_speed = INITIAL_SPEED;
	_nextPosition = CCPointZero;
	_state = kPlayerMoving;
	_jumping = false;
}

Eli * Eli::create() {
	Eli * eli = new Eli();
	if (eli && eli->initWithFile("eli.png")) {
		eli->autorelease();
		return eli;
	}
	CC_SAFE_DELETE(eli);
	return NULL;
}
