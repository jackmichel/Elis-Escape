#ifndef __BRIDGE_H__
#define __BRIDGE_H__

#include "Tool.h"
#include "cocos2d.h"

USING_NS_CC;

class Bridge : public Tool {
	CCSize _screenSize;

public:

	Bridge(void);
	~Bridge(void);

	static Bridge * create (void);
	virtual const char * getType();
	virtual bool touchingTool(CCPoint location);
	virtual void setGridPosition(CCPoint location, int offsetX, int offsetY);

};

#endif
