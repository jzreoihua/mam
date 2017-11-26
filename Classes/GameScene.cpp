#include "GameScene.h"
#include "Utility.h"
#include "mianSceneui.h"
#include "Inputrd.h"
#include <algorithm>
#include "Gameduihua.h"
//#include "Esintc.h"

GameScene::GameScene()/*:
	m_state(GS_START),
	m_nGoldenBubbleCount(0),
	m_nSliveryBubbleCount(0),
	m_nScore(0)*/
{
	if (UserDefault::getInstance()->getBoolForKey("ismicpalying"))
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("game_scene_bg.mp3",true);
	srand(time(NULL));
}

GameScene::~GameScene()
{
	//clear();
}

Scene* GameScene::scene(int gknum)
{
	Scene* scene = NULL;
	do 
	{
		scene = Scene::create();
		CC_BREAK_IF(!scene);

		//GameScene* layer = GameScene::create();
		GameScene* layer = new GameScene();
		if (layer && layer->init(gknum))
		{

			layer->autorelease();
		}
		else
		{
			delete layer;
			layer = NULL;
			return NULL;
		}
		CC_BREAK_IF(!layer);

		scene->addChild(layer);

	} while (0);

	return scene;
}

bool GameScene::init(int gknum)
{
	bool bRet = false;
	do 
	{
		strguankNum = gknum;
		//CC_BREAK_IF(!CCLayer::init());
		
		//加载背景
		/*CCSprite* pSprite = CCSprite::create("gamebg.png");
		CC_BREAK_IF(!pSprite);
		pSprite->setPosition(Point::ZERO);
		this->addChild(pSprite, 0);*/
		
		/*ui::Layout* l = (ui::Layout*) rootNode->getChildByName("gamec");
		l->setClippingEnabled(true);*///设置裁剪
		//ClippingNode* clippingNode = ClippingNode::create();
		//clippingNode->setPosition(rootNode->getChildByName("gamec")->getPosition());
		//this->addChild(clippingNode);

		//clippingNode->setAlphaThreshold(0.05f); //设置alpha闸值  
		//clippingNode->setContentSize(rootNode->getChildByName("gamec")->getContentSize()); //设置尺寸大小  

		//clippingNode->setStencil(rootNode->getChildByName("gamec"));   //设置模板stencil  
		//clippingNode->addChild(rootNode->getChildByName("gamec"), 1);  //先添加标题,会完全显示出来,因为跟模板一样大小  
		////clippingNode->addChild(spark, 2);

		
		CC_BREAK_IF(!GameScene::initMyian());
		CC_BREAK_IF(!GameScene::initScheduler());
		CC_BREAK_IF(!GameScene::initBoard());
		CC_BREAK_IF(!GameScene::initReadyBubble());
		CC_BREAK_IF(!GameScene::initWaitBubble());
	/*	auto ly = mianSceneui::create();
		ly->setPosition(Point::ZERO);
		ly->setAnchorPoint(Point::ZERO);
		ly->setguankNum(strguankNum);
		this->addChild(ly);*/

		//auto Inputwordly = (Inputrd*)Inputrd::create(strguankNum);
		//Inputwordly->setPosition(Point::ZERO);
		//Inputwordly->setAnchorPoint(Point::ZERO);
		////Inputwordly->setguankNum(strguankNum);
		//this->addChild(Inputwordly);
		auto Inputwordly = Gameduihua::create();
		Inputwordly->setPosition(Point::ZERO);
		Inputwordly->setAnchorPoint(Point::ZERO);
		//Inputwordly->setguankNum(strguankNum);
		this->addChild(Inputwordly);
		bRet = true;

	} while (0);

	return bRet;
}
//复活
void GameScene::vtory(){
	
	_eventDispatcher->resumeEventListenersForTarget(chumoc);
	m_waitcont = UserDefault::getInstance()->getIntegerForKey("waitcont");
	std::string strm_waitcont = String::createWithFormat("%d", m_waitcont)->_string;
	aimCount->setString(strm_waitcont);
	initReadyBubble();
	initWaitBubble();


}
void GameScene::addwaitcont(){
	m_waitcont++;
	std::string strm_waitcont = String::createWithFormat("%d", m_waitcont)->_string;
	aimCount->setString(strm_waitcont);
}
void GameScene::setbubSpeed(int _bubSpeed){
	bub_Speed=_bubSpeed;
}

