#include "Popinterface.h"
#include "StartLayer.h"
#include "GameShuJu.h"

 
//#include "Utility.h"


Popinterface::Popinterface()
{
}


Popinterface::~Popinterface()
{
}
Layer* Popinterface::create(int i)
{
	
	Popinterface *pRet = new Popinterface();
	if (pRet && pRet->init(i))
	{
		
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}
//{
//	popmun = i;
//	Popinterface *layer;
//	do
//	{
//		// 'scene' is an autorelease object
//		
//		
//		// 'layer' is an autorelease object
//		layer = Popinterface::create();
//		CC_BREAK_IF(!layer);
//
//		// add layer as a child to scene
//
//	} while (0);
//
//	// return the scene
//	return layer;
//}

// on "init" you need to initialize your instance
bool Popinterface::init(int i)
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCLayer::init());

		
		//log("sceneNum = %d", getNum());
		//CCLabelTTF *label = CCLabelTTF::create("New Game", "Arial", 24 * 2);
		//auto *pMenuItem = CCMenuItemLabel::create(label, this, menu_selector(StartLayer::menuNewGameCallback));
		//pMenuItem->setTag(1);
		//pMenuItem->setPosition(winSize.width / 2, winSize.height / 2);
		//

		//      CCMenu* pMenu = CCMenu::create(pMenuItem, NULL);
		//      pMenu->setPosition(CCPointZero);
		//      CC_BREAK_IF(! pMenu);
		//      this->addChild(pMenu, 1);
		
		//_gamescene = gamescene;
		popmun = i;
		
		log("%dpopmun", popmun);
		sbaiNode = CSLoader::createNode("csb/sbaiScene.csb");
		sbaiNode->setPosition(Point::ZERO);
		sbaiNode->setAnchorPoint(Point::ZERO);
		this->addChild(sbaiNode);

		Size winSize = Director::getInstance()->getVisibleSize();
		sbaiNode->getChildByName("uiceng")->setPositionX(winSize.width / 2);

		auto btn = (Sprite*)sbaiNode->getChildByName("uiceng")->getChildByName("micenbtn");
		Size btnsize = btn->getContentSize();
		Rect btnrect = Rect(0, 0, btnsize.width, btnsize.height);
		btnSpriteFrame1 = SpriteFrame::create("res/tc/gou1.png", btnrect);
		btnSpriteFrame = SpriteFrame::create("res/tc/gou.png", btnrect);
		sbaiaction = CSLoader::createTimeline("csb/sbaiScene.csb");
		sbaiNode->runAction(sbaiaction);
		sbaiaction->gotoFrameAndPause(i);

		//金币数据
		myjinb=UserDefault::getInstance()->getIntegerForKey("myjinb");

		myjinb = 99;
		UserDefault::getInstance()->setIntegerForKey("myjinb", myjinb);
		auto wanzhentyt1_2 = (Sprite*)sbaiNode->getChildByName("uiceng")->getChildByName("wanzhentyt1_2");
		std::string strmyjinb = String::createWithFormat("%d", myjinb)->_string;
		jinbCount = Label::createWithCharMap("tc/jinb_num.png", 14, 19, '0');
		jinbCount->setAnchorPoint(Point::ANCHOR_MIDDLE);
		jinbCount->setPosition(wanzhentyt1_2->getContentSize().width / 1.5, wanzhentyt1_2->getContentSize().height / 2);
		
		jinbCount->setString(strmyjinb);
		
		wanzhentyt1_2->addChild(jinbCount);

		//log("stancm=%s", stancm);
		/*if (stancm == "cgong"){
			sbaiaction->gotoFrameAndPause(1);
		}
		else if (stancm == "sbai"){
			sbaiaction->gotoFrameAndPause(0);
		}*/

		Listener();

		//_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), rootNode->getChildByName("gamec"));
		
		//appear();
		bRet = true;
	} while (0);

	return bRet;
}
//void Popinterface::appear()
//{
//	//层弹出动画  
//	auto visibleSize = Director::getInstance()->getVisibleSize();
//	auto origin = Director::getInstance()->getVisibleOrigin();
//
//	this->setPosition(Point(origin.x + visibleSize.width / 2, origin.y - visibleSize.height / 2));
//	auto moveTo = MoveTo::create(0.5, Point(visibleSize.width / 2, visibleSize.height / 2));
//	auto easeBounceOut = EaseBackOut::create(moveTo);
//	this->runAction(easeBounceOut);
//}
//
void Popinterface::setguankNum(int num)
{
	strguankNum = num;
	return;
}

