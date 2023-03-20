#include "GameScene.h"

USING_NS_CC;

cocos2d::Scene* GameScene::createScene()
{
    return GameScene::create();
}

bool GameScene::init()
{
    if (!Scene::init()) return false;

    user = UserDefault::getInstance();
    Charcter_choes = user->getIntegerForKey("Charcter_choes");
    user->setIntegerForKey("choes_key", 1);

   Create_Sprite();
   Create_Font();

   // ĳ���� �ִϸ��̼� ����
   ChAnimation = new CharacterAnimation;
   ChAnimation->CharacterIdelAnimation(Charcter_choes);
   this->addChild(ChAnimation);

   // ���� Ŭ���� �ν��Ͻ� ����
   sound = new Sound;

   // ���� ���� ���� ���ӽ��۽� �ʱ�ȭ ����
   auto user = UserDefault::getInstance();
   sound->background_volume = user->getFloatForKey("BackGround");
   sound->effect_volume = user->getFloatForKey("Effect");

   sound->BottomTheme();

   log("Background volume : %f", sound->background_volume);

   // �� ����
   Map = new MapScene;
   Map->CreateMap();
   Map->setZOrder(20);
   this->addChild(Map);

   // Ŀ�� ����
   {
       cursor = Sprite::create("slaytheSpire/ui/cursors/gold2.png");
       cursor->setScale(0.8f);
       cursor->setZOrder(100);
       this->addChild(cursor);

       cursor_point = Sprite::create("slaytheSpire/ui/cursors/gold2.png", Rect(0, 0, 5, 5));
       cursor_point->setOpacity(0);
       this->addChild(cursor_point);
   }

   Mouse_listener = EventListenerMouse::create();
   Mouse_listener->onMouseMove = CC_CALLBACK_1(GameScene::onMouseMove, this);

   _eventDispatcher->addEventListenerWithSceneGraphPriority(Mouse_listener, this);

   Touch_listener = EventListenerTouchOneByOne::create();
   Touch_listener->setSwallowTouches(true);
   Touch_listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
   Touch_listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
   Touch_listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);

   _eventDispatcher->addEventListenerWithSceneGraphPriority(Touch_listener, this);

   cocos2d::log("GameScene");

   battel = new Battel;

   Ch_Damage = 6;
   Ch_Defend = 0;
   Ch_Weekening = 0;
   Ch_Impairment = 0;

   return true;
}

bool GameScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
    return true;
}

void GameScene::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
    if (choes == 0)
    {

    }
    else if (choes == 1)
    {
        cocos2d::log("Move");
        // �̵��� ��ǥ ũ�� ȭ��
        Vec2 pos = touch->getDelta();
        
        // �̵��� ��ǥ ��ŭ �̵�
        for (int i = 0; i < 4; i++)
            Map->Map[i]->setPosition(Vec2(Map->Map[i]->getPositionX(),
                Map->Map[i]->getPositionY() + pos.y));


        // ������ ������ ���������� �����̵��� ����ó��
        if (Map->Map[0]->getPositionY() > 300.f)
        {
            cocos2d::log("0");
            for (int i = 0; i < 4; i++)
            {
                Map->Map[i]->setPosition(Vec2(640, (i * 540) + 300));
            }
        }
        else if (Map->Map[3]->getPositionY() < 300.0f)
        {
            cocos2d::log("4");
            for (int i = 0; i < 4; i++)
            {
                Map->Map[3 - i]->setPosition(Vec2(640, -(i * 540) + 300));
            }
        }

        Vec2 Iconpos_1 = Map->Map[3]->getPosition();

        Map->BossIcon->setPosition(Iconpos_1);
        Map->BossBox->setPosition(Vec2(Map->BossIcon->getPositionX() - 150,
            Map->BossIcon->getPositionY() - 140));

        // ������ ��ġ ����
        for (int i = 0; i < 14; i++)
        {
            Map->MapIcon[i]->setPosition(Vec2(Map->MapIcon[i]->getPositionX(),
                Map->MapIcon[i]->getPositionY() + pos.y));
        }

        // ������ ������ ���������� �����̵��� ����ó��
        if (Map->MapIcon[0]->getPositionY() > 300.0f)
        {
            for (int i = 0; i < 14; i++)
            {
                Map->MapIcon[i]->setPositionY(300 + (i * 110));
            }
        }
        else if (Map->MapIcon[13]->getPositionY() < 120.0f)
        {
            for (int i = 0; i < 14; i++)
            {
                Map->MapIcon[13 - i]->setPositionY(120 - (i * 110));
            }
        }

        // ������ ���� ��Ŭ�� �ִٸ� ��ġ�� ����
        for (int i = 0; i < Map->circlecount; i++)
        {
            if (Map->IconCircle[i] != nullptr)
            {
               Map->IconCircle[i]->setPosition(Map->MapIcon[i]->getPosition());
            }
        }

        // �ٿ�� �ڽ� ��ġ ����
        for (int i = 0; i < 14; i++)
        {
            if (Map->IconBox[i] != nullptr)
            {
                Map->IconBox[i]->setPosition(Vec2(
                    Map->MapIcon[i]->getPositionX() - 30, 
                        Map->MapIcon[i]->getPositionY() - 30));
            }
        }
    }
}

void GameScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
    choes = user->getIntegerForKey("choes_key");
    cocos2d::log("chose : %d", choes);

    // ��, ������ �������� ������
    if (choes == 0)
    {
        // ���� Ŭ��
        if (TopMap_Box->isVisible() == true &&
            cursor_point->getBoundingBox().intersectsRect(TopMap_Box->getBoundingBox()))
        {
            cocos2d::log("TopMap");
            // �� ��������Ʈ ȭ�鿡 ǥ��
            Map->Visibletrue();
            // ��ġ�̺�Ʈ ���Ǻ��� �� ����
            user->setIntegerForKey("choes_key", 1);
            // ���� ���� ����
            sound->OpenMap();
        }
        // ��� ���� �� Ŭ��
        else if (TopDeck_Box->isVisible() == true &&
            cursor_point->getBoundingBox().intersectsRect(TopDeck_Box->getBoundingBox()))
        {
            cocos2d::log("TopDeck");
            // ���� ���� ī�� ȭ�鿡 ���
            deck = new Deck;
            deck->Create();
            this->addChild(deck);
            // ��ġ�̺�Ʈ ���Ǻ��� �� ����
            user->setIntegerForKey("choes_key", 2);

            // �� ���� ���� ����
            sound->ViewDeck();
        }
        // ���� Ŭ��
        else if (TopMenu_Box->isVisible() == true &&
            cursor_point->getBoundingBox().intersectsRect(TopMenu_Box->getBoundingBox()))
        {
            cocos2d::log("TopMenu");
            // �ɼ� ȭ�鿡 ���
            Gameoption = new GameOption;
            Gameoption->CreateGameOption();
            this->addChild(Gameoption);
            // ��ġ�̺�Ʈ ���Ǻ��� �� ����
            user->setIntegerForKey("choes_key", 3);

            // Ŭ�� ���� ����
            sound->MenuClick();
        }
        // �ϴ� ��밡���� �� Ŭ��
        else if (DeckBox->isVisible() == true &&
            cursor_point->getBoundingBox().intersectsRect(DeckBox->getBoundingBox()))
        {
            cocos2d::log("Can use Deck");
        }
        // �ϴ� ����� �� Ŭ��
        else if (DisDeckBox->isVisible() == true &&
            cursor_point->getBoundingBox().intersectsRect(DisDeckBox->getBoundingBox()))
        {
            cocos2d::log("Can't use Deck");
        }
        // ����ϱ� ��ư Ŭ�� (������ ������ ��ư)
        else if (CoutinueBox->isVisible() == true &&
            cursor_point->getBoundingBox().intersectsRect(CoutinueBox->getBoundingBox()))
        {
            cocos2d::log("countinue");

            // ���� ���� ����
            sound->MenuClick();
            // �������� ��׶��� ����
            sound->StopBottomTheme();
            // ĳ���� �׾����� ������ ���� ����
            sound->StopEndingTheme();
            

            // ���� �޴��� ȭ�� ��ȯ
            auto scene = MainMenu::createScene();
            _director->replaceScene(TransitionFade::create(1.0f, scene));
        }
        // ���� ȹ��
        else if (rewardBox->isVisible() == true &&
            cursor_point->getBoundingBox().intersectsRect(rewardBox->getBoundingBox()))
        {
            cocos2d::log("reward");
            // ���� ��� ����
            auto user = UserDefault::getInstance();
            char change_gold[100];
            // ���� ��� + ȹ�� ���
            sprintf(change_gold, "%d", battel->gold + user->getIntegerForKey("Gold"));

            GoldFont->setString(change_gold);
            rewardBox->setVisible(false);
            battel->Remove_reward();
            user->setIntegerForKey("Gold", battel->gold + user->getIntegerForKey("Gold"));

            // ��� ȹ�� ���� ����
            sound->GetGold();

            // �������� ����� ����
            sound->ResumeBottomTheme();
        }
        
    }
    // ���� ��������
    else if (choes == 1)
    {
        cocos2d::log("choes : %d", choes);
        // ���ư��� ��ư Ŭ��
        if (Map->CancleButton_Box != nullptr &&
            cursor_point->getBoundingBox().intersectsRect(Map->CancleButton_Box->getBoundingBox()))
        {
            cocos2d::log("Back Game Scene");
            // �� ��������Ʈ ȭ�鿡�� ����
            Map->Visiblefalse();
            // ��ġ �̺�Ʈ ���� ���� �� ����
            user->setIntegerForKey("choes_key", 0);

            // Ŭ�� ���� ����
            sound->MenuClick();
            // �� ���� ���� ����
            sound->OpenMap();
        }
        // �� ������ Ŭ��
        else if (cursor_point->getBoundingBox().intersectsRect(TopMap_Box->getBoundingBox()))
        {
            cocos2d::log("Map Again");
            // �� ��������Ʈ ȭ�鿡�� ����
            Map->Visiblefalse();
            // ��ġ �̺�Ʈ ���� ���� �� ����
            user->setIntegerForKey("choes_key", 0);

            // Ŭ�� ���� ����
            sound->MenuClick();
            // �� ���� ���� ����
            sound->OpenMap();
        }
        // �� ������ Ŭ��
        else if (cursor_point->getBoundingBox().intersectsRect(TopDeck_Box->getBoundingBox()))
        {
            cocos2d::log("Map->Deck");
            // �� ��������Ʈ ȭ�鿡�� ����
            Map->Visiblefalse();
            // ��ġ �̺�Ʈ ���� ���� �� ����
            user->setIntegerForKey("choes_key", 2);

            // ���� ī�� ��������Ʈ ����
            deck = new Deck;
            deck->Create();
            this->addChild(deck);

            // �� ���� ���� ����
            sound->ViewDeck();
        }
        // ���� Ŭ��
        else if (cursor_point->getBoundingBox().intersectsRect(TopMenu_Box->getBoundingBox()))
        {
            cocos2d::log("Map->Menu");
            // �� ��������Ʈ ����
            Map->Visiblefalse();
            // �ɼ� ȭ�鿡 ���
            Gameoption = new GameOption;
            Gameoption->CreateGameOption();
            this->addChild(Gameoption);
            // ��ġ �̺�Ʈ ���� ���� �� ����
            user->setIntegerForKey("choes_key", 3);

            // Ŭ�� ���� ����
            sound->MenuClick();
        }
        // �������� Ŭ��, ���� ������ �´� �� Ŭ���ߴ��� Ȯ��
        else if (cursor_point->getBoundingBox().intersectsRect(Map->IconBox[Map->floor]->getBoundingBox()))
        {
            cocos2d::log("Click Icon");
            Map->MenuCallBack();

            // �������� ���� ���� ����
            sound->MapClick();

            // ���� �� ����
            this->scheduleOnce(schedule_selector(GameScene::CreateBattelScene), 1.2f);

            DeckBox->setVisible(true);
            DisDeckBox->setVisible(true);
            EndTurnBox->setVisible(true);
            for (int i = 0; i < 5; i++)
            {
                CardBox[i]->setVisible(true);
            }
        }
        // ���� �������� Ŭ��
        else if (Map->floor == 14 && cursor_point->getBoundingBox().intersectsRect(Map->BossBox->getBoundingBox()))
        {
            log("Boss Icon");
            Map->MenuCallBack();

            // �������� ���� ���� ����
            sound->MapClick();

            // ���� �� ����
            this->scheduleOnce(schedule_selector(GameScene::CreateBattelScene), 1.2f);

            DeckBox->setVisible(true);
            DisDeckBox->setVisible(true);
            EndTurnBox->setVisible(true);
            for (int i = 0; i < 5; i++)
            {
                CardBox[i]->setVisible(true);
            }
        }

        auto target = static_cast<LayerColor*>(event->getCurrentTarget());
        Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = Map->MaplayerC->getContentSize();
        Rect rect = Rect(300, 130, s.width, s.height);
        // �� ��, �Ʒ��� ������ ���
        if (rect.containsPoint(locationInNode))
        {

        }
        
    }
    // ���� ��������
    else if (choes == 2)
    {
        cocos2d::log("choes : %d", choes);

        // �ٽ� ���� ��������
        if (cursor_point->getBoundingBox().intersectsRect(TopDeck_Box->getBoundingBox()))
        {
            // �� ��������Ʈ ����
            deck->Remove();
            // ��ġ �̺�Ʈ ���� ���� �� ����
            user->setIntegerForKey("choes_key", 0);
            // �� ���� ���� ����
            sound->ViewDeck();
        }
        // ���ư��� ��ư Ŭ��
        else if (deck->CancleButton_Box != nullptr &&
            cursor_point->getBoundingBox().intersectsRect(deck->CancleButton_Box->getBoundingBox()))
        {
            // �� ��������Ʈ ����
            deck->Remove();
            // ��ġ �̺�Ʈ ���� ���� �� ����
            user->setIntegerForKey("choes_key", 0);
            // �� ���� ���� ����
            sound->ViewDeck();
        }
        // ���� Ŭ��
        else if (TopMap_Box->isVisible() == true &&
            cursor_point->getBoundingBox().intersectsRect(TopMap_Box->getBoundingBox()))
        {
            cocos2d::log("TopMap");
            // �� ��������Ʈ ����
            deck->Remove();
            // �� ��������Ʈ ȭ�鿡 ǥ��
            Map->Visibletrue();
            // ��ġ�̺�Ʈ ���Ǻ��� �� ����
            user->setIntegerForKey("choes_key", 1);
            // ���� ���� ����
            sound->OpenMap();
        }
        // ���� Ŭ��
        else if (TopMenu_Box->isVisible() == true &&
            cursor_point->getBoundingBox().intersectsRect(TopMenu_Box->getBoundingBox()))
        {
            cocos2d::log("TopMenu");
            // �� ��������Ʈ ����
            deck->Remove();
            // �ɼ� ȭ�鿡 ���
            Gameoption = new GameOption;
            Gameoption->CreateGameOption();
            this->addChild(Gameoption);
            // ��ġ�̺�Ʈ ���Ǻ��� �� ����
            user->setIntegerForKey("choes_key", 3);

            // Ŭ�� ���� ����
            sound->MenuClick();
        }
    }
    // ������ ����������
    else if (choes == 3)
    {
        cocos2d::log("choes : %d", choes);
        // yes Ŭ��
        if (Gameoption->Yes_Button_Box != nullptr &&
            cursor_point->getBoundingBox().intersectsRect(Gameoption->Yes_Button_Box->getBoundingBox()))
        {
            cocos2d::log("Yes");
            // 1�������� ��׶��� ���� ����
            this->scheduleOnce(schedule_selector(GameScene::StopSound), 0.5f);
            // Ŭ�� ���� ����
            sound->MenuClick();
            // ���� �޴��� ��� ��ȯ
            auto scene = MainMenu::createScene();
            _director->replaceScene(TransitionFade::create(1.0f, scene));

        }
        // no Ŭ��
        else if (Gameoption->No_Button_Box != nullptr &&
            cursor_point->getBoundingBox().intersectsRect(Gameoption->No_Button_Box->getBoundingBox()))
        {
            cocos2d::log("No");
            // �ɼ� ��ü ����
            Gameoption->Remove();
            user->setIntegerForKey("choes_key", 0);
            // Ŭ�� ���� ����
            sound->MenuClick();
        }
        
    }
    // ���� ��
    else if (choes == 10 && playerturn == true)
    {
        // �� ���� ��ư Ŭ��
        if (EndTurnBox->isVisible() == true && cursor_point->getBoundingBox().intersectsRect(EndTurnBox->getBoundingBox()))
        {
            cocos2d::log("End Turn");
            // �÷��̾���� ���� false�� ����
            playerturn = false;
            // ī�� ��� Ȯ�� ������ ����
            this->unschedule(schedule_selector(GameScene::Check));
            // �� ���� ���� ����
            sound->EndTurn();
            // ī�� ����
            battel->Remove_Card();
            // ���� �ð� �� �� �� ���� ���� ����
            this->scheduleOnce(schedule_selector(GameScene::EnemyTurn), 0.5f);
            // 1���� ���� �ൿ�� �´� �ִϸ��̼� ���
            this->scheduleOnce(schedule_selector(GameScene::MonAction), 2.0f);
            // 4���� ü�� Ȯ���� ī�� ��ο�
            this->scheduleOnce(schedule_selector(GameScene::CheckHp), 4.0f);
        }
        // ī�� ���
        else if (battel->nowCost > 0)
        {
            // i��° ī�� Ŭ��
            for (int i = 0; i < 5; i++)
            {
                cocos2d::log("Card[i] : %d", i);
                // ī�� �ƿ����ο� �׼� ����
                if (CardBox[i]->isVisible() == true &&
                    cursor_point->getBoundingBox().intersectsRect(CardBox[i]->getBoundingBox()))
                {
                    cardnumber = i;

                    auto scale_1 = ScaleTo::create(1.0f, 1.2f);
                    auto scale_2 = ScaleTo::create(1.0f, 1.0f);
                    auto seq = Sequence::create(scale_1, scale_2, nullptr);
                    auto rep = RepeatForever::create(seq);

                    for (int j = 0; j < 5; j++)
                    {
                        if (j != cardnumber)
                        {
                            battel->CardOutline[j]->stopAllActions();
                            battel->CardOutline[j]->setVisible(false);
                        }
                    }
                    battel->CardOutline[i]->setVisible(true);
                    battel->CardOutline[i]->runAction(rep);
                    // ī�� ���� ���� ����
                    sound->CardSelect();
                    // ī�带 Ŭ���������� �������� �۵��ϵ���
                    this->schedule(schedule_selector(GameScene::Check));

                    break;
                }
            }
            for (int i = 0; i < 5; i++)
            {
                if (i == cardnumber)
                {
                    // ��� ī�� ���
                    if (ChCheck != nullptr &&
                        cursor_point->getBoundingBox().intersectsRect(ChAnimation->Character_Box->getBoundingBox()))
                    {
                        // ������ ����
                        this->unschedule(schedule_selector(GameScene::Check));

                        // ȭ��ǥ ����
                        this->removeChild(ChCheck);

                        // ī�� ����
                        battel->Remove_Use_Card(i);

                        CardBox[i]->setVisible(false);
                        // �� ȹ�� ���� ����
                        sound->GetDefend();
                        // �ڽ�Ʈ ����
                        battel->nowCost -= 1;
                        char changecost[10];
                        // ����� �ڽ�Ʈ ȭ�鿡 ���
                        sprintf(changecost, "%d/3", battel->nowCost);
                        battel->CostFont->setString(changecost);

                        // �� ȹ�� �ִϸ��̼�
                        auto sprite = Sprite::create("slaythespire/ui/intent/defend.png");
                        sprite->setPosition(Vec2(300, 320));
                        sprite->setOpacity(0);
                        this->addChild(sprite);

                        auto fadeto_1 = FadeTo::create(0.25f, 255);
                        auto fadeto_2 = FadeTo::create(0.25f, 0);
                        auto move = MoveBy::create(0.4f, Vec2(0, -75));
                        auto spawn = Spawn::create(fadeto_1, move, nullptr);
                        auto seq = Sequence::create(spawn, DelayTime::create(0.5f), fadeto_2, RemoveSelf::create(), nullptr);

                        sprite->runAction(seq);

                        // �� ǥ��
                        TTFConfig ttfConfig_1("slaythespire/GyeonggiCheonnyeonBatangBold.ttf", 20);

                        // �ߺ����� ����
                        this->removeChild(Ch_Defend_sprite);
                        Ch_Defend_sprite = Sprite::create("slaythespire/ui/intent/defend.png");
                        Ch_Defend_sprite->setPosition(Vec2(180, 200));
                        Ch_Defend_sprite->setScale(0.75f);
                        this->addChild(Ch_Defend_sprite);
                        
                        this->removeChild(Ch_Defend_font);
                        Ch_Defend_font = Label::createWithTTF(ttfConfig_1, "0");
                        Ch_Defend_font->setPosition(Vec2(180, 200));
                        Ch_Defend_font->enableOutline(Color4B::BLACK, 1);
                        this->addChild(Ch_Defend_font);

                        // �� ����
                        // �ջ� ������� ������ �� 3�� ȹ��
                        if (Ch_Impairment > 0)
                            Ch_Defend += 3;
                        else
                            Ch_Defend += 5;

                        char changedefend[10];
                        sprintf(changedefend, "%d", Ch_Defend);
                        Ch_Defend_font->setString(changedefend);
                    }
                    // ���� ī�� ���
                    else if (MonCheck != nullptr &&
                        cursor_point->getBoundingBox().intersectsRect(battel->mlayer->getBoundingBox()))
                    {
                        // ������ ����
                        this->unschedule(schedule_selector(GameScene::Check));

                        // ȭ��ǥ ����
                        this->removeChild(MonCheck);

                        // ī�� ����       
                        battel->Remove_Use_Card(i);

                        CardBox[i]->setVisible(false);
                        // ���� ���� ����
                        sound->ChAttack();
                        // �ڽ�Ʈ ����
                        battel->nowCost -= 1;
                        char changecost[10];
                        // ����� �ڽ�Ʈ ȭ�鿡 ���
                        sprintf(changecost, "%d/3", battel->nowCost);
                        battel->CostFont->setString(changecost);

                        // ���� ü�� ����
                        char changedefend[100];

                        cocos2d::log("Mon_Defend : %d", battel->Mon_Defend);
                        log("Ch_Damage : %d", Ch_Damage);


                        // ���� ���� ���Ϳ� ����� �ο�
                        // �� �̸��� ����� ����
                        if (battel->Mon_Defend > Ch_Damage)
                        {
                            // ���� �� ���
                            battel->Mon_Defend -= Ch_Damage;
                            sprintf(changedefend, "%d", battel->Mon_Defend);
                            battel->defend_font->setString(changedefend);
                            cocos2d::log("Mon_Defend > 6");
                            // ���� ������ ���� ����
                            sound->BlackAttack();
                        }
                        // ���� ���������� ü���� �ȱ���
                        else if (battel->Mon_Defend == Ch_Damage)
                        {
                            // ��� ��������Ʈ, ��Ʈ ����
                            battel->Mon_Defend = 0;
                            if (battel->defend_sprite != nullptr)
                                battel->defend_sprite->setVisible(false);

                            if (battel->defend_font != nullptr)
                                battel->defend_font->setVisible(false);

                            this->removeChild(battel->defend_sprite);
                            this->removeChild(battel->defend_font);
                            cocos2d::log("Mon_Defend == 6");
                            sound->BlackAttack();
                        }
                        // �� �̻��� ������� ����
                        else if (battel->Mon_Defend < Ch_Damage)
                        {
                            if (battel->Mon_Defend > 0)
                            {
                                battel->defend_sprite->setVisible(false);
                                this->removeChild(battel->defend_sprite);
                            }
                            if (battel->Mon_Defend > 0)
                            {
                                battel->defend_font->setVisible(false);
                                this->removeChild(battel->defend_font);
                            }
                            // ���� �μ����� ���� ���� ���� ����������
                            if (battel->Mon_Defend > 0)
                            {
                                sound->BreakDefend();
                            }

                            // ���ݷ°� �� ���̸�ŭ ����� �ο�
                            battel->Mon_Defend -= Ch_Damage;
                            int Hp = battel->NowHp;
                            cocos2d::log("Hp1 : %d", Hp);
                            Hp += battel->Mon_Defend;
                            cocos2d::log("Hp2 : %d", Hp);
                            if (Hp <= 0)
                            {
                                Hp = 0;
                                DeckBox->setVisible(false);
                                DisDeckBox->setVisible(false);
                                EndTurnBox->setVisible(false);
                                for (int i = 0; i < 5; i++)
                                {
                                    CardBox[i]->setVisible(false);
                                }
                                this->scheduleOnce(schedule_selector(GameScene::CheckHp), 1.0f);
                            }
                            char changeHp[100];
                            sprintf(changeHp, "%d/%d", Hp, battel->MaxHp);
                            battel->Mon_Hp_Font->setString(changeHp);

                            float hp = (float)Hp * 100 / battel->MaxHp;
                            battel->Mon_Hp->setPercent(hp);
                            battel->NowHp = Hp;
                            battel->Mon_Defend = 0;
                        }
                    }
                }
            }
        }
    }
    // �޽�
    else if (choes == 11)
    {
        if (cursor_point->getBoundingBox().intersectsRect(battel->campfire_choes->getBoundingBox()))
        {
            log("Sleep");
            // Ŭ�� ���� ����
            sound->MenuClick();
            // ü�� ȸ��
            auto Rest_blayer = LayerColor::create(Color4B::BLACK);
            Rest_blayer->setOpacity(0);
            this->addChild(Rest_blayer);

            auto FadeIn = FadeIn::create(0.75f);
            auto FadeOut = FadeOut::create(0.75f);
            auto seq_1 = Sequence::create(FadeIn, FadeOut, RemoveSelf::create(), nullptr);
            Rest_blayer->runAction(seq_1);

            auto seq_2 = Sequence::create(DelayTime::create(0.75f), RemoveSelf::create(), nullptr);
            battel->Rest_layer->runAction(seq_2);

            auto user = UserDefault::getInstance();
            int heal = (int)(0.3 * user->getIntegerForKey("Ch_MaxHp"));
            int NowHp = user->getIntegerForKey("Ch_Hp") + heal;
            // Maxü�º��� �������� Maxü������ ����
            if (NowHp > user->getIntegerForKey("Ch_MaxHp"))
            {
                NowHp = user->getIntegerForKey("Ch_MaxHp");
            }
            user->setIntegerForKey("Ch_Hp", NowHp);

            int nowhp = user->getIntegerForKey("Ch_Hp");
            int maxhp = user->getIntegerForKey("Ch_MaxHp");

            // ��� �ǳ� ü�� ����
            char changehp[100];
            sprintf(changehp, "%d/%d", nowhp, maxhp);
            HeartFont->setString(changehp);

            user->setIntegerForKey("choes_key", 0);

            // �� ���� ���� ����   
            Map->floor++;

            // �������� ��׶��� �����
            sound->ResumeBottomTheme();
            // ���� Ÿ�� �Ҹ� ����
            sound->StopCampFire();
        }
    }
    // �̺�Ʈ
    else if (choes == 12)
    {

    }
}

