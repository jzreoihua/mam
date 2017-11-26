#ifndef __XUANG_H__
#define __XUANG_H__

#include "cocos2d.h"

//#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
using namespace cocos2d;
class xuanG : public cocos2d::Layer
{
public:

	xuanG();
	~xuanG();
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	virtual bool TouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	virtual void TouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	// implement the "static node()" method manually
	CREATE_FUNC(xuanG);
private:

	ScaleTo *targetScTo;
	Node *xuangNode;
	Sprite* mygril[29];
	Sprite* heimi_15;
	//SpriteFrameCache* xuangframeCache;
	std::string xgName;
	Label* gNumCount;
	EventListenerTouchOneByOne *touchListener;
	int gknum;
};

#endif  // __HELLOWORLD_SCENE_H__