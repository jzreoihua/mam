#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <cmath>
#include <vector>
#include <list>

#include "cocos2d.h"
#include "BubbleConstant.h"


using namespace cocos2d;


static Size size;

void setZgamecSize(Size obj_z);
Point getPosByRowAndCol(int row, int col);
RowCol GetRowColByPos( int nPosX, int nPosY);

bool IsValidPos( int nRow, int nCol );
bool IsValidPos(RowCol nRownCol);
void GetAround( int nRow, int nCol, std::vector<RowCol> & vecRowCol );

//得到整条斜线上球的集合，分为左右斜线之分，左斜线代表从左上角到右下角， 右斜线代表从右上角到左下角,由mode值来区分
void GetGoldenLine (int nRow, int nCol, ROWCOL_LIST& listRowCol);
void GetSliveryLine(int nRow, int nCol, ROWCOL_LIST& listRowCol);

inline void setZgamecSize(Size obj_z)
{
	//Size obj_z = obj->getContentSize();

	size = obj_z;
}

inline Point getPosByRowAndCol(int row, int col)
{
	float posX, posY;

	//CCSize size = CCDirector::sharedDirector()->getWinSize();

	posX = col * 2 * BUBBLE_RADIUS + BUBBLE_RADIUS + (row % 2) * BUBBLE_RADIUS;
	posY = size.height - ( row * 2 * BUBBLE_RADIUS * sin(PI/3) + BUBBLE_RADIUS );

	return Vec2(posX, posY);
}

inline RowCol GetRowColByPos(int nPosX, int nPosY)
{
	int nRow, nCol;
	//需要四舍五入

	//nPosY = CCDirector::sharedDirector()->getWinSize().height - nPosY;//这个是距离上方的坐标
	nPosY = size.height - nPosY;
	nRow = ( nPosY -BUBBLE_RADIUS )/( 2 *BUBBLE_RADIUS *sin ( PI/3 ) ) +0.5;//计算球垂直方向位置

	nCol = (nPosX - (nRow % 2) * BUBBLE_RADIUS - BUBBLE_RADIUS) * 1.0 / (2 * BUBBLE_RADIUS) + 0.5; //计算球水平方向位置

	return RowCol( nRow, nCol );
}

//@获得周围停靠位置的列表nRow,nCol为要计算的停靠位置，vecPos返回它周围的位置
inline void GetAround(int nRow, int nCol, std::vector<RowCol> & vecPos)
{
	if (!IsValidPos(nRow, nCol))
	{
		return;
	}

	//同一行
	if (IsValidPos(nRow, nCol - 1))
	{
		vecPos.push_back(RowCol(nRow, nCol - 1));
	}
	if (IsValidPos(nRow, nCol + 1))
	{
		vecPos.push_back(RowCol(nRow, nCol + 1));
	}

	//左斜线
	if (IsValidPos(nRow - 1, nCol))
	{
		vecPos.push_back(RowCol(nRow - 1, nCol));
	}
	if (IsValidPos(nRow + 1, nCol))
	{
		vecPos.push_back(RowCol(nRow + 1, nCol));
	}

	//如果是单行
	int curCol;
	if (nRow % 2 == 0)
		curCol = nCol - 1;
	else
		curCol = nCol + 1;

	//右斜线
	if (IsValidPos(nRow - 1, curCol))
	{
		vecPos.push_back(RowCol(nRow - 1, curCol));
	}
	if (IsValidPos(nRow + 1, curCol))
	{
		vecPos.push_back(RowCol(nRow + 1, curCol));
	}

}

