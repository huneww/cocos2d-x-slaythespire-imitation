#include "Battel.h"

USING_NS_CC;
using namespace ui;

void Battel::Create(std::string _name)
{
	if (_name == "Monster")
	{
		Monster();
		DrawCard();
		CharacterInfo();
		MonAction(_name);
	}
	else if (_name == "Elite")
	{
		Elite();
		DrawCard();
		CharacterInfo();
		MonAction(_name);
	}
	else if (_name == "Rest")
	{
		Rest();
	}
	else if (_name == "Shop")
	{
		Shop();
	}
	else if (_name == "Event")
	{
		Event();
	}
	else if (_name == "Boss")
	{
		Boss();
		DrawCard();
		CharacterInfo();
		MonAction(_name);
	}
	else if (_name == "Chest")
	{
		Chest();
	}
	MaxCost = 3;
	nowCost = MaxCost;
	Mon_Defend = 0;
	name = _name;
	check = 0;
	action_check = 0;
}

void Battel::Monster()
{
	cocos2d::log("Monster");

	TTFConfig ttfConfig_1("slaythespire/GyeonggiCheonnyeonBatangBold.ttf", 20);

	// 몬스터 7마리중 한 개 소환
	random = RandomHelper::random_int(1, 7);
	
	Vec2 Mon_pos = Vec2(1000, 350);

	// 이전 단계에서 만났던 적은 만나지 안도록
	while (1)
	{
		if (check == random)
			random = RandomHelper::random_int(1, 7);
		else
			break;
	}

	check = random;

	// 랜덤 핼퍼로 나온값 대입
	// 1 : 도적
	if (random == 1)
	{
		log("looter animation");

		// 대미지
		Mon_Damage = 12;

		// 몬스터 애니메이션 생성
		auto cache = SpriteFrameCache::getInstance();
		cache->addSpriteFramesWithFile("slaythespire/monsters/theBottom/looter/looter.plist");

		Vector<SpriteFrame*> animFrames;

		for (int i = 1; i <= 134; i++)
		{
			std::string _frames = StringUtils::format("looter_idle (%d).png", i);
			SpriteFrame* frame = cache->getSpriteFrameByName(_frames);
			animFrames.pushBack(frame);
		}

		Monster_sprite = Sprite::createWithSpriteFrameName("looter_idle (1).png");
		Monster_sprite->setPosition(Mon_pos);
		this->addChild(Monster_sprite);

		auto animation = Animation::createWithSpriteFrames(animFrames, 0.05f);
		auto animate = Animate::create(animation);
		auto rep = RepeatForever::create(animate);
		Monster_sprite->runAction(rep);

		// 몬스터 최대 체력
		MaxHp = RandomHelper::random_int(28, 32);
		NowHp = MaxHp;
		sprintf(Hp, "%d/%d", NowHp, MaxHp);

		mlayer = LayerColor::create(Color4B::WHITE);
		mlayer->setOpacity(0);
		mlayer->setPosition(Vec2(Monster_sprite->getPositionX() - 60, Monster_sprite->getPositionY() - 140));
		mlayer->setContentSize(Size(120, 180));
		this->addChild(mlayer);

		// 몬스터 체력바 생성
		auto Mon_Hp_Bg = Scale9Sprite::create("slaythespire/ui/combat/bodyBg.png");
		Mon_Hp_Bg->setContentSize(Size(180, 12));
		Mon_Hp_Bg->setPosition(Vec2(Monster_sprite->getPositionX(), Monster_sprite->getPositionY() - 160));
		Mon_Hp_Bg->setColor(Color3B::BLACK);
		this->addChild(Mon_Hp_Bg);

		Mon_Hp = LoadingBar::create("slaythespire/ui/combat/bodyBg.png");
		Mon_Hp->setDirection(LoadingBar::Direction::LEFT);
		Mon_Hp->setPercent(100.0f);
		Mon_Hp->setScale9Enabled(true);
		Mon_Hp->setContentSize(Size(180, 12));
		Mon_Hp->setPosition(Vec2(Monster_sprite->getPositionX(), Monster_sprite->getPositionY() - 160));
		Mon_Hp->setColor(Color3B::RED);
		this->addChild(Mon_Hp);

		Mon_Hp_Font = Label::createWithTTF(ttfConfig_1, "0/0");
		Mon_Hp_Font->setPosition(Vec2(Monster_sprite->getPositionX(), Monster_sprite->getPositionY() - 160));
		Mon_Hp_Font->enableOutline(Color4B(114, 25, 30, 255), 2);
		// 랜덤으로 뽑은 체력을 적용
		Mon_Hp_Font->setString(Hp);
		this->addChild(Mon_Hp_Font);
	}
	// 2 : 초록 벌레
	else if (random == 2)
	{
		log("louseGreen anmation");

		auto cache = SpriteFrameCache::getInstance();
		cache->addSpriteFramesWithFile("slaythespire/monsters/theBottom/louseGreen/louseGreen.plist");

		Vector<SpriteFrame*> animFrames;

		for (int i = 1; i <= 89; i++)
		{
			std::string _frames = StringUtils::format("louseGreen_idle (%d).png", i);
			SpriteFrame* frame = cache->getSpriteFrameByName(_frames);
			animFrames.pushBack(frame);
		}

		Monster_sprite = Sprite::createWithSpriteFrameName("louseGreen_idle (1).png");
		Monster_sprite->setPosition(Mon_pos);
		this->addChild(Monster_sprite);
		// 1000 360
		auto animation = Animation::createWithSpriteFrames(animFrames, 0.05f);
		auto animate = Animate::create(animation);
		auto rep = RepeatForever::create(animate);
		Monster_sprite->runAction(rep);
			
		// 몬스터 최대 체력
		MaxHp = RandomHelper::random_int(10, 15);
		NowHp = MaxHp;
		sprintf(Hp, "%d/%d", NowHp, MaxHp);

		mlayer = LayerColor::create(Color4B::WHITE);
		mlayer->setOpacity(0);
		mlayer->setPosition(Vec2(Monster_sprite->getPositionX() - 60, Monster_sprite->getPositionY() - 140));
		mlayer->setContentSize(Size(100, 100));
		this->addChild(mlayer);

		// 몬스터 체력바 생성
		auto Mon_Hp_Bg = Scale9Sprite::create("slaythespire/ui/combat/bodyBg.png");
		Mon_Hp_Bg->setContentSize(Size(180, 12));
		Mon_Hp_Bg->setPosition(Vec2(Monster_sprite->getPositionX(), Monster_sprite->getPositionY() - 160));
		Mon_Hp_Bg->setColor(Color3B::BLACK);
		this->addChild(Mon_Hp_Bg);

		Mon_Hp = LoadingBar::create("slaythespire/ui/combat/bodyBg.png");
		Mon_Hp->setDirection(LoadingBar::Direction::LEFT);
		Mon_Hp->setPercent(100.0f);
		Mon_Hp->setScale9Enabled(true);
		Mon_Hp->setContentSize(Size(180, 12));
		Mon_Hp->setPosition(Vec2(Monster_sprite->getPositionX(), Monster_sprite->getPositionY() - 160));
		Mon_Hp->setColor(Color3B::RED);
		this->addChild(Mon_Hp);

		Mon_Hp_Font = Label::createWithTTF(ttfConfig_1, "0/0");
		Mon_Hp_Font->setPosition(Vec2(Monster_sprite->getPositionX(), Monster_sprite->getPositionY() - 160));
		Mon_Hp_Font->enableOutline(Color4B(114, 25, 30, 255), 2);
		// 랜덤으로 뽑은 체력을 적용
		Mon_Hp_Font->setString(Hp);
		this->addChild(Mon_Hp_Font);
	}
	// 3: 빨간 벌레
	else if (random == 3)
	{
		log("louseRed animation");

		// 대미지
		Mon_Damage = 5;

		auto cache = SpriteFrameCache::getInstance();
		cache->addSpriteFramesWithFile("slaythespire/monsters/theBottom/louseRed/louseRed.plist");

		Vector<SpriteFrame*> animFrames;

		for (int i = 1; i <= 88; i++)
		{
			std::string _frame = StringUtils::format("louseRed_idle (%d).png", i);
			SpriteFrame* frame = cache->getSpriteFrameByName(_frame);
			animFrames.pushBack(frame);
		}

		Monster_sprite = Sprite::createWithSpriteFrameName("louseRed_idle (1).png");
		Monster_sprite->setPosition(Mon_pos);
		this->addChild(Monster_sprite);

		auto animation = Animation::createWithSpriteFrames(animFrames, 0.05f);
		auto animate = Animate::create(animation);
		auto rep = RepeatForever::create(animate);
		Monster_sprite->runAction(rep);

		// 몬스터 최대 체력
		MaxHp = RandomHelper::random_int(10, 15);
		NowHp = MaxHp;
		sprintf(Hp, "%d/%d", NowHp, MaxHp);

		mlayer = LayerColor::create(Color4B::WHITE);
		mlayer->setOpacity(0);
		mlayer->setPosition(Vec2(Monster_sprite->getPositionX() - 60, Monster_sprite->getPositionY() - 140));
		mlayer->setContentSize(Size(100, 100));
		this->addChild(mlayer);

		// 몬스터 체력바 생성
		auto Mon_Hp_Bg = Scale9Sprite::create("slaythespire/ui/combat/bodyBg.png");
		Mon_Hp_Bg->setContentSize(Size(180, 12));
		Mon_Hp_Bg->setPosition(Vec2(Monster_sprite->getPositionX(), Monster_sprite->getPositionY() - 160));
		Mon_Hp_Bg->setColor(Color3B::BLACK);
		this->addChild(Mon_Hp_Bg);

		Mon_Hp = LoadingBar::create("slaythespire/ui/combat/bodyBg.png");
		Mon_Hp->setDirection(LoadingBar::Direction::LEFT);
		Mon_Hp->setPercent(100.0f);
		Mon_Hp->setScale9Enabled(true);
		Mon_Hp->setContentSize(Size(180, 12));
		Mon_Hp->setPosition(Vec2(Monster_sprite->getPositionX(), Monster_sprite->getPositionY() - 160));
		Mon_Hp->setColor(Color3B::RED);
		this->addChild(Mon_Hp);

		Mon_Hp_Font = Label::createWithTTF(ttfConfig_1, "0/0");
		Mon_Hp_Font->setPosition(Vec2(Monster_sprite->getPositionX(), Monster_sprite->getPositionY() - 160));
		Mon_Hp_Font->enableOutline(Color4B(114, 25, 30, 255), 2);
		// 랜덤으로 뽑은 체력을 적용
		Mon_Hp_Font->setString(Hp);
		this->addChild(Mon_Hp_Font);
	}
	// 4 : 턱 벌레
	else if (random == 4)
	{
		log("jawWorm animation");

		auto cache = SpriteFrameCache::getInstance();
		cache->addSpriteFramesWithFile("slaythespire/monsters/theBottom/jawWorm/jawWorm.plist");

		Vector<SpriteFrame*> animFrames;

		for (int i = 1; i <= 64; i++)
		{
			std::string _frame = StringUtils::format("jawWorm_idle (%d).png", i);
			SpriteFrame* frame = cache->getSpriteFrameByName(_frame);
			animFrames.pushBack(frame);
		}

		Monster_sprite = Sprite::createWithSpriteFrameName("jawWorm_idle (1).png");
		Monster_sprite->setPosition(Mon_pos);
		this->addChild(Monster_sprite);

		auto animation = Animation::createWithSpriteFrames(animFrames, 0.05f);
		auto animate = Animate::create(animation);
		auto rep = RepeatForever::create(animate);
		Monster_sprite->runAction(rep);

		// 몬스터 최대 체력
		MaxHp = RandomHelper::random_int(26, 30);
		NowHp = MaxHp;
		sprintf(Hp, "%d/%d", NowHp, MaxHp);

		mlayer = LayerColor::create(Color4B::WHITE);
		mlayer->setOpacity(0);
		mlayer->setPosition(Vec2(Monster_sprite->getPositionX() - 100, Monster_sprite->getPositionY() - 140));
		mlayer->setContentSize(Size(200, 180));
		this->addChild(mlayer);

		// 몬스터 체력바 생성
		auto Mon_Hp_Bg = Scale9Sprite::create("slaythespire/ui/combat/bodyBg.png");
		Mon_Hp_Bg->setContentSize(Size(180, 12));
		Mon_Hp_Bg->setPosition(Vec2(Monster_sprite->getPositionX(), Monster_sprite->getPositionY() - 160));
		Mon_Hp_Bg->setColor(Color3B::BLACK);
		this->addChild(Mon_Hp_Bg);

		Mon_Hp = LoadingBar::create("slaythespire/ui/combat/bodyBg.png");
		Mon_Hp->setDirection(LoadingBar::Direction::LEFT);
		Mon_Hp->setPercent(100.0f);
		Mon_Hp->setScale9Enabled(true);
		Mon_Hp->setContentSize(Size(180, 12));
		Mon_Hp->setPosition(Vec2(Monster_sprite->getPositionX(), Monster_sprite->getPositionY() - 160));
		Mon_Hp->setColor(Color3B::RED);
		this->addChild(Mon_Hp);

		Mon_Hp_Font = Label::createWithTTF(ttfConfig_1, "0/0");
		Mon_Hp_Font->setPosition(Vec2(Monster_sprite->getPositionX(), Monster_sprite->getPositionY() - 160));
		Mon_Hp_Font->enableOutline(Color4B(114, 25, 30, 255), 2);
		// 랜덤으로 뽑은 체력을 적용
		Mon_Hp_Font->setString(Hp);
		this->addChild(Mon_Hp_Font);
	}
	// 5 : 광신도
	else if (random == 5)
	{
		log("cultist animation");

		Mon_pos = Vec2(1000, 330);

		// 대미지
		Mon_Damage = 3;

		firstturn = true;

		auto cache = SpriteFrameCache::getInstance();
		cache->addSpriteFramesWithFile("slaythespire/monsters/theBottom/cultist/cultist.plist");

		Vector<SpriteFrame*> animFrames;

		for (int i = 1; i <= 108; i++)
		{
			std::string _frame = StringUtils::format("cultist_idle (%d).png", i);
			SpriteFrame* frame = cache->getSpriteFrameByName(_frame);
			animFrames.pushBack(frame);
		}

		Monster_sprite = Sprite::createWithSpriteFrameName("cultist_idle (1).png");
		Monster_sprite->setPosition(Mon_pos);
		this->addChild(Monster_sprite);

		auto animation = Animation::createWithSpriteFrames(animFrames, 0.05f);
		auto animate = Animate::create(animation);
		auto rep = RepeatForever::create(animate);
		Monster_sprite->runAction(rep);

		// 몬스터 최대 체력
		MaxHp = RandomHelper::random_int(20, 28);
		NowHp = MaxHp;
		sprintf(Hp, "%d/%d", NowHp, MaxHp);

		mlayer = LayerColor::create(Color4B::WHITE);
		mlayer->setOpacity(0);
		mlayer->setPosition(Vec2(Monster_sprite->getPositionX() - 100, Monster_sprite->getPositionY() - 140));
		mlayer->setContentSize(Size(200, 180));
		this->addChild(mlayer);

		// 몬스터 체력바 생성
		auto Mon_Hp_Bg = Scale9Sprite::create("slaythespire/ui/combat/bodyBg.png");
		Mon_Hp_Bg->setContentSize(Size(180, 12));
		Mon_Hp_Bg->setPosition(Vec2(Monster_sprite->getPositionX(), Monster_sprite->getPositionY() - 130));
		Mon_Hp_Bg->setColor(Color3B::BLACK);
		this->addChild(Mon_Hp_Bg);

		Mon_Hp = LoadingBar::create("slaythespire/ui/combat/bodyBg.png");
		Mon_Hp->setDirection(LoadingBar::Direction::LEFT);
		Mon_Hp->setPercent(100.0f);
		Mon_Hp->setScale9Enabled(true);
		Mon_Hp->setContentSize(Size(180, 12));
		Mon_Hp->setPosition(Vec2(Monster_sprite->getPositionX(), Monster_sprite->getPositionY() - 130));
		Mon_Hp->setColor(Color3B::RED);
		this->addChild(Mon_Hp);

		Mon_Hp_Font = Label::createWithTTF(ttfConfig_1, "0/0");
		Mon_Hp_Font->setPosition(Vec2(Monster_sprite->getPositionX(), Monster_sprite->getPositionY() - 130));
		Mon_Hp_Font->enableOutline(Color4B(114, 25, 30, 255), 2);
		// 랜덤으로 뽑은 체력을 적용
		Mon_Hp_Font->setString(Hp);
		this->addChild(Mon_Hp_Font);
	}	
	// 6 : 슬라임 1
	else if (random == 6)
	{
		log("slime_1 animation");

		auto cache = SpriteFrameCache::getInstance();
		cache->addSpriteFramesWithFile("slaythespire/monsters/theBottom/slimeAltL/slimeAltL.plist");

		Vector<SpriteFrame*> animFrames;

		for (int i = 1; i <= 111; i++)
		{
			std::string _frame = StringUtils::format("slimeAltL_idle (%d).png", i);
			SpriteFrame* frame = cache->getSpriteFrameByName(_frame);
			animFrames.pushBack(frame);
		}

		Monster_sprite = Sprite::createWithSpriteFrameName("slimeAltL_idle (1).png");
		Monster_sprite->setPosition(Mon_pos);
		this->addChild(Monster_sprite);

		auto animation = Animation::createWithSpriteFrames(animFrames, 0.05f);
		auto animate = Animate::create(animation);
		auto rep = RepeatForever::create(animate);
		Monster_sprite->runAction(rep);

		// 몬스터 최대 체력
		MaxHp = RandomHelper::random_int(30, 36);
		NowHp = MaxHp;
		sprintf(Hp, "%d/%d", NowHp, MaxHp);

		mlayer = LayerColor::create(Color4B::WHITE);
		mlayer->setOpacity(0);
		mlayer->setPosition(Vec2(Monster_sprite->getPositionX() - 100, Monster_sprite->getPositionY() - 140));
		mlayer->setContentSize(Size(240, 100));
		this->addChild(mlayer);

		// 몬스터 체력바 생성
		auto Mon_Hp_Bg = Scale9Sprite::create("slaythespire/ui/combat/bodyBg.png");
		Mon_Hp_Bg->setContentSize(Size(180, 12));
		Mon_Hp_Bg->setPosition(Vec2(Monster_sprite->getPositionX(), Monster_sprite->getPositionY() - 160));
		Mon_Hp_Bg->setColor(Color3B::BLACK);
		this->addChild(Mon_Hp_Bg);

		Mon_Hp = LoadingBar::create("slaythespire/ui/combat/bodyBg.png");
		Mon_Hp->setDirection(LoadingBar::Direction::LEFT);
		Mon_Hp->setPercent(100.0f);
		Mon_Hp->setScale9Enabled(true);
		Mon_Hp->setContentSize(Size(180, 12));
		Mon_Hp->setPosition(Vec2(Monster_sprite->getPositionX(), Monster_sprite->getPositionY() - 160));
		Mon_Hp->setColor(Color3B::RED);
		this->addChild(Mon_Hp);

		Mon_Hp_Font = Label::createWithTTF(ttfConfig_1, "0/0");
		Mon_Hp_Font->setPosition(Vec2(Monster_sprite->getPositionX(), Monster_sprite->getPositionY() - 160));
		Mon_Hp_Font->enableOutline(Color4B(114, 25, 30, 255), 2);
		// 랜덤으로 뽑은 체력을 적용
		Mon_Hp_Font->setString(Hp);
		this->addChild(Mon_Hp_Font);
	}
	// 7 : 슬라임 2
	else if (random == 7)
	{
		log("slime_2 animation");

		auto cache = SpriteFrameCache::getInstance();
		cache->addSpriteFramesWithFile("slaythespire/monsters/theBottom/slimeL/slimeL.plist");

		Vector<SpriteFrame*> animFrames;

		for (int i = 1; i <= 112; i++)
		{
			std::string _frame = StringUtils::format("slimeL_idle (%d).png", i);
			SpriteFrame* frame = cache->getSpriteFrameByName(_frame);
			animFrames.pushBack(frame);
		}

		Monster_sprite = Sprite::createWithSpriteFrameName("slimeL_idle (1).png");
		Monster_sprite->setPosition(Mon_pos);
		this->addChild(Monster_sprite);

		auto animation = Animation::createWithSpriteFrames(animFrames, 0.05f);
		auto animate = Animate::create(animation);
		auto rep = RepeatForever::create(animate);
		Monster_sprite->runAction(rep);

		// 몬스터 최대 체력
		MaxHp = RandomHelper::random_int(30, 35);
		NowHp = MaxHp;
		sprintf(Hp, "%d/%d", NowHp, MaxHp);

		mlayer = LayerColor::create(Color4B::WHITE);
		mlayer->setOpacity(0);
		mlayer->setPosition(Vec2(Monster_sprite->getPositionX() - 140, Monster_sprite->getPositionY() - 140));
		mlayer->setContentSize(Size(280, 130));
		this->addChild(mlayer);

		// 몬스터 체력바 생성
		auto Mon_Hp_Bg = Scale9Sprite::create("slaythespire/ui/combat/bodyBg.png");
		Mon_Hp_Bg->setContentSize(Size(180, 12));
		Mon_Hp_Bg->setPosition(Vec2(Monster_sprite->getPositionX(), Monster_sprite->getPositionY() - 160));
		Mon_Hp_Bg->setColor(Color3B::BLACK);
		this->addChild(Mon_Hp_Bg);

		Mon_Hp = LoadingBar::create("slaythespire/ui/combat/bodyBg.png");
		Mon_Hp->setDirection(LoadingBar::Direction::LEFT);
		Mon_Hp->setPercent(100.0f);
		Mon_Hp->setScale9Enabled(true);
		Mon_Hp->setContentSize(Size(180, 12));
		Mon_Hp->setPosition(Vec2(Monster_sprite->getPositionX(), Monster_sprite->getPositionY() - 160));
		Mon_Hp->setColor(Color3B::RED);
		this->addChild(Mon_Hp);

		Mon_Hp_Font = Label::createWithTTF(ttfConfig_1, "0/0");
		Mon_Hp_Font->setPosition(Vec2(Monster_sprite->getPositionX(), Monster_sprite->getPositionY() - 160));
		Mon_Hp_Font->enableOutline(Color4B(114, 25, 30, 255), 2);
		// 랜덤으로 뽑은 체력을 적용
		Mon_Hp_Font->setString(Hp);
		this->addChild(Mon_Hp_Font);
	}

	Monster_sprite->setScale(0.8f);

	// 턴종료 버튼
	auto End_Turn_Bg = Sprite::create("slaythespire/ui/topPanel/endTurnButton.png");
	End_Turn_Bg->setPosition(Vec2(1150, 140));
	End_Turn_Bg->setScale(0.7f);
	this->addChild(End_Turn_Bg);

	auto End_Turn = Sprite::create("slaythespire/ui/topPanel/endTurnButtonGlow.png");
	End_Turn->setPosition(Vec2(1150, 140));
	End_Turn->setScale(0.7f);
	this->addChild(End_Turn);

	auto fadein = FadeIn::create(1.0f);
	auto fadeout = FadeOut::create(1.0f);
	auto seq_1 = Sequence::create(fadeout, fadein, nullptr);
	auto rep_1 = RepeatForever::create(seq_1);
	End_Turn->runAction(rep_1);

	auto End_Turn_Font = Label::createWithTTF(ttfConfig_1, "턴 종료");
	End_Turn_Font->setPosition(Vec2(1150, 140));
	this->addChild(End_Turn_Font);
}

