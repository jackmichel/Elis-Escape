#ifndef __TOOL_H__
#define __TOOL_H__

#include "cocos2d.h"
#include "Eli.h"

USING_NS_CC;

class Tool : public CCSprite {
	CCSize _screenSize;

public:

	Tool(void);
	~Tool(void);
	virtual const char * getType();
	virtual void checkCollision(Eli * eli);
	virtual bool touchingTool(CCPoint location);

};

#endif
