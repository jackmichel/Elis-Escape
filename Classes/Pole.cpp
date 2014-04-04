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
		pole->autorelease();
		return pole;
	}
	CC_SAFE_DELETE(pole);
	return NULL;
}

const char * Pole::getType() {
	return "Pole";
}