void Battel::MonAction(std::string _name)
{
	TTFConfig ttfConfig_1("slaythespire/GyeonggiCheonnyeonBatangBold.ttf", 20);

	log("Mon Action");

	// 이전 행동 제거
	if (attack != nullptr)
		this->removeChild(attack);
	if (defend != nullptr)
		this->removeChild(defend);
	if (attackfont != nullptr)
		this->removeChild(attackfont);
	if (buff_sprite != nullptr)
		this->removeChild(buff_sprite);
	if (buff != nullptr && random != 5)
		this->removeChild(buff);
	if (buff_font != nullptr && random != 5)
		this->removeChild(buff_font);
	if (attack_2 != nullptr)
		this->removeChild(attack_2);
	if (attackfont_2 != nullptr)
		this->removeChild(attackfont_2);

	// 랜덤 핼퍼로 나온 random 값 대입
	if (_name == "Monster")
	{
		if (random == 1)
		{
			cocos2d::log("Looter Action");

			action = RandomHelper::random_int(1, 2);

			// 이전 행동은 하지 안도록
			while (1)
			{
				if (action_check == action)
					action = RandomHelper::random_int(1, 2);
				else
					break;
			}

			action_check = action;

			// 공격, 찌르기
			if (action == 1)
			{
				attack = Sprite::create("slaythespire/ui/intent/attack/attack_intent_2.png");
				attack->setScale(0.75f);
				attack->setPosition(Vec2(mlayer->getPositionX() + 60, mlayer->getPositionY() + 180));
				this->addChild(attack);

				attackfont = Label::createWithTTF(ttfConfig_1, "0");
				attackfont->setPosition(Vec2(mlayer->getPositionX() + 40, mlayer->getPositionY() + 170));
				this->addChild(attackfont);

				sprintf(Damage, "%d", Mon_Damage);
				attackfont->setString(Damage);
			}
			// 방어
			else if (action == 2)
			{
				defend = Sprite::create("slaythespire/ui/intent/defend.png");
				defend->setScale(0.75f);
				defend->setPosition(Vec2(mlayer->getPositionX() + 60, mlayer->getPositionY() + 180));
				this->addChild(defend);
			}
		}
		else if (random == 2)
		{
			cocos2d::log("loseGreen Action");

			action = RandomHelper::random_int(1, 2);

			// 이전 행동은 하지 안도록
			while (1)
			{
				if (action_check == action)
				{
					action = RandomHelper::random_int(1, 2);
				}
				else
					break;
			}

			action_check = action;

			// 공격
			if (action == 1)
			{
				attack = Sprite::create("slaythespire/ui/intent/attack/attack_intent_2.png");
				attack->setScale(0.75f);
				attack->setPosition(mlayer->getPositionX() + 50, mlayer->getPositionY() + 130);
				this->addChild(attack);

				attackfont = Label::createWithTTF(ttfConfig_1, "0");
				attackfont->setPosition(Vec2(mlayer->getPositionX() + 30, mlayer->getPositionY() + 120));
				this->addChild(attackfont);

				// 대미지
				Mon_Damage = RandomHelper::random_int(5, 7);

				sprintf(Damage, "%d", Mon_Damage);
				attackfont->setString(Damage);
			}
			// 방어
			else if (action == 2)
			{
				defend = Sprite::create("slaythespire/ui/intent/defend.png");
				defend->setScale(0.75f);
				defend->setPosition(Vec2(mlayer->getPositionX() + 50, mlayer->getPositionY() + 130));
				this->addChild(defend);
			}	
		}
		else if (random == 3)
		{
			cocos2d::log("loseRed Action");

			action = RandomHelper::random_int(1, 2);

			// 이전 행동은 하지 안도록
			while (1)
			{
				if (action_check == action)
				{
					action = RandomHelper::random_int(1, 2);
				}
				else
					break;
			}

			action_check = action;

			// 공격
			if (action == 1)
			{
				attack = Sprite::create("slaythespire/ui/intent/attack/attack_intent_2.png");
				attack->setScale(0.75f);
				attack->setPosition(mlayer->getPositionX() + 50, mlayer->getPositionY() + 130);
				this->addChild(attack);

				attackfont = Label::createWithTTF(ttfConfig_1, "0");
				attackfont->setPosition(Vec2(mlayer->getPositionX() + 30, mlayer->getPositionY() + 120));
				this->addChild(attackfont);

				// 대미지
				Mon_Damage = RandomHelper::random_int(5, 6);

				sprintf(Damage, "%d", Mon_Damage);
				attackfont->setString(Damage);
			}
			// 방
			else if (action == 2)
			{
				defend = Sprite::create("slaythespire/ui/intent/defend.png");
				defend->setScale(0.75f);
				defend->setPosition(Vec2(mlayer->getPositionX() + 50, mlayer->getPositionY() + 130));
				this->addChild(defend);
			}
		}
		else if (random == 4)
		{
			cocos2d::log("jawWarm Action");

			action = RandomHelper::random_int(1, 2);
			if (action == 2)
				action = 3;

			// 이전 행동은 하지 안도록
			while (1)
			{
				if (action_check == action)
				{
					action = RandomHelper::random_int(1, 2);
					if (action == 2)
						action = 3;
				}
				else
					break;
			}

			action_check = action;

			// 공격
			if (action == 1)
			{
				attack = Sprite::create("slaythespire/ui/intent/attack/attack_intent_3.png");
				attack->setScale(0.75f);
				attack->setPosition(mlayer->getPositionX() + 100, mlayer->getPositionY() + 180);
				this->addChild(attack);

				attackfont = Label::createWithTTF(ttfConfig_1, "0");
				attackfont->setPosition(Vec2(mlayer->getPositionX() + 80, mlayer->getPositionY() + 170));
				this->addChild(attackfont);

				Mon_Damage = RandomHelper::random_int(11, 12);

				sprintf(Damage, "%d", Mon_Damage);
				attackfont->setString(Damage);
			}
			// 공,방
			else if (action == 3)
			{
				attack_2 = Sprite::create("slaythespire/ui/intent/attackDefend.png");
				attack_2->setScale(0.75f);
				attack_2->setPosition(Vec2(mlayer->getPositionX() + 100, mlayer->getPositionY() + 180));
				this->addChild(attack_2);

				Mon_Damage = 7;
			}
		}
		else if (random == 5)
		{
			cocos2d::log("cultist Action");

			if (Mon_Damage == 3)
				action = 2;
			else
				action = 1;

			// 공격
			if (action == 1)
			{
				attack = Sprite::create("slaythespire/ui/intent/attack/attack_intent_3.png");
				attack->setScale(0.75f);
				attack->setPosition(mlayer->getPositionX() + 100, mlayer->getPositionY() + 220);
				this->addChild(attack);

				attackfont = Label::createWithTTF(ttfConfig_1, "0");
				attackfont->setPosition(Vec2(mlayer->getPositionX() + 80, mlayer->getPositionY() + 210));
				this->addChild(attackfont);

				sprintf(Damage, "%d", Mon_Damage);
				attackfont->setString(Damage);
			}
			// 첫 턴에는 스킬 발동
			else if (action = 2)
			{
				buff_sprite = Sprite::create("slaythespire/ui/intent/buff1.png");
				buff_sprite->setScale(0.75f);
				buff_sprite->setPosition(Vec2(mlayer->getPositionX() + 100, mlayer->getPositionY() + 220));
				this->addChild(buff_sprite);

				// firstturn 값 변경
				firstturn = false;
			}
		}
		else if (random == 6)
		{
			log("Slime_1 Action");
			action = RandomHelper::random_int(1,2);

			// 이전 행동은 하지 안도록
			while (1)
			{
				if (action_check == action)
				{
					action = RandomHelper::random_int(1, 2);
				}
				else
					break;
			}

			action_check = action;

			// 공격
			if (action == 1)
			{
				attack = Sprite::create("slaythespire/ui/intent/attack/attack_intent_2.png");
				attack->setScale(0.75f);
				attack->setPosition(mlayer->getPositionX() + 100, mlayer->getPositionY() + 140);
				this->addChild(attack);

				attackfont = Label::createWithTTF(ttfConfig_1, "0");
				attackfont->setPosition(Vec2(mlayer->getPositionX() + 80, mlayer->getPositionY() + 130));
				this->addChild(attackfont);

				Mon_Damage = RandomHelper::random_int(8, 10);

				sprintf(Damage, "%d", Mon_Damage);
				attackfont->setString(Damage);
			}
			// 방어
			else if (action == 2)
			{
				defend = Sprite::create("slaythespire/ui/intent/defend.png");
				defend->setScale(0.75f);
				defend->setPosition(Vec2(mlayer->getPositionX() + 100, mlayer->getPositionY() + 140));
				this->addChild(defend);
			}
			// 디버프
			else if (action == 4)
			{
				buff_sprite = Sprite::create("slaythespire/ui/intent/debuff1.png");
				buff_sprite->setScale(0.75f);
				buff_sprite->setPosition(Vec2(mlayer->getPositionX() + 100, mlayer->getPositionY() + 140));
				this->addChild(buff_sprite);
			}
		}
		else if (random == 7)
		{
			log("Slime_2 Action");
			action = RandomHelper::random_int(1, 2);

			// 이전 행동은 하지 안도록
			while (1)
			{
				if (action_check == action)
				{
					action = RandomHelper::random_int(1, 2);
				}
				else
					break;
			}

			action_check = action;

			// 공
			if (action == 1)
			{
				attack = Sprite::create("slaythespire/ui/intent/attack/attack_intent_2.png");
				attack->setScale(0.75f);
				attack->setPosition(mlayer->getPositionX() + 140, mlayer->getPositionY() + 160);
				this->addChild(attack);

				attackfont = Label::createWithTTF(ttfConfig_1, "0");
				attackfont->setPosition(Vec2(mlayer->getPositionX() + 120, mlayer->getPositionY() + 150));
				this->addChild(attackfont);

				Mon_Damage = RandomHelper::random_int(6, 8);

				sprintf(Damage, "%d", Mon_Damage);
				attackfont->setString(Damage);
			}
			// 방
			else if (action == 2)
			{
				defend = Sprite::create("slaythespire/ui/intent/defend.png");
				defend->setScale(0.75f);
				defend->setPosition(Vec2(mlayer->getPositionX() + 140, mlayer->getPositionY() + 160));
				this->addChild(defend);
			}
			// 디버프
			else if (action == 4)
			{
				buff = Sprite::create("slaythespire/ui/intent/debuff1.png");
				buff->setScale(0.75f);
				buff->setPosition(Vec2(mlayer->getPositionX() + 140, mlayer->getPositionY() + 160));
				this->addChild(buff);
			}
		}
	}
	else if (_name == "Elite")
	{
		if (random == 1)
		{
			log("nobGremlin");

			action = RandomHelper::random_int(1, 2);
			if (action == 2) action = 3;

			// 이전 행동은 하지 안도록
			while (1)
			{
				if (action_check == action)
				{
					action = RandomHelper::random_int(1, 2);
					if (action == 2)
						action = 3;
				}
				else
					break;
			}

			action_check = action;

			// 약한 공격
			if (action == 1)
			{
				Mon_Damage = RandomHelper::random_int(6, 8);

				attack = Sprite::create("slaythespire/ui/intent/attackDebuff.png");
				attack->setScale(0.75f);
				attack->setPosition(Vec2(mlayer->getPositionX() + 100, mlayer->getPositionY() + 280));
				this->addChild(attack);

				attackfont = Label::createWithTTF(ttfConfig_1, "0");
				attackfont->setPosition(Vec2(mlayer->getPositionX() + 80, mlayer->getPositionY() + 270));
				this->addChild(attackfont);

				sprintf(Damage, "%d", Mon_Damage);
				attackfont->setString(Damage);
			}
			// 강한 공격
			else if (action == 3)
			{
				Mon_Damage = RandomHelper::random_int(14, 16);

				attack_2 = Sprite::create("slaythespire/ui/intent/attack/attack_intent_3.png");
				attack_2->setScale(0.75f);
				attack_2->setPosition(Vec2(mlayer->getPositionX() + 100, mlayer->getPositionY() + 280));
				this->addChild(attack_2);

				attackfont_2 = Label::createWithTTF(ttfConfig_1, "0");
				attackfont_2->setPosition(Vec2(mlayer->getPositionX() + 80, mlayer->getPositionY() + 270));
				this->addChild(attackfont_2);

				sprintf(Damage, "%d", Mon_Damage);
				attackfont_2->setString(Damage);
			}
		}
		else if (random == 2)
		{
			log("lagavulin");

			// 공격 만
			action = 1;
			Mon_Damage = RandomHelper::random_int(18, 20);

			attack = Sprite::create("slaythespire/ui/intent/attack/attack_intent_4.png");
			attack->setScale(0.75f);
			attack->setPosition(Vec2(mlayer->getPositionX() + 100, mlayer->getPositionY() + 280));
			this->addChild(attack);

			attackfont = Label::createWithTTF(ttfConfig_1, "0");
			attackfont->setPosition(Vec2(mlayer->getPositionX() + 80, mlayer->getPositionY() + 270));
			this->addChild(attackfont);

			sprintf(Damage, "%d", Mon_Damage);
			attackfont->setString(Damage);
		}
	}
	else if (_name == "Boss")
	{
		log("Guardian");

		action = RandomHelper::random_int(1, 4);

		// 이전 행동은 하지 안도록
		while (1)
		{
			if (action_check == action)
			{
				action = RandomHelper::random_int(1, 4);
			}
			else
				break;
		}

		action_check = action;


		// 휠윈드
		if (action == 1)
		{
			attack = Sprite::create("slaythespire/ui/intent/attack/attack_intent_5.png");
			attack->setScale(0.75f);
			attack->setPosition(Vec2(mlayer->getPositionX() + 120, mlayer->getPositionY() + 300));
			this->addChild(attack);

			attackfont = Label::createWithTTF(ttfConfig_1, "0");
			attackfont->setPosition(Vec2(mlayer->getPositionX() + 100, mlayer->getPositionY() + 290));
			this->addChild(attackfont);

			Mon_Damage = 5;

			sprintf(Damage, "%d", Mon_Damage * 4);
			attackfont->setString(Damage);
		}
		// 방어
		else if (action == 2)
		{
			defend = Sprite::create("slaythespire/ui/intent/defend.png");
			defend->setScale(0.75f);
			defend->setPosition(Vec2(mlayer->getPositionX() + 120, mlayer->getPositionY() + 300));
			this->addChild(defend);
		}
		// 약공
		else if (action == 3)
		{
			attack_2 = Sprite::create("slaythespire/ui/intent/attack/attack_intent_3.png");
			attack_2->setScale(0.75f);
			attack_2->setPosition(Vec2(mlayer->getPositionX() + 120, mlayer->getPositionY() + 300));
			this->addChild(attack_2);

			attackfont_2 = Label::createWithTTF(ttfConfig_1, "0");
			attackfont_2->setPosition(Vec2(mlayer->getPositionX() + 100, mlayer->getPositionY() + 290));
			this->addChild(attackfont_2);

			Mon_Damage = RandomHelper::random_int(9, 10);

			sprintf(Damage, "%d", Mon_Damage);
			attackfont_2->setString(Damage);
		}
		// 더블 어택
		else if (action == 4)
		{
			attack = Sprite::create("slaythespire/ui/intent/attackBuff.png");
			attack->setScale(0.75f);
			attack->setPosition(Vec2(mlayer->getPositionX() + 120, mlayer->getPositionY() + 300));
			this->addChild(attack);

			attackfont = Label::createWithTTF(ttfConfig_1, "0");
			attackfont->setPosition(Vec2(mlayer->getPositionX() + 100, mlayer->getPositionY() + 290));
			this->addChild(attackfont);

			Mon_Damage = 8;

			sprintf(Damage, "%d", Mon_Damage * 2);
			attackfont->setString(Damage);
		}
	}
}

