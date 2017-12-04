#include "Gameduihua.h"
#include "tinyxml2/tinyxml2.h"
using namespace cocos2d;
using namespace tinyxml2;
Gameduihua::Gameduihua()
{
}


Gameduihua::~Gameduihua()
{
}
Layer* Gameduihua::create(int i, int duint)
{

	Gameduihua *pRet = new Gameduihua();
	if (pRet && pRet->init(i, duint))
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
bool Gameduihua::init(int i, int duint)
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCLayer::init());
		//this->schedule(schedule_selector(Gameduihua::loop),0.1f);
		this->scheduleUpdate();
		isduwan = false;
		ispengbi = false;
		dtext = "";
		//strguankNum = i;
		UpdateNum = 0;
		mimaNum = 0;
		strmimaNum = "";
		ZipUtils::setPvrEncryptionKey(0x4ab3603a, 0x654c9a30, 0x55be3b35, 0xa7337055);
		Size winSize = Director::getInstance()->getVisibleSize();
		auto InputeNode = CSLoader::createNode("csb/duihua.csb");
		InputeNode->setPosition(Point::ZERO);
		InputeNode->setAnchorPoint(Point::ZERO);
		this->addChild(InputeNode);

		InputeNode->getChildByName("duhceng")->setPositionX(winSize.width / 2);

		//ui::ImageView* duihuank_3 = (ui::ImageView*)InputeNode->getChildByName("duhceng")->getChildByName("insweiz");
		//Dictionary *strings = Dictionary::createWithContentsOfFile("CHN_strings.xml");
		duihuank_3 = (Sprite*)InputeNode->getChildByName("duhceng")->getChildByName("duihuank_3");//底框
		//[1] 创建管理XML文档的对象：XMLDocument
		std::string path = "CHN_strings.xml";
		tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
		XMLError errorID = doc->LoadFile(path.c_str());

		//[3] 判断是否解析错误
		if (errorID != 0) {
			CCLOG("Parse Error!");
		}
		XMLElement* root = doc->RootElement();
		
		XMLElement* chd = root->FirstChildElement();
		for (int j = 1; j <i; j++ ) {

			CC_BREAK_IF(!chd);

			chd = chd->NextSiblingElement();//找到当前关
			
		
		}
		chd = chd->FirstChildElement();
		for (int j = 1; j <duint; j++) {

			CC_BREAK_IF(!chd);

			chd = chd->NextSiblingElement();//找到当前对话


		}
		Firstespeak = chd->FirstChildElement();
	
		strmimaNum = Firstespeak->Attribute("name");
		//log("name is %s", chd->NextSiblingElement()->Attribute("name"));
		dtext = Firstespeak->GetText();

		gNumCount = Label::createWithTTF(strmimaNum, "fonts/fanzzyuan.ttf", 18);
		//gNumCount->setString(Firstespeak->GetText());
		gNumCount->setColor(Color3B::BLACK);
		
		gNumCount->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
		//gNumCount->setAdditionalKerning(-13);//间距
		duihuank_3->addChild(gNumCount);
		//gNumCount->setScaleY(-1);
		gNumCount->setLineBreakWithoutSpace(true);
		gNumCount->setMaxLineWidth(duihuank_3->getContentSize().width*0.99);
		/*Size s = duihuank_3->getContentSize();
		s.setSize(duihuank_3->getContentSize().width*0.01, duihuank_3->getContentSize().height);
		gNumCount->setContentSize(s);*/
		//gNumCount->setDimensions(s.width,s.height);
		log("width=%f,height=%f",gNumCount->getContentSize().width, gNumCount->getContentSize().height);
		gNumCount->setPosition(duihuank_3->getContentSize().width*0.01, duihuank_3->getContentSize().height - (duihuank_3->getContentSize().height*2.1) / gNumCount->getContentSize().height);
		auto touchListener = EventListenerTouchOneByOne::create();

		touchListener->setSwallowTouches(true);
		touchListener->onTouchBegan = CC_CALLBACK_2(Gameduihua::TouchBegan, this);

		touchListener->onTouchEnded = CC_CALLBACK_2(Gameduihua::TouchEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), InputeNode->getChildByName("notouch"));

		bRet = true;
	} while (0);

	return bRet;
}


