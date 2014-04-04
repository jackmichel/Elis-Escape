#include "Tool.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

Tool::~Tool() {

}

Tool::Tool() {
	_screenSize = CCDirector::sharedDirector()->getWinSize();
}