void GameScene::onMouseMove(cocos2d::Event* event)
{
    _point = (EventMouse*)event;

    cursor->setPosition(Vec2(_point->getCursorX() + 27, _point->getCursorY() - 27));
    cursor_point->setPosition(Vec2(_point->getCursorX(), _point->getCursorY()));
}

void GameScene::Create_Sprite()
{
    // ���
    BackGround = Sprite::create("slaythespire/bottomScene/scene.jpg", Rect(2, 2, 1920, 1136));
    BackGround->setAnchorPoint(Vec2::ZERO);
    BackGround->setContentSize(Size(1280, 757));
    this->addChild(BackGround);

    // ��
    Wall = Sprite::create("slaythespire/bottomScene/scene.png", Rect(2, 500, 1920, 771));
    Wall->setContentSize(Size(1280, 514));
    Wall->setPosition(Vec2(640, 510));
    this->addChild(Wall);

    // �ٴ�
    Floor = Sprite::create("slaythespire/bottomScene/scene.png", Rect(2, 1273, 1920, 278));
    Floor->setContentSize(Size(1280, 185));
    Floor->setPosition(Vec2(640, 80));
    this->addChild(Floor);

    // ���
    Pillar = Sprite::create("slaythespire/bottomScene/scene2.png", Rect(749, 426, 744, 548));
    Pillar->setPosition(Vec2(640, 480));
    Pillar->setScale(0.7f);
    this->addChild(Pillar);

    // ���
    Decor = Sprite::create("slaythespire/bottomScene/scene2.png", Rect(1900, 727, 130, 247));
    Decor->setPosition(Vec2(120, 630));
    Decor->setScale(0.75f);
    this->addChild(Decor);

    // õ��
    Ceiling = Sprite::create("slaythespire/bottomScene/scene.png", Rect(2, 1553, 1920, 332));
    Ceiling->setContentSize(Size(1280, 221));
    Ceiling->setPosition(Vec2(640, 640));
    this->addChild(Ceiling);

    // ��� ��
    TopBar = Sprite::create("slaythespire/ui/topPanel/bar.png");
    TopBar->setContentSize(Size(1280, 64));
    TopBar->setPosition(Vec2(640, 687));
    TopBar->setZOrder(21);
    this->addChild(TopBar);

    // ü��
    Heart = Sprite::create("slaythespire/ui/topPanel/panelHeart.png");
    Heart->setScale(0.85f);
    Heart->setPosition(Vec2(180, 700));
    Heart->setZOrder(21);
    this->addChild(Heart);

    // ���
    Gold = Sprite::create("slaythespire/ui/topPanel/panelGoldBag.png");
    Gold->setScale(0.85f);
    Gold->setPosition(Vec2(290, 702));
    Gold->setZOrder(21);
    this->addChild(Gold);

    // ��� ��
    TopMap = Sprite::create("slaythespire/ui/topPanel/map.png");
    TopMap->setPosition(Vec2(1180, 702));
    TopMap->setScale(0.7f);
    TopMap->setZOrder(21);
    this->addChild(TopMap);

    // ��� �� �ٿ�� �ڽ�
    TopMap_Box = LayerColor::create(Color4B::RED);
    TopMap_Box->setContentSize(Size(40, 40));
    TopMap_Box->setPosition(Vec2(1160, 685));
    TopMap_Box->setOpacity(0);
    this->addChild(TopMap_Box);

    // ��� ��
    TopDeck = Sprite::create("slaythespire/ui/topPanel/deck.png");
    TopDeck->setPosition(Vec2(1220, 702));
    TopDeck->setScale(0.7f);
    TopDeck->setZOrder(21);
    this->addChild(TopDeck);

    // ��� �� �ٿ�� �ڽ�
    TopDeck_Box = LayerColor::create(Color4B::WHITE);
    TopDeck_Box->setContentSize(Size(40, 40));
    TopDeck_Box->setPosition(Vec2(1200, 685));
    TopDeck_Box->setOpacity(0);
    this->addChild(TopDeck_Box);

    // ���� �޴�
    TopMenu = Sprite::create("slaythespire/ui/topPanel/settings.png");
    TopMenu->setPosition(Vec2(1260, 702));
    TopMenu->setScale(0.7f);
    TopMenu->setZOrder(21);
    this->addChild(TopMenu);

    // ���� �޴� �ٿ���ڽ�
    TopMenu_Box = LayerColor::create(Color4B::ORANGE);
    TopMenu_Box->setContentSize(Size(40, 40));
    TopMenu_Box->setPosition(Vec2(1240, 685));
    TopMenu_Box->setOpacity(0);
    this->addChild(TopMenu_Box);

    // �ϴ� ������ �ִ� ī�� ����
    DeckBox = LayerColor::create(Color4B::WHITE);
    DeckBox->setContentSize(Size(80, 80));
    DeckBox->setPosition(40, 10);
    DeckBox->setOpacity(0);
    DeckBox->setVisible(false);
    this->addChild(DeckBox);

    // �ϴ� ����� ī�� ����
    DisDeckBox = LayerColor::create(Color4B::WHITE);
    DisDeckBox->setContentSize(Size(80, 80));
    DisDeckBox->setPosition(Vec2(1160, 10));
    DisDeckBox->setOpacity(0);
    DisDeckBox->setVisible(false);
    this->addChild(DisDeckBox);

    Vec2 pos_2 = Vec2(275, -50);

    for (int i = 0; i < 5; i++)
    {
        CardBox[i] = LayerColor::create(Color4B::ORANGE);
        CardBox[i]->setOpacity(0);
        CardBox[i]->setContentSize(Size(155, 210));
        CardBox[i]->setPosition(pos_2);
        CardBox[i]->setZOrder(5);
        CardBox[i]->setVisible(false);
        this->addChild(CardBox[i]);
        pos_2.x += 125;
    }

    // ������ ��ư
    EndTurnBox = LayerColor::create(Color4B::WHITE);
    EndTurnBox->setOpacity(0);
    EndTurnBox->setContentSize(Size(150, 62));
    EndTurnBox->setPosition(Vec2(1075, 110));
    EndTurnBox->setVisible(false);
    this->addChild(EndTurnBox);
    
    // ��� ��ư
    CoutinueBox = LayerColor::create(Color4B::WHITE);
    CoutinueBox->setOpacity(0);
    CoutinueBox->setContentSize(Size(110, 40));
    CoutinueBox->setPosition(Vec2(585, 80));
    CoutinueBox->setVisible(false);
    this->addChild(CoutinueBox);

    // ����
    rewardBox = LayerColor::create(Color4B::RED);
    rewardBox->setOpacity(0);
    rewardBox->setContentSize(Size(220, 40));
    rewardBox->setPosition(Vec2(530, 430));
    rewardBox->setVisible(false);
    rewardBox->setZOrder(10);
    this->addChild(rewardBox);

    // ĳ���Ϳ� ���� ���� ���� ����
    if (Charcter_choes == 0)
    {
        Item[0] = Sprite::create("slaythespire/relics/burningBlood.png");
        Item[0]->setScale(0.75f);
        Item[0]->setPosition(Vec2(35, 650));
        this->addChild(Item[0]);
    }
}

