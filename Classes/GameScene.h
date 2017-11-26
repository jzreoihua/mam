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
#include "Bubble.h"
#include "BubbleConstant.h"
#include "Popinterface.h"
#include "ui/CocosGUI.h"
#include "mianSceneui.h"
#include <list>
#include <vector>

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocostudio::timeline;

typedef std::list<Bubble*> BUBBLE_LIST;
typedef std::list<RowCol>  ROWCOL_LIST;

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
	void setbubSpeed(int _bubSpeed);
	void addwaitcont();
	void setSpbubnum(int num,char *name);
	virtual bool TouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	virtual void TouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	virtual void TouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	void selectedItemEvent(Ref* pSender, cocos2d::ui::ListView::EventType type);
	void btncallFunc(Object *pSender, cocos2d::ui::Button::TouchEventType type);
	//CREATE_FUNC(GameScene);

private:
	
	Bubble* randomBubble(int Mos = 1);
	Bubble* createBubble(BUBBLE_COLOR color);
	
	void clear();

	bool initScheduler();
	bool initReadyBubble();
	bool initBoard();
	bool initWaitBubble();
	bool initMyian();				//初始化界面
	bool isCollisionWithBorder();	//是否和左右边缘碰撞
	bool iswinorsb();//是否成功;
	bool isCollisionWithTopBorder(Bubble *pBubble);	//是否和顶层边缘碰撞，
	bool isCollisionWithBubble(CCPoint pos1, float radius1, CCPoint pos2, float radius2);	//是否和上方的球碰撞
	bool isCollision(Bubble* m_curReady);	//是否碰撞，仅包括是否和上方所有的球碰撞和顶层边缘碰撞， 不包括和左右边缘碰撞
	void teshuList();
	void adjustBubblePosition(Bubble* _curReady);
	
	//查找需要清除的球的集合
	ROWCOL_LIST findClearBubble(Bubble *pReadyBubble);
	//找到同样的球，并返回找到的同样的球的集合
	ROWCOL_LIST findSameBubble(Bubble *pReadyBubble);
	//查找金银色球所对应的要消除的球的集合
	ROWCOL_LIST findGoldenBubble(Bubble *pReadyBubble);
	ROWCOL_LIST findSliveryBubble(Bubble* pReadyBubble);

	//根据调整过后的球的位置和颜色类型， 作出相应的处理，如：金银色特殊泡泡的爆炸，球的下落等
	void execClearBubble(Bubble* pReadyBubble);

	//清除球的集合
	void clearBubble(const ROWCOL_LIST &bubbleList);

	//清除一个球的表现动作
	void removeBubbleAction(Bubble* pBubble);
	

	ROWCOL_LIST checkFallBubble();
	//执行可以掉落的泡泡
	void FallBubble(const ROWCOL_LIST &fallBubbleList);
	//掉落泡泡
	void downBubbleAction(Bubble *pBubble);
	
	//将wait状态的球换成ready状态
	void changeWaitToReady();

	void setEnable();
	void setDisableEnable();

	inline bool hasBall(int row, int col)
	{
		return m_board[row][col] != NULL;
	}
//private:
//	GameState m_state;
private:
	FadeIn* yfadein;
	FadeOut* yfadeout;
	Node* rootNode;
	Sprite* chumoc;//触摸处
	Sprite* jiant1_3;//箭头
	Sprite* Default;
	ui::ListView* teVew;//特殊球列表
	Label* aimCount;
	Label* gNumCount;
	ui::Layout* Zgamec;
	Size size;
	EventListenerTouchOneByOne* touchListener;
	ScaleTo *targetScTo;
	bool isTouchOne;
	
	bool islistouch;

	bool iskeyiZtesbtn;
	Bubble* m_board[MAX_ROWS][MAX_COLS];		//整个面板所有能放的泡泡

	Bubble* m_wait[MAX_WAIT_BUBBLE];			//正在等待发射的泡泡队列

	Bubble* m_curReady;							//当前正要发射的泡泡
	Bubble* m_curReadyclone;
	BUBBLE_LIST m_listBubble;		//当前图上所有的球
	int bub_Speed;//自己的球飞行速度
	int rdhmbub;//关卡难度
	int adspeed;//加速度
	int Vitorynum;			//过关条件
	int fbnqsl;
	int m_waitcont;//MAX_WAITBUBCONT;//全部可用的球
	int sgm_waitcont;
	float m_dRadianclone;						//范围为30度为150;默认为90度， 竖直方向
	int m_nRotation;						//发射器角度改变方向，也是玩的反弹角度

	int m_nWidth;			//游戏界面的宽度和高度
	int m_nHeight;
	int m_nScore;			//游戏所得到的分数
	int strguankNum; //当前第几关
	int m_nGoldenBubbleCount;
	int m_nSliveryBubbleCount;
	
	Label* tesCount[3];
	
	GameState m_state;
	
	Point m_real;
	Point m_realclone;
};
#endif