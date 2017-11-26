#include "xuanG.h"
#include "BubbleConstant.h"
#include "GameShuJu.h"
#include "GameScene.h"
#include "ui/CocosGUI.h"
xuanG::xuanG()
{
	
}

xuanG::~xuanG()
{

}

bool xuanG::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Layer::init());
		Size winSize = Director::getInstance()->getVisibleSize();
		ZipUtils::setPvrEncryptionKey(0x4ab3603a, 0x654c9a30, 0x55be3b35, 0xa7337055);
		//xuangframeCache = SpriteFrameCache::getInstance();
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("xuangkabm.plist", "xuangkabm.pvr.ccz");

		xgName = "xzsj";
		gknum = 1;

		
		
		xuangNode = CSLoader::createNode("csb/xuanGScene.csb");
		xuangNode->setPosition(Point::ZERO);
		xuangNode->setAnchorPoint(Point::ZERO);
		this->addChild(xuangNode);
		xuangNode->getChildByName("xuangui")->setPositionX(winSize.width / 2);
		heimi_15 = (Sprite*)xuangNode->getChildByName("xuangui")->getChildByName("heimi_15");
		ui::ImageView* szwenzi = (ui::ImageView*)xuangNode->getChildByName("xuangui")->getChildByName("szwenzi");
		//SpriteFrame* gNumCountframe = SpriteFrameCache::getInstance()->getSpriteFrameByName("xgshuzi.png");
		//auto* yous = Sprite::createWithSpriteFrameName("xgshuzi.png");
		//yous->setAnchorPoint(Point::ZERO);
		//yous->setPosition(466.43, 207.10);

		//addChild(yous);
		
		gNumCount = Label::createWithCharMap("res/xgshuzi.png", 26, 38, '0');
		gNumCount->setString(std::to_string(gknum));
		gNumCount->setPosition(szwenzi->getPosition().x - szwenzi->getContentSize().width / 2 - gNumCount->getContentSize().width / 2, szwenzi->getPosition().y);
		gNumCount->setAnchorPoint(Point::ANCHOR_MIDDLE);
		
		xuangNode->addChild(gNumCount);
		xuangNode->getChildByName("xuangui")->setPositionX(winSize.width / 2);

		touchListener = EventListenerTouchOneByOne::create();

		touchListener->setSwallowTouches(true);
		touchListener->onTouchBegan = CC_CALLBACK_2(xuanG::TouchBegan, this);
		
		touchListener->onTouchEnded = CC_CALLBACK_2(xuanG::TouchEnded, this);

		//_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), rootNode->getChildByName("gamec"));
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), xuangNode->getChildByName("xuangui")->getChildByName("guanka1_9"));
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), xuangNode->getChildByName("xuangui")->getChildByName("xiangzuo"));
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), xuangNode->getChildByName("xuangui")->getChildByName("xiangyou"));
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), xuangNode->getChildByName("xuangui")->getChildByName("x"));
		
		UserDefault::getInstance()->setBoolForKey("isExisted", false);
		//CCLOG("saved file path is %s", UserDefault::getInstance()->getXMLFilePath());
		if (!UserDefault::getInstance()->getBoolForKey("isExisted", false))
		{

			UserDefault::getInstance()->setBoolForKey("lv1", true);
			
			for (int i = 1; i < 10; i++)
			{
		
				//auto ns = String::createWithFormat("lv%d", i + 1)->_string;

				char ns[15] = { 0 };

				sprintf(ns, "lv%d", i + 1);
				UserDefault::getInstance()->setBoolForKey(ns, false);


			};
			UserDefault::getInstance()->setIntegerForKey("myjinb", 0);
			UserDefault::getInstance()->setBoolForKey("iseffectpalying", true);
			UserDefault::getInstance()->setBoolForKey("ismicpalying", true);
			//UserDefault::getInstance()->setIntegerForKey("bub_Speed", 5); //自己球飞行速度
			//UserDefault::getInstance()->setIntegerForKey("waitcont", 20);//自己总球数正比可g1
			//UserDefault::getInstance()->setIntegerForKey("spbub", 3);//特殊球可g
			//UserDefault::getInstance()->setIntegerForKey("spbub2", 3);
			//UserDefault::getInstance()->setIntegerForKey("spbub3", 3);
			//UserDefault::getInstance()->setIntegerForKey("myjinb", 666);//出世金币
			//UserDefault::getInstance()->setBoolForKey("isfrist", true);
			//UserDefault::getInstance()->setBoolForKey("isguanggao", true);//是否广告
			//UserDefault::getInstance()->setBoolForKey("isExisted", true);
			UserDefault::getInstance()->flush();
		}
		
		bRet = true;
	} while (0);

	return bRet;
}

