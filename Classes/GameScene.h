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
	bool initMyian();				//��ʼ������
	bool isCollisionWithBorder();	//�Ƿ�����ұ�Ե��ײ
	bool iswinorsb();//�Ƿ�ɹ�;
	bool isCollisionWithTopBorder(Bubble *pBubble);	//�Ƿ�Ͷ����Ե��ײ��
	bool isCollisionWithBubble(CCPoint pos1, float radius1, CCPoint pos2, float radius2);	//�Ƿ���Ϸ�������ײ
	bool isCollision(Bubble* m_curReady);	//�Ƿ���ײ���������Ƿ���Ϸ����е�����ײ�Ͷ����Ե��ײ�� �����������ұ�Ե��ײ
	void teshuList();
	void adjustBubblePosition(Bubble* _curReady);
	
	//������Ҫ�������ļ���
	ROWCOL_LIST findClearBubble(Bubble *pReadyBubble);
	//�ҵ�ͬ�����򣬲������ҵ���ͬ������ļ���
	ROWCOL_LIST findSameBubble(Bubble *pReadyBubble);
	//���ҽ���ɫ������Ӧ��Ҫ��������ļ���
	ROWCOL_LIST findGoldenBubble(Bubble *pReadyBubble);
	ROWCOL_LIST findSliveryBubble(Bubble* pReadyBubble);

	//���ݵ�����������λ�ú���ɫ���ͣ� ������Ӧ�Ĵ����磺����ɫ�������ݵı�ը����������
	void execClearBubble(Bubble* pReadyBubble);

	//�����ļ���
	void clearBubble(const ROWCOL_LIST &bubbleList);

	//���һ����ı��ֶ���
	void removeBubbleAction(Bubble* pBubble);
	

	ROWCOL_LIST checkFallBubble();
	//ִ�п��Ե��������
	void FallBubble(const ROWCOL_LIST &fallBubbleList);
	//��������
	void downBubbleAction(Bubble *pBubble);
	
	//��wait״̬���򻻳�ready״̬
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
	Sprite* chumoc;//������
	Sprite* jiant1_3;//��ͷ
	Sprite* Default;
	ui::ListView* teVew;//�������б�
	Label* aimCount;
	Label* gNumCount;
	ui::Layout* Zgamec;
	Size size;
	EventListenerTouchOneByOne* touchListener;
	ScaleTo *targetScTo;
	bool isTouchOne;
	
	bool islistouch;

	bool iskeyiZtesbtn;
	Bubble* m_board[MAX_ROWS][MAX_COLS];		//������������ܷŵ�����

	Bubble* m_wait[MAX_WAIT_BUBBLE];			//���ڵȴ���������ݶ���

	Bubble* m_curReady;							//��ǰ��Ҫ���������
	Bubble* m_curReadyclone;
	BUBBLE_LIST m_listBubble;		//��ǰͼ�����е���
	int bub_Speed;//�Լ���������ٶ�
	int rdhmbub;//�ؿ��Ѷ�
	int adspeed;//���ٶ�
	int Vitorynum;			//��������
	int fbnqsl;
	int m_waitcont;//MAX_WAITBUBCONT;//ȫ�����õ���
	int sgm_waitcont;
	float m_dRadianclone;						//��ΧΪ30��Ϊ150;Ĭ��Ϊ90�ȣ� ��ֱ����
	int m_nRotation;						//�������Ƕȸı䷽��Ҳ����ķ����Ƕ�

	int m_nWidth;			//��Ϸ����Ŀ�Ⱥ͸߶�
	int m_nHeight;
	int m_nScore;			//��Ϸ���õ��ķ���
	int strguankNum; //��ǰ�ڼ���
	int m_nGoldenBubbleCount;
	int m_nSliveryBubbleCount;
	
	Label* tesCount[3];
	
	GameState m_state;
	
	Point m_real;
	Point m_realclone;
};
#endif