void GameScene::setSpbubnum(int num, char *name){
	if (name == "spbub3"){
		if (num>intes[2])
			UserDefault::getInstance()->setIntegerForKey("spbub3", num);
		intes[2] = num;
		std::string strintes2 = String::createWithFormat("%d", intes[2])->_string;
		
		tesCount[2]->setString(strintes2);
	}
	else if (name == "spbub2"){
		if (num>intes[1])
			UserDefault::getInstance()->setIntegerForKey("spbub2", num);
		intes[1] = num;
		std::string strintes2 = String::createWithFormat("%d", intes[1])->_string;

		tesCount[1]->setString(strintes2);
	}
	else {
		if (num>intes[0])
			UserDefault::getInstance()->setIntegerForKey("spbub", num);
		intes[0] = num;
		std::string strintes2 = String::createWithFormat("%d", intes[0])->_string;
		//tesCount[0] = Label::createWithCharMap("tes_num.png", 15, 25, '0');
		tesCount[0]->setString(strintes2);
	}
}
//游戏结算
void GameScene::vjiesuan(int i){
	unschedule(schedule_selector(GameScene::loop));
	auto ly = (Popinterface*)Popinterface::create(i);
	ly->setPosition(Point::ZERO);
	ly->setAnchorPoint(Point::ZERO);
	ly->setguankNum(strguankNum);
	this->addChild(ly);
}
bool GameScene::initMyian(){
	bool bRet = false;
	do
	{
		istanc = false;
		intes[0] = UserDefault::getInstance()->getIntegerForKey("spbub");
		intes[1] = UserDefault::getInstance()->getIntegerForKey("spbub2");
		intes[2] = UserDefault::getInstance()->getIntegerForKey("spbub3");
		int f1 = 0, f2 = 1, t;
		for (int n = 0; n < strguankNum; n++){
			t = f2;
			f2 = f1 + f2;
			f1 = t;
			
		}
		fbnqsl = f2;
		int ggNum = strguankNum;
		rdhmbub = fbnqsl / 300 + ggNum * 8;
		
		Vitorynum = 21 + ggNum;//过关条件框里剩余球总数
		log("shengyu is %d", Vitorynum);
		
		adspeed = 1;
		this->setName("gameScene");

		rootNode = CSLoader::createNode("csb/MainScene.csb");
		rootNode->setPosition(Point::ZERO);
		rootNode->setAnchorPoint(Point::ZERO);
		this->addChild(rootNode);
		
		jiant1_3 = (Sprite*) rootNode->getChildByName("jiant1_3");
		Default = (Sprite*)rootNode->getChildByName("Default");
		Zgamec = (ui::Layout*) rootNode->getChildByName("gamec");
		size = Zgamec->getContentSize();
		setZgamecSize(size);
		
		bub_Speed = UserDefault::getInstance()->getIntegerForKey("bub_Speed");//飞行速度
		//我的球数标签
		m_waitcont = UserDefault::getInstance()->getIntegerForKey("waitcont");
		std::string strm_waitcont = String::createWithFormat("%d", m_waitcont)->_string;
	;
		aimCount = Label::createWithCharMap("aim_number.png", 23, 40, '0');

		aimCount->setPosition(43.4, 109.8);
		rootNode->addChild(aimCount, 1);
		aimCount->setString(strm_waitcont);

		//std::string strguankNum = String::createWithFormat("%d", guankNum)->_string;
		//关卡标签
		gNumCount = Label::createWithCharMap("res/finalstatement_rank_num.png", 17, 24, '0');

		gNumCount->setPosition(45.4, 752);
		rootNode->addChild(gNumCount, 1);
		gNumCount->setString(std::to_string(strguankNum));
		

		auto* yanj = Sprite::create("yanj.png");
		yanj->setPosition(263.0, 753.8);


		addChild(yanj);
		yanj->setOpacity(0);

		yfadein = FadeIn::create((Vitorynum - m_listBubble.size()) / 6.0);
		yfadeout = FadeOut::create((Vitorynum - m_listBubble.size()) / 6.0);
		auto yjact = RepeatForever::create(Sequence::create(
			yfadein,
			yfadeout,
			NULL
			));
		yanj->runAction(yjact);
		/*yanj->runAction(yjact);
		yfadein->setDuration((Vitorynum - m_listBubble.size()) / 6.0);
		
		yfadeout->setDuration((Vitorynum - m_listBubble.size()) / 6.0);
		auto yjact = RepeatForever::create(Sequence::create(
			yfadein,
			yfadeout,
			NULL
			));
		yanj->runAction(yjact);*/

		touchListener = EventListenerTouchOneByOne::create();
		touchListener->setSwallowTouches(true);
		touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::TouchBegan, this);
		touchListener->onTouchMoved = CC_CALLBACK_2(GameScene::TouchMoved, this);
		touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::TouchEnded, this);

		//_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), rootNode->getChildByName("gamec"));

		//可戳地
		chumoc = (Sprite*)rootNode->getChildByName("chumoc");
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), chumoc);
		
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), rootNode->getChildByName("notouch"));
		
		teVew = (ui::ListView*)rootNode->getChildByName("teVew");
		
		teVew->setScrollBarEnabled(false);
		for (int i = 1; i <= 3; i++){
			std::string tesname = String::createWithFormat("tes%d", i)->_string;
			auto tes = (ui::Button*)teVew->getChildByName(tesname.c_str());
			tes->addTouchEventListener(CC_CALLBACK_2(GameScene::btncallFunc, this));
			if (!tes->getChildrenCount()){
				tesCount[i - 1] = Label::createWithCharMap("tes_num.png", 15, 25, '0');
				tes->addChild(tesCount[i - 1]);
			}
			std::string strintes = String::createWithFormat("%d", intes[i - 1])->_string;
			tesCount[i - 1]->setString(strintes);
			tesCount[i - 1]->setPosition(tes->getContentSize().width - tesCount[i - 1]->getContentSize().width / 1.68, 20);
		}
		//暂停按钮
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), rootNode->getChildByName("pusebtn"));
		//特殊球按钮
		iskeyiZtesbtn = false;
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), rootNode->getChildByName("Ztesbtn"));

		this->runAction(Sequence::create(
			DelayTime::create(0.88f),
			CallFunc::create([=](){
			iskeyiZtesbtn = true;
			_eventDispatcher->pauseEventListenersForTarget(rootNode->getChildByName("notouch"));		
		}
			),
			NULL));
		//_eventDispatcher->pauseEventListenersForTarget(rootNode->getChildByName("notouch"));
		//_eventDispatcher->resumeEventListenersForTarget(rootNode->getChildByName("notouch"));
		this->setEnable();
		//_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), this);
		bRet = true;
	} while (0);
	return bRet;
}
bool GameScene::initScheduler()
{
	
	this->schedule(schedule_selector(GameScene::loop), 1.0f);
	//this->scheduleUpdate();
	return true;
}

//初始化泡泡队列，
bool GameScene::initBoard()
{
	bool bRet = false;
	do 
	{
		
		for (int row = 0; row < MAX_ROWS; row++)
		{
			for (int col = 0; col < MAX_COLS - row % 2; col++)
			{
				//初始化前INIT_LINE行， 其他行为NULL

				
				
				if (rand() % 1000 > rdhmbub&&row < INIT_LINE){
					
					Bubble* pBubble = randomBubble(0);
					if (pBubble == NULL)
					{
						CC_BREAK_IF(!pBubble);
					}
					pBubble->setPosition(getPosByRowAndCol(row, col));
					Zgamec->addChild(pBubble);

					m_board[row][col] = pBubble;
					m_board[row][col]->setRowColIndex(row, col);
					m_listBubble.push_back(pBubble);


				}
				else{
					m_board[row][col] = NULL;
					continue;
				}
				bRet = true;
			}
		}
	} while (0);

	return bRet;
}

//初如化泡泡发射器
bool GameScene::initReadyBubble()
{
	bool bRet = false;
	do 
	{
		m_curReady = randomBubble();
		CC_BREAK_IF(!m_curReady);

		//Size size = Director::getInstance()->getVisibleSize();
		m_curReady->setPosition(READY_BUBBLE_POS);
		m_curReady->setOpacity(168);
		this->addChild(m_curReady);

		bRet = true;
	} while (0);

	return bRet;
}