inline void GetGoldenLine(int nRow, int nCol, ROWCOL_LIST& listRowCol)
{		
	if (!IsValidPos(nRow, nCol))
		return;

	RowCol nextRowCol(nRow,nCol);
	bool nextFlag = false;
	
	listRowCol.push_back(nextRowCol);
	
	//左上角
	do 
	{
		if (nextRowCol.m_nRow % 2 == 0)
		{
			nextRowCol.m_nRow -= 1;
			nextRowCol.m_nCol -= 1;
		}
		else
		{
			nextRowCol.m_nRow -= 1;
		}

		if (IsValidPos(nextRowCol))
		{
			listRowCol.push_back(nextRowCol);
			nextFlag = true;
		}
		else
		{
			nextFlag = false;
		}
	} while (nextFlag);

// 	右下角
	nextRowCol.m_nRow = nRow;
	nextRowCol.m_nCol = nCol;
	do 
	{
		if (nextRowCol.m_nRow % 2 == 0)
		{
			nextRowCol.m_nRow += 1;
		}
		else
		{
			nextRowCol.m_nRow += 1;
			nextRowCol.m_nCol += 1;
		}
	
		if (IsValidPos(nextRowCol))
		{
			listRowCol.push_back(nextRowCol);
			nextFlag = true;
		}
		else
		{
			nextFlag = false;
		}
	} while (nextFlag);

	//同一行
	nextRowCol.m_nRow = nRow;
	nextRowCol.m_nCol = -1;
	do 
	{
		nextRowCol.m_nCol += 1;
	
		if (IsValidPos(nextRowCol))
		{
			listRowCol.push_back(nextRowCol);
			nextFlag = true;
		}
		else
		{
			nextFlag = false;
		}
	} while (nextFlag);
// 	
	//右上角
	nextRowCol.m_nRow = nRow;
	nextRowCol.m_nCol = nCol;
	do 
	{
		if (nextRowCol.m_nRow % 2 == 0)
		{
			nextRowCol.m_nRow -= 1;
		}
		else
		{
			nextRowCol.m_nRow -= 1;
			nextRowCol.m_nCol += 1;
		}
	
		if (IsValidPos(nextRowCol))
		{
			listRowCol.push_back(nextRowCol);
			nextFlag = true;
		}
		else
		{
			nextFlag = false;
		}
	} while (nextFlag);
	
	//左下角
	nextRowCol.m_nRow = nRow;
	nextRowCol.m_nCol = nCol;
	do 
	{
		if (nextRowCol.m_nRow % 2 == 0)
		{
			nextRowCol.m_nRow += 1;
			nextRowCol.m_nCol -= 1;
		}
		else
		{
			nextRowCol.m_nRow += 1;
		}
	
		if (IsValidPos(nextRowCol))
		{
			listRowCol.push_back(nextRowCol);
			nextFlag = true;
		}
		else
		{
			nextFlag = false;
		}
	} while (nextFlag);

}

inline void GetSliveryLine(int nRow, int nCol, ROWCOL_LIST& listRowCol)
{
	if (!IsValidPos(nRow, nCol))
		return;

	RowCol nextRowCol(nRow,nCol);
	bool nextFlag = false;

	listRowCol.push_back(nextRowCol);

	//左上角
	do 
	{
		if (nextRowCol.m_nRow % 2 == 0)
		{
			nextRowCol.m_nRow -= 1;
			nextRowCol.m_nCol -= 1;
		}
		else
		{
			nextRowCol.m_nRow -= 1;
		}

		if (IsValidPos(nextRowCol))
		{
			listRowCol.push_back(nextRowCol);
			nextFlag = true;
		}
		else
		{
			nextFlag = false;
		}
	} while (nextFlag);

	//同一行
	nextRowCol.m_nRow = nRow;
	nextRowCol.m_nCol = -1;
	do 
	{
		nextRowCol.m_nCol += 1;

		if (IsValidPos(nextRowCol))
		{
			listRowCol.push_back(nextRowCol);
			nextFlag = true;
		}
		else
		{
			nextFlag = false;
		}
	} while (nextFlag);

	//右上角
	nextRowCol.m_nRow = nRow;
	nextRowCol.m_nCol = nCol;
	do 
	{
		if (nextRowCol.m_nRow % 2 == 0)
		{
			nextRowCol.m_nRow -= 1;
		}
		else
		{
			nextRowCol.m_nRow -= 1;
			nextRowCol.m_nCol += 1;
		}

		if (IsValidPos(nextRowCol))
		{
			listRowCol.push_back(nextRowCol);
			nextFlag = true;
		}
		else
		{
			nextFlag = false;
		}
	} while (nextFlag);
}

//@一个位置是否有效的停靠点
inline bool IsValidPos(int nRow, int nCol)
{
	if (nRow < 0 || nCol < 0)
	{
		return false;
	}
	if (nRow >= MAX_ROWS || nCol >= MAX_COLS - nRow % 2)
	{
		return false;
	}

	return true;
}

inline bool IsValidPos(RowCol nRownCol)
{
	return IsValidPos(nRownCol.m_nRow, nRownCol.m_nCol);
}


#endif	//_UTILITY_H_