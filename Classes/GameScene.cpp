#include "GameScene.h"
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
		CC_BREAK_IF(!GameScene::createmianui());
		
		//auto Inputwordly = (Inputrd*)Inputrd::create(strguankNum);
		//Inputwordly->setPosition(Point::ZERO);
		//Inputwordly->setAnchorPoint(Point::ZERO);
		////Inputwordly->setguankNum(strguankNum);
		//this->addChild(Inputwordly);//输入密码界面
		
		
		//auto Inputwordly = Gameduihua::create(1);
		//Inputwordly->setPosition(Point::ZERO);
		//Inputwordly->setAnchorPoint(Point::ZERO);
		////Inputwordly->setguankNum(strguankNum);//对话层
		//this->addChild(Inputwordly);
		bRet = true;

	} while (0);

	return bRet;
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
		this->setName("gameScene");
		Size winSize = Director::getInstance()->getVisibleSize();
		rootNode = CSLoader::createNode("csb/MainScene.csb");
		rootNode->setPosition(Point::ZERO);
		rootNode->setAnchorPoint(Point::ZERO);
		this->addChild(rootNode,0);
		loadaction = CSLoader::createTimeline("csb/MainScene.csb");
		rootNode->runAction(loadaction);
		loadaction->gotoFrameAndPause(0);
		
		//暂停按钮
		auto touchListener = EventListenerTouchOneByOne::create();
		touchListener->setSwallowTouches(true);
		touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::TouchBegan, this);
		touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::TouchEnded, this);
	
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), rootNode->getChildByName("xiangyou_7"));
		//返回按钮
		tisikuang = ui::ImageView::create("tishidikuang.png");//提示底框
		tisikuang->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
		tisikuang->setPositionY(winSize.height);
		tisikuang->setScale9Enabled(true);//是否启用九宫格显示模式
		tisikuang->setCapInsets(Rect(1, 0, tisikuang->getContentSize().width - 1, tisikuang->getContentSize().height));//中间的小矩形
		tisikuang->setContentSize(Size(winSize.width, tisikuang->getContentSize().height));
		tisikuang->setVisible(false);
		tisCount = Label::createWithTTF("", "fonts/fanzzyuan.ttf", 26);//提示标签
		//tisCount->setString(Firstespeak->GetText());
		tisCount->setColor(Color3B::WHITE);

		tisCount->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
		//tisCount->setAdditionalKerning(-13);//间距
		tisikuang->addChild(tisCount);
		//tisCount->setScaleY(-1);
		tisCount->setLineBreakWithoutSpace(true);
		tisCount->setMaxLineWidth(tisikuang->getContentSize().width*0.99);;
		log("width=%f,height=%f", tisCount->getContentSize().width, tisCount->getContentSize().height);
		tisCount->setPosition(tisikuang->getContentSize().width/2, tisikuang->getContentSize().height*0.8 );

		rootNode->getChildByName("tancly")->addChild(tisikuang, 1);
		std::string tispath = "CN/tishi.xml";
		tinyxml2::XMLDocument* tisdoc = new tinyxml2::XMLDocument();//游戏提示配置xml加载
		XMLError tiserrorID = tisdoc->LoadFile(tispath.c_str());

		//[3] 判断是否解析错误
		if (tiserrorID != 0) {
			CCLOG("Parse Error!");
		}
		XMLElement* tisroot = tisdoc->RootElement();

		XMLElement* tischd = tisroot->FirstChildElement();
		for (int j = 1; j <strguankNum; j++) {

			CC_BREAK_IF(!tischd);

			tischd = tischd->NextSiblingElement();//找到当前关


		}
		putontis = tischd->FirstChildElement();//putongtis
		tisspming = putontis->NextSiblingElement();//spming
		std::string path = "youxipz.xml";
		tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();//游戏配置xml加载
		XMLError errorID = doc->LoadFile(path.c_str());

		//[3] 判断是否解析错误
		if (errorID != 0) {
			CCLOG("Parse Error!");
		}
		XMLElement* root = doc->RootElement();

		XMLElement* chd = root->FirstChildElement();
		for (int j = 1; j <strguankNum; j++) {

			CC_BREAK_IF(!chd);

			chd = chd->NextSiblingElement();//找到当前关


		}
		chd = chd->FirstChildElement();//daoju
		guankaspming = chd->NextSiblingElement();//spming
		for (XMLElement* e = chd->FirstChildElement(); e; e = e->NextSiblingElement()) {
			// 子元素e 为文本内容
			// GetText() : 文本内容

			//CCLOG("e : %s ,%s, %s", e->Name(), e->Attribute("name"), e->GetText());
			auto spite = (Sprite*)rootNode->getChildByName(e->Name());
			spite->setName(e->GetText());
			CCLOG("spite : %s ,%s, %s", e->Name(), spite->getName().c_str(), e->GetText());
			_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), spite);
		}
		/*guankaspname = chd->FirstChildElement();


		auto Spwupdx = (Sprite*)rootNode->getChildByName("Sprite1");
		
		for (int i = 2; Spwupdx;i++){
			
			_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), Spwupdx);
			auto Spritename = String::createWithFormat("Sprite%d", i)->_string;
			log(Spritename.c_str());
			Spwupdx = (Sprite*)rootNode->getChildByName(Spritename);
		}*/
		//this->runAction(Sequence::create(
		//	DelayTime::create(0.88f),
		//	CallFunc::create([=](){
		//	iskeyiZtesbtn = true;
		//	//_eventDispatcher->pauseEventListenersForTarget(rootNode->getChildByName("notouch"));		
		//}
		//	),
		//	NULL));


		//_eventDispatcher->pauseEventListenersForTarget(rootNode->getChildByName("notouch"));
		//_eventDispatcher->resumeEventListenersForTarget(rootNode->getChildByName("notouch"));

		//_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), this);
		bRet = true;
	} while (0);
	return bRet;
}

