#include "Fan.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

Fan::~Fan() {

}

Fan::Fan() {
	_screenSize = CCDirector::sharedDirector()->getWinSize();
}

Fan * Fan::create() {
	Fan * fan = new Fan();
	if (fan && fan->initWithFile("fan.png")) {
		fan->autorelease();
		return fan;
	}
	CC_SAFE_DELETE(fan);
	return NULL;
}

const char * Fan::getType() {
	return "Fan";
}
