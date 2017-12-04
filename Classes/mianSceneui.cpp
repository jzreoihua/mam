#include "mianSceneui.h"
#include "GameScene.h"

#include "GameShuJu.h"
using namespace cocos2d;

mianSceneui::mianSceneui()
{

}

mianSceneui::~mianSceneui()
{
	
}


// on "init" you need to initialize your instance
bool mianSceneui::init()
{
    bool bRet = false;
    do 
    {


		
        CC_BREAK_IF(! CCLayer::init());

		Size winSize = Director::getInstance()->getVisibleSize();
		ZipUtils::setPvrEncryptionKey(0x4ab3603a, 0x654c9a30, 0x55be3b35, 0xa7337055);
		Texture2D::PVRImagesHavePremultipliedAlpha(true);//解决打包图片白边
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("zhujiemui.plist", "zhujiemui.pvr.ccz");
		
		MainSuiNode = CSLoader::createNode("csb/MainSui.csb");
		MainSuiNode->setPosition(Point::ZERO);
		MainSuiNode->setAnchorPoint(Point::ZERO);
		this->addChild(MainSuiNode);
		zhuView = (ui::Layout*)MainSuiNode->getChildByName("mainui")->getChildByName("zhuui");//侦听选择语言点击
		hengView = (ui::ListView*)zhuView->getChildByName("heng");
		hengView->setScrollBarEnabled(false);
		hengView->setVisible(false);

		xuanzong = ui::ImageView::create("xuanzong.png", cocos2d::ui::Widget::TextureResType::PLIST);//选中图片框
		xuanzong->setAnchorPoint(Point::ZERO);
		
		

		auto wuping = (ui::Layout*)MainSuiNode->getChildByName("mainui")->getChildByName("wuping");
		wuping->addChild(xuanzong);
		xuanzong->setPositionX(-xuanzong->getContentSize().width);
		wuping->setPositionX(winSize.width - wuping->getContentSize().width);
		dutu_ly = (ui::Layout*)MainSuiNode->getChildByName("mainui")->getChildByName("wuping")->getChildByName("dutu_ly");//侦听选择语言点击
		dutu_ly->setPositionX(dutu_ly->getContentSize().width);

		wupditu = (ui::ImageView*)dutu_ly->getChildByName("wupditu");
		wupView = (ui::ListView*)dutu_ly->getChildByName("wuplist");
		
		wupView->setScrollBarEnabled(false);
		wupView->setVisible(false);
		dutu_ly->getChildByName("tishibtn")->setVisible(false);

		auto touchListener = EventListenerTouchOneByOne::create();
		touchListener->setSwallowTouches(true);
		touchListener->onTouchBegan = CC_CALLBACK_2(mianSceneui::TouchBegan, this);
		touchListener->onTouchEnded = CC_CALLBACK_2(mianSceneui::TouchEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), MainSuiNode->getChildByName("mainui")->getChildByName("zhucaid"));//左边弹出箭头按钮
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), dutu_ly->getChildByName("youtanann1_8"));//右边弹窗箭头按钮
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), dutu_ly->getChildByName("tishibtn"));

		auto notouchListener = EventListenerTouchOneByOne::create();
		notouchListener->setSwallowTouches(false);
		notouchListener->onTouchBegan = CC_CALLBACK_2(mianSceneui::TouchBegan, this);
		notouchListener->onTouchEnded = CC_CALLBACK_2(mianSceneui::TouchEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(notouchListener, MainSuiNode->getChildByName("mainui")->getChildByName("notouch"));

		for (int i = 0; i <3; i++){
			std::string tesname = String::createWithFormat("tes%d", i)->_string;
			auto tes = (ui::Button*)hengView->getChildByName(tesname.c_str());
			tes->addTouchEventListener(CC_CALLBACK_2(mianSceneui::btncallFunc, this));//添加左上按钮事件
			_eventDispatcher->pauseEventListenersForTarget(tes);
		
			std::string tesiname = String::createWithFormat("tesi%d", i)->_string;
			auto tesi = (ui::Button*)wupView->getChildByName(tesiname.c_str());
			tesi->addTouchEventListener(CC_CALLBACK_2(mianSceneui::btncallFunc, this));//添加右边薯条事件

		}

		this->runAction(Sequence::create(
			//DelayTime::create(0.0f),
			CallFunc::create([=](){
			_eventDispatcher->pauseEventListenersForTarget(MainSuiNode->getChildByName("mainui")->getChildByName("notouch"));
		}
		),
			NULL));
		bRet = true;
    } while (0);

    return bRet;
}
void mianSceneui::setyouwup(Sprite *target){
	ui::Layout *pLayout = ui::Layout::create();
	
	pLayout->setSize(cocos2d::CCSizeMake(64, 63));
	pLayout->setAnchorPoint(Point::ZERO);
	pLayout->addChild(target);
	target->setPosition(0, 0);
	target->setAnchorPoint(Point::ZERO);
	ui::Button *botton = ui::Button::create("kongbai.png", "kongbai.png", "", cocos2d::ui::Button::TextureResType::PLIST);
	//pLayout->addTouchEventListener(CC_CALLBACK_2(mianSceneui::btncallFunc, this));
	botton->setAnchorPoint(Point::ANCHOR_MIDDLE);
	//botton->setSize(cocos2d::CCSizeMake(64, 63));
	botton->setPosition(Vec2(pLayout->getContentSize().width / 2, pLayout->getContentSize().height/2));
	botton->addTouchEventListener(CC_CALLBACK_2(mianSceneui::btncallFunc, this));
	botton->setName(target->getName());
	pLayout->addChild(botton);
	
	
	wupView->pushBackCustomItem(pLayout);
	
	pLayout->setPosition(Vec2(0,0));
}

