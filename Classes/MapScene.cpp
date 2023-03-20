#include "MapScene.h"

USING_NS_CC;
using namespace ui;

void MapScene::CreateMap()
{
	MapSprite();
	MapFont();
	floor = 14;
	circlecount = 0;
	user = UserDefault::getInstance();
}

void MapScene::MapSprite()
{
	blayer = LayerColor::create(Color4B::BLACK);
	blayer->setOpacity(200);
	blayer->setName("Map_blayer");
	this->addChild(blayer);

	//  �� ����
	{
		// ���� ��׶���
		Map[0] = Sprite::create("slaythespire/ui/map/mapBot.png");
		Map[1] = Sprite::create("slaythespire/ui/map/mapMid.png");
		Map[2] = Sprite::create("slaythespire/ui/map/mapMid.png");
		Map[3] = Sprite::create("slaythespire/ui/map/mapTop.png");
		for (int i = 0; i < 4; i++)
		{
			Map[i]->setScale(0.5f);
			Map[i]->setPosition(Vec2(640, (i * 540) + 300));
		}

		// ���� ������ ���� ��׶���
		IconInfoBG = Sprite::create("slaythespire/ui/map/legend2.png");
		IconInfoBG->setPosition(Vec2(990, 330));
		IconInfoBG->setScale(0.7f);

		// ���� ������ ����
		IconInfo[0] = Sprite::create("slaythespire/ui/map/event.png");
		IconInfo[1] = Sprite::create("slaythespire/ui/map/shop.png");
		IconInfo[2] = Sprite::create("slaythespire/ui/map/chest.png");
		IconInfo[3] = Sprite::create("slaythespire/ui/map/rest.png");
		IconInfo[4] = Sprite::create("slaythespire/ui/map/monster.png");
		IconInfo[5] = Sprite::create("slaythespire/ui/map/elite.png");

		Vec2 pos = Vec2(930, 400);

		for (int i = 0; i < 6; i++)
		{
			IconInfo[i]->setPosition(pos);
			IconInfo[i]->setScale(0.45f);
			IconInfo[i]->setColor(Color3B::BLACK);
			pos.y -= 40;
		}

		// ��ġ ���� ������ ���̾�
		MaplayerC = LayerColor::create(Color4B::WHITE);
		MaplayerC->setContentSize(Size(690, 720));
		MaplayerC->setOpacity(0);
		MaplayerC->setPosition(Vec2(300, 0));
		this->addChild(MaplayerC);
	}

	// �� ������ ����
	{
		Vec2 Iconpos_1 = Map[3]->getPosition();

		// ���� ����
		BossIcon = Sprite::create("slaythespire/ui/map/boss/guardian.png");
		BossIcon->setPosition(Iconpos_1);
		BossIcon->setScale(0.7f);
		BossIcon->setColor(Color3B(21, 31, 41));
		BossIcon->setTag(14);
		BossIcon->setName("Boss");

		BossBox = LayerColor::create(Color4B::RED);
		BossBox->setOpacity(0);
		BossBox->setContentSize(Size(300, 300));
		BossBox->setPosition(Vec2(BossIcon->getPositionX() - 120,
			BossIcon->getPositionY() - 120));

		Vec2 Iconpos_2 = Vec2(640, 360);

		for (int i = 0; i < 14; i++)
		{

			// ù ��°�� ������ ����
			if (i == 0 || i == 1 || i == 2 || i == 3 || i == 6 || i == 7 || i == 8 || i == 11 || i == 12)
			{
				MapIcon[i] = Sprite::create("slaythespire/ui/map/monster.png");
				MapIcon[i]->setName("Monster");
			}
			// ���� ���� ������ �޽�
			else if (i == 4 || i == 9 || i == 13)
			{
				MapIcon[i] = Sprite::create("slaythespire/ui/map/rest.png");
				MapIcon[i]->setName("Rest");
			}
			// ����Ʈ 8%
			else if (i == 5 || i == 10)
			{
				MapIcon[i] = Sprite::create("slaythespire/ui/map/elite.png");
				MapIcon[i]->setName("Elite");
			}

			IconBox[i] = LayerColor::create(Color4B::ORANGE);
			IconBox[i]->setContentSize(Size(60, 60));
			IconBox[i]->setPosition(Vec2(
				MapIcon[i]->getPositionX() - 30,
				MapIcon[i]->getPositionY() - 30));
			IconBox[i]->setOpacity(0);

			MapIcon[i]->setColor(Color3B(21, 31, 41));
			MapIcon[i]->setScale(0.9f);
			MapIcon[i]->setPosition(Iconpos_2);
			MapIcon[i]->setTag(i);
			Iconpos_2.y += 110;
			
		}
	}

	MapIconlayer = Layer::create();
	for (int i = 0; i < 14; i++)
	{
		if (MapIcon[i] != nullptr)
			MapIconlayer->addChild(MapIcon[i]);
		if (IconBox[i] != nullptr)
			MapIconlayer->addChild(IconBox[i]);
	}
	MapIconlayer->addChild(BossIcon);
	MapIconlayer->addChild(BossBox);
	MapIconlayer->setZOrder(11);
	MapIconlayer->setPosition(Vec2::ZERO);
	this->addChild(MapIconlayer);

	// �ڷΰ��� ��ư ����
	{
		CancleButtonShadow = Sprite::create("slaythespire/ui/topPanel/cancelButtonShadow.png");
		CancleButtonShadow->setPosition(Vec2(170, 50));
		CancleButtonShadow->setScale(0.7f);
		//this->addChild(CancleButtonShadow);

		CancleButtonOutLine = Sprite::create("slaythespire/ui/topPanel/cancelButtonOutline.png");
		CancleButtonOutLine->setPosition(Vec2(180, 50));
		CancleButtonOutLine->setScale(0.7f);
		CancleButtonOutLine->setColor(Color3B(113, 93, 44));
		auto Fadein = FadeIn::create(1.0f);
		auto Fadeout = FadeOut::create(1.0f);
		auto OutLineAction = Sequence::create(Fadeout, Fadein, nullptr);
		auto rep = RepeatForever::create(OutLineAction);
		CancleButtonOutLine->runAction(rep);
		//this->addChild(CancleButtonOutLine);

		CancleButton = Sprite::create("slaythespire/ui/topPanel/cancelButton.png");
		CancleButton->setPosition(Vec2(180, 50));
		CancleButton->setScale(0.7f);
		//this->addChild(CancleButton);

		// �ڷΰ��� ��ư �ٿ�� �ڽ�
		CancleButton_Box = LayerColor::create(Color4B::WHITE, 265, 69);
		CancleButton_Box->setAnchorPoint(Vec2::ZERO);
		CancleButton_Box->setScale(0.7f);
		CancleButton_Box->setOpacity(0);
		CancleButton_Box->setPosition(Vec2(0, 70));
		CancleButton_Box->setTag(1);
		//this->addChild(CancleButton_Box);
	}

	MapSpritelayer = Layer::create();
	for (int i = 0; i < 4; i++)	MapSpritelayer->addChild(Map[i]);
	MapSpritelayer->addChild(IconInfoBG);
	for (int i = 0; i < 6; i++) MapSpritelayer->addChild(IconInfo[i]);
	MapSpritelayer->addChild(CancleButtonShadow);
	MapSpritelayer->addChild(CancleButtonOutLine);
	MapSpritelayer->addChild(CancleButton);
	MapSpritelayer->addChild(CancleButton_Box);
	MapSpritelayer->setZOrder(10);
	MapSpritelayer->setPosition(Vec2::ZERO);
	MapSpritelayer->setName("MapSpritelayer");
	this->addChild(MapSpritelayer);
}