bool GameScene::initWaitBubble()
{
	bool bRet = false;
	do 
	{
		for (int i = 0; i < MAX_WAIT_BUBBLE; i++)
		{
			Bubble *pBubble = randomBubble();
			CC_BREAK_IF(!pBubble);

			//Size size = Director::getInstance()->getVisibleSize();
			pBubble->setPosition(ccp((i+1) * BUBBLE_RADIUS * 2,WAIT_BUBBLE_POSY));
			m_wait[i] = pBubble;
			Default->addChild(pBubble);

			bRet = true;
		}
	} while (0);

	return bRet;
}
Bubble* GameScene::randomBubble(int Mos)
{
	BUBBLE_COLOR color = static_cast<BUBBLE_COLOR>(rand() % (COLOR_COUNT-1-3/* - 2*/));
	if (Mos){
		
		CCLOG("rdhmbub is %d", rdhmbub);
		if (rand() % 1000 < rdhmbub){
			color = static_cast<BUBBLE_COLOR>(COLOR_COUNT - 1-3);
		}
	}
	Bubble *pBubble = NULL;
	do 
	{
		pBubble = Bubble::create();

		if(pBubble && pBubble->initWithFile(g_bubbleName[color].c_str()))
		{
			pBubble->setBubbleColor(color);
			
			log("getBubbleColor is %d", pBubble->getBubbleColor());//启动计时器

		}
		else
		{
			CC_SAFE_DELETE(pBubble);
		}
	} while (0);

	return pBubble;
}

Bubble* GameScene::createBubble(BUBBLE_COLOR color)
{
	Bubble *pBubble = NULL;
	do 
	{
		pBubble = Bubble::create();

		if(pBubble && pBubble->initWithFile(g_bubbleName[color].c_str()))
		{
			pBubble->setBubbleColor(color);
		}
		else
		{
			CC_SAFE_DELETE(pBubble);
		}
	} while (0);

	return pBubble;
}

void GameScene::clear()
{
	//ROWCOL_LIST samelist;
	
	for (int nRow = 0; nRow < MAX_ROWS; nRow++)
	{
		for (int nCol = 0; nCol < MAX_COLS - nRow % 2; nCol++)
		{
			Bubble *obj = m_board[nRow][nCol];
			obj->removeFromParent();
			m_board[nRow][nCol] = NULL;
		}
	}
	//clearBubble(samelist);
	m_listBubble.clear();
}

bool GameScene::isCollisionWithBorder()	//是否和边缘碰撞
{
	//Size size = Director::getInstance()->getVisibleSize();
	Point pos = m_curReady->getPosition();

	if (pos.x < BUBBLE_RADIUS || pos.x > size.width - BUBBLE_RADIUS)
	{
		return true;
	}

	return false;
}

bool GameScene::isCollisionWithTopBorder(Bubble *pBubble)
{
	if (pBubble == NULL)
	{
		return false;
	}

	Point pos = pBubble->getPosition();
	//Size size = Director::getInstance()->getVisibleSize();
	if (pos.y > size.height - BUBBLE_RADIUS)
	{
		return true;
	}

	return false;
}

bool GameScene::isCollisionWithBubble(CCPoint pos1, float radius1, CCPoint pos2, float radius2)	//是否和上方的球碰撞
{
	return pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2) < pow(radius1 + radius2, 2);	//判断两圆是否相交, 公式：（x1-x2)^2 + (y1-y2)^2 < (r1 + r2)^2
}

bool GameScene::isCollision(Bubble* m_curReady)
{
	bool bRet = false;

	if (m_curReady->getPosition().y > size.height - BUBBLE_RADIUS)
	{
		bRet = true;
		return bRet;
	}

	for (BUBBLE_LIST::reverse_iterator iterBubble = m_listBubble.rbegin(); iterBubble != m_listBubble.rend(); ++iterBubble)
	{
		Bubble *pBubble = *iterBubble;
		
		if (pBubble && isCollisionWithBubble(pBubble->getPosition(), BUBBLE_RADIUS, m_curReady->getPosition(), BUBBLE_RADIUS))
		{
			bRet = true;
			return bRet;
		}
	}

	return bRet;
}

void GameScene::setEnable()
{
	////CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	isTouchOne = true;
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void GameScene::setDisableEnable()
{
	//CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	//_eventDispatcher->removeEventListenersForTarget(this);
	//_eventDispatcher->removeAllEventListeners();
	isTouchOne = false;
}

bool GameScene::TouchBegan(Touch* pTouch, Event* pEvent)
{
	
	auto target = static_cast<Sprite*>(pEvent->getCurrentTarget());//ªÒ»°µƒµ±«∞¥•√˛µƒƒø±Í  

	Point locationInNode = target->convertToNodeSpace(pTouch->getLocation());
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);

	if (rect.containsPoint(locationInNode)) {
		if (target->getName() != "chumoc"){
			targetScTo = ScaleTo::create(0.174f, 1.0928f);
			target->runAction(targetScTo);
		}
		
		return true;
	}
	else {
		return false;
	};
	
}

void GameScene::TouchMoved(Touch* pTouch, Event* pEvent)
{
	auto target = static_cast<Sprite*>(pEvent->getCurrentTarget());
	if (target->getName() == "chumoc"){
		
		Point pos = pTouch->getLocation();
		
		int offRealX = pos.x - jiant1_3->getPosition().x;
		int offRealY = pos.y - jiant1_3->getPosition().y;
		float cocosAngle = atan2(offRealX, offRealY) * 180 / PI;
		/*float angleRadians = atanf((float)offRealY / (float)offRealX);
		float angleDegrees = CC_RADIANS_TO_DEGREES(angleRadians);
		
		float cocosAngle = -1 * angleDegrees;
		cocosAngle = cocosAngle>0 ? cocosAngle - 90 : cocosAngle + 90;*/
		if (cocosAngle< 65 && cocosAngle>- 65){
			jiant1_3->setRotation(cocosAngle);
			log("cocosAngle is %f", cocosAngle);
		}
	}
}

