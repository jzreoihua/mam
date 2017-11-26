/************************************************************************/
/* 
** Date  : 2013/10/4

** author: Bright Moon

** Note	 : 1����Ϸ��һЩ����������
		   2����Ϸ��һЩö�ٱ���������
		   3����Ϸ��һЩ���ýṹ�������
*/
/************************************************************************/

#ifndef _BUBBLE_CONSTANT_H_
#define _BUBBLE_CONSTANT_H_

#include <string>

#define PI					(3.14)
#define MENU_SPACE			(40)
#define BUBBLE_RADIUS		(30.8)
#define MAX_WAITBUBCONT			(30)
#define MAX_ROWS			(9)
#define MAX_COLS			(7)
#define INIT_LINE			(2)

#define MAX_WAIT_BUBBLE		(7)
#define BUBBLE_SPEED		(30)

#define READY_BUBBLE_POS	ccp(233.8,118.8)
#define WAIT_BUBBLE_POSY	(166.2)
#define REMOVE_COUNT		(3)
#define SILVERY_COUNT		(4)
#define GOLDEN_COUNT		(5)

//6����ͨ��ɫ���ơ��ϡ������졢�̡��ڣ��� ����������ɫ��������
enum BUBBLE_COLOR
{
	BUBBLE_YELLOW,
	BUBBLE_PURPLE,	//��ɫ
	BUBBLE_BULE,
	BUBBLE_RED,
	BUBBLE_GREEN,
	BUBBLE_BLACK,
	BUBBLE_FREE,
	BUBBLE_SILVERY,	//��ɫ
	BUBBLE_GOLDEN,	//��ɫ
	BUBBLE_GOLDEN1,
	BUBBLE_GOLDEN2,
	COLOR_COUNT	//������ɫ����
};

enum GameDirection 
{
	LEFT, 
	RIGHT,
	TOP_LEFT, 
	TOP_RIGHT,
	BOTTOM_LEFT, 
	BOTTOM_RIGHT, 
	DIRECTION_COUNT
};

enum GameState
{
	GS_START,
	GS_FLY,
	GS_FIXED,
	GS_FALL
};

static const std::string g_bubbleName[COLOR_COUNT] = 
{
	"bubble_0.png",
	"bubble_1.png",
	"bubble_6.png",
	"bubble_3.png",
	"bubble_4.png",
	"bubble_5.png",
	"bubble_9.png",
	"bubble_7.png",
	"bubble_tes1.png",
	"bubble_tes2.png",
	"bubble_tes3.png",
	//"bubble_7.png"
};

//��Ϸ���нṹ��ķ�װ
struct RowCol
{
	bool operator==( const RowCol & rPos ) const 
	{
		return m_nRow == rPos.m_nRow && m_nCol == rPos.m_nCol;
	}

	RowCol( int nRow, int nCol )
	{
		m_nRow = nRow;
		m_nCol = nCol;
	}
	int m_nRow;
	int m_nCol;
};

#endif	//_BUBBLE_CONSTANT_H_