void GameScene::Create_Font()
{
    TTFConfig ttfConfig("slaythespire/GyeonggiCheonnyeonBatangBold.ttf", 20);

    auto user = UserDefault::getInstance();


    if (Charcter_choes == 0)
    {
        // ĳ���� �̸�
        CharcterName = Label::createWithTTF(ttfConfig, "���̾�Ŭ����");
        CharcterName->setPosition(Vec2(80, 702));
        CharcterName->setZOrder(21);
        this->addChild(CharcterName);

        // ü��
        HeartFont = Label::createWithTTF(ttfConfig, "0/0");
        HeartFont->setTextColor(Color4B(250, 128, 114, 255));
        HeartFont->enableOutline(Color4B::BLACK, 1);
        HeartFont->setPosition(Vec2(230, 702));
        HeartFont->setZOrder(21);
        this->addChild(HeartFont);

        auto user = UserDefault::getInstance();

        int Now = user->getIntegerForKey("Ch_Hp");
        int Max = user->getIntegerForKey("Ch_MaxHp");
        int Gold = user->getIntegerForKey("Gold");

        char Heart[100];
        sprintf(Heart, "%d/%d", Now, Max);
        HeartFont->setString(Heart);

        // ���� ���
        GoldFont = Label::createWithTTF(ttfConfig, "99");
        GoldFont->setTextColor(Color4B(239, 200, 81, 255));
        GoldFont->enableOutline(Color4B::BLACK, 1);
        GoldFont->setPosition(Vec2(330, 702));
        GoldFont->setZOrder(21);
        this->addChild(GoldFont);

        char Goldf[100];
        sprintf(Goldf, "%d", Gold);
        GoldFont->setString(Goldf);
    }
}