void GameScene::TouchEnded(Touch* pTouch, Event* pEvent)
{
	auto target = static_cast<Sprite*>(pEvent->getCurrentTarget()); 
	if (target->getName() != "chumoc"){

		auto targetScTo2 = ScaleTo::create(0.117f, 1.0f);
		target->stopAction(targetScTo);
		target->runAction(targetScTo2);
	}
	Point locationInNode = target->convertToNodeSpace(pTouch->getLocation());
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);

	if (rect.containsPoint(locationInNode)) { 
		//auto name = String::createWithFormat("%s2", i)->_string;
	 if (target->getName() == "chumoc"){
		 if (isTouchOne){
			 m_state = GS_FLY;
			 Point pos = pTouch->getLocation();
			 m_real = ccpNormalize(ccpSub(pos, m_curReady->getPosition()));
			 log("m_real is=%f%f", m_real.y,m_real.x);
			 int offRealX = pos.x - jiant1_3->getPosition().x;
			 int offRealY = pos.y - jiant1_3->getPosition().y;
			 float cocosAngle = atan2(offRealX, offRealY) * 180 / PI;
	
			 if (cocosAngle< 65 && cocosAngle>-65){
				 jiant1_3->setRotation(cocosAngle);
				 log("cocosAngle is %f", cocosAngle);
			 }

			 Rect mrect = Rect(0, 0, m_curReady->getContentSize().width, m_curReady->getContentSize().height);
			 SpriteFrame *msFrame = SpriteFrame::create(g_bubbleName[m_curReady->getBubbleColor()].c_str(), mrect);
			 m_curReady->setSpriteFrame(msFrame);
			 m_curReady->retain();
			 m_curReady->removeFromParent();
			 Zgamec->addChild(m_curReady);

			 Vec2 jiantcd = Vec2( m_real.x * 122, m_real.y * 122);
			 m_curReady->unschedule(schedule_selector(Bubble::loop));
			 m_curReady->setOpacity(255);

			 m_curReady->setPosition(m_curReady->getPosition().x - Zgamec->getPosition().x + jiantcd.x, m_curReady->getPosition().y - Zgamec->getPosition().y + jiantcd.y);
			
			 adspeed += 0.1;
			
			 if (m_curReady->getBubbleColor()<COLOR_COUNT-3){
				m_waitcont > 0 ? m_waitcont-- : NULL;//log("%d", m_waitcont);//
			 }
			 else if (m_curReady->getBubbleColor() == BUBBLE_GOLDEN){

				 m_curReadyclone = createBubble(m_curReady->getBubbleColor());
				 m_curReadyclone->unschedule(schedule_selector(Bubble::loop));
				 m_curReadyclone->setPosition(m_curReady->getPosition());
				 Zgamec->addChild(m_curReadyclone);
				 if (abs(m_real.x )< 0.1){
					 m_realclone.x += 0.118;
					 m_realclone.y = m_real.y;
				 }
				 else
					 m_realclone = m_real;
				 schedule([=](float dt){
					 if (isCollisionWithBorder())
					 {
						 m_realclone.x = -m_realclone.x;
					 }


					 Point pos = m_curReadyclone->getPosition();
					 log("m_curReadyclone%f,%f", pos.x, pos.y);
					 //m_curReadyclone->setPosition(ccp(pos.x + cos(m_dRadianclone)* (-bub_Speed), pos.y - sin(-m_dRadianclone) * bub_Speed));
					 m_curReadyclone->setPosition(ccp(pos.x - m_realclone.x * bub_Speed, pos.y + m_realclone.y * bub_Speed));


					 


					 if (isCollision(m_curReadyclone))	//如果和球或者上边缘碰撞了， 做相应的处理
					 {

						 adjustBubblePosition(m_curReadyclone);

						 //根据同样的球数量作出相应的清理处理
						 execClearBubble(m_curReadyclone);
						 //清除球之后，掉落处于悬挂状态的球
						 ROWCOL_LIST fallList = checkFallBubble();
						 FallBubble(fallList);
						 //判断符合成功或失败弹窗
						 iswinorsb();

						
						 unschedule("stop");
					 }

						 
						 

				 }, "stop");
			 }
			
			 std::string strm_waitcont = String::createWithFormat("%d", m_waitcont)->_string;
			 aimCount->setString(strm_waitcont);
			
			 setDisableEnable();
			 this->scheduleUpdate();
		 }
			//disappear();
		}
		
		else if (target->getName() == "pusebtn"){
			SimpleAudioEngine::getInstance()->playEffect("ui_eff.wav");
			if (!istanc){
				istanc = true;
				vjiesuan(2);
			
			}
			//disappear();
		}
		else if (target->getName() == "Ztesbtn"&&iskeyiZtesbtn){
			SimpleAudioEngine::getInstance()->playEffect("uibtn_eff.wav");
			teshuList();
			
			
		}
		else if (target->getName() == "zhucaid"){
			log("zhucaid");


		}
		
		else if (target->getName() == "notouch"){
			if (teVew->isVisible()){

				teVew->setVisible(false);
				_eventDispatcher->removeEventListenersForTarget(teVew);
				_eventDispatcher->pauseEventListenersForTarget(rootNode->getChildByName("notouch"));
			}
			


		}
		
	}


}
void GameScene::selectedItemEvent(Ref* pSender, cocos2d::ui::ListView::EventType type)
{
	ui::ListView* listView = static_cast<ui::ListView*>(pSender);
	ui::Button *button;
	switch (type)
	{
	
	case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_START:
	{
																	

																	
																	 button = (ui::Button*)listView->getItem(listView->getCurSelectedIndex());
																	 //button->setScale(0.9);
																	 //ui::Button *button = static_cast<ui::Button*>(item->getChildByTag(1));
																	 //auto btn=(Sprite*)listView->getItem(listView->getCurSelectedIndex()+1);
																	 //button->runAction(Sequence::create(targetScTo, targetScTo2));
																	 //log("button = %s", button->getName().c_str());
																	 islistouch = false;
																	 CC_UNUSED_PARAM(listView);
																	 CCLOG("select child start index = %ld", listView->getCurSelectedIndex());
																	 break;
	}
	case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_END:
	{
																   SimpleAudioEngine::getInstance()->playEffect("uibtn_eff.wav");
																   islistouch = true;
																   CC_UNUSED_PARAM(listView);
																   CCLOG("select child end index = %ld", listView->getCurSelectedIndex());
																   break;
	}
	default:
		
		break;
	}
}
void GameScene::loop(float dt)
{
	//int rdoneEmy = fbnqsl;//第一行消失的速度正比
	
	adspeed += 108;
	if (adspeed > 5388 - rdhmbub){
	
		adspeed = 0;
		ROWCOL_LIST samelist;
		int row = 0;
		int col;
		for (col = 0; col < MAX_COLS; col++)
		{
			//初始化前INIT_LINE行， 其他行为NULL

			samelist.push_back(RowCol(row, col));
		}
		
		//pBubble->setPosition(getPosByRowAndCol(row, col));
		if (samelist.empty()){
			
			//unschedule(schedule_selector(GameScene::loop));
			return;
		}
		SimpleAudioEngine::getInstance()->playEffect("xishou_eff.wav");
		clearBubble(samelist);
		this->runAction(
			Sequence::create(
			DelayTime::create(0.88f),
			CallFunc::create([=](){
			for (int row = 1; row < MAX_ROWS; row++)
			{
				for (int col = 0; col < MAX_COLS - row % 2; col++)
				{
					


					Bubble* pBubble = m_board[row][col];




					int irow;
					int icol;
					if (row % 2){//偶数行向前推进
						irow = row - 1;
						icol = col;
					}
					else{
						if (col == 0){//奇数行向前推进第一个变成前前行的最后一个因为偶数行差一个不够
							irow = row - 2;
							icol = MAX_COLS - 1;
						}
						else{
							irow = row - 1;
							icol = col - 1;
						}
					}

					m_board[irow][icol] = pBubble;

					if (pBubble != NULL)
					{
						m_board[irow][icol]->setRowColIndex(irow, icol);
						pBubble->setPosition(getPosByRowAndCol(irow, icol));
					}



				}
				yfadein->setDuration((Vitorynum - m_listBubble.size()) / 6.0);

				yfadeout->setDuration((Vitorynum - m_listBubble.size()) / 6.0);
			}}
		),
			NULL
			)
			);
		
		
		
		
	}
	
		
}

