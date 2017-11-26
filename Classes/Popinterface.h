#ifndef __POPINTER_SCENE_H__
#define __POPINTER_SCENE_H__

#include "cocos2d.h"
#include "GameShuJu.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "GameScene.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "StartLayer.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocostudio::timeline;
class Popinterface: public cocos2d::Layer
{
public:
	
	Popinterface();
	~Popinterface();
	virtual bool init(int i);
	static cocos2d::Layer* create(int i);
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer

	void setguankNum(int num);
	void appear();
	void disappear();
	void close();	
	void Listener();
	void selectedItemEvent(Ref* pSender, cocos2d::ui::ListView::EventType type);
	void btncallFunc(Object *pSender, cocos2d::ui::Button::TouchEventType type);
	void load(int loadnum);
	// a selector callback
	virtual bool TouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	virtual void TouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);

	// implement the "static node()" method manually
	//CREATE_FUNC(Popinterface);
private:
	int popmun;
	int myjinb;
	int _loadnum;
	int strguankNum; //当前第几关
	bool islistouch;
	bool isgoumaddlist;
	bool isjinbaddlist;
	Label *jinbCount;
	Node *sbaiNode;
	Node *loadNode;
	ui::ListView* GmLvew;
	ui::ListView* CzLvew;
	SpriteFrame *btnSpriteFrame1;
	SpriteFrame *btnSpriteFrame;
	//Scene* _gamescene;
	ActionTimeline *sbaiaction;
	ScaleTo *targetScTo;
	EventListenerTouchOneByOne *touchListener;
};

#endif