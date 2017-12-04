#include "StartLayer.h"

#include "xuanG.h"
#include "GameShuJu.h"

using namespace cocos2d;

StartLayer::StartLayer()
{
	
	/*if (UserDefault::getInstance()->getBoolForKey("ismicpalying"))
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("main_music.mp3", true);*/
	/*if (!UserDefault::getInstance()->getBoolForKey("iseffectpalying"))
		SimpleAudioEngine::getInstance()->setEffectsVolume(0.0);*/
}

StartLayer::~StartLayer()
{
	
}

Scene* StartLayer::scene()
{
    Scene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = Scene::create();
        CC_BREAK_IF(! scene);
		
        // 'layer' is an autorelease object
        StartLayer *layer = StartLayer::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool StartLayer::init()
{
    bool bRet = false;
    do 
    {


		
        CC_BREAK_IF(! CCLayer::init());

		Size winSize = Director::getInstance()->getVisibleSize();
		ZipUtils::setPvrEncryptionKey(0x4ab3603a, 0x654c9a30, 0x55be3b35, 0xa7337055); //4ab3603a654c9a3055be3b35a7337055
		isyuyantouch = true;
		/*auto startItem = MenuItemImage::create("startButton.png", "startButton2.png",
			CC_CALLBACK_0(StartLayer::menuStartCallback, this));
		startItem->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
		startItem->setScale(0.8f);
		auto startMenu = Menu::create(startItem, NULL);
		startMenu->setPosition(Vec2(0, 0));
		this->addChild(startMenu,1);


        CCLabelTTF* pLabel = CCLabelTTF::create("Bubble Cat 2014", "Arial", 24 * 3);
        CC_BREAK_IF(! pLabel);
        pLabel->setPosition(ccp(winSize.width / 2, winSize.height - 50));
        this->addChild(pLabel, 1);
*/
		//Sprite* pSprite = Sprite::create("StartScene_CN.png");
		pSprite = CSLoader::createNode("csb/startScene.csb");
		pSprite->getChildByName("startui")->setPositionX(winSize.width / 2);
        CC_BREAK_IF(! pSprite);
        //pSprite->setPosition(ccp(winSize.width/2, winSize.height/2));
        this->addChild(pSprite, 0);
		//auto skeleton = spine::SkeletonAnimation::createWithFile("spineboy.json", "spineboy.atlas");//加载文件
		//skeleton->setAnimation(0, "walk", true);//运行骨骼动画，参数：（什么意思？，动作名，是否循环播放）
		//skeleton->setPosition(200, 200);
		//skeleton->setScale(0.5f);//设置大小
		//skeleton->setTimeScale(0.5f);//设置运行速度
		//skeleton->setMix("walk", "run", 1.0f);//设置动画平缓切换用时
		//skeleton->addAnimation(0, "run", true);//在之前动作做完之后，添加一个动作
		//skeleton->setDebugBonesEnabled(true);//显示骨头
		//this->addChild(skeleton);
		//auto skeletonNode = spine::SkeletonAnimation::createWithFile("Dragon.json", "Dragon.atlas", 0.8F);//0.2是设置图片的缩放比例
		//skeletonNode->setPosition(Point(400, 200));
		//skeletonNode->setAnimation(0, "walk", true);//true是指循环播放walk动作
		//this->addChild(skeletonNode);
		//Vector<SpriteFrame*> animations;
		//auto spriteCache = SpriteFrameCache::getInstance();
		//char str[100] = { 0 };
		//std::ostringstream osr;
		//animations.pushBack(spriteCache->getSpriteFrameByName("bubble_2.png"));
		///*for (int i = 2; i< 8; i++)
		//{
		//	osr << "bubble_" << i << ".png";
		//	animations.pushBack(spriteCache->getSpriteFrameByName(osr.str()));
		//	osr.str("");
		//}*/
		//Animation* animation = Animation::createWithSpriteFrames(animations, 2.0f);

		////有多个动画时也可以使用AnimationCache
		//AnimationCache::sharedAnimationCache()->addAnimation(animation, "dance");
		////从缓存中读动画.                                                                                                                                                                   
		//Animation* danceAnimation = AnimationCache::sharedAnimationCache()->animationByName("dance");
		//Animate* animate = Animate::create(danceAnimation);
		//Sprite* grossini = Sprite::create();
		//SpriteFrame* frame = spriteCache->spriteFrameByName("bubble_1.png");
		//grossini->setDisplayFrame(frame);
		//grossini->setPosition(400, 500);
		//addChild(grossini, 0);
		//grossini->runAction(animate);
		
		//_grossini->runAction(Sequence::create(action, NULL));  //action->reverse()反向
		
		
		auto pictureNislock2 = ParticleSystemQuad::create("kaishit2.plist");
		pictureNislock2->setPosition(330, 660);
		//pictureNislock->retain();

		this->addChild(pictureNislock2);
		auto pictureNislock3 = ParticleSystemQuad::create("kaishit3.plist");
		pictureNislock3->setPosition(216.8, 600);
		//pictureNislock->retain();
		this->addChild(pictureNislock3);

		/*auto startwz = Sprite::create("dianjkaishi.png");
		
		startwz->setPosition(ccp(winSize.width / 2,57.8));
		startwz->runAction(
			RepeatForever::create(
			EaseOut::create(Blink::create(1.8, 1),1.8)
			)
			);
		this->addChild(startwz);*/
		
		shuView = (ui::ListView*)pSprite->getChildByName("startui")->getChildByName("yuyanui")->getChildByName("shu");
		yuyanView = (ui::Layout*)pSprite->getChildByName("startui")->getChildByName("yuyanui");//侦听选择语言点击
		shuView->setScrollBarEnabled(false);
		shuView->setVisible(false);
		auto touchListener = EventListenerTouchOneByOne::create();
		touchListener->setSwallowTouches(true);
		touchListener->onTouchBegan = CC_CALLBACK_2(StartLayer::TouchBegan, this);
		//touchListener->onTouchMoved = CC_CALLBACK_2(StartLayer::TouchMoved, this);
		touchListener->onTouchEnded = CC_CALLBACK_2(StartLayer::TouchEnded, this);

		//_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), rootNode->getChildByName("gamec"));
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), pSprite->getChildByName("startui")->getChildByName("kaishiyouxi_3"));
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), pSprite->getChildByName("startui")->getChildByName("zhan_5"));
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), pSprite->getChildByName("startui")->getChildByName("yuyan_4")); 


		auto notouchListener = EventListenerTouchOneByOne::create();
		notouchListener->setSwallowTouches(false);
		notouchListener->onTouchBegan = CC_CALLBACK_2(StartLayer::TouchBegan, this);
		notouchListener->onTouchEnded = CC_CALLBACK_2(StartLayer::TouchEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(notouchListener, pSprite->getChildByName("startui")->getChildByName("notouch"));
		//_eventDispatcher->pauseEventListenersForTarget(pSprite->getChildByName("startui")->getChildByName("notouch"));
		for (int i = 0; i <3; i++){
			std::string tesname = String::createWithFormat("tes%d", i)->_string;
			auto tes = (ui::Button*)shuView->getChildByName(tesname.c_str());
			tes->addTouchEventListener(CC_CALLBACK_2(StartLayer::btncallFunc, this));
			
		}
		
		this->runAction(Sequence::create(
			//DelayTime::create(0.0f),
			CallFunc::create([=](){
			_eventDispatcher->pauseEventListenersForTarget(pSprite->getChildByName("startui")->getChildByName("notouch"));
		}
		),
			NULL));
	
        bRet = true;
    } while (0);

    return bRet;
}


