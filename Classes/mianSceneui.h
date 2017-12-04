#ifndef __MIANSCENE_UI_H__
#define __MIANSCENE_UI_H__

#include "cocos2d.h"

#include "ui/CocosGUI.h"

#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"
#include "editor-support/cocostudio/CocoStudio.h"

using namespace cocos2d;
using namespace CocosDenshion;

using namespace cocostudio::timeline;

class mianSceneui : public cocos2d::Layer
{
public:

	mianSceneui();
	~mianSceneui();
    virtual bool init();  
	void setyouwup(Sprite *target);
	void setguankNum(int num);

    
	void btncallFunc(Object *pSender, cocos2d::ui::Button::TouchEventType type);
	void selectedItemEvent(Ref* pSender, cocos2d::ui::ListView::EventType type);
	void teshuList(Sprite *target);
	void tewupList(Sprite *target);
	virtual bool TouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	virtual void TouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	CREATE_FUNC(mianSceneui);
private:
	bool isyuyantouch;
	bool islistouch;
	ui::ImageView* xuanzong;
	ui::ListView* hengView;
	ui::Layout* zhuView;
	ui::ListView* wupView;
	ui::Layout* dutu_ly;
	ui::ImageView* wupditu;
	Node *MainSuiNode;
	int strguankNum;
};

#endif  // __HELLOWORLD_SCENE_H__