void Gameduihua::update(float delta){


		strmimaNum += dtext[mimaNum];
		log(strmimaNum.c_str());
		gNumCount->setString(strmimaNum);
		log("width=%f,height=%f", gNumCount->getContentSize().width, gNumCount->getContentSize().height);

		if (gNumCount->getContentSize().height > duihuank_3->getContentSize().height*0.88){
	
			strmimaNum = strmimaNum.substr(0, strmimaNum.length() - 6);
			gNumCount->setString(strmimaNum);
			ispengbi = true;
			this->unscheduleUpdate();
			return;
		}
		if (mimaNum < dtext.length()){
			mimaNum++;
		}
		else{
			
			
			//_scheduler->pauseTarget(this);
			this->unscheduleUpdate();
			isduwan = true;
		}


}
bool Gameduihua::TouchBegan(Touch* pTouch, Event* pEvent)
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
		auto targetScTo = ScaleTo::create(0.108f, targetscale);
		target->runAction(targetScTo);
		return true;
	}
	else{
		return false;
	}

}


void Gameduihua::TouchEnded(Touch* pTouch, Event* pEvent)
{
	auto target = static_cast<Sprite*>(pEvent->getCurrentTarget());

	
	auto targetScTo2 = ScaleTo::create(0.217f, 1.0f);
	target->stopAllActions();
	target->runAction(targetScTo2);
	Point locationInNode = target->convertToNodeSpace(pTouch->getLocation());
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);


	if (rect.containsPoint(locationInNode)&&target->isVisible()) {

		//_scheduler->pauseTarget(this);//暂停计时器
		if (!isduwan){
			
			this->unscheduleUpdate();
			if (ispengbi){
				ispengbi = false;
				strmimaNum = String::createWithFormat("%s\n", Firstespeak->Attribute("name"))->_string;
				gNumCount->setString(strmimaNum);
				mimaNum -= 5;
				dtext = Firstespeak->GetText();
				this->scheduleUpdate();
				//this->scheduleUpdate();
				return;

			}
			for (mimaNum; mimaNum < dtext.length(); mimaNum++){
				strmimaNum += dtext[mimaNum];
				gNumCount->setString(strmimaNum);
				if (gNumCount->getContentSize().height > duihuank_3->getContentSize().height*0.88){
					strmimaNum = strmimaNum.substr(0, strmimaNum.length() - 6);
					gNumCount->setString(strmimaNum);
					ispengbi = true;
					return;
				}
			}
			isduwan = true;
		}
		else{
			isduwan = false;
			Firstespeak = Firstespeak->NextSiblingElement();
			if (!Firstespeak){
				log("1111");
				this->removeFromParent();
			}
			else{
				strmimaNum = Firstespeak->Attribute("name");
				gNumCount->setString(strmimaNum);

				mimaNum = 0;
				dtext = Firstespeak->GetText();
				this->scheduleUpdate();
			}
		
		}
			






			
	
		
		//this->unschedule(schedule_selector(Gameduihua::loop));停止计时器
		//auto name = String::createWithFormat("%s2", i)->_string;
		//gNumCount->setString(std::to_string(mimaNum));
		//提取字符串中的数字
		/*auto ns = String::createWithFormat("Sprite_%d", i);
		CCString* CClSprite2name = CCString::createWithFormat("%s%d%s", "circle", i+5, "_mc");
		for (int i = 0; chalSprite2name[i] != '\0'; ++i) //当a数组元素不为结束符时.遍历字符串a.
		{
			if (chalSprite2name[i] >= '0'&& chalSprite2name[i] <= '9') //如果是数字.
			{
				cnt_int *= 10;
				cnt_int += chalSprite2name[i] - '0'; //数字字符的ascii-字符'0'的ascii码就等于该数字.
			}
		};
		mimaNum *= 10;
		mimaNum += cnt_int;
		}
		log("%d", cnt_int);*/

		

		//log(strmimaNum.c_str());
		//
		//const char *chalSprite2name = target->getName().c_str();
		//int cnt_int = strlen(chalSprite2name);//z字符长度
		//int intchar = chalSprite2name[cnt_int - 1] - '0';

		////strncpy(charmimamun, chalSprite2name + cnt_int - 1, 1);//截取最后一个字符
		//log("cnt_int=%d", chalSprite2name[cnt_int - 1]);
		//strmimaNum = strmimaNum + std::to_string(intchar);
		//log(strmimaNum.c_str());
		//gNumCount->setString(strmimaNum);
		//log("width=%f,height=%f", gNumCount->getContentSize().width, gNumCount->getContentSize().height);

		//if (gNumCount->getContentSize().height > duihuank_3->getContentSize().height){
		//	strmimaNum = "";
		//	gNumCount->setString(strmimaNum);
		//}
	}

	//Director::getInstance()->replaceScene(GameScene::scene());
}
