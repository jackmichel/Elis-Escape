#include "Catapult.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

Catapult::~Catapult() {

}

Catapult::Catapult() {
	_screenSize = CCDirector::sharedDirector()->getWinSize();
}

Catapult * Catapult::create() {
	Catapult * catapult = new Catapult();
	if (catapult && catapult->initWithFile("catapult.png")) {
		catapult->autorelease();
		return catapult;
	}
	CC_SAFE_DELETE(catapult);
	return NULL;
}

const char * Catapult::getType() {
	return "Catapult";
}
