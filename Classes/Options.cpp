#include "Options.h"
#include "MainMenu.h"
#include "Constants.h"
#include "Utils.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

//Create an area for the Options Menu to exist
CCScene* Options::scene() {
    CCScene *sc = CCScene::create();
    sc->setTag(TAG_OPTIONS_SCENE);
    Options *o = Options::create();
    sc->addChild(o, 0, TAG_OPTIONS_LAYER);
    return sc;
}

bool Options::init() {
	if ( !CCLayer::init() ) {
		return false;
	}

	//Sets the visible area
	windowSize = CCDirector::sharedDirector()->getWinSize();
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    //Create background image and ------ASK JACK HOW "Utils::scaleSprite(bg);" WORKS
    CCSprite* bg = CCSprite::create("Options.png");
    bg->setPosition(ccp(windowSize.width/2,windowSize.height/2));
    Utils::scaleSprite(bg);
    this->addChild(bg,-1);

    //Create Menu Buttons, places them in a Menu function, and positions them on the screen
    CCMenuItemImage *mainMenuButton = CCMenuItemImage::create("main_menu_button.png", "main_menu_button_selected.png", this, menu_selector(Options::mainMenu));
    CCMenu *menu = CCMenu::create(mainMenuButton, NULL);
    menu->setPosition(ccp(windowSize.width - 1010, windowSize.height/2 - 280));
    this->addChild(menu,2);

    int _musicToggle = CCUserDefault::sharedUserDefault()->getIntegerForKey("music");
    int _soundfxToggle = CCUserDefault::sharedUserDefault()->getIntegerForKey("soundfx");


    musicOn = CCMenuItemImage::create("music_on.png", "music_off.png", this, menu_selector(Options::fmusicOff));
    musicOff = CCMenuItemImage::create("music_off.png", "music_on.png", this, menu_selector(Options::fmusicOn));

    if(_musicToggle == 0) {
    	musicOff->setVisible(false);
    } else {
    	musicOn->setVisible(false);
    }

    soundfxOn = CCMenuItemImage::create("sound_fx_on.png", "sound_fx_off.png", this, menu_selector(Options::fsoundfxOff));
    soundfxOff = CCMenuItemImage::create("sound_fx_off.png", "sound_fx_on.png", this, menu_selector(Options::fsoundfxOn));

    if(_soundfxToggle == 0) {
    	soundfxOff->setVisible(false);
    } else {
    	soundfxOn->setVisible(false);
    }

    CCMenu *soundMenu = CCMenu::create(musicOn, musicOff, soundfxOn, soundfxOff, NULL);
    soundMenu->setPosition(ccp(windowSize.width * .33, windowSize.height / 2.3));
    soundfxOn->setPosition(ccp(400, 0));
    soundfxOff->setPosition(ccp(400, 0));
    this->addChild(soundMenu);

	return true;
}

//Allows for the return to the Main Menu when it's button is tapped
void Options::mainMenu() {
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInT::create(0.2,MainMenu::scene()));
}

void Options::fmusicOff() {
	musicOn->setVisible(false);
	musicOff->setVisible(true);
    if(SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying()) {
        SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    }
	CCUserDefault::sharedUserDefault()->setIntegerForKey("music", 1);
	CCUserDefault::sharedUserDefault()->flush();
}

void Options::fmusicOn() {
	musicOn->setVisible(true);
	musicOff->setVisible(false);
    if(!SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying()) {
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Audio/Music/Menu.mp3", true);
        SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.1f);
    }
	CCUserDefault::sharedUserDefault()->setIntegerForKey("music", 0);
	CCUserDefault::sharedUserDefault()->flush();
}

void Options::fsoundfxOff() {
	soundfxOff->setVisible(true);
	soundfxOn->setVisible(false);
	CCUserDefault::sharedUserDefault()->setIntegerForKey("soundfx", 1);
	CCUserDefault::sharedUserDefault()->flush();
}

void Options::fsoundfxOn() {
	soundfxOff->setVisible(false);
	soundfxOn->setVisible(true);
	CCUserDefault::sharedUserDefault()->setIntegerForKey("soundfx", 0);
	CCUserDefault::sharedUserDefault()->flush();
}
