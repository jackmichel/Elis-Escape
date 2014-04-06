#ifndef __POLE_H__
#define __POLE_H__

#include "Tool.h"
#include "cocos2d.h"

USING_NS_CC;

class Pole : public Tool {
	CCSize _screenSize;
	bool _canTurn;

public:

	Pole(void);
	~Pole(void);

	static Pole * create (void);
	virtual const char * getType();
	virtual void checkCollision(Eli * eli);
	void allowTurn();

};

#endif
