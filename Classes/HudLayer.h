#ifndef __HUDLAYER_H__
#define __HUDLAYER_H__

#include "cocos2d.h"

using namespace cocos2d;

class HudLayer : public cocos2d::CCLayer
{
private:
	CCSize windowSize;
	CCMenuItemImage *_runMode;
	CCMenuItemImage *_editMode;
    CCSprite *_toolbarBG;
    CCSprite *_modal;
    CCMenu *_modeMenu;
    CCMenu *_returnMenu;
    CCMenu *_modalMenu;
    CCMenu *_modalCont;
    CCMenu *_modalReplay;
    CCArray * _tools;
    CCArray * _toolLabels;
    int _movingTool;
    int _numBridges;
    char _bridges[256];
    int _numSprings;
    char _springs[256];
    int _numFans;
    char _fans[256];
    int _numPoles;
    char _poles[256];
    int _numCatapults;
    char _catapults[256];
    CCLabelTTF* _bridgeLabel;
    CCLabelTTF* _springLabel;
    CCLabelTTF* _fanLabel;
    CCLabelTTF* _poleLabel;
    CCLabelTTF* _catapultLabel;

public:
    virtual bool init();
    static CCScene* scene();
    void switchMode();
    void levelComplete();
    void mainMenu();
    void levelSelect();
    void listTools(CCArray * tools);
    void hideTools();
    void showTools();
    void subtractTool(const char * type);
    void addTool();
    void nextLevel();
    void replay();
    void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	void ccTouchesEnded(CCSet *pTouches, CCEvent *event);
    CC_SYNTHESIZE(CCArray*, _touches, touches);
    CREATE_FUNC(HudLayer);
};

#endif // __HUDLAYER_H__