void GameScene::update(float delta)
{
	
	if (isCollisionWithBorder())
	{
		m_real.x = -m_real.x;
	}
	

	
	/*if (m_curReady->getPosition().y>=Zgamec->getPosition().y){
		if (isfashe){
			isfashe = false;
			m_curReady->retain();
			m_curReady->removeFromParent();
			Zgamec->addChild(m_curReady);
			m_curReady->setPosition(m_curReady->getPosition().x - Zgamec->getPosition().x, m_curReady->getPosition().y - Zgamec->getPosition().y);
		}
	}*/
	
	Point pos = m_curReady->getPosition();
	m_curReady->setPosition(ccp(pos.x + m_real.x * bub_Speed, pos.y + m_real.y * bub_Speed));
	
		
		if (isCollision(m_curReady))	//如果和球或者上边缘碰撞了， 做相应的处理
		{
			//isconmReady = true;
			m_real = Point::ZERO;

			adjustBubblePosition(m_curReady);

			//根据同样的球数量作出相应的清理处理
			execClearBubble(m_curReady);
			//清除球之后，掉落处于悬挂状态的球
			ROWCOL_LIST fallList = checkFallBubble();
			FallBubble(fallList);
			//判断符合成功或失败弹窗


			if (!iswinorsb()){
				if (m_curReady->getBubbleColor() <COLOR_COUNT - 3){
					changeWaitToReady();
				}
				else{

					initReadyBubble();
				}
				//m_curReady = m_curReadyclone;
			}

			this->unscheduleUpdate();
			setEnable();
		}
	
	
}
void GameScene::btncallFunc(Object *pSender, cocos2d::ui::Button::TouchEventType type){
	auto butten = (Sprite*)pSender;
	unsigned int tag = butten->getTag();
	auto targetScTo = ScaleTo::create(0.174f, 1.0928f);

	switch (type)
	{
	case ui::Button::TouchEventType::BEGAN:
		//butten->setPositionY(butten->getPositionY() - 10);


		butten->runAction(targetScTo);
		break;

	case ui::Button::TouchEventType::MOVED:

		break;

	case ui::Button::TouchEventType::ENDED:
		if (islistouch){
			//butten->setPositionY(butten->getPositionY() + 10);
			butten->stopAllActions();
			auto targetScTo2 = ScaleTo::create(0.117f, 1.0f);
			butten->runAction(targetScTo2);
			auto pBubble = Bubble::create();
			pBubble->unschedule(schedule_selector(Bubble::loop));
			if (butten->getName() == "tes1")
			{
				log("tes_1");

				pBubble->setBubbleColor(BUBBLE_COLOR::BUBBLE_GOLDEN);
				if (intes[0] > 0 && m_curReady->getBubbleColor() != BUBBLE_GOLDEN){
					std::string strintes1 = String::createWithFormat("%d", --intes[0])->_string;
					tesCount[0]->setString(strintes1);
				}
				else{
					return;
				}

			}
			else if (butten->getName() == "tes2")
			{
				pBubble->setBubbleColor(BUBBLE_COLOR::BUBBLE_GOLDEN1);
				if (intes[1] > 0 && m_curReady->getBubbleColor() != BUBBLE_GOLDEN1){
					std::string strintes2 = String::createWithFormat("%d", --intes[1])->_string;
					tesCount[1]->setString(strintes2);
				}
				else{
					return;
				}
				log("tes_2");
			}
			else if (butten->getName() == "tes3")
			{
				pBubble->setBubbleColor(BUBBLE_COLOR::BUBBLE_GOLDEN2);
				if (intes[2] > 0 && m_curReady->getBubbleColor() != BUBBLE_GOLDEN2){
					std::string strintes3 = String::createWithFormat("%d", --intes[2])->_string;
					tesCount[2]->setString(strintes3);
				}
				else{
					return;
				}
				log("tes_3");
			}

			std::string tesbubname = String::createWithFormat("bubble_%s.png", butten->getName().c_str())->_string;

			if (pBubble && pBubble->initWithFile(tesbubname.c_str()))
			{


				this->addChild(pBubble);
				//m_curReadyclone = m_curReady;
				m_curReady->removeFromParent();
				m_curReady = pBubble;

				m_curReady->setPosition(READY_BUBBLE_POS);
				m_curReady->setOpacity(168);
				log("getBubbleColor is %d", pBubble->getBubbleColor());//启动计时器

			}
		}
		break;

	case ui::Button::TouchEventType::CANCELED:
		//butten->setPositionY(butten->getPositionY() + 10);
		butten->stopAllActions();
		auto targetScTo2 = ScaleTo::create(0.117f, 1.0f);
		butten->runAction(targetScTo2);
		break;


	}

}
void GameScene::teshuList(){
	if (!teVew->isVisible()){
		

		teVew->setVisible(true);
		teVew->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(GameScene::selectedItemEvent, this));

		teVew ->setTouchEnabled(true);
		/*int intes1 = UserDefault::getInstance()->getIntegerForKey("waitcont");
		int intes1 = UserDefault::getInstance()->getIntegerForKey("waitcont");
		int intes1 = UserDefault::getInstance()->getIntegerForKey("waitcont");*/
		

		
		
		_eventDispatcher->resumeEventListenersForTarget(rootNode->getChildByName("notouch"));
	}
	else{
		
		teVew->setVisible(false);
		_eventDispatcher->removeEventListenersForTarget(teVew);
		_eventDispatcher->pauseEventListenersForTarget(rootNode->getChildByName("notouch"));
	}

}
void GameScene::adjustBubblePosition(Bubble* _curReady)
{

	Point curPos = _curReady->getPosition();
	RowCol rowcol_index = GetRowColByPos(curPos.x, curPos.y);
	int k=0;
	if (_curReady->getBubbleColor() == BUBBLE_GOLDEN1){
		_curReady->removeFromParent();
		for (int i = 0; i < 7;i++){
			int j = i % 3 - 1;
			if (rowcol_index.m_nRow % 2){
				
				if (rowcol_index.m_nCol <MAX_COLS - 1 - i % 2 && rowcol_index.m_nCol>0)
					rowcol_index = RowCol(rowcol_index.m_nRow + j, rowcol_index.m_nCol + i %2);
			}
			else{
				if (rowcol_index.m_nCol <MAX_COLS - i % 2 && rowcol_index.m_nCol>1)
					rowcol_index = RowCol(rowcol_index.m_nRow + j, rowcol_index.m_nCol + i % 2-1);
			}
			if (m_board[rowcol_index.m_nRow][rowcol_index.m_nCol] == NULL){
				Bubble* pBubble = randomBubble(0);
				if (pBubble == NULL)
				{
					CC_BREAK_IF(!pBubble);
				}

				pBubble->setPosition(getPosByRowAndCol(rowcol_index.m_nRow, rowcol_index.m_nCol));
				Zgamec->addChild(pBubble);

				m_board[rowcol_index.m_nRow][rowcol_index.m_nCol] = pBubble;
				m_board[rowcol_index.m_nRow][rowcol_index.m_nCol]->setRowColIndex(rowcol_index.m_nRow, rowcol_index.m_nCol);
				m_listBubble.push_back(pBubble);
				execClearBubble(pBubble);
				if (k > 3){
					return;
				}
				k++;
			}
		}
		return;
	}
	
	if (m_board[rowcol_index.m_nRow][rowcol_index.m_nCol] != NULL){
		Point p = getPosByRowAndCol(rowcol_index.m_nRow, rowcol_index.m_nCol);
		//Bubble *pBubble = m_board[rowcol_index.m_nRow][rowcol_index.m_nCol];
		auto picaizhiy = ParticleSystemQuad::create("shenli.plist");
		picaizhiy->setPosition(p.x, p.y);
		Zgamec->addChild(picaizhiy);
	}


	if (rowcol_index.m_nRow % 2 == 1 && rowcol_index.m_nCol == MAX_COLS - 1){
	if (m_board[rowcol_index.m_nRow][rowcol_index.m_nCol - 1] == NULL){
	rowcol_index = RowCol(rowcol_index.m_nRow, rowcol_index.m_nCol - 1);

	}
	else{
	rowcol_index = RowCol(rowcol_index.m_nRow + 1, rowcol_index.m_nCol);
	}

	}
	if (rowcol_index.m_nRow > MAX_ROWS - 1){
		_curReady->removeFromParent();
		return;
	}
	Point adjustPos = getPosByRowAndCol(rowcol_index.m_nRow, rowcol_index.m_nCol);
	
	_curReady->setPosition(adjustPos);
	
	if (_curReady->getBubbleColor() < COLOR_COUNT - 3){
		SimpleAudioEngine::getInstance()->playEffect("fasep_eff.wav");
		_curReady->schedule(schedule_selector(Bubble::loop), 1.0f);
	}
	else{
		SimpleAudioEngine::getInstance()->playEffect("fases_eff.wav");
	}

	//Zgamec->addChild(m_curReady);
	//m_curReady->setPosition(m_curReady->getPosition().x - Zgamec->getPosition().x, m_curReady->getPosition().y - Zgamec->getPosition().y);

	//m_curReady->setPosition(adjustPos.x - Zgamec->getPosition().x, adjustPos.y - Zgamec->getPosition().y);

	_curReady->setRowColIndex(rowcol_index.m_nRow, rowcol_index.m_nCol);

	m_board[rowcol_index.m_nRow][rowcol_index.m_nCol] = _curReady;
	log("m_nRow=%d,m_nCol=%d", rowcol_index.m_nRow, rowcol_index.m_nCol);


	//log("sceneNum1 = %d", tancNum11);
	m_listBubble.push_back(_curReady);
	

}
//是否胜利失败
bool GameScene::iswinorsb()
{
	yfadein->setDuration((Vitorynum - m_listBubble.size()) / 6.0);

	yfadeout->setDuration((Vitorynum - m_listBubble.size()) / 6.0);
	if (m_listBubble.size() >= Vitorynum || m_waitcont <= 0){
		
		if (m_listBubble.size() >= Vitorynum){
			//i = 1;//胜利
			
			//shengli_eff
			SimpleAudioEngine::getInstance()->stopBackgroundMusic();
			SimpleAudioEngine::getInstance()->playEffect("shengli_eff.mp3");
			_eventDispatcher->removeAllEventListeners();
			for (BUBBLE_LIST::const_iterator iterBubble = m_listBubble.begin();
				iterBubble != m_listBubble.end();
				++iterBubble)
			{

				//m_listBubble.at
				Bubble *pBubble = *iterBubble;
				auto picaizhiy = ParticleSystemQuad::create("shenli.plist");

				//picaizhiz->setDuration(2.0);

				//picaizhiz->setPosition(45, 210);


				picaizhiy->setPosition(pBubble->getContentSize().width / 2, pBubble->getContentSize().height / 2);
				//pBubble->addChild(picaizhiz);
				pBubble->addChild(picaizhiy);
				
			}
			//_eventDispatcher->pauseEventListenersForTarget(chumoc);

			auto* yous = Sprite::create("yous.png");
			yous->setAnchorPoint(Point::ZERO);
			yous->setPosition(466.43, 207.10);


			addChild(yous);
			auto* zuos = Sprite::create("zuos.png");
			zuos->setAnchorPoint(Point::ZERO);
			zuos->setPosition(-333.83, 207.10);


			addChild(zuos);


			zuos->runAction(
				Sequence::create(
				EaseIn::create(MoveTo::create(1.6f, Vec2(-283.27, 207.10)), 0.18),
				EaseOut::create(MoveTo::create(1.6f, Vec2(-0.62, 207.10)), 0.16),

				NULL
				)
				);
			yous->runAction(
				Sequence::create(
				EaseIn::create(MoveTo::create(1.6f, Vec2(446.17, 207.10)), 0.18),
				EaseOut::create(MoveTo::create(1.6f, Vec2(216.68, 207.10)), 0.16),

				CallFunc::create([=]{
				std::vector<Vec2> xy_array;
				xy_array.push_back(Vec2(234.6, 659.8));
				xy_array.push_back(Vec2(228, 629.2));
				xy_array.push_back(Vec2(239.8, 380.0));
				xy_array.push_back(Vec2(239.8, 296.1));
				xy_array.push_back(Vec2(241.4, 241.4));
				xy_array.push_back(Vec2(239.8, 281.0));
				for (std::vector<Vec2>::const_iterator iterVec2 = xy_array.begin();
					iterVec2 != xy_array.end();
					++iterVec2)
				{

					auto picaizhiy = ParticleSystemQuad::create("bomb.plist");
					picaizhiy->setPosition(*iterVec2);
					this->addChild(picaizhiy);
				}
				auto picaizhiy = ParticleSystemQuad::create("hongx.plist");


				picaizhiy->setPosition(260.6, 528);
				picaizhiy->setOpacity(160);
				this->addChild(picaizhiy);


			}),
				DelayTime::create(1.68f),

				CallFunc::create([=]{

				//SimpleAudioEngine::getInstance()->stopAllEffects();
				SimpleAudioEngine::getInstance()->playEffect("guanm_eff.wav");
				if (!istanc){
					istanc = true;
					vjiesuan(1);
				}
			}
			),
				NULL
				)
				);


			
		
		}
		else if (m_waitcont <= 0){
			//i = 0;//失败
			SimpleAudioEngine::getInstance()->playEffect("shibai_eff.wav");
			if (!istanc){
				istanc = true;
				vjiesuan(0);
			}
			/*ly->stancm = "sbai";
	log("stancm=%s", ly->stancm);*/
		}

		//log("tancNum=%d", tancNum);
		
		return true;
	}
	return false;
}
//将wait状态的球换成ready状态
void GameScene::changeWaitToReady()
{
	/*Bubble* mbub = m_wait[0];
	Zgamec->addChild(mbub);*/
	
	m_wait[MAX_WAIT_BUBBLE - 1]->retain();
	Default->removeChild(m_wait[MAX_WAIT_BUBBLE - 1], false);

	this->addChild(m_wait[MAX_WAIT_BUBBLE - 1]);
	m_curReady = m_wait[MAX_WAIT_BUBBLE - 1];

	m_curReady->setPosition(READY_BUBBLE_POS);
	m_curReady->setOpacity(168);
	
	//Size size = Director::getInstance()->getVisibleSize();
	//CCSize size = CCDirector::sharedDirector()->getWinSize();
	
		int dd = m_waitcont > MAX_WAIT_BUBBLE ? 0 : MAX_WAIT_BUBBLE - m_waitcont;//不知道为什么这里要这样写才解决，程序有毛病吧
		sgm_waitcont = m_waitcont;
		for (int index = MAX_WAIT_BUBBLE - 1; index >0 + dd; index--)
		{


			m_wait[index] = m_wait[index - 1];

			m_wait[index - 1]->setPosition((index + 1) * BUBBLE_RADIUS * 2, WAIT_BUBBLE_POSY);



		}
		if (m_waitcont>MAX_WAIT_BUBBLE){
			m_wait[0] = randomBubble();

			m_wait[0]->setPosition(ccp(1 * BUBBLE_RADIUS * 2, WAIT_BUBBLE_POSY));
			Default->addChild(m_wait[0]);
		}
	
	
}