void Popinterface::disappear()
{
	//消失动画，消失后移除自身  
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto moveTo = MoveTo::create(0.5, Point(origin.x + visibleSize.width / 2, origin.y - visibleSize.height / 2));
	auto easeBounceIn = EaseBackIn::create(moveTo);
	Sequence* seq = Sequence::create(easeBounceIn, RemoveSelf::create(true), NULL);
	this->runAction(seq);
}

//void Popinterface::close()
//{
//	disappear();
//}


bool Popinterface::TouchBegan(Touch* pTouch, Event* pEvent)
{

	auto target = static_cast<Sprite*>(pEvent->getCurrentTarget()); 

	Point locationInNode = target->convertToNodeSpace(pTouch->getLocation());
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);

	if (rect.containsPoint(locationInNode)) {
		float targetscale;

		targetscale = 1.2928f;
		targetScTo = ScaleTo::create(0.108f, targetscale);
		target->runAction(targetScTo);
		
		return true;
	}
	else {
		return false;
	};

}



void Popinterface::TouchEnded(Touch* pTouch, Event* pEvent)
{
	int pop = popmun;
	
	
	auto target = static_cast<Sprite*>(pEvent->getCurrentTarget());
	

		auto targetScTo2 = ScaleTo::create(0.217f, 1.0f);
		target->stopAction(targetScTo);
		target->runAction(targetScTo2);

	Point locationInNode = target->convertToNodeSpace(pTouch->getLocation());
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);
	
	if (rect.containsPoint(locationInNode) && target->isVisible()) {
		//继续按钮
		if (target->getName() == "jixubtn" || target->getName() == "x_1"){
			
			SimpleAudioEngine::getInstance()->playEffect("uibtn_eff.wav");
			
			
			this->removeFromParent();
			istanc = false;
			auto _GameScene = (GameScene*)Director::getInstance()->getRunningScene()->getChildByName("gameScene");
			_GameScene->schedule(schedule_selector(GameScene::loop), 1.0f);
			
			//disappear();
		}//主界面按钮和确定按钮
		else if (target->getName() == "zhujiembtn"){
			
			istanc = false;
			SimpleAudioEngine::getInstance()->playEffect("uibtn_eff.wav");
			if (pop == 1){
				//if (isfist)//如果第一次看提示
				load(0);
				return;
			}
			this->removeFromParent();
			Director::getInstance()->replaceScene(StartLayer::scene());
		}//购买按钮和加号按钮和（第2关后加号按钮变成完整提示按钮）
		else if (target->getName() == "shangdbtn"||target->getName() == "wanzhentyt"){
			SimpleAudioEngine::getInstance()->playEffect("uibtn_eff.wav");
			if (strguankNum > 2 && myjinb-->0){
			//操作一次金币-1不够再弹购买界面
				
				touchListener = NULL;
				popmun = 1;
				Listener();
				sbaiaction->gotoFrameAndPause(popmun);

				UserDefault::getInstance()->setIntegerForKey("myjinb", myjinb);
				std::string strmyjinb = String::createWithFormat("%d", myjinb)->_string;
				jinbCount->setString(strmyjinb);
				return;
			}
			
			
			
			//_eventDispatcher->resumeEventListenersForTarget(sbaiNode->getChildByName("uiceng")->getChildByName("CzLvew"));
			//for (int i = 1; i <5; i++){
			//	//std::string listname = String::createWithFormat("list%d", i)->_string;
			//	std::string btname = String::createWithFormat("goumbtn%d", i)->_string;
			//	auto tes = (ui::Button*)sbaiNode->getChildByName("uiceng")->getChildByName("CzLvew")->getChildByName(btname.c_str());
			//	//_eventDispatcher->resumeEventListenersForTarget(tes);
			//	

			//}
			touchListener = NULL;
			popmun = 3;
			Listener();

			sbaiaction->gotoFrameAndPause(popmun);

			//_eventDispatcher->removeEventListenersForTarget();

		}//充值标题
		
		else if (target->getName() == "notouch"){

			return;
		}//返回按钮
		else if (target->getName() == "tishi1_4"){

			SimpleAudioEngine::getInstance()->playEffect("uibtn_eff.wav");
			//this->removeChild(CzLvew);
			//this->removeChild(GmLvew);


			//_eventDispatcher->removeEventListener(touchListener);
			touchListener = NULL;
			popmun = 1;
			Listener();

			sbaiaction->gotoFrameAndPause(popmun);
		}//返回按钮
		else if (target->getName() == "fanhubtn_6"){
			SimpleAudioEngine::getInstance()->playEffect("uibtn_eff.wav");
			//this->removeChild(CzLvew);
			this->removeChild(GmLvew);
			
			
			_eventDispatcher->removeEventListener(touchListener);
			touchListener = NULL;
			popmun = 2;
			Listener();

			sbaiaction->gotoFrameAndPause(popmun);

		}
		else if (target->getName() == "micenbtn" ){
			
			auto spme1 = SpriteFrame::create("res/tc/gou1.png", rect);
			auto spme = SpriteFrame::create("res/tc/gou.png", rect);
			if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()){
				

				target->setSpriteFrame(spme1);
				ismicpalying = false;
				SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
			}
			else{
				target->setSpriteFrame(spme);
				ismicpalying = true;
				SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
			}

		}
		else if (target->getName() == "meffenbtn"){
			bool _iseffectpaly = iseffectpalying;
			auto spme1 = SpriteFrame::create("res/tc/gou1.png", rect);
			auto spme = SpriteFrame::create("res/tc/gou.png", rect);
			if (_iseffectpaly){
				iseffectpalying = false;
				
				target->setSpriteFrame(spme1);
				//SimpleAudioEngine::getInstance()->pauseAllEffects();
				SimpleAudioEngine::getInstance()->setEffectsVolume(0.0);
			}
			else{
				
				iseffectpalying = true;
				
				target->setSpriteFrame(spme);
				SimpleAudioEngine::getInstance()->setEffectsVolume(1.0);
				//SimpleAudioEngine::getInstance()->resumeAllEffects();
			}
			//Director::getInstance()->popScene();

		}
		else if (target->getName() == "Sprite_1"){
			if (_loadnum != 0){
				this->removeChild(loadNode);
			}

		}
	}

}
void Popinterface::Listener()
{
	int _popmun = popmun;
	//int _myjinb = myjinb;
	bool _iseffectpaly = iseffectpalying;
	jinbCount->setVisible(false);
	touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(Popinterface::TouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(Popinterface::TouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), sbaiNode->getChildByName("notouch"));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), sbaiNode->getChildByName("uiceng")->getChildByName("x_1"));
	if ( _popmun <= 2){
		//i=0返回主界面i=1提示界面i=2主菜单界面i=3购买界面
		
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), sbaiNode->getChildByName("uiceng")->getChildByName("zhujiembtn"));
		
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), sbaiNode->getChildByName("uiceng")->getChildByName("jixubtn"));
		
		
		
		if (_popmun == 2){
			std::string strmyjinb = String::createWithFormat("%d", myjinb)->_string;
			log("_myjinbis%d", myjinb);
			jinbCount->setString(strmyjinb);
			jinbCount->setVisible(true);
			_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), sbaiNode->getChildByName("uiceng")->getChildByName("tishi1_4"));
			_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), sbaiNode->getChildByName("uiceng")->getChildByName("wanzhentyt"));
			_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), sbaiNode->getChildByName("uiceng")->getChildByName("micenbtn"));
			_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), sbaiNode->getChildByName("uiceng")->getChildByName("meffenbtn"));
			_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), sbaiNode->getChildByName("uiceng")->getChildByName("shangdbtn"));
			auto micenbtn = (Sprite*)sbaiNode->getChildByName("uiceng")->getChildByName("micenbtn");
			auto meffenbtn = (Sprite*)sbaiNode->getChildByName("uiceng")->getChildByName("meffenbtn");
			if (_iseffectpaly){
				meffenbtn->setSpriteFrame(btnSpriteFrame);
			}
			else{
				meffenbtn->setSpriteFrame(btnSpriteFrame1);

			}
			if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()){
				micenbtn->setSpriteFrame(btnSpriteFrame);

			}
			else{
				micenbtn->setSpriteFrame(btnSpriteFrame1);
			}
		}

	}
	else if (_popmun == 3){
		//商店窗口

		//_eventDispatcher->removeEventListenersForTarget(sbaiNode->getChildByName("uiceng")->getChildByName("jixubtn"));
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(),sbaiNode->getChildByName("uiceng")->getChildByName("fanhubtn_6"));
		

		
		//GmLvew = (ui::ListView*)sbaiNode->getChildByName("uiceng")->getChildByName("GmLvew");

		//GmLvew->setScrollBarEnabled(false); //设置true时: 存在滚动条 设置false时： 隐藏滚动条
		//GmLvew->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(Popinterface::selectedItemEvent, this));
		CzLvew = (ui::ListView*)sbaiNode->getChildByName("uiceng")->getChildByName("CzLvew");

		CzLvew->setScrollBarEnabled(false);
		CzLvew->setVisible(true);
		CzLvew->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(Popinterface::selectedItemEvent, this));
		
		
		
		for (int i = 1; i <5; i++){
			//std::string listname = String::createWithFormat("list%d", i)->_string;
			std::string btname = String::createWithFormat("goumbtn%d", i)->_string;
			auto tes = (ui::Button*)sbaiNode->getChildByName("uiceng")->getChildByName("CzLvew")->getChildByName(btname.c_str());
			tes->addTouchEventListener(CC_CALLBACK_2(Popinterface::btncallFunc, this));


		}

		//_eventDispatcher->pauseEventListenersForTarget(GmLvew);

		/*for (int i = 1; i < 5; i++){
			std::string listname = String::createWithFormat("list%d", i)->_string;
			std::string jbtname = String::createWithFormat("jinbmbtn%d", i)->_string;
			auto jibtn = (ui::Button*)GmLvew->getChildByName(listname.c_str())->getChildByName(jbtname.c_str());
			_eventDispatcher->pauseEventListenersForTarget(jibtn);
		}*/

	}

	isgoumaddlist = true;
	isjinbaddlist = false;
	
}
void Popinterface::selectedItemEvent(Ref* pSender, cocos2d::ui::ListView::EventType type)
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
void Popinterface::btncallFunc(Object *pSender, cocos2d::ui::Button::TouchEventType type){
	auto butten = (Sprite*)pSender;
	unsigned int tag = butten->getTag();
	auto targetScTo = ScaleTo::create(0.174f, 1.0928f);

	switch (type)
	{
	case ui::Button::TouchEventType::BEGAN:
		butten->runAction(targetScTo);
		break;
	case ui::Button::TouchEventType::MOVED:

		break;

	case ui::Button::TouchEventType::ENDED:
		if (islistouch){
			//butten->setPositionY(butten->getPositionY() + 10);
			auto _GameScene = (GameScene*)Director::getInstance()->getRunningScene()->getChildByName("gameScene");
			butten->stopAllActions();
			auto targetScTo2 = ScaleTo::create(0.117f, 1.0f);
			butten->runAction(targetScTo2);
			auto pBubble = Bubble::create();
			pBubble->unschedule(schedule_selector(Bubble::loop));
			
			 if (butten->getName() == "goumbtn1")//去除广告
			{
				UserDefault::getInstance()->setBoolForKey("isguanggao", false);
			}
			else if (butten->getName() == "goumbtn2")//+1080金币
			{
				myjinb += 2;
			}
			else if (butten->getName() == "goumbtn3")//+2180
			{
				myjinb += 5;
			}
			else if (butten->getName() == "goumbtn4")//3380
			{
				myjinb += 8;
			}
			UserDefault::getInstance()->setIntegerForKey("myjinb", myjinb);
			std::string strmyjinb = String::createWithFormat("%d", myjinb)->_string;
			
			jinbCount->setString(strmyjinb);

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
//0加载中1购买成功2金币不足3已达到最大值
void Popinterface::load(int loadnum){
	_loadnum = loadnum;
	loadNode = CSLoader::createNode("csb/load.csb");
	loadNode->setPosition(Point::ZERO);
	loadNode->setAnchorPoint(Point::ZERO);
	this->addChild(loadNode);
	auto loadaction = CSLoader::createTimeline("csb/load.csb");
	loadNode->runAction(loadaction);
	loadaction->gotoFrameAndPause(loadnum);
	Size winSize = Director::getInstance()->getVisibleSize();
	loadNode->getChildByName("loadui")->setPositionX(winSize.width / 2);
		
	
	auto Loading = loadNode->getChildByName("loadui");
	auto LoadrotateBy = EaseIn::create(RotateBy::create(0.8f, Vec3(0, 0, 360)), 1.168f);
	Loading->getChildByName("load_1")->runAction(RepeatForever::create(LoadrotateBy));
	//auto LoadrScaleTo = ScaleTo::create(MoveTonum,)
	/*float EaseInnum = 1.168f;
	float MoveTonum = 1.3678f;
	auto LoadrScalefan = EaseIn::create(ScaleTo::create(MoveTonum, 0.6), EaseInnum);
	auto LoadrScalezhen = EaseOut::create(ScaleTo::create(MoveTonum, 1), EaseInnum);
	
	Loading->getChildByName("loadwubx_17")->runAction(RepeatForever::create(Sequence::create(
	LoadrScalefan,
	LoadrScalezhen,
	NULL)));*/


	auto LoadListener = EventListenerTouchOneByOne::create();
	LoadListener->setSwallowTouches(true);
	LoadListener->onTouchBegan = CC_CALLBACK_2(Popinterface::TouchBegan, this);
	LoadListener->onTouchEnded = CC_CALLBACK_2(Popinterface::TouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(LoadListener->clone(), loadNode->getChildByName("loadui")->getChildByName("Sprite_1"));
	
}