void Battel::MonActionAnimation(std::string _name)
{
	cocos2d::log("MonActionAnimation");

	TTFConfig ttfConfig_1("slaythespire/GyeonggiCheonnyeonBatangBold.ttf", 20);

	// 방어력이 남아있다면 제거
	if (defend_sprite != nullptr)
		this->removeChild(defend_sprite);
	if (defend_font != nullptr)
		this->removeChild(defend_font);

	// 랜덤 핼퍼로 나온값 대입
	if (_name == "Monster")
	{
		if (random == 1)
		{
			// 공
			if (action == 1)
			{
				auto slash = Sprite::create("slaythespire/vfx/combat/slash_1.png");
				slash->setRotation(-90.0f);
				slash->setPosition(Vec2(350, 340));
				slash->setOpacity(0);
				this->addChild(slash);

				auto fadein = FadeIn::create(0.1f);
				auto fadeout = FadeOut::create(0.1f);
				auto move = MoveBy::create(0.25f, Vec2(-50, 0));
				auto spawn = Spawn::create(fadein, move, nullptr);
				auto seq = Sequence::create(spawn, fadeout, RemoveSelf::create(true), nullptr);
				slash->runAction(seq);
			}
			// 방
			else if (action == 2)
			{
				// 방어도 획득 애니메이션
				auto sprite = Sprite::create("slaythespire/ui/intent/defend.png");
				sprite->setPosition(Vec2(1000, 360));
				sprite->setOpacity(0);
				this->addChild(sprite);

				auto fadeto_1 = FadeTo::create(0.25f, 255);
				auto fadeto_2 = FadeTo::create(0.25f, 0);
				auto move = MoveBy::create(0.4f, Vec2(0, -75));
				auto spawn = Spawn::create(fadeto_1, move, nullptr);
				auto seq = Sequence::create(spawn, DelayTime::create(0.5f), fadeto_2, RemoveSelf::create(), nullptr);

				sprite->runAction(seq);

				// 몬스터 방어력 저장
				Mon_Defend = 6;

				// 방어도 표시
				defend_sprite = Sprite::create("slaythespire/ui/intent/defend.png");
				defend_sprite->setPosition(Vec2(900, 190));
				defend_sprite->setScale(0.75f);
				this->addChild(defend_sprite);

				defend_font = Label::createWithTTF(ttfConfig_1, "0");
				defend_font->setPosition(Vec2(900, 190));
				defend_font->enableOutline(Color4B::BLACK, 1);
				this->addChild(defend_font);

				sprintf(Defend, "%d", Mon_Defend);
				defend_font->setString(Defend);
			}
		}
		else if (random == 2)
		{
			// 공
			if (action == 1)
			{
				auto slash = Sprite::create("slaythespire/vfx/combat/slash_1.png");
				slash->setRotation(-120.0f);
				slash->setPosition(Vec2(350, 360));
				slash->setOpacity(0);
				this->addChild(slash);

				auto fadein = FadeIn::create(0.1f);
				auto fadeout = FadeOut::create(0.1f);
				auto move = MoveBy::create(0.25f, Vec2(-50, -30));
				auto spawn = Spawn::create(fadein, move, nullptr);
				auto seq = Sequence::create(spawn, fadeout, RemoveSelf::create(true), nullptr);
				slash->runAction(seq);
			}
			// 방
			else if (action == 2)
			{
				// 방어도 획득 애니메이션
				auto sprite = Sprite::create("slaythespire/ui/intent/defend.png");
				sprite->setPosition(Vec2(1000, 360));
				sprite->setOpacity(0);
				this->addChild(sprite);

				auto fadeto_1 = FadeTo::create(0.25f, 255);
				auto fadeto_2 = FadeTo::create(0.25f, 0);
				auto move = MoveBy::create(0.4f, Vec2(0, -75));
				auto spawn = Spawn::create(fadeto_1, move, nullptr);
				auto seq = Sequence::create(spawn, DelayTime::create(0.5f), fadeto_2, RemoveSelf::create(), nullptr);

				sprite->runAction(seq);

				// 몬스터 방어력 저장
				Mon_Defend = 6;

				// 방어도 표시
				defend_sprite = Sprite::create("slaythespire/ui/intent/defend.png");
				defend_sprite->setPosition(Vec2(900, 190));
				defend_sprite->setScale(0.75f);
				this->addChild(defend_sprite);

				defend_font = Label::createWithTTF(ttfConfig_1, "0");
				defend_font->setPosition(Vec2(900, 190));
				defend_font->enableOutline(Color4B::BLACK, 1);
				this->addChild(defend_font);

				sprintf(Defend, "%d", Mon_Defend);
				defend_font->setString(Defend);
			}
			// 디버프
			else if (action == 4)
			{
				auto debuff_sprite = Sprite::create("slaythespire/vfx/web.png");
				debuff_sprite->setPosition(Vec2(350, 360));
				debuff_sprite->setOpacity(0);
				this->addChild(debuff_sprite);

				auto scale_up = ScaleBy::create(0.25f, 1.2f);
				auto fadein = FadeIn::create(0.1f);
				auto fadeout = FadeOut::create(0.1f);
				auto spawn = Spawn::create(scale_up, fadein, nullptr);
				auto seq = Sequence::create(spawn, fadeout, RemoveSelf::create(), nullptr);
				debuff_sprite->runAction(seq);
			}
		}
		else if (random == 3)
		{
			// 공
			if (action == 1)
			{
				auto slash = Sprite::create("slaythespire/vfx/combat/slash_1.png");
				slash->setRotation(-120.0f);
				slash->setPosition(Vec2(350, 360));
				slash->setOpacity(0);
				this->addChild(slash);

				auto fadein = FadeIn::create(0.1f);
				auto fadeout = FadeOut::create(0.1f);
				auto move = MoveBy::create(0.25f, Vec2(-50, -30));
				auto spawn = Spawn::create(fadein, move, nullptr);
				auto seq = Sequence::create(spawn, fadeout, RemoveSelf::create(true), nullptr);
				slash->runAction(seq);
			}
			// 방
			else if (action == 2)
			{
				// 방어도 획득 애니메이션
				auto sprite = Sprite::create("slaythespire/ui/intent/defend.png");
				sprite->setPosition(Vec2(1000, 360));
				sprite->setOpacity(0);
				this->addChild(sprite);

				auto fadeto_1 = FadeTo::create(0.25f, 255);
				auto fadeto_2 = FadeTo::create(0.25f, 0);
				auto move = MoveBy::create(0.4f, Vec2(0, -75));
				auto spawn = Spawn::create(fadeto_1, move, nullptr);
				auto seq = Sequence::create(spawn, DelayTime::create(0.5f), fadeto_2, RemoveSelf::create(), nullptr);

				sprite->runAction(seq);

				// 몬스터 방어력 저장
				Mon_Defend = 6;

				// 방어도 표시
				defend_sprite = Sprite::create("slaythespire/ui/intent/defend.png");
				defend_sprite->setPosition(Vec2(900, 190));
				defend_sprite->setScale(0.75f);
				this->addChild(defend_sprite);

				defend_font = Label::createWithTTF(ttfConfig_1, "0");
				defend_font->setPosition(Vec2(900, 190));
				defend_font->enableOutline(Color4B::BLACK, 1);
				this->addChild(defend_font);

				sprintf(Defend, "%d", Mon_Defend);
				defend_font->setString(Defend);
			}
		}
		else if (random == 4)
		{
			// 공격
			if (action == 1)
			{
				Size size = Size(60, 120);

				auto fadein = FadeIn::create(0.1f);
				auto fadeout = FadeOut::create(0.1f);
				auto move_1 = MoveBy::create(0.25f, Vec2(0, 30));
				auto move_2 = MoveBy::create(0.25f, Vec2(0, -30));

				auto spawn_1 = Spawn::create(fadein, move_1, nullptr);
				auto spawn_2 = Spawn::create(fadein, move_2, nullptr);

				auto seq_1 = Sequence::create(spawn_1, fadeout, RemoveSelf::create(), nullptr);
				auto seq_2 = Sequence::create(spawn_2, fadeout, RemoveSelf::create(), nullptr);

				auto a = Sprite::create("slaythespire/vfx/orb.png");
				a->setContentSize(size);
				a->setPosition(Vec2(260, 280));
				a->setOpacity(0);
				a->runAction(seq_1->clone());
				this->addChild(a);

				auto a_1 = Sprite::create("slaythespire/vfx/orb.png");
				a_1->setContentSize(size);
				a_1->setPosition(Vec2(260, 420));
				a_1->setOpacity(0);
				a_1->runAction(seq_2->clone());
				this->addChild(a_1);

				auto b = Sprite::create("slaythespire/vfx/orb.png");
				b->setContentSize(size);
				b->setPosition(Vec2(310, 280));
				b->setOpacity(0);
				b->runAction(seq_1->clone());
				this->addChild(b);

				auto b_1 = Sprite::create("slaythespire/vfx/orb.png");
				b_1->setContentSize(size);
				b_1->setPosition(Vec2(310, 420));
				b_1->setOpacity(0);
				b_1->runAction(seq_2->clone());
				this->addChild(b_1);

				auto c = Sprite::create("slaythespire/vfx/orb.png");
				c->setContentSize(size);
				c->setPosition(Vec2(360, 280));
				c->setOpacity(0);
				c->runAction(seq_1->clone());
				this->addChild(c);

				auto c_1 = Sprite::create("slaythespire/vfx/orb.png");
				c_1->setContentSize(size);
				c_1->setPosition(Vec2(360, 420));
				c_1->setOpacity(0);
				c_1->runAction(seq_2->clone());
				this->addChild(c_1);
			}
			// 공, 방
			else if (action == 3)
			{
				// 할퀴는 애니메이션
				auto Toenail_1 = Sprite::create("slaythespire/vfx/combat/slash_1.png");
				Toenail_1->setRotation(135.0);
				Toenail_1->setPosition(Vec2(270, 300));
				Toenail_1->setOpacity(0);
				this->addChild(Toenail_1);

				auto Toenail_2 = Sprite::create("slaythespire/vfx/combat/slash_1.png");
				Toenail_2->setRotation(135.0);
				Toenail_2->setPosition(Vec2(300, 330));
				Toenail_2->setOpacity(0);
				this->addChild(Toenail_2);

				auto Toenail_3 = Sprite::create("slaythespire/vfx/combat/slash_1.png");
				Toenail_3->setRotation(135.0);
				Toenail_3->setPosition(Vec2(330, 360));
				Toenail_3->setOpacity(0);
				this->addChild(Toenail_3);

				auto fadein = FadeIn::create(0.1f);
				auto fadeout = FadeOut::create(0.1f);
				auto move_1 = MoveBy::create(0.25f, Vec2(30, -30));
				auto spawn_1 = Spawn::create(fadein, move_1, nullptr);
				auto seq_1 = Sequence::create(spawn_1, fadeout, RemoveSelf::create(), nullptr);

				Toenail_1->runAction(seq_1->clone());
				Toenail_2->runAction(seq_1->clone());
				Toenail_3->runAction(seq_1->clone());

				// 방어도 획득 애니메이션
				auto sprite = Sprite::create("slaythespire/ui/intent/defend.png");
				sprite->setPosition(Vec2(1000, 360));
				sprite->setOpacity(0);
				this->addChild(sprite);

				auto fadeto_1 = FadeTo::create(0.25f, 255);
				auto fadeto_2 = FadeTo::create(0.25f, 0);
				auto move = MoveBy::create(0.4f, Vec2(0, -75));
				auto spawn = Spawn::create(fadeto_1, move, nullptr);
				auto seq = Sequence::create(spawn, DelayTime::create(0.5f), fadeto_2, RemoveSelf::create(), nullptr);

				sprite->runAction(seq);

				// 몬스터 방어력 저장
				Mon_Defend = 5;

				// 방어도 표시
				defend_sprite = Sprite::create("slaythespire/ui/intent/defend.png");
				defend_sprite->setPosition(Vec2(900, 190));
				defend_sprite->setScale(0.75f);
				this->addChild(defend_sprite);

				defend_font = Label::createWithTTF(ttfConfig_1, "0");
				defend_font->setPosition(Vec2(900, 190));
				defend_font->enableOutline(Color4B::BLACK, 1);
				this->addChild(defend_font);

				sprintf(Defend, "%d", Mon_Defend);
				defend_font->setString(Defend);
			}
		}
		else if (random == 5)
		{
			// 공
			if (action == 1)
			{
				auto slash = Sprite::create("slaythespire/vfx/combat/slash_1.png");
				slash->setRotation(-120.0f);
				slash->setPosition(Vec2(350, 360));
				slash->setOpacity(0);
				this->addChild(slash);

				auto fadein = FadeIn::create(0.1f);
				auto fadeout = FadeOut::create(0.1f);
				auto move = MoveBy::create(0.25f, Vec2(-50, -30));
				auto spawn = Spawn::create(fadein, move, nullptr);
				auto seq = Sequence::create(spawn, fadeout, RemoveSelf::create(true), nullptr);
				slash->runAction(seq);
			}
			// 버프
			else if (action == 2)
			{
				// 체력바 하단에 버프 표시
				TTFConfig ttfConfig_2("slaythespire/GyeonggiCheonnyeonBatangBold.ttf", 12);

				buff = Sprite::create("slaythespire/ui/intent/tip/3.png");
				buff->setScale(0.35f);
				buff->setPosition(Vec2(920, 180));
				this->addChild(buff);

				buff_font = Label::createWithTTF(ttfConfig_2, "0");
				buff_font->setPosition(Vec2(915, 175));
				buff_font->setColor(Color3B::GREEN);
				this->addChild(buff_font);
			}
			char changebuff[100];
			sprintf(changebuff, "%d", Mon_Damage);
			buff_font->setString(changebuff);

			// 대미지 점차 증가
			Mon_Damage += 3;
		}
		else if (random == 6)
		{
			// 공
			if (action == 1)
			{
				auto slash = Sprite::create("slaythespire/vfx/combat/slash_1.png");
				slash->setRotation(-120.0f);
				slash->setPosition(Vec2(350, 360));
				slash->setOpacity(0);
				this->addChild(slash);

				auto fadein = FadeIn::create(0.1f);
				auto fadeout = FadeOut::create(0.1f);
				auto move = MoveBy::create(0.25f, Vec2(-50, -30));
				auto spawn = Spawn::create(fadein, move, nullptr);
				auto seq = Sequence::create(spawn, fadeout, RemoveSelf::create(true), nullptr);
				slash->runAction(seq);
			}
			// 방
			else if (action == 2)
			{
				// 방어도 획득 애니메이션
				auto sprite = Sprite::create("slaythespire/ui/intent/defend.png");
				sprite->setPosition(Vec2(1000, 360));
				sprite->setOpacity(0);
				this->addChild(sprite);

				auto fadeto_1 = FadeTo::create(0.25f, 255);
				auto fadeto_2 = FadeTo::create(0.25f, 0);
				auto move = MoveBy::create(0.4f, Vec2(0, -75));
				auto spawn = Spawn::create(fadeto_1, move, nullptr);
				auto seq = Sequence::create(spawn, DelayTime::create(0.5f), fadeto_2, RemoveSelf::create(), nullptr);

				sprite->runAction(seq);

				// 몬스터 방어력 저장
				Mon_Defend = 3;

				// 방어도 표시
				defend_sprite = Sprite::create("slaythespire/ui/intent/defend.png");
				defend_sprite->setPosition(Vec2(900, 190));
				defend_sprite->setScale(0.75f);
				this->addChild(defend_sprite);

				defend_font = Label::createWithTTF(ttfConfig_1, "0");
				defend_font->setPosition(Vec2(900, 190));
				defend_font->enableOutline(Color4B::BLACK, 1);
				this->addChild(defend_font);

				sprintf(Defend, "%d", Mon_Defend);
				defend_font->setString(Defend);
			}
			// 디버프
			else if (action == 4)
			{
				auto debuff_sprite = Sprite::create("slaythespire/vfx/web.png");
				debuff_sprite->setPosition(Vec2(350, 360));
				debuff_sprite->setOpacity(0);
				this->addChild(debuff_sprite);

				auto scale_up = ScaleBy::create(0.25f, 1.2f);
				auto fadein = FadeIn::create(0.1f);
				auto fadeout = FadeOut::create(0.1f);
				auto spawn = Spawn::create(scale_up, fadein, nullptr);
				auto seq = Sequence::create(spawn, fadeout, RemoveSelf::create(), nullptr);
				debuff_sprite->runAction(seq);
			}
		}
		else if (random == 7)
		{
			// 공
			if (action == 1)
			{
				auto slash = Sprite::create("slaythespire/vfx/combat/slash_1.png");
				slash->setRotation(-120.0f);
				slash->setPosition(Vec2(350, 360));
				slash->setOpacity(0);
				this->addChild(slash);

				auto fadein = FadeIn::create(0.1f);
				auto fadeout = FadeOut::create(0.1f);
				auto move = MoveBy::create(0.25f, Vec2(-50, -30));
				auto spawn = Spawn::create(fadein, move, nullptr);
				auto seq = Sequence::create(spawn, fadeout, RemoveSelf::create(true), nullptr);
				slash->runAction(seq);
			}
			// 방
			else if (action == 2)
			{
				// 방어도 획득 애니메이션
				auto sprite = Sprite::create("slaythespire/ui/intent/defend.png");
				sprite->setPosition(Vec2(1000, 360));
				sprite->setOpacity(0);
				this->addChild(sprite);

				auto fadeto_1 = FadeTo::create(0.25f, 255);
				auto fadeto_2 = FadeTo::create(0.25f, 0);
				auto move = MoveBy::create(0.4f, Vec2(0, -75));
				auto spawn = Spawn::create(fadeto_1, move, nullptr);
				auto seq = Sequence::create(spawn, DelayTime::create(0.5f), fadeto_2, RemoveSelf::create(), nullptr);

				sprite->runAction(seq);

				// 몬스터 방어력 저장
				Mon_Defend = 3;

				// 방어도 표시
				defend_sprite = Sprite::create("slaythespire/ui/intent/defend.png");
				defend_sprite->setPosition(Vec2(900, 190));
				defend_sprite->setScale(0.75f);
				this->addChild(defend_sprite);

				defend_font = Label::createWithTTF(ttfConfig_1, "0");
				defend_font->setPosition(Vec2(900, 190));
				defend_font->enableOutline(Color4B::BLACK, 1);
				this->addChild(defend_font);

				sprintf(Defend, "%d", Mon_Defend);
				defend_font->setString(Defend);
			}
			// 디버프
			else if (action == 4)
			{
				auto debuff_sprite = Sprite::create("slaythespire/vfx/web.png");
				debuff_sprite->setPosition(Vec2(350, 360));
				debuff_sprite->setOpacity(0);
				this->addChild(debuff_sprite);

				auto scale_up = ScaleBy::create(0.25f, 1.2f);
				auto fadein = FadeIn::create(0.1f);
				auto fadeout = FadeOut::create(0.1f);
				auto spawn = Spawn::create(scale_up, fadein, nullptr);
				auto seq = Sequence::create(spawn, fadeout, RemoveSelf::create(), nullptr);
				debuff_sprite->runAction(seq);
			}
		}

		auto attackanimation = Sprite::create("slaythespire/vfx/combat/slash_1.png");
		attackanimation->setRotation(135.0);
		attackanimation->setPosition(Vec2(320, 360));
		attackanimation->setOpacity(0);
		this->addChild(attackanimation);

		auto move_1 = MoveTo::create(0.25f, Vec2(300, 340));
		auto fadein = FadeIn::create(0.25f);
		auto spawn = Spawn::create(move_1, fadein, RemoveSelf::create(true), nullptr);
		attackanimation->runAction(spawn);
	}
	else if (_name == "Elite")
	{
		if (random == 1)
		{
			// 약공
			if (action == 1)
			{
				auto slash = Sprite::create("slaythespire/vfx/combat/slash_1.png");
				slash->setRotation(180.0f);
				slash->setPosition(Vec2(340, 400));
				slash->setOpacity(0);
				this->addChild(slash);

				auto fadein = FadeIn::create(0.1f);
				auto fadeout = FadeOut::create(0.1f);
				auto move = MoveBy::create(0.25f, Vec2(0, -50));
				auto spawn = Spawn::create(fadein, move, nullptr);
				auto seq = Sequence::create(spawn, fadeout, RemoveSelf::create(true), nullptr);
				slash->runAction(seq);
			}
			// 강공
			else if (action == 3)
			{
				auto slash = Sprite::create("slaythespire/vfx/combat/slash_1.png");
				slash->setRotation(-120.0f);
				slash->setPosition(Vec2(350, 360));
				slash->setOpacity(0);
				this->addChild(slash);

				auto fadein = FadeIn::create(0.1f);
				auto fadeout = FadeOut::create(0.1f);
				auto move = MoveBy::create(0.25f, Vec2(-50, -30));
				auto spawn = Spawn::create(fadein, move, nullptr);
				auto seq = Sequence::create(spawn, fadeout, RemoveSelf::create(true), nullptr);
				slash->runAction(seq);
			}
		}
		else if (random == 2)
		{
			// 공
			if (action == 1)
			{
				auto slash = Sprite::create("slaythespire/vfx/combat/slash_1.png");
				slash->setRotation(-120.0f);
				slash->setPosition(Vec2(350, 360));
				slash->setOpacity(0);
				this->addChild(slash);

				auto fadein = FadeIn::create(0.1f);
				auto fadeout = FadeOut::create(0.1f);
				auto move = MoveBy::create(0.25f, Vec2(-50, -30));
				auto spawn = Spawn::create(fadein, move, nullptr);
				auto seq = Sequence::create(spawn, fadeout, RemoveSelf::create(true), nullptr);
				slash->runAction(seq);
			}
		}
	}
	else if (_name == "Boss")
	{

		// 휠윈드
		if (action == 1)
		{
			// GameScene에서 애니메이션 실행
		}
		// 방어
		else if (action == 2)
		{
			// 방어도 획득 애니메이션
			auto sprite = Sprite::create("slaythespire/ui/intent/defend.png");
			sprite->setPosition(Vec2(1000, 360));
			sprite->setOpacity(0);
			this->addChild(sprite);

			auto fadeto_1 = FadeTo::create(0.25f, 255);
			auto fadeto_2 = FadeTo::create(0.25f, 0);
			auto move = MoveBy::create(0.4f, Vec2(0, -75));
			auto spawn = Spawn::create(fadeto_1, move, nullptr);
			auto seq = Sequence::create(spawn, DelayTime::create(0.5f), fadeto_2, RemoveSelf::create(), nullptr);

			sprite->runAction(seq);

			// 몬스터 방어력 저장
			Mon_Defend = 9;

			// 방어도 표시
			defend_sprite = Sprite::create("slaythespire/ui/intent/defend.png");
			defend_sprite->setPosition(Vec2(900, 190));
			defend_sprite->setScale(0.75f);
			this->addChild(defend_sprite);

			defend_font = Label::createWithTTF(ttfConfig_1, "0");
			defend_font->setPosition(Vec2(900, 190));
			defend_font->enableOutline(Color4B::BLACK, 1);
			this->addChild(defend_font);

			sprintf(Defend, "%d", Mon_Defend);
			defend_font->setString(Defend);
		}
		// 약공
		else if (action == 3)
		{
			auto slash = Sprite::create("slaythespire/vfx/combat/slash_1.png");
			slash->setRotation(-120.0f);
			slash->setPosition(Vec2(350, 360));
			slash->setOpacity(0);
			this->addChild(slash);

			auto fadein = FadeIn::create(0.1f);
			auto fadeout = FadeOut::create(0.1f);
			auto move = MoveBy::create(0.25f, Vec2(-50, -30));
			auto spawn = Spawn::create(fadein, move, nullptr);
			auto seq = Sequence::create(spawn, fadeout, RemoveSelf::create(true), nullptr);
			slash->runAction(seq);
		}
		// 더블 어택
		else if (action == 4)
		{
			// GameScene에서 애니메이션 실행
		}
	}
}

