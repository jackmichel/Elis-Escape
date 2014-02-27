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
        _vector.y += PLAYER_JUMP * 0.25f;
        if (_vector.y > PLAYER_JUMP ) {
        	_jumping = false;
        }
    }

    if (_vector.y < -TERMINAL_VELOCITY) {
    	_vector.y = -TERMINAL_VELOCITY;
    }

    _nextPosition.x = this->getPositionX() + _vector.x;
  	_nextPosition.y = this->getPositionY() + _vector.y;
  	this->setPosition(ccp(_nextPosition.x,_nextPosition.y));
}