void GameScene::Check(float dt)
{
    int number = 0;

    if (choes == 10)
    {
        // ī�忡 ����� ��ȣ ȹ��
        for (int i = 0; i < 5; i++)
        {
            if (battel->CardOutline[i] != nullptr && battel->CardOutline[i]->isVisible() == true)
            {
                number = battel->card[i];
                break;
            }
        }

        // ���� ī�尡 ���� ���̾ �浹�ϸ�
        if (number == 1)
        {
            if (cursor_point->getBoundingBox().intersectsRect(battel->mlayer->getBoundingBox()))
            {
                // �ߺ� ���� ����
                if (MonCheck != nullptr)
                {
                    this->removeChild(MonCheck);
                }
                MonCheck = Sprite::create("slaythespire/ui/option/toggleButtonOverlay2.png");
                if (Map->MapIcon[Map->floor]->getName() == "Monster")
                {
                    if (battel->random == 1 || battel->random == 5)
                        MonCheck->setPosition(Vec2(battel->mlayer->getPositionX() + 60, battel->mlayer->getPositionY() + 220));
                    else if (battel->random == 2 || battel->random == 3)
                        MonCheck->setPosition(Vec2(battel->mlayer->getPositionX() + 50, battel->mlayer->getPositionY() + 100));
                    else if (battel->random == 4)
                        MonCheck->setPosition(Vec2(battel->mlayer->getPositionX() + 100, battel->mlayer->getPositionY() + 220));
                    else if (battel->random == 6)
                        MonCheck->setPosition(Vec2(battel->mlayer->getPositionX() + 100, battel->mlayer->getPositionY() + 160));
                    else if (battel->random == 7)
                        MonCheck->setPosition(Vec2(battel->mlayer->getPositionX() + 140, battel->mlayer->getPositionY() + 180));
                }
                else if (Map->MapIcon[Map->floor]->getName() == "Elite")
                    MonCheck->setPosition(Vec2(battel->mlayer->getPositionX() + 100, battel->mlayer->getPositionY() + 320));
                else if (Map->floor == 14)
                    MonCheck->setPosition(Vec2(battel->mlayer->getPositionX() + 120, battel->mlayer->getPositionY() + 280));

                MonCheck->setZOrder(10);
                this->addChild(MonCheck);
            }
            else
            {
                if (MonCheck != nullptr)
                {
                    this->removeChild(MonCheck);
                }
            }
        }

        // ��� ī�尡 ĳ���� ���̾ �浹�ϸ�
        else if (number == 2)
        {
            if (cursor_point->getBoundingBox().intersectsRect(ChAnimation->Character_Box->getBoundingBox()))
            {
                // �ߺ� ���� ����
                if (ChCheck != nullptr)
                {
                    this->removeChild(ChCheck);
                }
                ChCheck = Sprite::create("slaythespire/ui/option/toggleButtonOverlay2.png");
                ChCheck->setPosition(Vec2(340, 430));
                ChCheck->setZOrder(10);
                this->addChild(ChCheck);
            }
            else
            {
                if (ChCheck != nullptr)
                {
                    this->removeChild(ChCheck);
                }
            }
        }
    }
}