void Battel::Elite()
{
	TTFConfig ttfConfig_1("slaythespire/GyeonggiCheonnyeonBatangBold.ttf", 20);

	cocos2d::log("Elite");
	// 앨리트 3마리중 한 마리 소환
	random = RandomHelper::random_int(1, 2);

	Vec2 Mon_pos = Vec2(1000, 380);

	if (random == 1)
	{
		auto cache = SpriteFrameCache::getInstance();
		cache->addSpriteFramesWithFile("slaythespire/monsters/theBottom/Elite/nobGremlin/nobGremlin.plist");

		Vector<SpriteFrame*> animFrames;

		for (int i = 0; i < 89; i++)
		{
			std::string _frame = StringUtils::format("skeleton_a_60_%03d.png", i);
			auto frame = cache->getSpriteFrameByName(_frame);
			animFrames.pushBack(frame);
		}

		Monster_sprite = Sprite::createWithSpriteFrameName("skeleton_a_60_000.png");
		Monster_sprite->setPosition(Mon_pos);
		this->addChild(Monster_sprite);

		auto animation = Animation::createWithSpriteFrames(animFrames, 0.05f);
		auto animate = Animate::create(animation);
		auto rep = RepeatForever::create(animate);
		Monster_sprite->runAction(rep);

		// 몬스터 최대 체력
		MaxHp = RandomHelper::random_int(46, 50);
		NowHp = MaxHp;
		sprintf(Hp, "%d/%d", NowHp, MaxHp);

	}
	else if (random == 2)
	{
		auto cache = SpriteFrameCache::getInstance();
		cache->addSpriteFramesWithFile("slaythespire/monsters/theBottom/Elite/lagavulin/lagavulin.plist");

		Vector<SpriteFrame*> animFrames;

		for (int i = 0; i < 54; i++)
		{
			std::string _frame = StringUtils::format("skeleton_I_60_%03d.png", i);
			SpriteFrame* frame = cache->getSpriteFrameByName(_frame);
			animFrames.pushBack(frame);
		}

		Monster_sprite = Sprite::createWithSpriteFrameName("skeleton_I_60_000.png");
		Monster_sprite->setPosition(Mon_pos);
		this->addChild(Monster_sprite);

		auto animation = Animation::createWithSpriteFrames(animFrames, 0.05f);
		auto animate = Animate::create(animation);
		auto rep = RepeatForever::create(animate);
		Monster_sprite->runAction(rep);

		// 몬스터 최대 체력
		MaxHp = RandomHelper::random_int(56, 60);
		NowHp = MaxHp;
		sprintf(Hp, "%d/%d", NowHp, MaxHp);
	}

	mlayer = LayerColor::create(Color4B::WHITE);
	mlayer->setOpacity(0);
	mlayer->setPosition(Vec2(Monster_sprite->getPositionX() - 110, Monster_sprite->getPositionY() - 170));
	mlayer->setContentSize(Size(240, 240));
	this->addChild(mlayer);

	// 몬스터 체력바 생성
	auto Mon_Hp_Bg = Scale9Sprite::create("slaythespire/ui/combat/bodyBg.png");
	Mon_Hp_Bg->setContentSize(Size(180, 12));
	Mon_Hp_Bg->setPosition(Vec2(Monster_sprite->getPositionX(), Monster_sprite->getPositionY() - 180));
	Mon_Hp_Bg->setColor(Color3B::BLACK);
	this->addChild(Mon_Hp_Bg);

	Mon_Hp = LoadingBar::create("slaythespire/ui/combat/bodyBg.png");
	Mon_Hp->setDirection(LoadingBar::Direction::LEFT);
	Mon_Hp->setPercent(100.0f);
	Mon_Hp->setScale9Enabled(true);
	Mon_Hp->setContentSize(Size(180, 12));
	Mon_Hp->setPosition(Vec2(Monster_sprite->getPositionX(), Monster_sprite->getPositionY() - 180));
	Mon_Hp->setColor(Color3B::RED);
	this->addChild(Mon_Hp);

	Mon_Hp_Font = Label::createWithTTF(ttfConfig_1, "0/0");
	Mon_Hp_Font->setPosition(Vec2(Monster_sprite->getPositionX(), Monster_sprite->getPositionY() - 180));
	Mon_Hp_Font->enableOutline(Color4B(114, 25, 30, 255), 2);
	// 랜덤으로 뽑은 체력을 적용
	Mon_Hp_Font->setString(Hp);
	this->addChild(Mon_Hp_Font);

	// 턴종료 버튼
	auto End_Turn_Bg = Sprite::create("slaythespire/ui/topPanel/endTurnButton.png");
	End_Turn_Bg->setPosition(Vec2(1150, 140));
	End_Turn_Bg->setScale(0.7f);
	this->addChild(End_Turn_Bg);

	auto End_Turn = Sprite::create("slaythespire/ui/topPanel/endTurnButtonGlow.png");
	End_Turn->setPosition(Vec2(1150, 140));
	End_Turn->setScale(0.7f);
	this->addChild(End_Turn);

	auto fadein = FadeIn::create(1.0f);
	auto fadeout = FadeOut::create(1.0f);
	auto seq_1 = Sequence::create(fadeout, fadein, nullptr);
	auto rep_1 = RepeatForever::create(seq_1);
	End_Turn->runAction(rep_1);

	auto End_Turn_Font = Label::createWithTTF(ttfConfig_1, "턴 종료");
	End_Turn_Font->setPosition(Vec2(1150, 140));
	this->addChild(End_Turn_Font);
}