bool xuanG::TouchBegan(Touch* pTouch, Event* pEvent)
{
	auto target = static_cast<Sprite*>(pEvent->getCurrentTarget());

	Point locationInNode = target->convertToNodeSpace(pTouch->getLocation());
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);
	if (rect.containsPoint(locationInNode)) {
		float targetscale;
		if (target->getName() != "guanka1_9"){
			targetscale = 1.2928f;

		}
		else{
			targetscale = 1.0f;
		}
		targetScTo = ScaleTo::create(0.108f, targetscale);
		target->runAction(targetScTo);
		return true;
	}
	else{
		return false;
	}

}


void xuanG::TouchEnded(Touch* pTouch, Event* pEvent)
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
		if (target->getName() == "x"){
			SimpleAudioEngine::getInstance()->playEffect("ui_eff.wav");
			this->removeFromParent();
		}
		else if (target->getName() == "xiangzuo"){
			//std::string framename = String::createWithFormat("guanka%d", gknum)->_string;
			//auto* yous = Sprite::createWithSpriteFrameName("guanka7.png");
			//yous->setAnchorPoint(Point::ZERO);
			////background->setAnchorPoint(Vec2(0.5f, 0.5f));

			//addChild(yous);
			if (target->isVisible() && (gknum++<10)){

				Sprite* xiayou = (Sprite*)xuangNode->getChildByName("xuangui")->getChildByName("xiangyou");
				
				if (gknum >1 && !xiayou->isVisible())
					xiayou->setVisible(true);
				std::string framename = String::createWithFormat("guanka%d.png", gknum)->_string;
				//auto* yous = Sprite::createWithSpriteFrameName(framename);
				SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(framename);
				Sprite* guanka1_9 = (Sprite*)xuangNode->getChildByName("xuangui")->getChildByName("guanka1_9");
				guanka1_9->setSpriteFrame(frame);
				gNumCount->setString(std::to_string(gknum));
				
				char num[15] = { 0 };
				sprintf(num, "lv%d", gknum);
				log("%s", num);
				heimi_15->setVisible(!UserDefault::getInstance()->getBoolForKey(num));
				if (gknum > 9){
					target->setVisible(false);
					gNumCount->setPositionX(gNumCount->getPositionX() - gNumCount->getContentSize().width / 3);
				}
			}
			
		}
		else if (target->getName() == "xiangyou"){
			if (target->isVisible() && (gknum-->1)){

				Sprite* xiazuo = (Sprite*)xuangNode->getChildByName("xuangui")->getChildByName("xiangzuo");
				if (gknum > 1 && !xiazuo->isVisible()){
					xiazuo->setVisible(true);
					gNumCount->setPositionX(gNumCount->getPositionX() + gNumCount->getContentSize().width / 3);
				}
					std::string framename = String::createWithFormat("guanka%d.png", gknum)->_string;
					SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(framename);
					Sprite* guanka1_9 = (Sprite*)xuangNode->getChildByName("xuangui")->getChildByName("guanka1_9");
					guanka1_9->setSpriteFrame(frame);
					gNumCount->setString(std::to_string(gknum));
					
					char num[15] = { 0 };
					sprintf(num, "lv%d", gknum);
					log("%s", num);
					heimi_15->setVisible(!UserDefault::getInstance()->getBoolForKey(num));
					if (gknum < 2){
						
						target->setVisible(false);
					}
			}
		}
		else if (target->getName() == "guanka1_9"&&!heimi_15->isVisible()){
			Director::getInstance()->replaceScene(GameScene::scene(gknum));
			log("this is %s", target->getName().c_str());
		}
	}

	//Director::getInstance()->replaceScene(GameScene::scene());
}

