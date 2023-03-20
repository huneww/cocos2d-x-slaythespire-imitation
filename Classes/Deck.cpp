#include "Deck.h"

USING_NS_CC;
using namespace ui;

void Deck::Create()
{
	blayer = LayerColor::create(Color4B::BLACK);
	blayer->setOpacity(150);
	this->addChild(blayer);

	Vec2 pos = Vec2(100, 580);

	TTFConfig ttfConfig("slaythespire/GyeonggiCheonnyeonBatangBold.ttf", 15);
	TTFConfig ttfConfig_2("slaythespire/GyeonggiCheonnyeonBatangBold.ttf", 12);
	TTFConfig ttfConfig_3("slaythespire/GyeonggiCheonnyeonBatangBold.ttf", 20);

	// 현재 소지 카드 생성
	for (int i = 0; i < 12; i++)
	{
		if (i <= 5)
		{
			// 카드 백그라운드
			Card[i][0] = Sprite::create("slaythespire/cardui/cardui.png", Rect(1224, 1197, 608, 838));
			Card[i][0]->setScale(0.25f);
			Card[i][0]->setPosition(pos);
			// 카드 이미지
			Card[i][1] = Sprite::create("slaythespire/1024Portraits/red/attack/strike.png");
			Card[i][1]->setScale(0.25f);
			Card[i][1]->setPosition(Vec2(pos.x, pos.y + 40));
			// 카드 이미지 테두리
			Card[i][2] = Sprite::create("slaythespire/cardui/cardui3.png", Rect(2, 834, 523, 369));
			Card[i][2]->setScale(0.25f);
			Card[i][2]->setPosition(Vec2(pos.x, pos.y + 30));
			// 카드 이름 판넬
			Card[i][3] = Sprite::create("slaythespire/cardui/cardui.png", Rect(540, 200, 648, 153));
			Card[i][3]->setScale(0.25f);
			Card[i][3]->setPosition(Vec2(pos.x, pos.y + 85));
			// 카드 코스트
			Card[i][4] = Sprite::create("slaythespire/cardui/cardui.png", Rect(1968, 1379, 72, 71));
			Card[i][4]->setScale(0.5f);
			Card[i][4]->setPosition(Vec2(pos.x - 70, pos.y + 95));
			// 카드 코스트 폰트
			CardInfo[i][0] = Label::createWithTTF(ttfConfig, " 1 ");
			CardInfo[i][0]->enableOutline(Color4B::GRAY, 1);
			CardInfo[i][0]->setPosition(Vec2(pos.x - 70, pos.y + 95));
			CardInfo[i][0]->setZOrder(5);
			// 카드 이름
			CardInfo[i][1] = Label::createWithTTF(ttfConfig, "타격");
			CardInfo[i][1]->enableOutline(Color4B::GRAY, 1);
			CardInfo[i][1]->setPosition(Vec2(pos.x, pos.y + 94));
			CardInfo[i][1]->setZOrder(5);
			// 카드 효과
			CardInfo[i][2] = Label::createWithTTF(ttfConfig_2, "피해를 6 줍니다.");
			CardInfo[i][2]->enableOutline(Color4B::GRAY, 1);
			CardInfo[i][2]->setPosition(Vec2(pos.x, pos.y - 35));
		}
		else
		{
			// 카드 백그라운드
			Card[i][0] = Sprite::create("slaythespire/cardui/cardui3.png", Rect(2, 1205, 597, 838));
			Card[i][0]->setScale(0.25f);
			Card[i][0]->setPosition(pos);
			// 카드 이미지
			Card[i][1] = Sprite::create("slaythespire/1024Portraits/red/skill/defend.png");
			Card[i][1]->setScale(0.25f);
			Card[i][1]->setPosition(Vec2(pos.x, pos.y + 40));
			// 카드 이미지 테두리
			Card[i][2] = Sprite::create("slaythespire/cardui/cardui2.png", Rect(1179, 2, 524, 363));
			Card[i][2]->setScale(0.25f);
			Card[i][2]->setPosition(Vec2(pos.x, pos.y + 33));
			// 카드 이름 판넬
			Card[i][3] = Sprite::create("slaythespire/cardui/cardui.png", Rect(540, 200, 648, 153));
			Card[i][3]->setScale(0.25f);
			Card[i][3]->setPosition(Vec2(pos.x, pos.y + 85));
			// 카드 코스트
			Card[i][4] = Sprite::create("slaythespire/cardui/cardui.png", Rect(1968, 1379, 72, 71));
			Card[i][4]->setScale(0.5f);
			Card[i][4]->setPosition(Vec2(pos.x - 70, pos.y + 95));
			// 카드 코스트 폰트
			CardInfo[i][0] = Label::createWithTTF(ttfConfig, " 1 ");
			CardInfo[i][0]->enableOutline(Color4B::GRAY, 1);
			CardInfo[i][0]->setPosition(Vec2(pos.x - 70, pos.y + 95));
			CardInfo[i][0]->setZOrder(5);
			// 카드 이름
			CardInfo[i][1] = Label::createWithTTF(ttfConfig, "수비");
			CardInfo[i][1]->enableOutline(Color4B::GRAY, 1);
			CardInfo[i][1]->setPosition(Vec2(pos.x, pos.y + 94));
			CardInfo[i][1]->setZOrder(5);
			// 카드 효과
			CardInfo[i][2] = Label::createWithTTF(ttfConfig_2, "방어도를 5 얻습니다.");
			CardInfo[i][2]->enableOutline(Color4B::GRAY, 1);
			CardInfo[i][2]->setPosition(Vec2(pos.x, pos.y - 35));
		}
		log("%d pos : %f", i, pos.x);

		pos.x += 200;

		if (i == 4)
		{
			log("a");
			// Y 값 조정
			pos.x = 100;
			pos.y -= 230;
		}
		else if (i == 9)
		{
			log("b");
			// Y 값 조정
			pos.x = 100;
			pos.y -= 230;
		}
	}

	auto layer = LayerColor::create(Color4B::WHITE);
	layer->setContentSize(Size(1000, 800));
	layer->setPosition(Vec2(0, 0));
	layer->setOpacity(0);
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j <= 4; j++)
		{
			layer->addChild(Card[i][j]);
			if (j <= 2)
			{
				layer->addChild(CardInfo[i][j]);
			}
		}
	}

	auto scrollView = ScrollView::create();
	scrollView->setContentSize(Size(1000, 800));
	scrollView->setInnerContainerSize(scrollView->getContentSize());
	scrollView->setDirection(ScrollView::Direction::VERTICAL);
	scrollView->setBounceEnabled(true);
	scrollView->setScrollBarAutoHideEnabled(true);

	scrollView->addChild(layer);
	scrollView->setPosition(Vec2(200, 20));
	this->addChild(scrollView);

	// 뒤로가기 버튼 생성
	{
		CancleButtonShadow = Sprite::create("slaythespire/ui/topPanel/cancelButtonShadow.png");
		CancleButtonShadow->setPosition(Vec2(170, 50));
		CancleButtonShadow->setScale(0.7f);
		this->addChild(CancleButtonShadow);

		CancleButtonOutLine = Sprite::create("slaythespire/ui/topPanel/cancelButtonOutline.png");
		CancleButtonOutLine->setPosition(Vec2(180, 50));
		CancleButtonOutLine->setScale(0.7f);
		CancleButtonOutLine->setColor(Color3B(113, 93, 44));
		auto Fadein = FadeIn::create(1.0f);
		auto Fadeout = FadeOut::create(1.0f);
		auto OutLineAction = Sequence::create(Fadeout, Fadein, nullptr);
		auto rep = RepeatForever::create(OutLineAction);
		CancleButtonOutLine->runAction(rep);
		this->addChild(CancleButtonOutLine);

		CancleButton = Sprite::create("slaythespire/ui/topPanel/cancelButton.png");
		CancleButton->setPosition(Vec2(180, 50));
		CancleButton->setScale(0.7f);
		this->addChild(CancleButton);

		// 뒤로가기 버튼 바운딩 박스
		CancleButton_Box = LayerColor::create(Color4B::WHITE, 265, 69);
		CancleButton_Box->setAnchorPoint(Vec2::ZERO);
		CancleButton_Box->setScale(0.7f);
		CancleButton_Box->setOpacity(0);
		CancleButton_Box->setPosition(Vec2(0, 70));
		CancleButton_Box->setTag(1);
		this->addChild(CancleButton_Box);
		
		CancleFont = Label::createWithTTF(ttfConfig_3, "돌아가기");
		CancleFont->setPosition(Vec2(80, 90));
		CancleFont->setTextColor(Color4B::YELLOW);
		CancleFont->enableOutline(Color4B::BLACK, 2);
		this->addChild(CancleFont);
	}
}

void Deck::Remove()
{
	this->removeAllChildren();
}