bool StartLayer::TouchBegan(Touch* pTouch, Event* pEvent)
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
		targetScTo = ScaleTo::create(0.108f, targetscale);
		target->runAction(targetScTo);
		return true;
	}
	else {
		return false;
	};

}



void StartLayer::TouchEnded(Touch* pTouch, Event* pEvent)
{
	auto target = static_cast<Sprite*>(pEvent->getCurrentTarget());


	auto targetScTo2 = ScaleTo::create(0.217f, 1.0f);
	target->stopAction(targetScTo);
	target->runAction(targetScTo2);
	Point locationInNode = target->convertToNodeSpace(pTouch->getLocation());
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);


	if (rect.containsPoint(locationInNode)) {
		//auto name = String::createWithFormat("%s2", i)->_string;
		if (target->getName() == "kaishiyouxi_3"){
			SimpleAudioEngine::getInstance()->playEffect("ui_eff.wav");
			//Director::getInstance()->pushScene(xuanG::scene());
			auto ly = xuanG::create();
			ly->setPosition(Point::ZERO);
			ly->setAnchorPoint(Point::ZERO);
			this->addChild(ly);
		}
		else if (target->getName() == "zhan_5"){

		}
		else if (target->getName() == "yuyan_4"&&isyuyantouch){

			isyuyantouch = false;
			log("thisyuyan_4");
			teshuList();
		}
		else if (target->getName() == "notouch"&&isyuyantouch){
			isyuyantouch = false;
			teshuList();
			
		}
	}
	
}
void StartLayer::btncallFunc(Object *pSender, cocos2d::ui::Button::TouchEventType type){
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

			butten->stopAllActions();
			auto targetScTo2 = ScaleTo::create(0.117f, 1.0f);
			butten->runAction(targetScTo2);

			if (butten->getName() == "tes0")
			{
				log("tes_1");



			}
			else if (butten->getName() == "tes1")
			{

			}
			else if (butten->getName() == "tes2")
			{
			

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
void StartLayer::selectedItemEvent(Ref* pSender, cocos2d::ui::ListView::EventType type)
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
void StartLayer::teshuList(){
	Size shusize = shuView->getContentSize();
	float EaseInnum = 0.168f;
	float MoveTonum = 0.3678f;

	/*Point yuyanxy = yuyanView->getPosition();
	yuyanxy.y = yuyanxy.y;- shusize.height;
	shuView->setPositionY(yuyanxy.y);*/
	if (!shuView->isVisible()){
		_eventDispatcher->resumeEventListenersForTarget(pSprite->getChildByName("startui")->getChildByName("notouch"));
		shuView->setPositionY(-shusize.height);
		shuView->setVisible(true);
		Vec2 yuyanxy = Vec2(shuView->getPositionX(),0);
		auto moveshuView = EaseIn::create(MoveTo::create(MoveTonum, yuyanxy), EaseInnum);
		shuView->runAction(Sequence::create(
			moveshuView,
			CallFunc::create([=](){
			

			shuView->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(StartLayer::selectedItemEvent, this));

			shuView->setTouchEnabled(true);
			isyuyantouch = true;
		}
		),
			NULL));
		
	}
	else{
		Vec2 yuyanxy = Vec2(shuView->getPositionX(), - shusize.height);
		//(1 - shuView->getPositionY() / (-shusize.height))
		auto moveshuView = EaseIn::create(MoveTo::create(MoveTonum, yuyanxy), EaseInnum);
		
		_eventDispatcher->removeEventListenersForTarget(shuView);
		_eventDispatcher->pauseEventListenersForTarget(pSprite->getChildByName("startui")->getChildByName("notouch"));
		shuView->runAction(Sequence::create(moveshuView, 
			CallFunc::create([=](){ 
			shuView->setVisible(false); 
			isyuyantouch = true;
		}
		),
			NULL));
	}

}