void GameScene::MonAction(float dt)
{
    // ���� ���� �ʱ�ȭ
    battel->Mon_Defend = 0;

    // ������ �ο�
    if (battel->name != "Boss")
    {
        if (battel->action == 1 || battel->action == 3)
        {
            cocos2d::log("Mon_Damage : %d", battel->Mon_Damage);
            char changedefend[10];

            if (Ch_Defend > battel->Mon_Damage)
            {
                Ch_Defend -= battel->Mon_Damage;
                sprintf(changedefend, "%d", Ch_Defend);
                Ch_Defend_font->setString(changedefend);
                sound->BlackAttack();
            }
            else if (Ch_Defend == battel->Mon_Damage)
            {
                Ch_Defend_sprite->setVisible(false);
                Ch_Defend_font->setVisible(false);
                this->removeChild(Ch_Defend_sprite);
                this->removeChild(Ch_Defend_font);
                sound->BreakDefend();
            }
            else if (Ch_Defend < battel->Mon_Damage)
            {
                if (Ch_Defend_sprite != nullptr)
                {
                    //Ch_Defend_sprite->setVisible(false);
                    this->removeChild(Ch_Defend_sprite);
                }

                if (Ch_Defend_font != nullptr)
                {
                    //Ch_Defend_font->setVisible(false);
                    this->removeChild(Ch_Defend_font);
                }

                // ���� �μ����� ���� ���� ������
                if (Ch_Defend > 0)
                {
                    sound->BreakDefend();
                }

                Ch_Defend -= battel->Mon_Damage;
                int Hp = battel->Ch_NowHp;
                Hp += Ch_Defend;
                cocos2d::log("Ch Hp : %d", Hp);
                if (Hp <= 0)
                {
                    Hp = 0;
                    DeckBox->setVisible(false);
                    DisDeckBox->setVisible(false);
                    EndTurnBox->setVisible(false);
                    for (int i = 0; i < 5; i++)
                    {
                        CardBox[i]->setVisible(false);
                    }
                    this->scheduleOnce(schedule_selector(GameScene::CheckHp), 1.0f);
                    this->unschedule(schedule_selector(GameScene::Check));
                }
                char changeHp[20];
                sprintf(changeHp, "%d/%d", Hp, battel->Ch_MaxHp);
                battel->Character_Hp_Font->setString(changeHp);
                HeartFont->setString(changeHp);

                float hp = (float)Hp * 100 / battel->Ch_MaxHp;

                battel->Character_Hp->setPercent(hp);
                battel->Ch_NowHp = Hp;
                auto user = UserDefault::getInstance();
                user->setIntegerForKey("Ch_Hp", Hp);

                // �� ��Ȳ�� �´� ���� ���� ����
                if (battel->name == "Monster")
                {
                    if (battel->random == 1)
                    {
                        sound->DaggerAtk();
                    }
                    else if (battel->random == 2)
                    {
                        sound->DaggerAtk();
                    }
                    else if (battel->random == 3)
                    {
                        sound->DaggerAtk();
                    }
                    else if (battel->random == 4)
                    {
                        if (battel->action == 1)
                            sound->SwordAtk();
                        else if (battel->action == 3)
                        {
                            // ���ݰ� ���ΰ��� ��
                            sound->ScimitarAtk();
                            sound->GetDefend();
                        }
                    }
                    else if (battel->random == 5)
                    {
                        sound->SwordAtk();
                    }
                    else if (battel->random == 6)
                    {
                        sound->SlimeAtk();
                    }
                    else if (battel->random == 7)
                    {
                        sound->SlimeAtk();
                    }
                }
                else if (battel->name == "Elite")
                {
                    if (battel->random == 1)
                    {
                        if (battel->action == 1)
                        {
                            sound->AttackSound();
                        }
                        else if (battel->action == 3)
                        {
                            sound->HeavyAttackSound();
                        }
                    }
                    else if (battel->random == 2)
                    {
                        if (battel->action == 1)
                        {
                            sound->ScimitarAtk();
                        }
                    }
                }
            }
        }
        else if (battel->action == 4)
        {
            // �� ��Ȳ�� �´� ���� ���� ����
            if (battel->name == "Monster")
            {
                // ���� ���� ������ ���� ����
                if (battel->random == 3)
                {
                    sound->Buff();
                }
            }
        }
    }
    else if (battel->name == "Boss")
    {
        if (battel->name == "Boss")
            {
            if (battel->action == 1)
            {
                count = 0;
                this->schedule(schedule_selector(GameScene::Whirlwind), 0.1f);
            }
            else if (battel->action == 3)
            {
                sound->SwordAtk();

                char changedefend[10];

                if (Ch_Defend > battel->Mon_Damage)
                {
                    Ch_Defend -= battel->Mon_Damage;
                    sprintf(changedefend, "%d", Ch_Defend);
                    Ch_Defend_font->setString(changedefend);
                    sound->BlackAttack();
                }
                else if (Ch_Defend == battel->Mon_Damage)
                {
                    Ch_Defend_sprite->setVisible(false);
                    Ch_Defend_font->setVisible(false);
                    this->removeChild(Ch_Defend_sprite);
                    this->removeChild(Ch_Defend_font);
                    sound->BreakDefend();
                }
                else if (Ch_Defend < battel->Mon_Damage)
                {
                    if (Ch_Defend_sprite != nullptr)
                    {
                        //Ch_Defend_sprite->setVisible(false);
                        this->removeChild(Ch_Defend_sprite);
                    }

                    if (Ch_Defend_font != nullptr)
                    {
                        //Ch_Defend_font->setVisible(false);
                        this->removeChild(Ch_Defend_font);
                    }

                    // ���� �μ����� ���� ���� ������
                    if (Ch_Defend > 0)
                    {
                        sound->BreakDefend();
                    }

                    Ch_Defend -= battel->Mon_Damage;
                    int Hp = battel->Ch_NowHp;
                    Hp += Ch_Defend;
                    cocos2d::log("Ch Hp : %d", Hp);
                    if (Hp <= 0)
                    {
                        Hp = 0;
                        DeckBox->setVisible(false);
                        DisDeckBox->setVisible(false);
                        EndTurnBox->setVisible(false);
                        for (int i = 0; i < 5; i++)
                        {
                            CardBox[i]->setVisible(false);
                        }
                        this->scheduleOnce(schedule_selector(GameScene::CheckHp), 1.0f);
                        this->unschedule(schedule_selector(GameScene::Check));
                    }
                    char changeHp[20];
                    sprintf(changeHp, "%d/%d", Hp, battel->Ch_MaxHp);
                    battel->Character_Hp_Font->setString(changeHp);
                    HeartFont->setString(changeHp);

                    float hp = (float)Hp * 100 / battel->Ch_MaxHp;

                    battel->Character_Hp->setPercent(hp);
                    battel->Ch_NowHp = Hp;
                    auto user = UserDefault::getInstance();
                    user->setIntegerForKey("Ch_Hp", Hp);
                }
            }
            else if (battel->action == 4)
            {
                count = 0;
                this->schedule(schedule_selector(GameScene::DoubleAtk), 0.4f);
            }
        }
    }
    // �� ȹ��
    if (battel->action == 2)
    {
        // �� ȹ�� ����
        sound->GetDefend();
    }
    // ���ŵ���� ���� ���� ����
    if (battel->random == 5 && battel->action == 2)
        sound->Buff();
    
    // ���� �ִϸ��̼� ����
    battel->MonActionAnimation(Map->MapIcon[Map->floor]->getName());
}

