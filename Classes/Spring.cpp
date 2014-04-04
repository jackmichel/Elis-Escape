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
		return spring;
	}
	CC_SAFE_DELETE(spring);
	return NULL;
}

const char * Spring::getType() {
	return "Spring";
}