void Battel::Shop()
{
	cocos2d::log("Shop");
}

void Battel::Event()
{
	cocos2d::log("Event");
}

void Battel::Boss()
{
	cocos2d::log("Boss");

	TTFConfig ttfConfig_1("slaythespire/GyeonggiCheonnyeonBatangBold.ttf", 20);

	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("slaythespire/monsters/theBottom/boss/guardian/guardian.plist");

	Vector<SpriteFrame*> animFrames;

	for (int i = 0; i < 67; i++)
	{
		std::string _frame = StringUtils::format("skeleton_i_60_%03d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(_frame);
		animFrames.pushBack(frame);
	}

	Vec2 Mon_pos = Vec2(1000, 340);
	
	Monster_sprite = Sprite::createWithSpriteFrameName("skeleton_i_60_000.png");
	Monster_sprite->setPosition(Mon_pos);
	Monster_sprite->setScale(0.45f);
	this->addChild(Monster_sprite);

	auto animation = Animation::createWithSpriteFrames(animFrames, 0.05f);
	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);
	Monster_sprite->runAction(rep);

	// 몬스터 최대 체력
	MaxHp = 180;
	NowHp = 11;
	sprintf(Hp, "%d/%d", NowHp, MaxHp);

	mlayer = LayerColor::create(Color4B::WHITE);
	mlayer->setOpacity(0);
	mlayer->setPosition(Vec2(Monster_sprite->getPositionX() - 130, Monster_sprite->getPositionY() - 150));
	mlayer->setContentSize(Size(260, 260));
	this->addChild(mlayer);

	// 몬스터 체력바 생성
	auto Mon_Hp_Bg = Scale9Sprite::create("slaythespire/ui/combat/bodyBg.png");
	Mon_Hp_Bg->setContentSize(Size(180, 12));
	Mon_Hp_Bg->setPosition(Vec2(Monster_sprite->getPositionX(), Monster_sprite->getPositionY() - 160));
	Mon_Hp_Bg->setColor(Color3B::BLACK);
	this->addChild(Mon_Hp_Bg);

	Mon_Hp = LoadingBar::create("slaythespire/ui/combat/bodyBg.png");
	Mon_Hp->setDirection(LoadingBar::Direction::LEFT);
	Mon_Hp->setPercent(6);
	Mon_Hp->setScale9Enabled(true);
	Mon_Hp->setContentSize(Size(180, 12));
	Mon_Hp->setPosition(Vec2(Monster_sprite->getPositionX(), Monster_sprite->getPositionY() - 160));
	Mon_Hp->setColor(Color3B::RED);
	this->addChild(Mon_Hp);

	Mon_Hp_Font = Label::createWithTTF(ttfConfig_1, "0/0");
	Mon_Hp_Font->setPosition(Vec2(Monster_sprite->getPositionX(), Monster_sprite->getPositionY() - 160));
	Mon_Hp_Font->enableOutline(Color4B(114, 25, 30, 255), 2);
	// 랜덤으로 뽑은 체력을 적용
	Mon_Hp_Font->setString(Hp);
	this->addChild(Mon_Hp_Font);

	// 턴종료 버튼
	auto End_Turn_Bg = Sprite::create("slaythespire/ui/topPanel/endTurnButton.png");
	End_Turn_Bg->setPosition(Vec2(1150, 140));
	End_Turn_Bg->setScale(0.7f);
	this->addChild(End_Turn_Bg);

	auto End_Turn = Sprite::create("slaythespire/ui/topPanel/endTurnButtonGlow.png");
	End_Turn->setPosition(Vec2(1150, 140));
	End_Turn->setScale(0.7f);
	this->addChild(End_Turn);

	auto fadein = FadeIn::create(1.0f);
	auto fadeout = FadeOut::create(1.0f);
	auto seq_1 = Sequence::create(fadeout, fadein, nullptr);
	auto rep_1 = RepeatForever::create(seq_1);
	End_Turn->runAction(rep_1);

	auto End_Turn_Font = Label::createWithTTF(ttfConfig_1, "턴 종료");
	End_Turn_Font->setPosition(Vec2(1150, 140));
	this->addChild(End_Turn_Font);
}

