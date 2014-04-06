#ifndef __ELI_H__
#define __ELI_H__

#define INITIAL_SPEED 5
#define INITIAL_JUMP_SPEED 0.5f
#define TERMINAL_VELOCITY 14
#define AIR_FRICTION 0.9999f
#define PLAYER_JUMP 18
#define GRAVITY 1.5

#include "cocos2d.h"

USING_NS_CC;

typedef enum
{
    kPlayerMoving,
    kPlayerFalling,
    kPlayerDying

} EliState;

class Eli : public CCSprite {
	float _speed;
	float _jumpSpeed;
	CCSize _screenSize;
	CCAction * _run;
	CCAction * _jump;

public:

	Eli(void);
	~Eli(void);

	CC_SYNTHESIZE(EliState, _state, State);
	CC_SYNTHESIZE(bool, _jumping, Jumping);
	CC_SYNTHESIZE(bool, _inAir, InAir);
	CC_SYNTHESIZE(CCPoint, _nextPosition, NextPosition);
	CC_SYNTHESIZE(float, _width, Width);
	CC_SYNTHESIZE(float, _height, Height);
	CC_SYNTHESIZE(CCPoint, _vector, Vector);

	static Eli * create (void);
	void update (float dt);
	void createAnimations();
	void startRunAnimation();
	void jumpAnimation();
	void reset();
	void changeDirection();
	void jump();
	void hitSpring();
	void resetJumpSpeed();

};

#endif
