/************************************************************************/
/* 
**  Date   :   2013/9/21

** author  :   Bright Moon

** function:   ��Ϸ�����߼���ȫ�����ڴ�ģ���У� ��Ҫ������
			   1����Ϸ���ݺ͵ȴ���������ݳ�ʼ��
			   2����Ϸ�����Ŀ��غʹ���
			   3�����ݵ���ײ���ʹ����������ݵ�λ�ã�
			   4����ײ�������ͬ���ݵ��㷨
			   5�����ݵ�����
			   6���������Ƿ����������ݵļ��
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

//��Ϸ�������� ���е��߼��ͱ��ֶ���������������
class GameScene : public cocos2d::Layer
{
public:
	GameScene();
	~GameScene();

public:
	//������ʾ
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