void Battel::Rest()
{
	// 최대 체력의 30% 회복
	cocos2d::log("Rest");

	Rest_layer = Layer::create();

	// 백그라운드
	auto campfire_bg_after = Sprite::create("slaythespire/bottomScene/scene2.jpg", Rect(2, 2, 1920, 1136));
	campfire_bg_after->setScale(0.7f);
	campfire_bg_after->setPosition(Vec2(640, 360));
	Rest_layer->addChild(campfire_bg_after);

	// 캠프파이어 주변 불빛
	campfire_bg_before = Sprite::create("slaythespire/bottomScene/scene2.png", Rect(2, 161, 697, 239));
	campfire_bg_before->setPosition(Vec2(940, 120));
	Rest_layer->addChild(campfire_bg_before);

	auto user = UserDefault::getInstance();

	int character = user->getIntegerForKey("Charcter_choes");

	// 캐릭터 어깨뷰 (불이 켜져있을때), 캐릭터별로 설정
	if (character == 0)
	{
		shoulder_before = Sprite::create("slaythespire/characters/ironclad/shoulder.png");
		shoulder_before->setScale(0.7f);
		shoulder_before->setPosition(Vec2(640, 360));
		Rest_layer->addChild(shoulder_before);
	}

	// 캠프파이어
	campfire = Sprite::create("slaythespire/bottomScene/scene.png", Rect(2, 2, 1840, 496));
	campfire->setScale(0.7f);
	campfire->setPosition(Vec2(640, 180));
	Rest_layer->addChild(campfire);

	// 선택지 그림자
	auto campfire_shadow = Sprite::create("slaythespire/ui/campfire/buttonShadow.png");
	campfire_shadow->setScale(0.7f);
	campfire_shadow->setPosition(Vec2(650, 410));
	campfire_shadow->setOpacity(150);
	Rest_layer->addChild(campfire_shadow);

	// 선택지 아웃라인
	choes_outline = Sprite::create("slaythespire/ui/campfire/outline.png");
	choes_outline->setScale(0.75f);
	choes_outline->setPosition(Vec2(640, 420));
	choes_outline->setOpacity(0);
	Rest_layer->addChild(choes_outline);

	// 선택지 아웃라인 액션
	auto fadeto_255 = FadeTo::create(1.0f, 255);
	auto fadeto_0 = FadeTo::create(1.0f, 0);
	auto seq = Sequence::createWithTwoActions(fadeto_255, fadeto_0);
	auto rep = RepeatForever::create(seq);
	choes_outline->runAction(rep);

	// 선택지
	campfire_choes = Sprite::create("slaythespire/ui/campfire/sleep.png");
	campfire_choes->setScale(0.7f);
	campfire_choes->setPosition(Vec2(640, 420));
	Rest_layer->addChild(campfire_choes);

	TTFConfig ttfConfig("slaythespire/GyeonggiCheonnyeonBatangBold.ttf", 20);

	// 휴식 설명
	Sleep_Info = Label::createWithTTF(ttfConfig, "0");
	Sleep_Info->setPosition(Vec2(640, 340));
	Sleep_Info->enableShadow();
	Sleep_Info->enableOutline(Color4B(229, 229, 229, 255));
	Rest_layer->addChild(Sleep_Info);

	int max = user->getIntegerForKey("Ch_MaxHp");
	int heal = (int)(0.3 * max);

	char heal_font[100];
	sprintf(heal_font, "최대 체력의 30%%를 회복합니다. (%d)", heal);
	Sleep_Info->setString(heal_font);

	Rest_layer->setPosition(Vec2::ZERO);
	this->addChild(Rest_layer);
}

