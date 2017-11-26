/************************************************************************/
/* 
**  Date   :   2013/9/21

** author  :   Bright Moon

** function:   游戏的主数据，全部放在此模块中

*/
/************************************************************************/

#ifndef _GAME_SHUJU_H_
#define _GAME_SHUJU_H_
#include <string>
//#include <cmath>
//#include <vector>
//#include <list>
//#include "Bubble.h"
//
//#include "cocos2d.h"
//#include "BubbleConstant.h"


//using namespace cocos2d;


/**********res.h声明全局变量************/
 





extern bool istanc;
extern bool ismicpalying;
extern bool iseffectpalying;
//extern std::string strguankNum;
extern int intes[3];
//
//static std::string stancm;
//class GameShuJu
//{
//public:
//	GameShuJu();
//	~GameShuJu();
//}
//void setNum(int obj);
//int getNum();
//inline int getNum()
//{
//	return tancNum;
//}
//inline void setNum(int obj_z)
//{
//	tancNum = obj_z;
//}
//class GameShuJu 
//{
//
////public:
//private:
//	Label* aimCount;
//
//	Size size;
//	EventListenerTouchOneByOne* touchListener;
//	bool isTouchOne;
//	Bubble* m_board[MAX_ROWS][MAX_COLS];		//整个面板所有能放的泡泡
//
//	Bubble* m_wait[MAX_WAIT_BUBBLE];			//正在等待发射的泡泡队列
//
//	Bubble* m_curReady;							//当前正要发射的泡泡
//
//	BUBBLE_LIST m_listBubble;		//当前图上所有的球
//	int m_waitcont = MAX_WAITBUBCONT;
//	double m_dRadian;						//范围为30度为150;默认为90度， 竖直方向
//	int m_nRotation;						//发射器角度改变方向，也是玩的反弹角度
//
//	int m_nWidth;			//游戏界面的宽度和高度
//	int m_nHeight;
//
//	int m_nScore;			//游戏所得到的分数
//	int sceneNum;
//	int m_nGoldenBubbleCount;
//	int m_nSliveryBubbleCount;
//
//	GameState m_state;
//
//	Point m_real;
//	friend class Popinterface;
//};
#endif