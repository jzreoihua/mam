#include "Inputrd.h"

using namespace cocos2d;
Inputrd::Inputrd()
{
}


Inputrd::~Inputrd()
{
}
Layer* Inputrd::create(int i)
{

	Inputrd *pRet = new Inputrd();
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

bool Inputrd::init(int i)
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCLayer::init());
		strguankNum = i;
		mimaNum = 123;
		strmimaNum = "";
		ZipUtils::setPvrEncryptionKey(0x4ab3603a, 0x654c9a30, 0x55be3b35, 0xa7337055);
		Size winSize = Director::getInstance()->getVisibleSize();
		auto InputeNode = CSLoader::createNode("csb/InputwordScene.csb");
		InputeNode->setPosition(Point::ZERO);
		InputeNode->setAnchorPoint(Point::ZERO);
		this->addChild(InputeNode);
		log("1");
		

		InputeNode->getChildByName("moceng")->setPositionX(winSize.width / 2);

		ui::ImageView* szwenzi = (ui::ImageView*)InputeNode->getChildByName("moceng")->getChildByName("insweiz");
		gNumCount = Label::createWithCharMap("res/mimawenzi.png", 46, 49, '0');
		gNumCount->setString(std::to_string(mimaNum));
		gNumCount->setPosition(szwenzi->getPosition());
		gNumCount->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		gNumCount->setAdditionalKerning(-13);
		InputeNode->addChild(gNumCount);
		auto touchListener = EventListenerTouchOneByOne::create();

		touchListener->setSwallowTouches(true);
		touchListener->onTouchBegan = CC_CALLBACK_2(Inputrd::TouchBegan, this);

		touchListener->onTouchEnded = CC_CALLBACK_2(Inputrd::TouchEnded, this);
		for (int i = 0; i < 10; i++){
			auto ns = String::createWithFormat("Sprite_%d", i)->_string;
			_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), InputeNode->getChildByName("moceng")->getChildByName(ns));
		}


		auto tesi = (ui::Button*)InputeNode->getChildByName("moceng")->getChildByName("xiangyou_7");//���أ�x��
		tesi->addTouchEventListener(CC_CALLBACK_2(Inputrd::btncallFunc, this));
		auto tesi1 = (ui::Button*)InputeNode->getChildByName("moceng")->getChildByName("zhenque_19");//�����ȷ
		tesi1->addTouchEventListener(CC_CALLBACK_2(Inputrd::btncallFunc, this));
		auto tesi2 = (ui::Button*)InputeNode->getChildByName("moceng")->getChildByName("xiaochu");//�����������
		tesi2->addTouchEventListener(CC_CALLBACK_2(Inputrd::btncallFunc, this));
		

		bRet = true;
	} while (0);

	return bRet;
}


void Inputrd::btncallFunc(Object *pSender, cocos2d::ui::Button::TouchEventType type){
	auto butten = (Sprite*)pSender;
	unsigned int tag = butten->getTag();
	auto targetScTo = ScaleTo::create(0.174f, 1.0928f);
	auto targetScTo2 = ScaleTo::create(0.117f, 1.0f);
	switch (type)
	{
	case ui::Button::TouchEventType::BEGAN:
		butten->runAction(targetScTo);
		break;
	case ui::Button::TouchEventType::MOVED:

		break;

	case ui::Button::TouchEventType::ENDED:

			butten->stopAllActions();
			
			butten->runAction(targetScTo2);

			if (butten->getName() == "xiangyou_7")//���أ�x��
			{
				this->removeFromParent();
			}
			else if (butten->getName() == "zhenque_19")//�����ȷ
			{
			
			}
			else if (butten->getName() == "xiaochu")//�����������
			{
				strmimaNum = "";
				gNumCount->setString(strmimaNum);
			}
			
		
		break;

	case ui::Button::TouchEventType::CANCELED:
		butten->stopAllActions();
		
		butten->runAction(targetScTo2);
		break;


	}
}
bool Inputrd::TouchBegan(Touch* pTouch, Event* pEvent)
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


void Inputrd::TouchEnded(Touch* pTouch, Event* pEvent)
{
	auto target = static_cast<Sprite*>(pEvent->getCurrentTarget());

	
	auto targetScTo2 = ScaleTo::create(0.217f, 1.0f);
	target->stopAllActions();
	target->runAction(targetScTo2);
	Point locationInNode = target->convertToNodeSpace(pTouch->getLocation());
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);


	if (rect.containsPoint(locationInNode)&&target->isVisible()) {
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
		if (strlen(strmimaNum.c_str()) < 4){
			const char *chalSprite2name = target->getName().c_str();
			int cnt_int = strlen(chalSprite2name);//z�ַ�����
			int intchar = chalSprite2name[cnt_int - 1] - '0';
			
			//strncpy(charmimamun, chalSprite2name + cnt_int - 1, 1);//��ȡ���һ���ַ�
			log("cnt_int=%d", chalSprite2name[cnt_int - 1]);
			strmimaNum = strmimaNum + std::to_string(intchar);
			log(strmimaNum.c_str());
			gNumCount->setString(strmimaNum);
		}
		
	}

	//Director::getInstance()->replaceScene(GameScene::scene());
}