void Battel::Chest()
{
	cocos2d::log("Chest");
}

void Battel::CharacterInfo()
{
	cocos2d::log("CharacterInfo");

	// 사용 가능한 코스트
	Sprite* Costlayer[6];
	Costlayer[0] = Sprite::create("slaythespire/ui/topPanel/red/layer1.png");
	Costlayer[1] = Sprite::create("slaythespire/ui/topPanel/red/layer2.png");
	Costlayer[2] = Sprite::create("slaythespire/ui/topPanel/red/layer3.png");
	Costlayer[3] = Sprite::create("slaythespire/ui/topPanel/red/layer4.png");
	Costlayer[4] = Sprite::create("slaythespire/ui/topPanel/red/layer5.png");
	Costlayer[5] = Sprite::create("slaythespire/ui/topPanel/red/layer6.png");

	for (int i = 0; i < 6; i++)
	{
		Costlayer[i]->setPosition(Vec2(100, 150));
		Costlayer[i]->setScale(0.8f);
		this->addChild(Costlayer[i]);
	}

	auto rotate = RotateBy::create(5.0f, 180.0f);
	auto rep = RepeatForever::create(rotate);

	for (int i = 0; i < 5; i++)
	{
		Costlayer[i]->runAction(rep->clone());
	}

	TTFConfig ttfConfig("slaythespire/GyeonggiCheonnyeonBatangBold.ttf", 28);
	CostFont = Label::createWithTTF(ttfConfig, "3/3");
	CostFont->enableOutline(Color4B(102, 38, 33, 255), 2);
	CostFont->setPosition(Vec2(100, 150));
	this->addChild(CostFont);

	// 뽑을수 있는 카드 더미
	auto Deck = Sprite::create("slaythespire/ui/deckButton/base.png");
	Deck->setPosition(Vec2(80, 50));
	Deck->setScale(0.9f);
	this->addChild(Deck);

	auto DeckShadow = Sprite::create("slaythespire/ui/deckButton/shadow.png");
	DeckShadow->setPosition(Vec2(80, 50));
	DeckShadow->setScale(0.9f);
	this->addChild(DeckShadow);

	// 사용한 카드 더미
	auto DisDeck = Sprite::create("slaythespire/ui/discardButton/base.png");
	DisDeck->setPosition(Vec2(1200, 50));
	DisDeck->setScale(0.9f);
	this->addChild(DisDeck);

	auto DisDeckShadow = Sprite::create("slaythespire/ui/discardButton/shadow.png");
	DisDeckShadow->setPosition(Vec2(1200, 50));
	DisDeckShadow->setScale(0.9f);
	this->addChild(DisDeckShadow);

	// 캐릭터 HP바
	auto Character_Hp_Bg = Scale9Sprite::create("slaythespire/ui/combat/bodyBg.png");
	Character_Hp_Bg->setContentSize(Size(220, 12));
	Character_Hp_Bg->setPosition(Vec2(300, 200));
	Character_Hp_Bg->setColor(Color3B::BLACK);
	this->addChild(Character_Hp_Bg);

	Character_Hp = LoadingBar::create("slaythespire/ui/combat/bodyBg.png");
	Character_Hp->setDirection(LoadingBar::Direction::LEFT);
	Character_Hp->setPercent(100.0f);
	Character_Hp->setScale9Enabled(true);
	Character_Hp->setContentSize(Size(220, 12));
	Character_Hp->setPosition(Vec2(300, 200));
	Character_Hp->setColor(Color3B::RED);
	this->addChild(Character_Hp);

	auto user = UserDefault::getInstance();

	TTFConfig ttfConfig_1("slaythespire/GyeonggiCheonnyeonBatangBold.ttf", 20);
	Ch_NowHp = user->getIntegerForKey("Ch_Hp");
	Ch_MaxHp = user->getIntegerForKey("Ch_MaxHp");
	Character_Hp_Font = Label::createWithTTF(ttfConfig_1, "0/0");
	Character_Hp_Font->setPosition(Vec2(300, 200));
	Character_Hp_Font->enableOutline(Color4B(114, 25, 30, 255), 2);
	this->addChild(Character_Hp_Font);

	char Ch_hp[100];
	sprintf(Ch_hp, "%d/%d", Ch_NowHp, Ch_MaxHp);
	Character_Hp_Font->setString(Ch_hp);

	float hp = (float)Ch_NowHp * 100 / Ch_MaxHp;
	Character_Hp->setPercent(hp);
}

void Battel::Remove_Card()
{
	for (int i = 0; i < 5; i++)
	{
		CardOutline[i]->stopAllActions();
		this->removeChild(CardOutline[i]);
		for (int j = 0; j < 5; j++)
		{
			this->removeChild(Card[i][j]);
			if (j <= 2)
			{
				this->removeChild(CardInfo[i][j]);
			}
		}
	}
}

