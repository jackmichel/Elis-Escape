#ifndef __FAN_H__
#define __FAN_H__

#include "Tool.h"
#include "cocos2d.h"

USING_NS_CC;

class Fan : public Tool {
	CCSize _screenSize;

public:

	Fan(void);
	~Fan(void);

	static Fan * create (void);
	virtual const char * getType();

};

#endif
