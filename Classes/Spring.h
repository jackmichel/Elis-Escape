#ifndef __SPRING_H__
#define __SPRING_H__

#include "Tool.h"
#include "cocos2d.h"

USING_NS_CC;

class Spring : public Tool {
	CCSize _screenSize;
	bool _canJump;

public:

	Spring(void);
	~Spring(void);

	static Spring * create (void);
	virtual const char * getType();
	virtual void checkCollision(Eli * eli);
	void allowJump();

};

#endif
