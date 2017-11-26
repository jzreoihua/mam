#include "Bubble.h"


Bubble::Bubble()
{
	
}

Bubble::~Bubble()
{
}



bool Bubble::init()
{
	m_color = COLOR_COUNT;
	m_nRowIndex = -1;
	m_nColIndex = -1;
	
	step = 0;
	this->schedule(schedule_selector(Bubble::loop), 1.0f);
	this->setScale(0.988);

	return true;
}


void Bubble::loop(float){
	step++;
	
	if (step >5+rand()%5){
		step = 0;
		
		runbubtion();
	}
}
void Bubble::setBubbleColor(BUBBLE_COLOR color)
{
	m_color = color;
	
	
}

BUBBLE_COLOR Bubble::getBubbleColor()
{
	return m_color;
}

void Bubble::setRowIndex(int row)
{
	m_nRowIndex = row;
}

int Bubble::getRowIndex()
{
	return m_nRowIndex;
}

void Bubble::setColumnIndex(int col)
{
	m_nColIndex = col;
}

int Bubble::getColumnIndex()
{
	return m_nColIndex;
}

BUBBLE_COLOR Bubble::randomColor()
{
	m_color= static_cast<BUBBLE_COLOR>(rand() % COLOR_COUNT);
	return m_color;
}
void Bubble::runbubtion(){
	
	
	auto animation = Animation::create();
	std::string s;
	for (int i = 2; i<10; i++)
	{
		s = g_bubbleName[getBubbleColor()].substr(0, 8);

		char szName[100] = { 0 };
		sprintf(szName, "bubdonghua/%s%d.png", s.c_str(), i);
		//if ((fopen(szName, "rb")) != NULL)
		animation->addSpriteFrameWithFile(szName);


	}

	// should last 2.8 seconds. And there are 14 frames. 
	animation->setDelayPerUnit(0.128f);
	//animation->setLoops(2);
	animation->setRestoreOriginalFrame(true);

	auto action = Animate::create(animation);
	this->runAction(action);
	//this->stopAction(action);
	  //∑¥œÚaction->reverse()À≥–Ú÷¥––Sequence”¿‘∂RepeatForever::create(
}