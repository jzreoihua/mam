#ifndef __INPUTRD__H_
#define __INPUTRD__H_

#include <iostream>

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocostudio::timeline;
class Inputrd : public cocos2d::Layer
{
public:
	Inputrd();
	~Inputrd();
	static cocos2d::Layer* create(int i);
	virtual bool init(int i);

	//static void  teshuListEaseIn(Sprite *sprite1, Sprite *sprite2, Vec2 _yuyanxy);
	//CREATE_FUNC(Inputrd);
	//void setguankNum(int num);
	void btncallFunc(Object *pSender, cocos2d::ui::Button::TouchEventType type);

	virtual bool TouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	virtual void TouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	private:
		bool isyuyantouch;
		bool islistouch;

		int strguankNum;
		int mimaNum;
		std::string strmimaNum;
		Label *gNumCount;
};

#endif