ROWCOL_LIST GameScene::findClearBubble(Bubble *pReadyBubble)
{
	ROWCOL_LIST clearRowCollist;
	if (pReadyBubble == NULL)
	{
		return clearRowCollist;
	}

	/*if (pReadyBubble->getBubbleColor() == BUBBLE_GOLDEN)
	{
		clearRowCollist = findGoldenBubble(pReadyBubble);
	}*///金色泡泡
	else if (pReadyBubble->getBubbleColor() == BUBBLE_SILVERY)
	{
		clearRowCollist = findSliveryBubble(pReadyBubble);
	}
	else if (pReadyBubble->getBubbleColor() == COLOR_COUNT)
	{
		return clearRowCollist;
	}
	else
	{
		clearRowCollist = findSameBubble(pReadyBubble);
		if (clearRowCollist.size() < REMOVE_COUNT)
		{
			clearRowCollist.clear();
		}
	} 
	
	return clearRowCollist;
}

ROWCOL_LIST GameScene::findSameBubble(Bubble *pReadyBubble)
{
	ROWCOL_LIST samelist;
	BUBBLE_COLOR nColor= pReadyBubble->getBubbleColor();
	int nRow = pReadyBubble->getRowIndex();
	int nCol = pReadyBubble->getColumnIndex();
	samelist.push_back(RowCol(nRow, nCol));

	ROWCOL_LIST::const_iterator itCur = samelist.begin();

	//循环查找同样的球
	do 
	{
		std::vector<RowCol> vecRowCol;

		GetAround(itCur->m_nRow, itCur->m_nCol, vecRowCol);

		for (size_t i = 0; i < vecRowCol.size(); i++)
		{
			Bubble* pCurBubble = m_board[ vecRowCol[i].m_nRow ][ vecRowCol[i].m_nCol ];
			if (pCurBubble && pCurBubble->getBubbleColor() == nColor)
			{
				RowCol rc(vecRowCol[i].m_nRow, vecRowCol[i].m_nCol);
				ROWCOL_LIST::iterator itFind = std::find(samelist.begin(), samelist.end(), rc);
				//查找是否已经在列表中
				if (itFind == samelist.end())
				{
					
					samelist.push_back(vecRowCol[i]);
				}
			}
		}
		itCur++;
	} while (itCur != samelist.end());
	
	return samelist;
}