void GameScene::DrawCard()
{
    log("Draw Card");
    // ĳ���� ����� ��� �ʱ�ȭ
    Ch_Damage = 6;
    // ī�� �̱�
    battel->DrawCard();
    // ī�� �̱� ���� ����
    sound->DrawCardSound();
    // �ڽ�Ʈ �ʱ�ȭ
    battel->nowCost = battel->MaxCost;

    // �ʱ�ȭ�� �ڽ�Ʈ ȭ�鿡 ���
    char cost[10];
    sprintf(cost, "%d/%d", battel->MaxCost, battel->MaxCost);
    battel->CostFont->setString(cost);

    // visible������ �ٿ�� �ڽ� visible����
    for (int i = 0; i < 5; i++)
    {
        if (CardBox[i]->isVisible() == false)
        {
            CardBox[i]->setVisible(true);
        }
    }

    // ���� �����൵ ǥ��
    battel->MonAction(Map->MapIcon[Map->floor]->getName());
}

void GameScene::CheckHp(float dt)
{
    // ���� óġ
    if (battel->NowHp <= 0)
    {
        // �¸� ���� ����
        sound->Victory();

        // ���� battel �� ������ ���ο� battel �� �߰�
        battel->Remove();
        this->removeChild(battel);
        this->unschedule(schedule_selector(GameScene::CheckHp));

        // �Ϲݸ�, ����Ʈ óġ�� ����ǰ ȹ��
        if (Map->floor != 14)
        {
            battel->MonDead(Map->MapIcon[Map->floor]->getName());
            // ����� �Ͻ�����
            if (Map->MapIcon[Map->floor]->getName() == "Monster")
            {
                sound->PauseBottomTheme();
            }
            // ����Ʈ���̶�� ����� ����
            if (Map->MapIcon[Map->floor]->getName() == "Elite")
            {
                sound->StopEliteTheme();
            }
        }
        // ���� óġ�� ����
        else
        {
            battel->ChDead(Map->MapIcon[Map->floor]->getName());
            CoutinueBox->setVisible(true);
            // �������� ���� ����
            sound->StopBottomTheme();
            // ���� ��׶��� ���� ����
            sound->EndingTheme();
        }

        this->addChild(battel);

        rewardBox->setVisible(true);

        // choes_key ������ �� ����
        user->setIntegerForKey("choes_key", 0);
        // �� �����ҋ� ���� ����
        Map->floor++;

        // ������ ü�� ȸ��
        battel->Ch_NowHp += 6;

        if (battel->Ch_NowHp > battel->Ch_MaxHp)
            battel->Ch_NowHp = battel->Ch_MaxHp;

        auto user = UserDefault::getInstance();
        user->setIntegerForKey("Ch_Hp", battel->Ch_NowHp);

        char change[100];
        sprintf(change, "%d/%d", battel->Ch_NowHp, battel->Ch_MaxHp);
        HeartFont->setString(change);
    }
    // ĳ���� ����
    else if (battel->Ch_NowHp <= 0)
    {
        // ���� battel �� ������ ���ο� battel �� �߰�
        battel->Remove();
        this->removeChild(battel);
        this->removeChild(ChAnimation);
        this->unschedule(schedule_selector(GameScene::CheckHp));
        auto user = UserDefault::getInstance();

        battel->ChDead(Map->MapIcon[Map->floor]->getName());
        this->addChild(battel);
        CoutinueBox->setVisible(true);
        
        // �������� ��׶��� ���� ����
        if (Map->MapIcon[Map->floor]->getName() == "Monster")
        {
            sound->StopBottomTheme();
        }
        if (Map->MapIcon[Map->floor]->getName() == "Elite")
        {
            sound->StopEliteTheme();
        }


        // ĳ���� ���� ���� ����
        sound->ChDead();

        // choes_key ������ �� ����
        user->setIntegerForKey("choes_key", 0);
    }
    // �ƹ��� ���� �ʾ����� ī�� ��ο�
    else
    {
        // �÷��̾� �� ���� ���� ����
        sound->PlayerTurn();
        // ī�� ��ο�
        DrawCard();
        // �÷��̾��� bool���� �� ����
        playerturn = true;
    }

    // ĳ���� ���� �ʱ�ȭ
    Ch_Defend = 0;
    this->removeChild(Ch_Defend_sprite);
    this->removeChild(Ch_Defend_font);
}