bool mianSceneui::TouchBegan(Touch* pTouch, Event* pEvent)
{
	auto target = static_cast<Sprite*>(pEvent->getCurrentTarget());//ªÒ»°µƒµ±«∞¥•√˛µƒƒø±Í  

	Point locationInNode = target->convertToNodeSpace(pTouch->getLocation());
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);

	if (rect.containsPoint(locationInNode)) {
		float targetscale;
		if (target->getName() != "startui"){
			targetscale = 1.2928f;

		}
		else{
			targetscale = 1.0f;
		}
		auto targetScTo = ScaleTo::create(0.108f, targetscale);
		target->runAction(targetScTo);
		return true;
	}
	else {
		return false;
	};

}


void mianSceneui::TouchEnded(Touch* pTouch, Event* pEvent)
{
	auto target = static_cast<Sprite*>(pEvent->getCurrentTarget());


	auto targetScTo2 = ScaleTo::create(0.217f, 1.0f);
	target->stopAllActions();
	target->runAction(targetScTo2);
	Point locationInNode = target->convertToNodeSpace(pTouch->getLocation());
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);


	if (rect.containsPoint(locationInNode) && target->isVisible()) {
		//auto name = String::createWithFormat("%s2", i)->_string;
		/*std::string framename = String::createWithFormat("%s2.png", target->getName().c_str())->_string;
		SpriteFrame* targetframe2 = SpriteFrameCache::getInstance()->getSpriteFrameByName(framename);
		if (targetframe2){
			target->setSpriteFrame(targetframe2);
		}*/
		if (target->getName() == "zhucaid"&&isyuyantouch){


			isyuyantouch = false;
			log("thisyuyan_4");
			teshuList(target);
		}
		else if (target->getName() == "notouch"&&isyuyantouch){
			isyuyantouch = false;
			teshuList((Sprite*)MainSuiNode->getChildByName("mainui")->getChildByName("zhucaid"));

		}
		else if (target->getName() == "youtanann1_8"){
			tewupList(target);

		}
		else if (target->getName() == "tishibtn"){
			auto ly = (Popinterface*)Popinterface::create(2);//2是提示界面
			ly->setPosition(Point::ZERO);
			ly->setAnchorPoint(Point::ZERO);
			ly->setguankNum(strguankNum);
			this->addChild(ly);
		}
		
	}
}
void mianSceneui::setguankNum(int num){
	strguankNum = num;
	return;
}
void mianSceneui::btncallFunc(Object *pSender, cocos2d::ui::Button::TouchEventType type){
	auto butten = (ui::Button*)pSender;
	unsigned int tag = butten->getTag();
	auto targetScTo = ScaleTo::create(0.108f, 1.2928f);

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

			butten->stopAllActions();
			auto targetScTo2 = ScaleTo::create(0.217f, 1.0f);
			butten->runAction(targetScTo2);
			/*butten->runAction(Sequence::create(
				targetScTo2,
				CallFunc::create([=](){


				std::string framename = String::createWithFormat("%s2.png", butten->getName().c_str())->_string;
				SpriteFrame* targetframe2 = SpriteFrameCache::getInstance()->getSpriteFrameByName(framename);
				if (targetframe2){
					butten->setSpriteFrame(targetframe2);
				}
			}
			),
				NULL));*/

			
			if (butten->getName() == "tes0")//音效
			{
				log("tes_1");
				auto spme = SpriteFrameCache::getInstance()->getSpriteFrameByName("yinxiao.png");
				auto spme1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("yinxiao2.png");
				if (UserDefault::getInstance()->getBoolForKey("iseffectpalying")){
					
					UserDefault::getInstance()->setBoolForKey("iseffectpalying", false);
					//butten->setSpriteFrame(spme1);
					//SimpleAudioEngine::getInstance()->pauseAllEffects();
					butten->loadTextures("yinxiao2.png", "yinxiao2.png", "", cocos2d::ui::Button::TextureResType::PLIST);
					SimpleAudioEngine::getInstance()->setEffectsVolume(0.0);
				}
				else{

					//iseffectpalying = true;
					UserDefault::getInstance()->setBoolForKey("iseffectpalying", true);
					//butten->setSpriteFrame(spme);
					butten->loadTextures("yinxiao.png", "yinxiao.png", "", cocos2d::ui::Button::TextureResType::PLIST);
					SimpleAudioEngine::getInstance()->setEffectsVolume(1.0);
					//SimpleAudioEngine::getInstance()->resumeAllEffects();
				}


			}
			else if (butten->getName() == "tes1")//音乐
			{
				//butten->loadTextures()
				//butten->setBright()
				

				/*auto spme = SpriteFrameCache::getInstance()->getSpriteFrameByName("yinyue.png");
				auto spme1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("yinyue2.png");*/
				//Size s = butten->getContentSize();
				//Rect rect = Rect(0, 0, s.width, s.height);
				//auto spme = SpriteFrame::create("res/tc/gou.png", rect);
				//butten->setSpriteFrame(spme);
				if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()){


					butten->loadTextures("yinyue2.png", "yinyue2.png", "", cocos2d::ui::Button::TextureResType::PLIST);
					UserDefault::getInstance()->setBoolForKey("ismicpalying", false);
					SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
				}
				else{
					butten->loadTextures("yinyue.png", "yinyue.png", "", cocos2d::ui::Button::TextureResType::PLIST);
					UserDefault::getInstance()->setBoolForKey("ismicpalying", true);
					SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
				}
			}
			else if (butten->getName() == "tes2")//返回主菜单
			{

				auto ly = (Popinterface*)Popinterface::create(0);//0是主菜单界面
				ly->setPosition(Point::ZERO);
				ly->setAnchorPoint(Point::ZERO);
				ly->setguankNum(strguankNum);
				this->addChild(ly);
			}
			else{
				auto _GameScene = (GameScene*)Director::getInstance()->getRunningScene()->getChildByName("gameScene");
				if (xuanzong->getParent() != butten){
					xuanzong->retain();
					xuanzong->removeFromParent();
					xuanzong->setPositionX(0);
					butten->addChild(xuanzong);
					
					_GameScene->clickwup(butten->getName());
					log("butten:%s", butten->getName().c_str());
				}
				else{
					
					xuanzong->retain();
					xuanzong->removeFromParent();
					_GameScene->clickwup(butten->getName(),true);
				}
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
void mianSceneui::selectedItemEvent(Ref* pSender, cocos2d::ui::ListView::EventType type)
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
//左上横弹ui
void mianSceneui::teshuList(Sprite *target)
{
	Size shusize = hengView->getContentSize();
	float EaseInnum = 0.168f;
	float MoveTonum = 0.3678f;

	/*Point yuyanxy = yuyanView->getPosition();
	yuyanxy.y = yuyanxy.y;- shusize.height;
	hengView->setPositionY(yuyanxy.y);*/
	std::string framename = String::createWithFormat("%s2.png", target->getName().c_str())->_string;
	std::string targetframename = String::createWithFormat("%s.png", target->getName().c_str())->_string;
	if (!hengView->isVisible()){//弹出

		SpriteFrame* targetframe2 = SpriteFrameCache::getInstance()->getSpriteFrameByName(framename);
		target->setSpriteFrame(targetframe2);
		_eventDispatcher->resumeEventListenersForTarget(MainSuiNode->getChildByName("mainui")->getChildByName("notouch"));
		hengView->setPositionX(-shusize.width);
		
		hengView->setVisible(true);
		Vec2 yuyanxy = Vec2(-MainSuiNode->getChildByName("mainui")->getChildByName("zhucaid")->getContentSize().width / 3.8, hengView->getPositionY());
		auto moveshuView = EaseIn::create(MoveTo::create(MoveTonum, yuyanxy), EaseInnum);
		hengView->runAction(Sequence::create(
			moveshuView,
			CallFunc::create([=](){


			hengView->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(mianSceneui::selectedItemEvent, this));

			hengView->setTouchEnabled(true);
			isyuyantouch = true;
			for (int i = 0; i <3; i++){
				std::string tesname = String::createWithFormat("tes%d", i)->_string;
				auto tes = (ui::Button*)hengView->getChildByName(tesname.c_str());
				_eventDispatcher->resumeEventListenersForTarget(tes);
				

			}
		}
		),
			NULL));

	}
	else{
		//回收
		for (int i = 0; i <3; i++){
			std::string tesname = String::createWithFormat("tes%d", i)->_string;
			auto tes = (ui::Button*)hengView->getChildByName(tesname.c_str());
			//添加左上按钮事件
			_eventDispatcher->pauseEventListenersForTarget(tes);

		}
		SpriteFrame* targetframe = SpriteFrameCache::getInstance()->getSpriteFrameByName(targetframename);
		target->setSpriteFrame(targetframe);
		Vec2 yuyanxy = Vec2(-shusize.width,hengView->getPositionY());
		//(1 - hengView->getPositionY() / (-shusize.height))
		auto moveshuView = EaseIn::create(MoveTo::create(MoveTonum, yuyanxy), EaseInnum);

		_eventDispatcher->removeEventListenersForTarget(hengView);
		_eventDispatcher->pauseEventListenersForTarget(MainSuiNode->getChildByName("mainui")->getChildByName("notouch"));
		hengView->runAction(Sequence::create(moveshuView,
			CallFunc::create([=](){
			hengView->setVisible(false);
			isyuyantouch = true;
			
		}
		),
			NULL));
	}

}
//右边横弹ui
void mianSceneui::tewupList(Sprite *target){
	_eventDispatcher->pauseEventListenersForTarget(dutu_ly->getChildByName("youtanann1_8"));
	Size shusize = dutu_ly->getContentSize();

	float EaseInnum = 0.168f;
	float MoveTonum = 0.3678f;
	std::string framename = String::createWithFormat("%s2.png", target->getName().c_str())->_string;
	std::string targetframename = String::createWithFormat("%s.png", target->getName().c_str())->_string;
	log(framename.c_str(), targetframename.c_str());


	if (!wupView->isVisible()){
		SpriteFrame* targetframe2 = SpriteFrameCache::getInstance()->getSpriteFrameByName(framename);
		target->setSpriteFrame(targetframe2);
		dutu_ly->setPositionX(shusize.width);
		dutu_ly->getChildByName("tishibtn")->setVisible(true);
		wupView->setVisible(true);
		auto wuping = (ui::Layout*)MainSuiNode->getChildByName("mainui")->getChildByName("wuping");
		Vec2 yuyanxy = Vec2(wuping->getContentSize().width - shusize.width, dutu_ly->getPositionY());
		auto moveshuView = EaseIn::create(MoveTo::create(MoveTonum, yuyanxy), EaseInnum);
		dutu_ly->runAction(Sequence::create(
			moveshuView,
			CallFunc::create([=](){


			wupView->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(mianSceneui::selectedItemEvent, this));

			wupView->setTouchEnabled(true);
			_eventDispatcher->resumeEventListenersForTarget(dutu_ly->getChildByName("youtanann1_8"));
		}
		),
			NULL));

	}
	else{
		SpriteFrame* targetframe = SpriteFrameCache::getInstance()->getSpriteFrameByName(targetframename);
		target->setSpriteFrame(targetframe);
		Vec2 yuyanxy = Vec2(shusize.width, dutu_ly->getPositionY());
		//(1 - hengView->getPositionY() / (-shusize.height))
		auto moveshuView = EaseIn::create(MoveTo::create(MoveTonum, yuyanxy), EaseInnum);

		_eventDispatcher->removeEventListenersForTarget(wupView);
		
		dutu_ly->runAction(Sequence::create(moveshuView,
			CallFunc::create([=](){
			dutu_ly->getChildByName("tishibtn")->setVisible(false);
			wupView->setVisible(false);
			
			_eventDispatcher->resumeEventListenersForTarget(dutu_ly->getChildByName("youtanann1_8"));
		
		}
		),
			NULL));
	}

}