//查找金色泡泡消除的球集合
ROWCOL_LIST GameScene::findGoldenBubble(Bubble *pReadyBubble)
{
	int nRow = pReadyBubble->getRowIndex();
	int nCol = pReadyBubble->getColumnIndex();
	
	ROWCOL_LIST clearGoldenList;
	GetGoldenLine(nRow, nCol, clearGoldenList);

	return clearGoldenList;
}

//查找银色泡泡消除的球集合
ROWCOL_LIST GameScene::findSliveryBubble(Bubble* pReadyBubble)
{
	int nRow = pReadyBubble->getRowIndex();
	int nCol = pReadyBubble->getColumnIndex();

	ROWCOL_LIST clearSliveryList;
	GetSliveryLine(nRow, nCol, clearSliveryList);

	return clearSliveryList;
}

/************************************************************************/
/* params: 发射后已经调整好位置的球
** NOTE  : 这是一个相当重要的函数，游戏的核心功能都在这个执行清理泡泡函数中，主要执行以下功能
		 1、如果消除泡泡数量达到GOLDEN_COUNT个，就执行金色泡泡的效果
		 2、同理，达到SLIVERY_COUNT个， 就执行银色泡泡效果
		 3、达到3个，小于SLIVERY_COUNT个，消除同样的球
		 4、小于3个，什么都不做
*/
/************************************************************************/
void GameScene::execClearBubble(Bubble* pReadyBubble)
{
	//要执行清除球， 需要先找到需要清理的球
	ROWCOL_LIST clearBubbleList = findClearBubble(pReadyBubble);
	clearBubble(clearBubbleList);
}

