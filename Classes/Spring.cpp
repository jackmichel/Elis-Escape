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
		spring->createAnimations();
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
			this->runAction(_bounce);
			_canJump = false;
			CCCallFunc* moveCallback = CCCallFunc::create(this, callfunc_selector(Spring::allowJump));
			CCDelayTime* delayAction = CCDelayTime::create(0.1f);
			this->runAction(CCSequence::create(delayAction, moveCallback, NULL));
		}
	}
}

bool Spring::touchingTool(CCPoint location) {
	bool isTouching = false;
	int height = this->getContentSize().height * 4;
	int width = this->getContentSize().width * 4;
	int left = this->getPosition().x - (width / 2);
	int right = left + width;
	int bottom = this->getPosition().y - (height / 2);
	int top = bottom + height;

	if ((location.x >= left && location.x <= right) && (location.y >= bottom && location.y <= top)) {
		isTouching = true;
	}

	return isTouching;
}

void Spring::allowJump() {
	_canJump = true;
}

void Spring::createAnimations() {
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("spring_animation.plist");

	CCAnimation* animation;
	CCSpriteFrame * frame;

	animation = CCAnimation::create();
	CCString * name;
	for (int i = 1; i <= 3; i++) {
		name = CCString::createWithFormat("s%04d.png", i);
		frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
		animation->addSpriteFrame(frame);
	}
	animation->setDelayPerUnit(0.08f);
	_bounce = CCSequence::create(CCAnimate::create(animation), NULL);
	_bounce->retain();
}

