#include "GameOption.h"

USING_NS_CC;

void GameOption::CreateGameOption()
{
	OptionSprite();
	OptionFont();
}

void GameOption::OptionSprite()
{
	log("OptionSprite");
	// 반투면 레이어 생성
	auto blayer = LayerColor::create(Color4B::BLACK);
	blayer->setOpacity(200);

	// 설정 창 백그라운드
	auto BackGround = Sprite::create("slaythespire/ui/option/confirm.png");
	BackGround->setPosition(Vec2(640, 360));

	// yes 버튼
	auto Yes_Button = Sprite::create("slaythespire/ui/option/yes.png");
	Yes_Button->setPosition(Vec2(520, 220));

	// yes 버튼 바운딩 박스
	Yes_Button_Box = LayerColor::create(Color4B::WHITE);
	Yes_Button_Box->setPosition(Vec2(445, 200));
	Yes_Button_Box->setOpacity(0);
	Yes_Button_Box->setContentSize(Size(140, 45));

	// no 버튼
	auto No_Button = Sprite::create("slaythespire/ui/option/no.png");
	No_Button->setPosition(Vec2(770, 220));

	// no 버튼 바운딩 박스
	No_Button_Box = LayerColor::create(Color4B::WHITE);
	No_Button_Box->setPosition(Vec2(695, 200));
	No_Button_Box->setOpacity(0);
	No_Button_Box->setContentSize(Size(140, 45));

	auto Spritelayer = Layer::create();
	Spritelayer->addChild(blayer);
	Spritelayer->addChild(BackGround);
	Spritelayer->addChild(Yes_Button);
	Spritelayer->addChild(Yes_Button_Box);
	Spritelayer->addChild(No_Button);
	Spritelayer->addChild(No_Button_Box);
	Spritelayer->setPosition(Vec2::ZERO);
	Spritelayer->setName("Spritelayer");
	this->addChild(Spritelayer);
}

void GameOption::OptionFont()
{
	log("OptionFont");
	TTFConfig ttfConfig_1("slaythespire/GyeonggiCheonnyeonBatangBold.ttf", 18);
	TTFConfig ttfConfig_2("slaythespire/GyeonggiCheonnyeonBatangBold.ttf", 28);
	
	// yes
	auto Yes = Label::createWithTTF(ttfConfig_1, "예");
	Yes->setPosition(Vec2(510, 220));
	Yes->setTextColor(Color4B(239, 200, 81, 255));
	Yes->enableOutline(Color4B::BLACK, 1);
	Yes->setZOrder(10);

	// no
	auto No = Label::createWithTTF(ttfConfig_1, "아니요");
	No->setPosition(Vec2(780, 220));
	No->setTextColor(Color4B(239, 200, 81, 255));
	No->enableOutline(Color4B::BLACK, 1);
	No->setZOrder(10);

	// 경고 문구
	auto Warning_1 = Label::createWithTTF(ttfConfig_2, "정말로 종료하시겠습니까?");
	Warning_1->setPosition(Vec2(640, 400));
	Warning_1->setTextColor(Color4B(250, 128, 114, 255));
	Warning_1->enableOutline(Color4B::BLACK, 1);

	auto Warning_2 = Label::createWithTTF(ttfConfig_1, "종료하면 일부 데이터를 제외하고\n모든 데이터가 초기화 됩니다.", TextHAlignment::CENTER);
	Warning_2->setPosition(Vec2(640, 350));
	Warning_2->setTextColor(Color4B(239, 200, 81, 255));
	Warning_2->enableOutline(Color4B::BLACK, 1);

	auto Fontlayer = Layer::create();
	Fontlayer->addChild(Yes);
	Fontlayer->addChild(No);
	Fontlayer->addChild(Warning_1);
	Fontlayer->addChild(Warning_2);
	Fontlayer->setPosition(Vec2::ZERO);
	Fontlayer->setName("Fontlayer");
	this->addChild(Fontlayer);
}

void GameOption::Remove()
{
	this->removeChildByName("Spritelayer");
	this->removeChildByName("Fontlayer");
}