void GameScene::CreateBattelScene(float dt)
{
    this->removeChild(battel);
    if (battel != nullptr)
    {
        delete battel;
    }
    battel = new Battel;
    battel->Create(Map->MapIcon[Map->floor]->getName());
    this->addChild(battel);

    if (Map->floor <= 13)
    {
        if (Map->MapIcon[Map->floor]->getName() == "Monster" ||
            Map->MapIcon[Map->floor]->getName() == "Elite")
        {
            // choes �� ����
            user->setIntegerForKey("choes_key", 10);
            // ��Ʋ ���� ���� ����
            sound->BattelStartMonster();
            // �÷��̾��� bool���� �� ����
            playerturn = true;
            // ����Ʈ���̶�� ����� ����
            if (Map->MapIcon[Map->floor]->getName() == "Elite")
            {
                sound->PauseBottomTheme();
                sound->EliteTheme();
            }
        }
        else if (Map->MapIcon[Map->floor]->getName() == "Rest")
        {
            // choes �� ����
            user->setIntegerForKey("choes_key", 11);
            // ���� Ÿ�� �Ҹ� ����
            sound->CampFire();
            // �������� ��׶��� �Ͻ�����
            sound->PauseBottomTheme();
        }
    }
    // ���� ��������
    else if (Map->floor == 14)
    {
        // choes �� ����
        user->setIntegerForKey("choes_key", 10);
        // ��Ʋ ���� ���� ����
        sound->BattelStartBoss();
        // �÷��̾��� bool���� �� ����
        playerturn = true;
    }
}

void GameScene::StopSound(float dt)
{
    sound->StopBottomTheme();
}

void GameScene::EnemyTurn(float dt)
{
    sound->EnemyTurn();
}

void GameScene::Whirlwind(float dt)
{
    sound->ButcherAtk();

    char changedefend[10];

    if (Ch_Defend > battel->Mon_Damage)
    {
        Ch_Defend -= battel->Mon_Damage;
        sprintf(changedefend, "%d", Ch_Defend);
        Ch_Defend_font->setString(changedefend);
        sound->BlackAttack();
    }
    else if (Ch_Defend == battel->Mon_Damage)
    {
        this->removeChild(Ch_Defend_sprite);
        this->removeChild(Ch_Defend_font);
    }
    else if (Ch_Defend < battel->Mon_Damage)
    {
        if (Ch_Defend_sprite != nullptr)
        {
            //Ch_Defend_sprite->setVisible(false);
            this->removeChild(Ch_Defend_sprite);
        }

        if (Ch_Defend_font != nullptr)
        {
            //Ch_Defend_font->setVisible(false);
            this->removeChild(Ch_Defend_font);
        }

        // ���� �μ����� ���� ���� ������
        if (Ch_Defend > 0)
        {
            sound->BreakDefend();
        }

        Ch_Defend -= battel->Mon_Damage;
        int Hp = battel->Ch_NowHp;
        Hp += Ch_Defend;
        cocos2d::log("Ch Hp : %d", Hp);
        if (Hp <= 0)
        {
            Hp = 0;
            DeckBox->setVisible(false);
            DisDeckBox->setVisible(false);
            EndTurnBox->setVisible(false);
            for (int i = 0; i < 5; i++)
            {
                CardBox[i]->setVisible(false);
            }
            this->scheduleOnce(schedule_selector(GameScene::CheckHp), 1.0f);
            this->unschedule(schedule_selector(GameScene::Check));
        }
        char changeHp[20];
        sprintf(changeHp, "%d/%d", Hp, battel->Ch_MaxHp);
        battel->Character_Hp_Font->setString(changeHp);
        HeartFont->setString(changeHp);

        float hp = (float)Hp * 100 / battel->Ch_MaxHp;

        battel->Character_Hp->setPercent(hp);
        battel->Ch_NowHp = Hp;
        auto user = UserDefault::getInstance();
        user->setIntegerForKey("Ch_Hp", Hp);

        // ĳ���� ���� ��� 0���� �ʱ�ȭ
        Ch_Defend = 0;
    }

    int X = RandomHelper::random_int(330, 350);
    int Y = RandomHelper::random_int(300, 360);

    auto slash = Sprite::create("slaythespire/vfx/combat/slash_1.png");
    slash->setRotation(90.0f);
    slash->setPosition(Vec2(X, Y));
    slash->setOpacity(0);
    this->addChild(slash);

    auto move = MoveBy::create(0.25f, Vec2(-30, 0));
    auto fadein = FadeIn::create(0.1f);
    auto fadeout = FadeOut::create(0.1f);
    auto spawn = Spawn::create(move, fadein, nullptr);
    auto seq = Sequence::create(spawn, fadeout, RemoveSelf::create(), nullptr);
    slash->runAction(seq);
       
    count++;

    if (count == 4)
        this->unschedule(schedule_selector(GameScene::Whirlwind));
}

void GameScene::DoubleAtk(float dt)
{
    sound->SwordAtk();

    char changedefend[10];

    if (Ch_Defend > battel->Mon_Damage)
    {
        Ch_Defend -= battel->Mon_Damage;
        sprintf(changedefend, "%d", Ch_Defend);
        Ch_Defend_font->setString(changedefend);
        sound->BlackAttack();
    }
    else if (Ch_Defend == battel->Mon_Damage)
    {
        Ch_Defend_sprite->setVisible(false);
        Ch_Defend_font->setVisible(false);
        this->removeChild(Ch_Defend_sprite);
        this->removeChild(Ch_Defend_font);
        sound->BreakDefend();
    }
    else if (Ch_Defend < battel->Mon_Damage)
    {
        if (Ch_Defend_sprite != nullptr)
        {
            //Ch_Defend_sprite->setVisible(false);
            this->removeChild(Ch_Defend_sprite);
        }

        if (Ch_Defend_font != nullptr)
        {
            //Ch_Defend_font->setVisible(false);
            this->removeChild(Ch_Defend_font);
        }

        // ���� �μ����� ���� ���� ������
        if (Ch_Defend > 0)
        {
            sound->BreakDefend();
        }

        Ch_Defend -= battel->Mon_Damage;
        int Hp = battel->Ch_NowHp;
        Hp += Ch_Defend;
        cocos2d::log("Ch Hp : %d", Hp);
        if (Hp <= 0)
        {
            Hp = 0;
            DeckBox->setVisible(false);
            DisDeckBox->setVisible(false);
            EndTurnBox->setVisible(false);
            for (int i = 0; i < 5; i++)
            {
                CardBox[i]->setVisible(false);
            }
            this->scheduleOnce(schedule_selector(GameScene::CheckHp), 1.0f);
            this->unschedule(schedule_selector(GameScene::Check));
        }
        char changeHp[20];
        sprintf(changeHp, "%d/%d", Hp, battel->Ch_MaxHp);
        battel->Character_Hp_Font->setString(changeHp);
        HeartFont->setString(changeHp);

        float hp = (float)Hp * 100 / battel->Ch_MaxHp;

        battel->Character_Hp->setPercent(hp);
        battel->Ch_NowHp = Hp;
        auto user = UserDefault::getInstance();
        user->setIntegerForKey("Ch_Hp", Hp);

        // ĳ���� ���� ��� 0���� �ʱ�ȭ
        Ch_Defend = 0;
    }

    auto slash = Sprite::create("slaythespire/vfx/combat/slash_1.png");
    slash->setRotation(180.0f);
    slash->setPosition(Vec2(330, 410));
    slash->setOpacity(0);
    this->addChild(slash);

    auto move = MoveBy::create(0.25f, Vec2(0, -40));
    auto fadein = FadeIn::create(0.1f);
    auto fadeout = FadeOut::create(0.1f);
    auto spawn = Spawn::create(move, fadein, nullptr);
    auto seq = Sequence::create(spawn, fadeout, RemoveSelf::create(), nullptr);
    slash->runAction(seq);

    count++;

    if (count == 2)
        this->unschedule(schedule_selector(GameScene::DoubleAtk));
}