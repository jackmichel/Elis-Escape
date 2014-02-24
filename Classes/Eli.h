#ifndef __ELI_H__
#define __ELI_H__

#define INITIAL_SPEED 8

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
	CCSize _screenSize;
	CCPoint _nextPosition;

public:

	Eli(void);
	~Eli(void);

	CC_SYNTHESIZE(EliState, _state, State);
	CC_SYNTHESIZE(bool, _jumping, Jumping);
	CC_SYNTHESIZE(bool, _inAir, InAir);

	static Eli * create (void);

};

#endif
