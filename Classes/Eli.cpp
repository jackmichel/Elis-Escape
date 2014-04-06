#include "Eli.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

Eli::~Eli() {

}

Eli::Eli() {
	_screenSize = CCDirector::sharedDirector()->getWinSize();
	_speed = INITIAL_SPEED;
	_jumpSpeed = INITIAL_JUMP_SPEED;
	_nextPosition = CCPointZero;
	_state = kPlayerMoving;
	_jumping = false;
}

Eli * Eli::create() {
	Eli * eli = new Eli();
	if (eli && eli->initWithFile("eli.png")) {
		eli->createAnimations();
		eli->autorelease();
		return eli;
	}
	CC_SAFE_DELETE(eli);
	return NULL;
}

void Eli::update (float dt) {

    _vector.x = _speed;

	switch (_state) {
		case kPlayerMoving:
			_vector.y -= GRAVITY;
		break;

        case kPlayerFalling:
			_vector.y -= GRAVITY;
			_vector.x *= AIR_FRICTION;
		break;

        case kPlayerDying:
            _vector.y -= GRAVITY;
            _vector.x = -_speed;
            this->setPositionX(this->getPositionX() + _vector.x);
        break;
	}

    if (_jumping) {
        _state = kPlayerFalling;
        _vector.y += PLAYER_JUMP * _jumpSpeed;
        SimpleAudioEngine::sharedEngine()->playEffect("Audio/Sound Effects/Jump1.wav", false);
        if (_vector.y > PLAYER_JUMP ) {
        	_jumping = false;
        }
    }

    if (_vector.y < -TERMINAL_VELOCITY) {
    	_vector.y = -TERMINAL_VELOCITY;
    }

    _nextPosition.x = this->getPositionX() + _vector.x;
  	_nextPosition.y = this->getPositionY() + _vector.y;
}

void Eli::createAnimations() {
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("eli_running.plist");

	CCAnimation* animation;
	CCSpriteFrame * frame;

	animation = CCAnimation::create();
	CCString * name;
	for (int i = 1; i <= 5; i++) {
		name = CCString::createWithFormat("e%04d.png", i);
		frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
		animation->addSpriteFrame(frame);
	}
	animation->setDelayPerUnit(0.08f);
	animation->setLoops(-1);
	_run = CCSequence::create(CCAnimate::create(animation), NULL);
	_run->retain();

	animation = CCAnimation::create();
	for (int i = 1; i <= 2; i++) {
		name = CCString::createWithFormat("j%04d.png", i);
		frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
		animation->addSpriteFrame(frame);
	}
	animation->setDelayPerUnit(0.15f);
	_jump = CCSequence::create(CCAnimate::create(animation), NULL);
	_jump->retain();
}

void Eli::startRunAnimation() {
	this->stopAllActions();
	this->runAction(_run);
}

void Eli::jumpAnimation() {
	this->stopAllActions();
	this->runAction(_jump);
}

void Eli::jump() {
	if (this->getState() != (kPlayerDying || kPlayerFalling) && !this->getInAir()) {
		this->jumpAnimation();
		this->setJumping(true);
		this->setInAir(true);
	}
}

void Eli::changeDirection() {
	_speed = -_speed;
	this->setScaleX(-this->getScaleX());
}

void Eli::hitSpring() {
	_jumpSpeed = 1.6f;
	this->setInAir(false);
	this->setState(kPlayerMoving);
	this->jump();
	CCCallFunc* moveCallback = CCCallFunc::create(this, callfunc_selector(Eli::resetJumpSpeed));
	CCDelayTime* delayAction = CCDelayTime::create(0.1f);
	this->runAction(CCSequence::create(delayAction, moveCallback, NULL));
}

void Eli::resetJumpSpeed() {
	_jumpSpeed = INITIAL_JUMP_SPEED;
}

void Eli::reset() {
	_speed = INITIAL_SPEED;
	this->stopAllActions();
	this->setScaleX(1.0f);
}