void MapScene::MapFont()
{
	TTFConfig ttfConfig("slaythespire/GyeonggiCheonnyeonBatangBold.ttf", 20);
	TTFConfig ttfConfig_2("slaythespire/GyeonggiCheonnyeonBatangBold.ttf", 28);

	Fontlayer = Layer::create();

	// ���ư���
	BackFont = Label::createWithTTF(ttfConfig, "���ư���");
	BackFont->setPosition(Vec2(80, 90));
	BackFont->setTextColor(Color4B::YELLOW);
	BackFont->enableOutline(Color4B::BLACK, 2);
	Fontlayer->addChild(BackFont);

	// ����
	IconFont = Label::createWithTTF(ttfConfig_2, "����");
	IconFont->setTextColor(Color4B::BLACK);
	IconFont->setPosition(Vec2(990, 450));
	Fontlayer->addChild(IconFont);

	// ���� ������ ����
	IconInfoFont[0] = Label::createWithTTF(ttfConfig, "����");
	IconInfoFont[1] = Label::createWithTTF(ttfConfig, "����");
	IconInfoFont[2] = Label::createWithTTF(ttfConfig, "����");
	IconInfoFont[3] = Label::createWithTTF(ttfConfig, "�޽�");
	IconInfoFont[4] = Label::createWithTTF(ttfConfig, "��");
	IconInfoFont[5] = Label::createWithTTF(ttfConfig, "����Ʈ");

	Vec2 pos = Vec2(990, 400);

	for (int i = 0; i < 6; i++)
	{
		IconInfoFont[i]->setTextColor(Color4B::BLACK);
		IconInfoFont[i]->setPosition(pos);
		pos.y -= 40;
		Fontlayer->addChild(IconInfoFont[i]);
	}

	Fontlayer->setZOrder(10);
	this->addChild(Fontlayer);
}