bool GameScene::createmianui(){
	bool bRet = false;
	do
	{
		Sceneuily = mianSceneui::create();
		Sceneuily->setPosition(Point::ZERO);
		Sceneuily->setAnchorPoint(Point::ZERO);
		Sceneuily->setguankNum(strguankNum);
		this->addChild(Sceneuily, 1);///ui层
		bRet = true;
	} while (0);
	return bRet;
}





bool GameScene::TouchBegan(Touch* pTouch, Event* pEvent)
{
	
	auto target = static_cast<Sprite*>(pEvent->getCurrentTarget());//ªÒ»°µƒµ±«∞¥•√˛µƒƒø±Í  

	Point locationInNode = target->convertToNodeSpace(pTouch->getLocation());
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);

	if (rect.containsPoint(locationInNode)) {
		
		if (target->getName() == "xiangyou_7"){
			float targetscale = 1.2928f;
			auto targetScTo = ScaleTo::create(0.108f, targetscale);
			target->runAction(targetScTo);
		}

		
		return true;
	}
	else {
		return false;
	};
	
}


void GameScene::TouchEnded(Touch* pTouch, Event* pEvent)
{
	auto target = static_cast<Sprite*>(pEvent->getCurrentTarget()); 

	Point locationInNode = target->convertToNodeSpace(pTouch->getLocation());
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);
	if (target->getName() == "xiangyou_7"){

		//loadNode->runAction(loadaction)
		auto targetScTo2 = ScaleTo::create(0.217f, 1.0f);
		target->stopAllActions();
		target->runAction(targetScTo2);
	}
	if (rect.containsPoint(locationInNode)) { 
		//auto name = String::createWithFormat("%s2", i)->_string;
		CCLOG("spite : %s", target->getName().c_str());
		if (target->getName() == "xiangyou_7"){
			if (target->isVisible()){
				loadactiongotoFrameAndPause(0);
				
			}
			//target->setVisible(false);
			return;
		}
		else{
			//CCLOG("target : %s,", target->getName().c_str());
			clickwup(target->getName());
		}

		
		

		
	}


}
void GameScene::loop(float dt)
{
	//int rdoneEmy = fbnqsl;//第一行消失的速度正比
	if (++tistime > 5){
		tistime = 0;
		tisikuang->setVisible(false);
		this->unschedule(schedule_selector(GameScene::loop));
	}
		
}

void GameScene::update(float delta)
{
	
	
	
}


