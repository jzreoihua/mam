#ifndef __GAMEDUIHUA__H_
#define __GAMEDUIHUA__H_

#include <iostream>

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocostudio::timeline;
class Gameduihua : public cocos2d::Layer
{
public:
	Gameduihua();
	~Gameduihua();
	
	virtual bool init();

	//static void  teshuListEaseIn(Sprite *sprite1, Sprite *sprite2, Vec2 _yuyanxy);
	
	//void setguankNum(int num);

	void loop(float);
	virtual bool TouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	virtual void TouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	CREATE_FUNC(Gameduihua);
private:
	bool isyuyantouch;
	bool islistouch;

	int strguankNum;
	int mimaNum;
	std::string strmimaNum;
	std::string dtext;
	Label *gNumCount;
	Sprite *duihuank_3;
};

#endif