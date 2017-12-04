/************************************************************************/
/* 
**  Date   :   2013/9/21

** author  :   Bright Moon

** function:   游戏的主逻辑，全部放在此模块中， 主要包括：
			   1、游戏泡泡和等待发射的泡泡初始化
			   2、游戏触摸的开关和处理
			   3、泡泡的碰撞检测和处理（调整泡泡的位置）
			   4、碰撞后查找相同泡泡的算法
			   5、泡泡的消除
			   6、消除后是否有悬挂泡泡的检测
*/
/************************************************************************/

#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include "cocos2d.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"
#include "GameShuJu.h"
#include "Popinterface.h"
#include "ui/CocosGUI.h"
#include "mianSceneui.h"
#include <list>
#include <vector>
#include "tinyxml2/tinyxml2.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocostudio::timeline;
using namespace tinyxml2;

//游戏主场景， 所有的逻辑和表现都在这个场景中完成
class GameScene : public cocos2d::Layer
{
public:
	GameScene();
	~GameScene();

public:
	//界面显示
	static cocos2d::Scene* scene(int gknum);

	virtual bool init(int gknum);
	void vtory();
	void vjiesuan(int i);
	void loop(float);
	void update(float);
	void clickwup(std::string targetname, bool isfan = false, XMLElement* xmlfanwei = NULL);
	void findwup(XMLElement* dangqianwup, bool isfan = false, XMLElement* xmlfanwei = NULL);
	void loadactiongotoFrameAndPause(int Num);
	virtual bool TouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	virtual void TouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	
	//CREATE_FUNC(GameScene);
private:
	bool createmianui();
	bool initMyian();
	
private:
	int strguankNum;
	int tistime;
	mianSceneui *Sceneuily;
	Node *rootNode;
	ActionTimeline *loadaction;
	XMLElement* guankaspming;
	XMLElement* tisspming;
	XMLElement* putontis;
	ui::ImageView* tisikuang;
	Label *tisCount;

};
#endif