// ������ ��������
void MapScene::Visiblefalse()
{
	for (int i = 0; i < 4; i++)
		if (Map[i] != nullptr)
			Map[i]->setVisible(false);
	MaplayerC->setVisible(false);
	MapIconlayer->setVisible(false);
			
	MapSpritelayer->setVisible(false);
	blayer->setVisible(false);
	Fontlayer->setVisible(false);

	for (int i = 0; i < circlecount; i++)
		IconCircle[i]->setVisible(false);
}

// �ٽ� ������ ������
void MapScene::Visibletrue()
{
	for (int i = 0; i < 4; i++)
		if (Map[i] != nullptr)
			Map[i]->setVisible(true);
	MaplayerC->setVisible(true);
	MapIconlayer->setVisible(true);

	MapSpritelayer->setVisible(true);
	blayer->setVisible(true);
	Fontlayer->setVisible(true);

	for (int i = 0; i < circlecount; i++)
		IconCircle[i]->setVisible(true);
}

// ������ Ŭ�� �ݹ� �Լ�
void MapScene::MenuCallBack()
{
	auto hide = Hide::create();
	auto delaytime = DelayTime::create(1.2f);
	auto seq_1 = Sequence::createWithTwoActions(delaytime, hide);

	// ���� ���������� �ֺ��� ���� ǥ�� �� ����
	// ���� Ŭ���ÿ��� ��Ŭ �������� ����
	circlecount++;
	if (floor <= 13)
	{
		IconCircle[floor] = Sprite::create("slaythespire/ui/map/circle1.png");
		IconCircle[floor]->setPosition(MapIcon[floor]->getPosition());
		IconCircle[floor]->setZOrder(12);
		IconCircle[floor]->setColor(Color3B(21, 31, 41));
		IconCircle[floor]->setScale(0.9f);

		// �����ϰ� ������ ������
		float random = RandomHelper::random_int(1, 360);
		IconCircle[floor]->setRotation(random);

		this->addChild(IconCircle[floor]);

		// ��Ŭ �ִϸ��̼� ����, ��������Ʈ�� �׼� �߰�
		auto animation = Animation::create();
		animation->setDelayPerUnit(0.05f);

		{
			animation->addSpriteFrameWithFile("slaythespire/ui/map/circle2.png");
			animation->addSpriteFrameWithFile("slaythespire/ui/map/circle3.png");
			animation->addSpriteFrameWithFile("slaythespire/ui/map/circle4.png");
			animation->addSpriteFrameWithFile("slaythespire/ui/map/circle5.png");
		}

		auto animate = Animate::create(animation);

		IconCircle[floor]->runAction(animate);
	}

	// ��� ��ο����ٰ� ���������� �̵�
	auto bthis = LayerColor::create(Color4B::BLACK);
	bthis->setOpacity(0);
	bthis->setZOrder(20);
	this->addChild(bthis);

	auto fadein = FadeIn::create(1.0f);
	auto fadeout = FadeOut::create(1.0f);
	auto seq = Sequence::create(DelayTime::create(0.2f), fadein, DelayTime::create(0.3f), fadeout, RemoveSelf::create(), nullptr);

	bthis->runAction(seq);

	// ������Ÿ������ ��� �ڿ� visible�� ��ȭ
	for (int i = 0; i < 4; i++)
		Map[i]->runAction(seq_1->clone());
	MaplayerC->runAction(seq_1->clone());
	MapSpritelayer->runAction(seq_1->clone());
	MapIconlayer->runAction(seq_1->clone());;
	Fontlayer->runAction(seq_1->clone());
	blayer->runAction(seq_1->clone());
	//for (int i = 0; i <= floor; i++)
	//{
	//	if (IconCircle[i] != nullptr && IconCircle[i]->isVisible() == true)
	//		IconCircle[i]->runAction(seq_1->clone());
	//}
}