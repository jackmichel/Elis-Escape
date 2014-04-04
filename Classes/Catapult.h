#ifndef __CATAPULT_H__
#define __CATAPULT_H__

#include "Tool.h"
#include "cocos2d.h"

USING_NS_CC;

class Catapult : public Tool {
	CCSize _screenSize;

public:

	Catapult(void);
	~Catapult(void);

	static Catapult * create (void);
	virtual const char * getType();

};

#endif