//消除bubbleList里所有的球
void GameScene::clearBubble(const ROWCOL_LIST &bubbleList)
{
	int nRow, nCol;
	for (ROWCOL_LIST::const_iterator iterBubble = bubbleList.begin();
		iterBubble != bubbleList.end();
		++iterBubble)
	{
		nRow = iterBubble->m_nRow;
		nCol = iterBubble->m_nCol;

		Bubble *obj = m_board[nRow][nCol];
		if (obj&&obj->getBubbleColor() != BUBBLE_GOLDEN2)//obj->getBubbleColor() != 7)
		{

			removeBubbleAction(obj);
			m_board[nRow][nCol] = NULL;
			BUBBLE_LIST::iterator itFind = std::find(m_listBubble.begin(), m_listBubble.end(), obj);
			if (itFind != m_listBubble.end())
			{
				m_listBubble.erase(itFind);
			}
			
		}
		
		
		
	}
}

void GameScene::removeBubbleAction(Bubble* pBubble)
{
	//auto picaizhiz = ParticleSystemQuad::create("caiz.plist");
	auto picaizhiy = ParticleSystemQuad::create("bomb.plist");

	//picaizhiz->setDuration(2.0);
	picaizhiy->setDuration(1.0);
	//picaizhiz->setPosition(45, 210);
	
	int xrand = 2+rand() % 18;
	xrand = xrand % 2 ? xrand : -xrand;
	int yrand = 2+rand() % 18;
	yrand = yrand % 2 ? yrand : -yrand;
	picaizhiy->setPosition(pBubble->getContentSize().width / 2 + xrand, pBubble->getContentSize().height / 2 + yrand);
	//pBubble->addChild(picaizhiz);
	pBubble->addChild(picaizhiy);
	SimpleAudioEngine::getInstance()->playEffect("xiaoshi_eff.wav");
	pBubble->runAction(
		Sequence::create(
		FadeOut::create(0.5f),
		CallFunc::create(
		
			CC_CALLBACK_0(Sprite::removeFromParent, pBubble)),
			NULL
		)
	);
}



ROWCOL_LIST GameScene::checkFallBubble()
{
	ROWCOL_LIST LinkBubbleList;	//所有连接在一起的球

	for (int i = 0; i < MAX_COLS; i++)
	{
		if (m_board[0][i] != NULL)
		{
			LinkBubbleList.push_back(RowCol(0, i));
		}
	}
	if (LinkBubbleList.empty())//LinkBubbleList为空
	{
		return LinkBubbleList;
	}

	//从上到下查找所有相连的球，则剩下没有找到的就是不相连的
	ROWCOL_LIST::const_iterator itCur = LinkBubbleList.begin();
	do 
	{
		std::vector<RowCol> vecRowCol;
		GetAround(itCur->m_nRow, itCur->m_nCol, vecRowCol);

		for (size_t i = 0; i < vecRowCol.size(); i++)
		{
			Bubble *pBubble = m_board[ vecRowCol[i].m_nRow ][ vecRowCol[i].m_nCol ];
			if (pBubble)
			{
				RowCol pos(vecRowCol[i].m_nRow, vecRowCol[i].m_nCol);
				ROWCOL_LIST::iterator itFind = std::find(LinkBubbleList.begin(), LinkBubbleList.end(), pos);

				//查找是否已经在列表中
				if (itFind == LinkBubbleList.end())
				{
					LinkBubbleList.push_back(vecRowCol[i]);
				}
			}
		}
		itCur++;
	} while (itCur != LinkBubbleList.end());

	ROWCOL_LIST NoLinkBubblelist;	//找出剩下的所有没有连接的球，就是要下落的球
	for (int i = 0; i < MAX_ROWS; i++)
	{
		for (int j = 0; j < MAX_COLS - i % 2; j++)
		{
			if (m_board[i][j] != NULL)
			{
				RowCol findRowCol(i,j);
				ROWCOL_LIST::iterator itFind = std::find(LinkBubbleList.begin(), LinkBubbleList.end(), findRowCol);
				if (itFind == LinkBubbleList.end())
				{
					NoLinkBubblelist.push_back(findRowCol);
				}
			}
		}
	}
	//ROWCOL_LIST NoLinkBubblelist;
	//bool isshbub = false;
	//
	//int j;
	//for (int i = 1; i < MAX_ROWS; i++)
	//	{
	//		for (j = 0; j < MAX_COLS - i % 2; j++)
	//		{
	//			/*if (i % 2 && j == MAX_COLS - 2){
	//				if (m_board[i - 1][j+1])
	//					isshbub = true;
	//				
	//			}
	//			if (m_board[i - 1][j]){
	//				isshbub = true;
	//			}*/
	//			
	//			if (m_board[i][j])
	//			{
	//				if (i % 2){
	//					if (!m_board[i - 1][j] && !m_board[i - 1][j + 1] && !m_board[i][j + 1] && !m_board[i][j -1])
	//						NoLinkBubblelist.push_back(RowCol(i,j));
	//				
	//				}
	//				else{
	//					if (!m_board[i - 1][j] && !m_board[i - 1][j - 1] && !m_board[i][j + 1] && !m_board[i][j - 1])
	//						NoLinkBubblelist.push_back(RowCol(i, j));
	//				}
	//			}
	//		}
	//		/*if (!isshbub){
	//			
	//			for (int k = 0; k < j; k++)
	//			{
	//				NoLinkBubblelist.push_back(RowCol(i, k));
	//			}
	//		}*/
	//	}
	return NoLinkBubblelist;
}

//执行可以掉落的泡泡
void GameScene::FallBubble(const ROWCOL_LIST &fallBubbleList)
{
	for (ROWCOL_LIST::const_iterator iter = fallBubbleList.begin(); iter != fallBubbleList.end(); iter++)
	{
		Bubble *pBubble = m_board[ iter->m_nRow ][ iter->m_nCol ];
		if (pBubble != NULL)
		{
			downBubbleAction(pBubble);
			
			BUBBLE_LIST::iterator iterBubble = std::find(m_listBubble.begin(), m_listBubble.end(),pBubble);
			if (iterBubble != m_listBubble.end())
			{
				m_listBubble.erase(iterBubble);
				m_board[ iter->m_nRow ][ iter->m_nCol ] = NULL;
			}
		}
	}
	
}

//掉落泡泡
void GameScene::downBubbleAction(Bubble *pBubble)
{
	float offY = -298;

	Point pos = pBubble->getPosition();
	pBubble->runAction(
			Sequence::create(
			EaseBackIn::create(MoveTo::create((pos.y - offY ) / 600.0, ccp(pos.x, 52.8))),
			CallFunc::create([=](){removeBubbleAction(pBubble); }),
				NULL
			)
		);//CCCallFuncN::create(this, callfuncN_selector(GameScene::callbackRemoveBubble))CC_CALLBACK_0(Sprite::removeFromParent, pBubble)
}