void Battel::DrawCard()
{

	TTFConfig ttfConfig("slaythespire/GyeonggiCheonnyeonBatangBold.ttf", 15);
	TTFConfig ttfConfig_2("slaythespire/GyeonggiCheonnyeonBatangBold.ttf", 12);

	Vec2 pos = Vec2(350, 50);

	for (int i = 0; i < 5; i++)
	{
		// 랜덤한 카드를 획득
		card[i] = RandomHelper::random_int(1, 2);

		// 공격카드 획득
		if (card[i] == 1)
		{
			// 카드 백그라운드
			Card[i][0] = Sprite::create("slaythespire/cardui/cardui.png", Rect(1224, 1197, 608, 838));
			Card[i][0]->setScale(0.25f);
			Card[i][0]->setPosition(pos);
			Card[i][0]->setZOrder(i);
			log("Card[%d][0]X : %.0f", i, Card[i][0]->getPositionX());
			log("Card[%d][0]Y : %.0f", i, Card[i][0]->getPositionY());
			// 카드 이미지
			Card[i][1] = Sprite::create("slaythespire/1024Portraits/red/attack/strike.png");
			Card[i][1]->setScale(0.25f);
			Card[i][1]->setPosition(Vec2(pos.x, pos.y + 40));
			Card[i][1]->setZOrder(i);
			log("Card[%d][1]X : %.0f", i, Card[i][1]->getPositionX());
			log("Card[%d][1]Y : %.0f", i, Card[i][1]->getPositionY());
			// 카드 이미지 테두리
			Card[i][2] = Sprite::create("slaythespire/cardui/cardui3.png", Rect(2, 834, 523, 369));
			Card[i][2]->setScale(0.25f);
			Card[i][2]->setPosition(Vec2(pos.x, pos.y + 30));
			Card[i][2]->setZOrder(i);
			log("Card[%d][2]X : %.0f", i, Card[i][2]->getPositionX());
			log("Card[%d][2]Y : %.0f", i, Card[i][2]->getPositionY());
			// 카드 이름 판넬
			Card[i][3] = Sprite::create("slaythespire/cardui/cardui.png", Rect(540, 200, 648, 153));
			Card[i][3]->setScale(0.25f);
			Card[i][3]->setPosition(Vec2(pos.x, pos.y + 85));
			Card[i][3]->setZOrder(i);
			log("Card[%d][3]X : %.0f", i, Card[i][3]->getPositionX());
			log("Card[%d][3]Y : %.0f", i, Card[i][3]->getPositionY());
			// 카드 코스트
			Card[i][4] = Sprite::create("slaythespire/cardui/cardui.png", Rect(1968, 1379, 72, 71));
			Card[i][4]->setScale(0.5f);
			Card[i][4]->setPosition(Vec2(pos.x - 70, pos.y + 95));
			Card[i][4]->setZOrder(i);
			log("Card[%d][4]X : %.0f", i, Card[i][4]->getPositionX());
			log("Card[%d][4]Y : %.0f", i, Card[i][4]->getPositionY());
			// 카드 아웃라인
			CardOutline[i] = Sprite::create("slaythespire/cardui/cardui4.png", Rect(600, 1372, 366, 489));
			CardOutline[i]->setContentSize(Size(162, 230));
			CardOutline[i]->setPosition(Vec2(pos.x - 5, pos.y));
			CardOutline[i]->setZOrder(i);
			log("CardOutline[%d]X : %0.f", i, CardOutline[i]->getPositionX());
			log("CardOutline[%d]Y : %0.f", i, CardOutline[i]->getPositionY());
			// 카드 코스트 폰트
			CardInfo[i][0] = Label::createWithTTF(ttfConfig, " 1 ");
			CardInfo[i][0]->enableOutline(Color4B::GRAY, 1);
			CardInfo[i][0]->setPosition(Vec2(pos.x - 70, pos.y + 95));
			CardInfo[i][0]->setZOrder(i);
			log("CardInfo[%d][0]X : %.0f", i, CardInfo[i][0]->getPositionX());
			log("CardInfo[%d][0]Y : %.0f", i, CardInfo[i][0]->getPositionY());
			// 카드 이름
			CardInfo[i][1] = Label::createWithTTF(ttfConfig, "타격");
			CardInfo[i][1]->enableOutline(Color4B::GRAY, 1);
			CardInfo[i][1]->setPosition(Vec2(pos.x, pos.y + 94));
			CardInfo[i][1]->setZOrder(i);
			log("CardInfo[%d][1]X : %.0f", i, CardInfo[i][1]->getPositionX());
			log("CardInfo[%d][1]Y : %.0f", i, CardInfo[i][1]->getPositionY());
			// 카드 효과
			CardInfo[i][2] = Label::createWithTTF(ttfConfig_2, "피해를 6 줍니다.");
			CardInfo[i][2]->enableOutline(Color4B::GRAY, 1);
			CardInfo[i][2]->setPosition(Vec2(pos.x, pos.y - 35));
			CardInfo[i][2]->setZOrder(i);
			log("CardInfo[%d][2]X : %.0f", i, CardInfo[i][2]->getPositionX());
			log("CardInfo[%d][2]Y : %.0f", i, CardInfo[i][2]->getPositionY());
		}
		// 방어카드 획득
		else if (card[i] == 2)
		{
			// 카드 백그라운드
			Card[i][0] = Sprite::create("slaythespire/cardui/cardui3.png", Rect(2, 1205, 597, 838));
			Card[i][0]->setScale(0.25f);
			Card[i][0]->setPosition(pos);
			Card[i][0]->setZOrder(i);
			log("Card[%d][0]X : %.0f", i, Card[i][0]->getPositionX());
			log("Card[%d][0]Y : %.0f", i, Card[i][0]->getPositionY());
			// 카드 이미지
			Card[i][1] = Sprite::create("slaythespire/1024Portraits/red/skill/defend.png");
			Card[i][1]->setScale(0.25f);
			Card[i][1]->setPosition(Vec2(pos.x, pos.y + 40));
			Card[i][1]->setZOrder(i);
			log("Card[%d][1]X : %.0f", i, Card[i][1]->getPositionX());
			log("Card[%d][1]Y : %.0f", i, Card[i][1]->getPositionY());
			// 카드 이미지 테두리
			Card[i][2] = Sprite::create("slaythespire/cardui/cardui2.png", Rect(1179, 2, 524, 363));
			Card[i][2]->setScale(0.25f);
			Card[i][2]->setPosition(Vec2(pos.x, pos.y + 33));
			Card[i][2]->setZOrder(i);
			log("Card[%d][2]X : %.0f", i, Card[i][2]->getPositionX());
			log("Card[%d][2]Y : %.0f", i, Card[i][2]->getPositionY());
			// 카드 이름 판넬
			Card[i][3] = Sprite::create("slaythespire/cardui/cardui.png", Rect(540, 200, 648, 153));
			Card[i][3]->setScale(0.25f);
			Card[i][3]->setPosition(Vec2(pos.x, pos.y + 85));
			Card[i][3]->setZOrder(i);
			log("Card[%d][3]X : %.0f", i, Card[i][3]->getPositionX());
			log("Card[%d][3]Y : %.0f", i, Card[i][3]->getPositionY());
			// 카드 코스트
			Card[i][4] = Sprite::create("slaythespire/cardui/cardui.png", Rect(1968, 1379, 72, 71));
			Card[i][4]->setScale(0.5f);
			Card[i][4]->setPosition(Vec2(pos.x - 70, pos.y + 95));
			Card[i][4]->setZOrder(i);
			log("Card[%d][4]X : %.0f", i, Card[i][4]->getPositionX());
			log("Card[%d][4]Y : %.0f", i, Card[i][4]->getPositionY());
			// 카드 아웃라인
			CardOutline[i] = Sprite::create("slaythespire/cardui/cardui4.png", Rect(600, 1372, 366, 489));
			CardOutline[i]->setContentSize(Size(162, 230));
			CardOutline[i]->setPosition(Vec2(pos.x - 5, pos.y));
			CardOutline[i]->setZOrder(i);
			log("CardOutline[%d]X : %0.f", i, CardOutline[i]->getPositionX());
			log("CardOutline[%d]Y : %0.f", i, CardOutline[i]->getPositionY());
			// 카드 코스트 폰트
			CardInfo[i][0] = Label::createWithTTF(ttfConfig, " 1 ");
			CardInfo[i][0]->enableOutline(Color4B::GRAY, 1);
			CardInfo[i][0]->setPosition(Vec2(pos.x - 70, pos.y + 95));
			CardInfo[i][0]->setZOrder(i);
			log("CardInfo[%d][0]X : %.0f", i, CardInfo[i][0]->getPositionX());
			log("CardInfo[%d][0]Y : %.0f", i, CardInfo[i][0]->getPositionY());
			// 카드 이름
			CardInfo[i][1] = Label::createWithTTF(ttfConfig, "수비");
			CardInfo[i][1]->enableOutline(Color4B::GRAY, 1);
			CardInfo[i][1]->setPosition(Vec2(pos.x, pos.y + 94));
			CardInfo[i][1]->setZOrder(i);
			log("CardInfo[%d][1]X : %.0f", i, CardInfo[i][1]->getPositionX());
			log("CardInfo[%d][1]Y : %.0f", i, CardInfo[i][1]->getPositionY());
			// 카드 효과
			CardInfo[i][2] = Label::createWithTTF(ttfConfig_2, "방어도를 5 얻습니다.");
			CardInfo[i][2]->enableOutline(Color4B::GRAY, 1);
			CardInfo[i][2]->setPosition(Vec2(pos.x, pos.y - 35));
			CardInfo[i][2]->setZOrder(i);
			log("CardInfo[%d][2]X : %.0f", i, CardInfo[i][2]->getPositionX());
			log("CardInfo[%d][2]Y : %.0f", i, CardInfo[i][2]->getPositionY());
		}
		pos.x += 125;
	}

	for (int i = 0; i < 5; i++)
	{
		CardOutline[i]->setVisible(false);
		this->addChild(CardOutline[i]);
		for (int j = 0; j < 5; j++)
		{
			Card[i][j]->setVisible(true);
			this->addChild(Card[i][j]);
		}
		for (int j = 0; j < 3; j++)
		{
			CardInfo[i][j]->setVisible(true);
			this->addChild(CardInfo[i][j]);
		}
	}

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (Card[i][j]->isVisible() == false)
			{
				log("Card[%d][%d]->isVisible() == false", i, j);
			}
		}
		for (int j = 0; j < 2; j++)
		{
			if (CardInfo[i][j]->isVisible() == false)
			{
				log("CardInf[%d][%d]->isVisible() == false", i, j);
			}
		}
	}
}

void Battel::Remove()
{
	this->removeAllChildren();
}

void Battel::MonDead(std::string _name)
{
	TTFConfig ttfConfig("slaythespire/GyeonggiCheonnyeonBatangBold.ttf", 28);
	TTFConfig ttfConfig_1("slaythespire/GyeonggiCheonnyeonBatangBold.ttf", 18);

	Reward_layer = Layer::create();

	auto blayer = LayerColor::create(Color4B::BLACK);
	blayer->setOpacity(200);
	Reward_layer->addChild(blayer);

	// 전리품
	auto reward_bg = Sprite::create("slaythespire/ui/reward/rewardScreenSheet.png");
	reward_bg->setPosition(Vec2(640, 360));
	reward_bg->setScale(0.5f);
	Reward_layer->addChild(reward_bg);

	auto rewardlist = Sprite::create("slaythespire/ui/reward/rewardListItemPanel.png");
	rewardlist->setPosition(Vec2(640, 450));
	rewardlist->setScale(0.5f);
	Reward_layer->addChild(rewardlist);

	// 랜덤한 골드 지급
	if (_name == "Monster")
	{
		gold = RandomHelper::random_int(15, 20);
	}
	else if (_name == "Elite")
	{
		gold = RandomHelper::random_int(30, 40);
	}
	char goldfont[100];
	sprintf(goldfont, "%d 골드", gold);

	auto goldreward = Sprite::create("slaythespire/ui/topPanel/gold.png");
	goldreward->setPosition(Vec2(550, 450));
	goldreward->setScale(0.5f);
	Reward_layer->addChild(goldreward);

	auto goldreward_font = Label::createWithTTF(ttfConfig_1, "0");
	goldreward_font->setPosition(Vec2(600, 450));
	Reward_layer->addChild(goldreward_font);
	goldreward_font->setString(goldfont);

	// 배너
	auto banner = Sprite::create("slaythespire/ui/selectBanner.png");
	banner->setPosition(Vec2(640, 530));
	banner->setScale(0.5f);
	banner->setOpacity(0);
	Reward_layer->addChild(banner);

	auto fadeto = FadeTo::create(0.5f, 255);
	auto delay = DelayTime::create(0.5f);
	auto seq = Sequence::create(delay, fadeto, nullptr);
	banner->runAction(seq);

	auto bannerfont = Label::createWithTTF(ttfConfig, "전리품");
	bannerfont->enableOutline(Color4B::GRAY, 1);
	bannerfont->setPosition(Vec2(640, 545));
	bannerfont->setOpacity(0);
	Reward_layer->addChild(bannerfont);

	auto fadeto_2 = FadeTo::create(0.5f, 255);
	auto delay_2 = DelayTime::create(1.0f);
	auto seq_2 = Sequence::create(delay_2, fadeto_2, nullptr);
	bannerfont->runAction(seq_2);

	Reward_layer->setPosition(Vec2::ZERO);
	this->addChild(Reward_layer);
}

void Battel::ChDead(std::string _name)
{
	TTFConfig ttfConfig("slaythespire/GyeonggiCheonnyeonBatangBold.ttf", 28);
	TTFConfig ttfConfig_1("slaythespire/GyeonggiCheonnyeonBatangBold.ttf", 20);

	auto blayer = LayerColor::create(Color4B::BLACK);
	this->addChild(blayer);

	// 캐릭터 죽음 스프라이트
	auto chdead = Sprite::create("slaythespire/characters/ironclad/corpse.png");
	chdead->setPosition(Vec2(300, 340));
	chdead->setScale(0.75f);
	this->addChild(chdead);

	auto banner = Sprite::create("slaythespire/ui/selectBanner.png");
	banner->setPosition(Vec2(640, 530));
	banner->setScale(0.8f);
	banner->setOpacity(0);
	this->addChild(banner);

	auto fadeto = FadeTo::create(0.5f, 255);
	auto delay = DelayTime::create(0.5f);
	auto seq = Sequence::create(delay, fadeto, nullptr);
	banner->runAction(seq);

	Label* bannerfont;

	// 캐릭터가 죽을시
	if (Ch_NowHp <= 0)
		bannerfont = Label::createWithTTF(ttfConfig, "졌군...");
	// 보스를 죽일시
	if (NowHp <= 0)
		bannerfont = Label::createWithTTF(ttfConfig, "승리..?");

	bannerfont->enableOutline(Color4B::GRAY, 1);
	bannerfont->setPosition(Vec2(640, 545));
	bannerfont->setOpacity(0);
	this->addChild(bannerfont);
	
	auto fadeto_2 = FadeTo::create(0.5f, 255);
	auto delay_2 = DelayTime::create(1.0f);
	auto seq_2 = Sequence::create(delay_2, fadeto_2, nullptr);
	bannerfont->runAction(seq_2);

	// 메인 메뉴로 돌아가는 버튼
	auto Continue_Bg = Sprite::create("slaythespire/ui/topPanel/endTurnButton.png");
	Continue_Bg->setPosition(Vec2(640, 100));
	Continue_Bg->setScale(0.5f);
	this->addChild(Continue_Bg);

	auto Continue = Sprite::create("slaythespire/ui/topPanel/endTurnButtonGlow.png");
	Continue->setPosition(Vec2(640, 100));
	Continue->setScale(0.5f);
	this->addChild(Continue);

	auto fadein = FadeIn::create(1.0f);
	auto fadeout = FadeOut::create(1.0f);
	auto seq_3 = Sequence::create(fadeout, fadein, nullptr);
	auto rep_3 = RepeatForever::create(seq_3);
	Continue->runAction(rep_3);

	auto Continue_Font = Label::createWithTTF(ttfConfig_1, "계 속");
	Continue_Font->setPosition(Vec2(640, 100));
	this->addChild(Continue_Font);
}

void Battel::Remove_reward()
{
	this->removeChild(Reward_layer);
}

void Battel::Remove_Use_Card(int number)
{
	CardOutline[number]->stopAllActions();
	CardOutline[number]->setVisible(false);
	for (int i = 0; i < 5; i++)
	{
		this->removeChild(Card[number][i]);
	}
	for (int i = 0; i < 3; i++)
	{
		this->removeChild(CardInfo[number][i]);
	}
}

void Battel::Stop_Card_Outline(int number)
{
	CardOutline[number]->stopAllActions();
	CardOutline[number]->setVisible(false);
}