void GameScene::loadactiongotoFrameAndPause(int Num){
	loadaction->gotoFrameAndPause(Num);
	for (XMLElement* e = guankaspming->FirstChildElement(); e; e = e->NextSiblingElement()) {//解决跳帧回来变初始显示
		for (const XMLAttribute* attr = e->FirstAttribute(); attr; attr = attr->Next()) {
			std::string attrname = attr->Name();
			if (attrname == "setvisible"){
				rootNode->getChildByName(e->Name())->setVisible(attr->BoolValue());
			}
		}
	}

}
void GameScene::clickwup(std::string targetname, bool isfan,XMLElement* xmlfanwei){
	if (!xmlfanwei){
		xmlfanwei = guankaspming;//关卡物品
	}
	auto target = (Sprite*)rootNode->getChildByName(targetname);
	for (XMLElement* e = xmlfanwei->FirstChildElement(); e; e = e->NextSiblingElement()) {//e
		// 子元素e 为文本内容
		// GetText() : 文本内容
		if (e->Name() == targetname){//找到target，e为当前点击的
			//CCLOG("target : %s, e:%s,", target->getName().c_str(), e->Name());

			for (const XMLAttribute* attr = e->FirstAttribute(); attr; attr = attr->Next()) {
				// Name()  : 属性名称
				// Value() : 属性值

				//auto attrname = String::createWithFormat("%s", attr->Name())->_string;
				CCLOG("attr : %s,%d", attr->Name(), attr->IntValue());
				std::string attrname = attr->Name();
				if (attrname == "iskezhixing"){//是否可执行 
					if (attr->BoolValue()){
						//修改为不可用


						if (e->Attribute("setkezhixing")){
							e->SetAttribute(attr->Name(), true);
						}
						else{
							e->SetAttribute(attr->Name(), false);
						}
						if (e->Attribute("setbukekvisible") ){
							if (target)
								target->setVisible(e->Attribute("setbukekvisible"));
						}
						else{
							if (e->Attribute("setvisible")){
								if(target)
									target->setVisible(e->Attribute("setvisible"));
							}
							else{
								
								e->SetAttribute("setvisible", false);
								if (target)
									target->setVisible(false);
							}
						}
					}
					else{
						return;
					}

					//CCLOG("chd_attr : %s , %d", attr->Name(), attr->IntValue());
				}
				else if (attrname == "daoqianz"){//在第几帧可用

					if (loadaction->getCurrentFrame() != attr->IntValue()){
						return;
					}
					CCLOG("chd_attr : %s , %s,%d", attr->Name(), attr->Value(), loadaction->getCurrentFrame());
				}
				else if (attrname == "isguog"&&attr->BoolValue()){//是否过关
					CCLOG("chd_attr :isguog");
				}
				else if (attrname == "tianjia"&&attr->BoolValue()){//是否添加到右边ui
					CCLOG("chd_attr :tianjia");
					XMLElement* tj = e->FirstChildElement();

					for (const XMLAttribute* tj_attr = tj->FirstAttribute(); tj_attr; tj_attr = tj_attr->Next()) {
						std::string tjrname = tj_attr->Name();
						if (tjrname == "yidzongsp"){
							Size winSize = Director::getInstance()->getVisibleSize();
							Vec2 yuyanxy = Vec2(winSize.width, winSize.height / 2);
							auto pngname = String::createWithFormat("%s.png", tj_attr->Value())->_string;

							auto moveshuView = MoveTo::create(0.628f, yuyanxy);
							auto yidspite = Sprite::createWithSpriteFrameName(pngname);
							yidspite->setPosition(target->getPosition());
							this->addChild(yidspite);
							yidspite->runAction(Sequence::create(
								moveshuView,
								CallFunc::create([=](){
								bool fist = true;
								for (const XMLAttribute* yaotjsp = tj_attr; yaotjsp; yaotjsp = yaotjsp->Next()){
									if (tj_attr->Next() && fist){
										fist = false;
										continue;
									}
									auto pngname = String::createWithFormat("%s.png", yaotjsp->Value())->_string;
									auto addspitename = String::createWithFormat("%s", yaotjsp->Value())->_string;
									auto addspite = Sprite::createWithSpriteFrameName(pngname);
									addspite->setName(addspitename);
									log("pngname:%s", addspite->getName().c_str());
									Sceneuily->setyouwup(addspite);

								}
								yidspite->removeFromParent();
								//CC_CALLBACK_0(Sprite::removeFromParent, yidspite);
							}
							),
								NULL));
							//移动代码

							break;
						}

					}

				}
				else if (attrname == "tishi"){//是否启动提示
					tistime = 0;
					tisikuang->setVisible(true);
					if (!this->isScheduled(schedule_selector(GameScene::loop)))
						this->schedule(schedule_selector(GameScene::loop), 1.0f);
					std::string attrValue = attr->Value();
					if (attrValue == "puton"){//普通提示
						tisCount->setString(putontis->FirstAttribute()->Value());
					}
					else if (attrValue == "tancts"){//有弹窗提示
						tisCount->setString(putontis->FirstChildElement()->GetText());
					}
					else if (attrValue == "gexing"){//物品个性提示
						std::string ename = e->Name();
						for (XMLElement* tise = tisspming->FirstChildElement(); tise; tise = tise->NextSiblingElement()) {
							std::string tisename = tise->Name();
							if (tisename == ename){
								tisCount->setString(tise->GetText());
								break;
							}
						
						}
					}

					CCLOG("chd_attr :tishi");
				}
				else if (attrname == "youtanc"&&attr->BoolValue()){//右边弹窗能用吗
					CCLOG("chd_attr :youtanc");
				}
				else if (attrname == "tiaozhen"){//跳到第几帧
					
					loadactiongotoFrameAndPause(attr->IntValue());
				}
				else if (attrname == "iszhanlia"){//是否粘连其他物品
					
					CCLOG("chd_attr : %s , %s", attr->Name(), attr->Value());
					for (XMLElement* a = e->FirstChildElement(); a; a = a->NextSiblingElement()) {
						if (isfan){
							CCLOG("chd_attr :22222222222");
							findwup(a, isfan);
						}
						else{
							CCLOG("chd_attr :111111111111");
							findwup(a);
						}
					}

					
				}
				//else if (attrname == "setkezhixing"){//设置是否可用
				////	CCLOG("chd_attr : %s , %s", attr->Name(), attr->BoolValue());
				//	e->SetAttribute("iskezhixing", attr->BoolValue());
				//	
				//}
				/*else if (attrname == "setvisible"){
				target->setVisible(attr->BoolValue());
				}*/
			}
			break;
		}
			
			CCLOG("e : %s ,%s, %s", e->Name(), e->Attribute("name"), e->GetText());
	}
	
}
void GameScene::findwup(XMLElement* dangqianwup, bool isfan, XMLElement* xmlfanwei){
	if (!xmlfanwei){
		xmlfanwei = guankaspming;//关卡物品
	}
	std::string dqname = dangqianwup->Name();
	for (XMLElement* e = xmlfanwei->FirstChildElement(); e; e = e->NextSiblingElement()) {//e
		// 子元素e 为文本内容
		// GetText() : 文本内容
		log("e:%s, dangqianwup:%s", e->Name(),dangqianwup->Name());
		std::string ename = e->Name();
		
		if (ename == dqname){//找到target，e为当前点击的
			
			log("3333333333333333333");
			
			for (const XMLAttribute* danattr = dangqianwup->FirstAttribute(); danattr; danattr = danattr->Next()) {
				
				if (isfan){
					
					e->SetAttribute(danattr->Name(), !danattr->BoolValue());
					log("34343434565656656");
				}
				else{
					e->SetAttribute(danattr->Name(), danattr->BoolValue());
					log("11111111111111111");
				}

			}
			break;
		}
	}
}
//掉落泡泡
//void GameScene::downBubbleAction(Bubble *pBubble)
//{
//	float offY = -298;
//
//	Point pos = pBubble->getPosition();
//	pBubble->runAction(
//			Sequence::create(
//			EaseBackIn::create(MoveTo::create((pos.y - offY ) / 600.0, ccp(pos.x, 52.8))),
//			CallFunc::create([=](){removeBubbleAction(pBubble); }),
//				NULL
//			)
//		);//CCCallFuncN::create(this, callfuncN_selector(GameScene::callbackRemoveBubble))CC_CALLBACK_0(Sprite::removeFromParent, pBubble)
//}