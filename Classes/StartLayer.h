#ifndef __START_LAYER_H__
#define __START_LAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"
#include "editor-support/cocostudio/CocoStudio.h"

using namespace cocos2d;
using namespace CocosDenshion;

using namespace cocostudio::timeline;
class StartLayer: public cocos2d::Layer
{
public:

	StartLayer();
	~StartLayer();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::Scene* scene();
	void btncallFunc(Object *pSender, cocos2d::ui::Button::TouchEventType type);
	void selectedItemEvent(Ref* pSender, cocos2d::ui::ListView::EventType type);
	void teshuList();
	virtual bool TouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	virtual void TouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
    // implement the "static node()" method manually
    CREATE_FUNC(StartLayer);
private:
	ScaleTo *targetScTo;
	Node *pSprite;
	ui::ListView* shuView;
	ui::Layout* yuyanView;
	bool islistouch;
	bool isyuyantouch;
};

#endif  // __HELLOWORLD_SCENE_H__