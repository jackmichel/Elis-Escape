#ifndef __TOOL_H__
#define __TOOL_H__

#include "cocos2d.h"

USING_NS_CC;

class Tool : public CCSprite {
	CCSize _screenSize;

public:

	Tool(void);
	~Tool(void);
	virtual const char * getType();
	bool touchingTool(CCPoint location);

};

#endif
