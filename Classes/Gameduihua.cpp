#include "Gameduihua.h"

using namespace cocos2d;
Gameduihua::Gameduihua()
{
}


Gameduihua::~Gameduihua()
{
}

bool Gameduihua::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCLayer::init());
		this->schedule(schedule_selector(Gameduihua::loop), 1.0f);
		dtext = "dihwojdaojsdasckxchdjvmxcvxcmvnmzieshjdhfjsxv�ҵĺ�ˬ�һ��̳������ѡ��������Ժó�������ó��ڷ�";
		//strguankNum = i;
		mimaNum = 123;
		strmimaNum = "";
		ZipUtils::setPvrEncryptionKey(0x4ab3603a, 0x654c9a30, 0x55be3b35, 0xa7337055);
		Size winSize = Director::getInstance()->getVisibleSize();
		auto InputeNode = CSLoader::createNode("csb/duihua.csb");
		InputeNode->setPosition(Point::ZERO);
		InputeNode->setAnchorPoint(Point::ZERO);
		this->addChild(InputeNode);

		InputeNode->getChildByName("duhceng")->setPositionX(winSize.width / 2);

		//ui::ImageView* duihuank_3 = (ui::ImageView*)InputeNode->getChildByName("duhceng")->getChildByName("insweiz");
		duihuank_3 = (Sprite*)InputeNode->getChildByName("duhceng")->getChildByName("duihuank_3");//�׿�
		gNumCount = Label::createWithCharMap("res/mimawenzi.png", 46, 49, '0');
		gNumCount->setString(std::to_string(mimaNum));
		
		gNumCount->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
		gNumCount->setAdditionalKerning(-13);
		duihuank_3->addChild(gNumCount);

		//gNumCount->setScaleY(-1);
		gNumCount->setLineBreakWithoutSpace(true);
		gNumCount->setMaxLineWidth(duihuank_3->getContentSize().width*0.99);
		/*Size s = duihuank_3->getContentSize();
		s.setSize(duihuank_3->getContentSize().width*0.01, duihuank_3->getContentSize().height);
		gNumCount->setContentSize(s);*/
		//gNumCount->setDimensions(s.width,s.height);
		log("width=%f,height=%f",gNumCount->getContentSize().width, gNumCount->getContentSize().height);
		gNumCount->setPosition(duihuank_3->getContentSize().width*0.01, duihuank_3->getContentSize().height - duihuank_3->getContentSize().height / gNumCount->getContentSize().height);
		auto touchListener = EventListenerTouchOneByOne::create();

		touchListener->setSwallowTouches(true);
		touchListener->onTouchBegan = CC_CALLBACK_2(Gameduihua::TouchBegan, this);

		touchListener->onTouchEnded = CC_CALLBACK_2(Gameduihua::TouchEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), InputeNode->getChildByName("notouch"));


		bRet = true;
	} while (0);

	return bRet;
}


void Gameduihua::loop(float){

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
		_scheduler->pauseTarget(this);//��ͣ��ʱ��
		//this->unschedule(schedule_selector(Gameduihua::loop));ֹͣ��ʱ��
		//auto name = String::createWithFormat("%s2", i)->_string;
		//gNumCount->setString(std::to_string(mimaNum));
		//��ȡ�ַ����е�����
		/*auto ns = String::createWithFormat("Sprite_%d", i);
		CCString* CClSprite2name = CCString::createWithFormat("%s%d%s", "circle", i+5, "_mc");
		for (int i = 0; chalSprite2name[i] != '\0'; ++i) //��a����Ԫ�ز�Ϊ������ʱ.�����ַ���a.
		{
			if (chalSprite2name[i] >= '0'&& chalSprite2name[i] <= '9') //���������.
			{
				cnt_int *= 10;
				cnt_int += chalSprite2name[i] - '0'; //�����ַ���ascii-�ַ�'0'��ascii��͵��ڸ�����.
			}
		};
		mimaNum *= 10;
		mimaNum += cnt_int;
		}
		log("%d", cnt_int);*/

		log(strmimaNum.c_str());
		
		const char *chalSprite2name = target->getName().c_str();
		int cnt_int = strlen(chalSprite2name);//z�ַ�����
		int intchar = chalSprite2name[cnt_int - 1] - '0';

		//strncpy(charmimamun, chalSprite2name + cnt_int - 1, 1);//��ȡ���һ���ַ�
		log("cnt_int=%d", chalSprite2name[cnt_int - 1]);
		strmimaNum = strmimaNum + std::to_string(intchar);
		log(strmimaNum.c_str());
		gNumCount->setString(strmimaNum);
		log("width=%f,height=%f", gNumCount->getContentSize().width, gNumCount->getContentSize().height);

		if (gNumCount->getContentSize().height > duihuank_3->getContentSize().height){
			strmimaNum = "";
			gNumCount->setString(strmimaNum);
		}
	}

	//Director::getInstance()->replaceScene(GameScene::scene());
}
