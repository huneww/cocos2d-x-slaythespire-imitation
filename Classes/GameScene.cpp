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

   // 캐릭터 애니메이션 생성
   ChAnimation = new CharacterAnimation;
   ChAnimation->CharacterIdelAnimation(Charcter_choes);
   this->addChild(ChAnimation);

   // 사운드 클래스 인스턴스 생성
   sound = new Sound;

   // 사운드 조절 변수 게임시작시 초기화 실행
   auto user = UserDefault::getInstance();
   sound->background_volume = user->getFloatForKey("BackGround");
   sound->effect_volume = user->getFloatForKey("Effect");

   sound->BottomTheme();

   log("Background volume : %f", sound->background_volume);

   // 맵 생성
   Map = new MapScene;
   Map->CreateMap();
   Map->setZOrder(20);
   this->addChild(Map);

   // 커서 생성
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
        // 이동한 좌표 크기 화인
        Vec2 pos = touch->getDelta();
        
        // 이동한 좌표 만큼 이동
        for (int i = 0; i < 4; i++)
            Map->Map[i]->setPosition(Vec2(Map->Map[i]->getPositionX(),
                Map->Map[i]->getPositionY() + pos.y));


        // 지도가 정해진 영역에서만 움직이도록 예외처리
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

        // 아이콘 위치 조정
        for (int i = 0; i < 14; i++)
        {
            Map->MapIcon[i]->setPosition(Vec2(Map->MapIcon[i]->getPositionX(),
                Map->MapIcon[i]->getPositionY() + pos.y));
        }

        // 지도가 정해진 영역에서만 움직이도록 예외처리
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

        // 아이콘 선택 서클이 있다면 위치를 변경
        for (int i = 0; i < Map->circlecount; i++)
        {
            if (Map->IconCircle[i] != nullptr)
            {
               Map->IconCircle[i]->setPosition(Map->MapIcon[i]->getPosition());
            }
        }

        // 바운딩 박스 위치 변경
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

    // 맵, 설정이 열여있지 안을때
    if (choes == 0)
    {
        // 지도 클릭
        if (TopMap_Box->isVisible() == true &&
            cursor_point->getBoundingBox().intersectsRect(TopMap_Box->getBoundingBox()))
        {
            cocos2d::log("TopMap");
            // 맵 스프라이트 화면에 표시
            Map->Visibletrue();
            // 터치이벤트 조건변수 값 변경
            user->setIntegerForKey("choes_key", 1);
            // 오픈 사운드 실행
            sound->OpenMap();
        }
        // 상단 현재 덱 클릭
        else if (TopDeck_Box->isVisible() == true &&
            cursor_point->getBoundingBox().intersectsRect(TopDeck_Box->getBoundingBox()))
        {
            cocos2d::log("TopDeck");
            // 현재 소지 카드 화면에 출력
            deck = new Deck;
            deck->Create();
            this->addChild(deck);
            // 터치이벤트 조건변수 값 변경
            user->setIntegerForKey("choes_key", 2);

            // 덱 오픈 사운드 실행
            sound->ViewDeck();
        }
        // 설정 클릭
        else if (TopMenu_Box->isVisible() == true &&
            cursor_point->getBoundingBox().intersectsRect(TopMenu_Box->getBoundingBox()))
        {
            cocos2d::log("TopMenu");
            // 옵션 화면에 출력
            Gameoption = new GameOption;
            Gameoption->CreateGameOption();
            this->addChild(Gameoption);
            // 터치이벤트 조건변수 값 변경
            user->setIntegerForKey("choes_key", 3);

            // 클릭 사운드 실행
            sound->MenuClick();
        }
        // 하단 사용가능한 덱 클릭
        else if (DeckBox->isVisible() == true &&
            cursor_point->getBoundingBox().intersectsRect(DeckBox->getBoundingBox()))
        {
            cocos2d::log("Can use Deck");
        }
        // 하단 사용한 덱 클릭
        else if (DisDeckBox->isVisible() == true &&
            cursor_point->getBoundingBox().intersectsRect(DisDeckBox->getBoundingBox()))
        {
            cocos2d::log("Can't use Deck");
        }
        // 계속하기 버튼 클릭 (죽으면 나오는 버튼)
        else if (CoutinueBox->isVisible() == true &&
            cursor_point->getBoundingBox().intersectsRect(CoutinueBox->getBoundingBox()))
        {
            cocos2d::log("countinue");

            // 오픈 사운드 실행
            sound->MenuClick();
            // 스테이지 백그라운드 정지
            sound->StopBottomTheme();
            // 캐릭터 죽었을때 나오는 사운드 정지
            sound->StopEndingTheme();
            

            // 메인 메뉴로 화면 전환
            auto scene = MainMenu::createScene();
            _director->replaceScene(TransitionFade::create(1.0f, scene));
        }
        // 보상 획득
        else if (rewardBox->isVisible() == true &&
            cursor_point->getBoundingBox().intersectsRect(rewardBox->getBoundingBox()))
        {
            cocos2d::log("reward");
            // 소지 골드 변경
            auto user = UserDefault::getInstance();
            char change_gold[100];
            // 기존 골드 + 획득 골드
            sprintf(change_gold, "%d", battel->gold + user->getIntegerForKey("Gold"));

            GoldFont->setString(change_gold);
            rewardBox->setVisible(false);
            battel->Remove_reward();
            user->setIntegerForKey("Gold", battel->gold + user->getIntegerForKey("Gold"));

            // 골드 획득 사운드 실행
            sound->GetGold();

            // 스테이지 배경음 실행
            sound->ResumeBottomTheme();
        }
        
    }
    // 맵을 열었을때
    else if (choes == 1)
    {
        cocos2d::log("choes : %d", choes);
        // 돌아가기 버튼 클릭
        if (Map->CancleButton_Box != nullptr &&
            cursor_point->getBoundingBox().intersectsRect(Map->CancleButton_Box->getBoundingBox()))
        {
            cocos2d::log("Back Game Scene");
            // 맵 스프라이트 화면에서 제거
            Map->Visiblefalse();
            // 터치 이벤트 조건 변수 값 변경
            user->setIntegerForKey("choes_key", 0);

            // 클릭 사운드 실행
            sound->MenuClick();
            // 맵 오픈 사운드 실행
            sound->OpenMap();
        }
        // 맵 아이콘 클릭
        else if (cursor_point->getBoundingBox().intersectsRect(TopMap_Box->getBoundingBox()))
        {
            cocos2d::log("Map Again");
            // 맵 스프라이트 화면에서 제거
            Map->Visiblefalse();
            // 터치 이벤트 조건 변수 값 변경
            user->setIntegerForKey("choes_key", 0);

            // 클릭 사운드 실행
            sound->MenuClick();
            // 맵 오픈 사운드 실행
            sound->OpenMap();
        }
        // 덱 아이콘 클릭
        else if (cursor_point->getBoundingBox().intersectsRect(TopDeck_Box->getBoundingBox()))
        {
            cocos2d::log("Map->Deck");
            // 맵 스프라이트 화면에서 제거
            Map->Visiblefalse();
            // 터치 이벤트 조건 변수 값 변경
            user->setIntegerForKey("choes_key", 2);

            // 소지 카드 스프라이트 생성
            deck = new Deck;
            deck->Create();
            this->addChild(deck);

            // 덱 오픈 사운드 실행
            sound->ViewDeck();
        }
        // 설정 클릭
        else if (cursor_point->getBoundingBox().intersectsRect(TopMenu_Box->getBoundingBox()))
        {
            cocos2d::log("Map->Menu");
            // 맵 스프라이트 제거
            Map->Visiblefalse();
            // 옵션 화면에 출력
            Gameoption = new GameOption;
            Gameoption->CreateGameOption();
            this->addChild(Gameoption);
            // 터치 이벤트 조건 변수 값 변경
            user->setIntegerForKey("choes_key", 3);

            // 클릭 사운드 실행
            sound->MenuClick();
        }
        // 스테이지 클릭, 현재 층수에 맞는 걸 클릭했는지 확인
        else if (cursor_point->getBoundingBox().intersectsRect(Map->IconBox[Map->floor]->getBoundingBox()))
        {
            cocos2d::log("Click Icon");
            Map->MenuCallBack();

            // 스테이지 선택 사운드 실행
            sound->MapClick();

            // 전투 씬 생성
            this->scheduleOnce(schedule_selector(GameScene::CreateBattelScene), 1.2f);

            DeckBox->setVisible(true);
            DisDeckBox->setVisible(true);
            EndTurnBox->setVisible(true);
            for (int i = 0; i < 5; i++)
            {
                CardBox[i]->setVisible(true);
            }
        }
        // 보스 스테이지 클릭
        else if (Map->floor == 14 && cursor_point->getBoundingBox().intersectsRect(Map->BossBox->getBoundingBox()))
        {
            log("Boss Icon");
            Map->MenuCallBack();

            // 스테이지 선택 사운드 실행
            sound->MapClick();

            // 전투 씬 생성
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
        // 맵 위, 아래로 움직일 경우
        if (rect.containsPoint(locationInNode))
        {

        }
        
    }
    // 댁을 열었을때
    else if (choes == 2)
    {
        cocos2d::log("choes : %d", choes);

        // 다시 덱을 눌렀을때
        if (cursor_point->getBoundingBox().intersectsRect(TopDeck_Box->getBoundingBox()))
        {
            // 덱 스프라이트 제거
            deck->Remove();
            // 터치 이벤트 조건 변수 값 변경
            user->setIntegerForKey("choes_key", 0);
            // 덱 오픈 사운드 실행
            sound->ViewDeck();
        }
        // 돌아가기 버튼 클릭
        else if (deck->CancleButton_Box != nullptr &&
            cursor_point->getBoundingBox().intersectsRect(deck->CancleButton_Box->getBoundingBox()))
        {
            // 덱 스프라이트 제거
            deck->Remove();
            // 터치 이벤트 조건 변수 값 변경
            user->setIntegerForKey("choes_key", 0);
            // 덱 오픈 사운드 실행
            sound->ViewDeck();
        }
        // 지도 클릭
        else if (TopMap_Box->isVisible() == true &&
            cursor_point->getBoundingBox().intersectsRect(TopMap_Box->getBoundingBox()))
        {
            cocos2d::log("TopMap");
            // 덱 스프라이트 제거
            deck->Remove();
            // 맵 스프라이트 화면에 표시
            Map->Visibletrue();
            // 터치이벤트 조건변수 값 변경
            user->setIntegerForKey("choes_key", 1);
            // 오픈 사운드 실행
            sound->OpenMap();
        }
        // 설정 클릭
        else if (TopMenu_Box->isVisible() == true &&
            cursor_point->getBoundingBox().intersectsRect(TopMenu_Box->getBoundingBox()))
        {
            cocos2d::log("TopMenu");
            // 덱 스프라이트 제거
            deck->Remove();
            // 옵션 화면에 출력
            Gameoption = new GameOption;
            Gameoption->CreateGameOption();
            this->addChild(Gameoption);
            // 터치이벤트 조건변수 값 변경
            user->setIntegerForKey("choes_key", 3);

            // 클릭 사운드 실행
            sound->MenuClick();
        }
    }
    // 설정이 열여있을때
    else if (choes == 3)
    {
        cocos2d::log("choes : %d", choes);
        // yes 클릭
        if (Gameoption->Yes_Button_Box != nullptr &&
            cursor_point->getBoundingBox().intersectsRect(Gameoption->Yes_Button_Box->getBoundingBox()))
        {
            cocos2d::log("Yes");
            // 1스테이지 백그라운드 사운드 정지
            this->scheduleOnce(schedule_selector(GameScene::StopSound), 0.5f);
            // 클릭 사운드 실행
            sound->MenuClick();
            // 메인 메뉴로 장면 전환
            auto scene = MainMenu::createScene();
            _director->replaceScene(TransitionFade::create(1.0f, scene));

        }
        // no 클릭
        else if (Gameoption->No_Button_Box != nullptr &&
            cursor_point->getBoundingBox().intersectsRect(Gameoption->No_Button_Box->getBoundingBox()))
        {
            cocos2d::log("No");
            // 옵션 객체 제거
            Gameoption->Remove();
            user->setIntegerForKey("choes_key", 0);
            // 클릭 사운드 실행
            sound->MenuClick();
        }
        
    }
    // 전투 중
    else if (choes == 10 && playerturn == true)
    {
        // 턴 종료 버튼 클릭
        if (EndTurnBox->isVisible() == true && cursor_point->getBoundingBox().intersectsRect(EndTurnBox->getBoundingBox()))
        {
            cocos2d::log("End Turn");
            // 플레이어어턴 변수 false로 변경
            playerturn = false;
            // 카드 사용 확인 스케줄 제거
            this->unschedule(schedule_selector(GameScene::Check));
            // 턴 종료 사운드 실행
            sound->EndTurn();
            // 카드 제거
            battel->Remove_Card();
            // 일정 시간 후 적 턴 시작 사운드 실행
            this->scheduleOnce(schedule_selector(GameScene::EnemyTurn), 0.5f);
            // 1초후 몬스터 행동에 맞는 애니메이션 재생
            this->scheduleOnce(schedule_selector(GameScene::MonAction), 2.0f);
            // 4초후 체력 확인후 카드 드로우
            this->scheduleOnce(schedule_selector(GameScene::CheckHp), 4.0f);
        }
        // 카드 사용
        else if (battel->nowCost > 0)
        {
            // i번째 카드 클릭
            for (int i = 0; i < 5; i++)
            {
                cocos2d::log("Card[i] : %d", i);
                // 카드 아웃라인에 액션 적용
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
                    // 카드 선택 사운드 실행
                    sound->CardSelect();
                    // 카드를 클릭했을때만 스케쥴이 작동하도록
                    this->schedule(schedule_selector(GameScene::Check));

                    break;
                }
            }
            for (int i = 0; i < 5; i++)
            {
                if (i == cardnumber)
                {
                    // 방어 카드 사용
                    if (ChCheck != nullptr &&
                        cursor_point->getBoundingBox().intersectsRect(ChAnimation->Character_Box->getBoundingBox()))
                    {
                        // 스케줄 제거
                        this->unschedule(schedule_selector(GameScene::Check));

                        // 화살표 제거
                        this->removeChild(ChCheck);

                        // 카드 제거
                        battel->Remove_Use_Card(i);

                        CardBox[i]->setVisible(false);
                        // 방어도 획득 사운드 실행
                        sound->GetDefend();
                        // 코스트 차감
                        battel->nowCost -= 1;
                        char changecost[10];
                        // 변경된 코스트 화면에 출력
                        sprintf(changecost, "%d/3", battel->nowCost);
                        battel->CostFont->setString(changecost);

                        // 방어도 획득 애니메이션
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

                        // 방어도 표시
                        TTFConfig ttfConfig_1("slaythespire/GyeonggiCheonnyeonBatangBold.ttf", 20);

                        // 중복생성 방지
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

                        // 방어도 저장
                        // 손상 디버프가 있으면 방어도 3만 획득
                        if (Ch_Impairment > 0)
                            Ch_Defend += 3;
                        else
                            Ch_Defend += 5;

                        char changedefend[10];
                        sprintf(changedefend, "%d", Ch_Defend);
                        Ch_Defend_font->setString(changedefend);
                    }
                    // 공격 카드 사용
                    else if (MonCheck != nullptr &&
                        cursor_point->getBoundingBox().intersectsRect(battel->mlayer->getBoundingBox()))
                    {
                        // 스케줄 제거
                        this->unschedule(schedule_selector(GameScene::Check));

                        // 화살표 제거
                        this->removeChild(MonCheck);

                        // 카드 제거       
                        battel->Remove_Use_Card(i);

                        CardBox[i]->setVisible(false);
                        // 공격 사운드 실행
                        sound->ChAttack();
                        // 코스트 차감
                        battel->nowCost -= 1;
                        char changecost[10];
                        // 변경된 코스트 화면에 출력
                        sprintf(changecost, "%d/3", battel->nowCost);
                        battel->CostFont->setString(changecost);

                        // 몬스터 체력 감소
                        char changedefend[100];

                        cocos2d::log("Mon_Defend : %d", battel->Mon_Defend);
                        log("Ch_Damage : %d", Ch_Damage);


                        // 방어도에 따라 몬스터에 대미지 부여
                        // 방어도 미만의 대미지 받음
                        if (battel->Mon_Defend > Ch_Damage)
                        {
                            // 남은 방어도 출력
                            battel->Mon_Defend -= Ch_Damage;
                            sprintf(changedefend, "%d", battel->Mon_Defend);
                            battel->defend_font->setString(changedefend);
                            cocos2d::log("Mon_Defend > 6");
                            // 방어도가 남을시 사운드 실행
                            sound->BlackAttack();
                        }
                        // 방어도는 없어졌지만 체력은 안까짐
                        else if (battel->Mon_Defend == Ch_Damage)
                        {
                            // 방어 스프라이트, 폰트 제거
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
                        // 방어도 이상의 대미지를 받음
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
                            // 방패 부셔지는 사운드 실행 방어도가 남아있을때
                            if (battel->Mon_Defend > 0)
                            {
                                sound->BreakDefend();
                            }

                            // 공격력과 방어도 차이만큼 대미지 부여
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
    // 휴식
    else if (choes == 11)
    {
        if (cursor_point->getBoundingBox().intersectsRect(battel->campfire_choes->getBoundingBox()))
        {
            log("Sleep");
            // 클릭 사운드 실행
            sound->MenuClick();
            // 체력 회복
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
            // Max체력보다 높아지면 Max체력으로 변경
            if (NowHp > user->getIntegerForKey("Ch_MaxHp"))
            {
                NowHp = user->getIntegerForKey("Ch_MaxHp");
            }
            user->setIntegerForKey("Ch_Hp", NowHp);

            int nowhp = user->getIntegerForKey("Ch_Hp");
            int maxhp = user->getIntegerForKey("Ch_MaxHp");

            // 상단 판낼 체력 변경
            char changehp[100];
            sprintf(changehp, "%d/%d", nowhp, maxhp);
            HeartFont->setString(changehp);

            user->setIntegerForKey("choes_key", 0);

            // 맵 층수 변수 증가   
            Map->floor++;

            // 스테이지 백그라운드 재시작
            sound->ResumeBottomTheme();
            // 장작 타는 소리 정지
            sound->StopCampFire();
        }
    }
    // 이벤트
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
    // 배경
    BackGround = Sprite::create("slaythespire/bottomScene/scene.jpg", Rect(2, 2, 1920, 1136));
    BackGround->setAnchorPoint(Vec2::ZERO);
    BackGround->setContentSize(Size(1280, 757));
    this->addChild(BackGround);

    // 벽
    Wall = Sprite::create("slaythespire/bottomScene/scene.png", Rect(2, 500, 1920, 771));
    Wall->setContentSize(Size(1280, 514));
    Wall->setPosition(Vec2(640, 510));
    this->addChild(Wall);

    // 바닥
    Floor = Sprite::create("slaythespire/bottomScene/scene.png", Rect(2, 1273, 1920, 278));
    Floor->setContentSize(Size(1280, 185));
    Floor->setPosition(Vec2(640, 80));
    this->addChild(Floor);

    // 기둥
    Pillar = Sprite::create("slaythespire/bottomScene/scene2.png", Rect(749, 426, 744, 548));
    Pillar->setPosition(Vec2(640, 480));
    Pillar->setScale(0.7f);
    this->addChild(Pillar);

    // 장식
    Decor = Sprite::create("slaythespire/bottomScene/scene2.png", Rect(1900, 727, 130, 247));
    Decor->setPosition(Vec2(120, 630));
    Decor->setScale(0.75f);
    this->addChild(Decor);

    // 천장
    Ceiling = Sprite::create("slaythespire/bottomScene/scene.png", Rect(2, 1553, 1920, 332));
    Ceiling->setContentSize(Size(1280, 221));
    Ceiling->setPosition(Vec2(640, 640));
    this->addChild(Ceiling);

    // 상단 바
    TopBar = Sprite::create("slaythespire/ui/topPanel/bar.png");
    TopBar->setContentSize(Size(1280, 64));
    TopBar->setPosition(Vec2(640, 687));
    TopBar->setZOrder(21);
    this->addChild(TopBar);

    // 체력
    Heart = Sprite::create("slaythespire/ui/topPanel/panelHeart.png");
    Heart->setScale(0.85f);
    Heart->setPosition(Vec2(180, 700));
    Heart->setZOrder(21);
    this->addChild(Heart);

    // 골드
    Gold = Sprite::create("slaythespire/ui/topPanel/panelGoldBag.png");
    Gold->setScale(0.85f);
    Gold->setPosition(Vec2(290, 702));
    Gold->setZOrder(21);
    this->addChild(Gold);

    // 상단 맵
    TopMap = Sprite::create("slaythespire/ui/topPanel/map.png");
    TopMap->setPosition(Vec2(1180, 702));
    TopMap->setScale(0.7f);
    TopMap->setZOrder(21);
    this->addChild(TopMap);

    // 상단 맵 바운딩 박스
    TopMap_Box = LayerColor::create(Color4B::RED);
    TopMap_Box->setContentSize(Size(40, 40));
    TopMap_Box->setPosition(Vec2(1160, 685));
    TopMap_Box->setOpacity(0);
    this->addChild(TopMap_Box);

    // 상단 덱
    TopDeck = Sprite::create("slaythespire/ui/topPanel/deck.png");
    TopDeck->setPosition(Vec2(1220, 702));
    TopDeck->setScale(0.7f);
    TopDeck->setZOrder(21);
    this->addChild(TopDeck);

    // 상단 덱 바운딩 박스
    TopDeck_Box = LayerColor::create(Color4B::WHITE);
    TopDeck_Box->setContentSize(Size(40, 40));
    TopDeck_Box->setPosition(Vec2(1200, 685));
    TopDeck_Box->setOpacity(0);
    this->addChild(TopDeck_Box);

    // 설정 메뉴
    TopMenu = Sprite::create("slaythespire/ui/topPanel/settings.png");
    TopMenu->setPosition(Vec2(1260, 702));
    TopMenu->setScale(0.7f);
    TopMenu->setZOrder(21);
    this->addChild(TopMenu);

    // 설정 메뉴 바운딩박스
    TopMenu_Box = LayerColor::create(Color4B::ORANGE);
    TopMenu_Box->setContentSize(Size(40, 40));
    TopMenu_Box->setPosition(Vec2(1240, 685));
    TopMenu_Box->setOpacity(0);
    this->addChild(TopMenu_Box);

    // 하단 뽑을수 있는 카드 더미
    DeckBox = LayerColor::create(Color4B::WHITE);
    DeckBox->setContentSize(Size(80, 80));
    DeckBox->setPosition(40, 10);
    DeckBox->setOpacity(0);
    DeckBox->setVisible(false);
    this->addChild(DeckBox);

    // 하단 사용한 카드 더미
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

    // 턴종료 버튼
    EndTurnBox = LayerColor::create(Color4B::WHITE);
    EndTurnBox->setOpacity(0);
    EndTurnBox->setContentSize(Size(150, 62));
    EndTurnBox->setPosition(Vec2(1075, 110));
    EndTurnBox->setVisible(false);
    this->addChild(EndTurnBox);
    
    // 계속 버튼
    CoutinueBox = LayerColor::create(Color4B::WHITE);
    CoutinueBox->setOpacity(0);
    CoutinueBox->setContentSize(Size(110, 40));
    CoutinueBox->setPosition(Vec2(585, 80));
    CoutinueBox->setVisible(false);
    this->addChild(CoutinueBox);

    // 보상
    rewardBox = LayerColor::create(Color4B::RED);
    rewardBox->setOpacity(0);
    rewardBox->setContentSize(Size(220, 40));
    rewardBox->setPosition(Vec2(530, 430));
    rewardBox->setVisible(false);
    rewardBox->setZOrder(10);
    this->addChild(rewardBox);

    // 캐릭터에 따라 시작 유물 변경
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
        // 캐릭터 이름
        CharcterName = Label::createWithTTF(ttfConfig, "아이언클래드");
        CharcterName->setPosition(Vec2(80, 702));
        CharcterName->setZOrder(21);
        this->addChild(CharcterName);

        // 체력
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

        // 소지 골드
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
        // 카드에 저장된 번호 획득
        for (int i = 0; i < 5; i++)
        {
            if (battel->CardOutline[i] != nullptr && battel->CardOutline[i]->isVisible() == true)
            {
                number = battel->card[i];
                break;
            }
        }

        // 공격 카드가 몬스터 레이어에 충돌하면
        if (number == 1)
        {
            if (cursor_point->getBoundingBox().intersectsRect(battel->mlayer->getBoundingBox()))
            {
                // 중복 생성 방지
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

        // 방어 카드가 캐릭터 레이어에 충돌하면
        else if (number == 2)
        {
            if (cursor_point->getBoundingBox().intersectsRect(ChAnimation->Character_Box->getBoundingBox()))
            {
                // 중복 생성 방지
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
    // 몬스터 방어력 초기화
    battel->Mon_Defend = 0;

    // 데미지 부여
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

                // 방패 부서지는 사운드 방어도가 있을때
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

                // 각 상황에 맞는 공격 사운드 실행
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
                            // 공격과 방어두개다 함
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
            // 각 상황에 맞는 공격 사운드 실행
            if (battel->name == "Monster")
            {
                // 빨간 벌래 공버프 사운드 실행
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

                    // 방패 부서지는 사운드 방어도가 있을때
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
    // 방어도 획득
    if (battel->action == 2)
    {
        // 방어도 획득 사운드
        sound->GetDefend();
    }
    // 광신도라면 버프 사운드 실행
    if (battel->random == 5 && battel->action == 2)
        sound->Buff();
    
    // 몬스터 애니메이션 실행
    battel->MonActionAnimation(Map->MapIcon[Map->floor]->getName());
}

void GameScene::DrawCard()
{
    log("Draw Card");
    // 캐릭터 대미지 계속 초기화
    Ch_Damage = 6;
    // 카드 뽑기
    battel->DrawCard();
    // 카드 뽑기 사운드 실행
    sound->DrawCardSound();
    // 코스트 초기화
    battel->nowCost = battel->MaxCost;

    // 초기화한 코스트 화면에 출력
    char cost[10];
    sprintf(cost, "%d/%d", battel->MaxCost, battel->MaxCost);
    battel->CostFont->setString(cost);

    // visible변경한 바운딩 박스 visible변경
    for (int i = 0; i < 5; i++)
    {
        if (CardBox[i]->isVisible() == false)
        {
            CardBox[i]->setVisible(true);
        }
    }

    // 몬스터 다음행도 표시
    battel->MonAction(Map->MapIcon[Map->floor]->getName());
}

void GameScene::CheckHp(float dt)
{
    // 몬스터 처치
    if (battel->NowHp <= 0)
    {
        // 승리 사운드 실행
        sound->Victory();

        // 기존 battel 씬 제거후 새로운 battel 씬 추가
        battel->Remove();
        this->removeChild(battel);
        this->unschedule(schedule_selector(GameScene::CheckHp));

        // 일반몹, 엘리트 처치시 전리품 획득
        if (Map->floor != 14)
        {
            battel->MonDead(Map->MapIcon[Map->floor]->getName());
            // 배경음 일시정지
            if (Map->MapIcon[Map->floor]->getName() == "Monster")
            {
                sound->PauseBottomTheme();
            }
            // 엘리트몹이라면 배경음 정지
            if (Map->MapIcon[Map->floor]->getName() == "Elite")
            {
                sound->StopEliteTheme();
            }
        }
        // 보스 처치시 엔딩
        else
        {
            battel->ChDead(Map->MapIcon[Map->floor]->getName());
            CoutinueBox->setVisible(true);
            // 스테이지 사운드 정지
            sound->StopBottomTheme();
            // 엔딩 백그라운드 사운드 실행
            sound->EndingTheme();
        }

        this->addChild(battel);

        rewardBox->setVisible(true);

        // choes_key 데이터 값 변경
        user->setIntegerForKey("choes_key", 0);
        // 맵 선택할떄 변수 증가
        Map->floor++;

        // 유물로 체력 회복
        battel->Ch_NowHp += 6;

        if (battel->Ch_NowHp > battel->Ch_MaxHp)
            battel->Ch_NowHp = battel->Ch_MaxHp;

        auto user = UserDefault::getInstance();
        user->setIntegerForKey("Ch_Hp", battel->Ch_NowHp);

        char change[100];
        sprintf(change, "%d/%d", battel->Ch_NowHp, battel->Ch_MaxHp);
        HeartFont->setString(change);
    }
    // 캐릭터 죽음
    else if (battel->Ch_NowHp <= 0)
    {
        // 기존 battel 씬 제거후 새로운 battel 씬 추가
        battel->Remove();
        this->removeChild(battel);
        this->removeChild(ChAnimation);
        this->unschedule(schedule_selector(GameScene::CheckHp));
        auto user = UserDefault::getInstance();

        battel->ChDead(Map->MapIcon[Map->floor]->getName());
        this->addChild(battel);
        CoutinueBox->setVisible(true);
        
        // 스테이지 백그라운드 사운드 정지
        if (Map->MapIcon[Map->floor]->getName() == "Monster")
        {
            sound->StopBottomTheme();
        }
        if (Map->MapIcon[Map->floor]->getName() == "Elite")
        {
            sound->StopEliteTheme();
        }


        // 캐릭터 죽음 사운드 실행
        sound->ChDead();

        // choes_key 데이터 값 변경
        user->setIntegerForKey("choes_key", 0);
    }
    // 아무도 죽지 않았으면 카드 드로우
    else
    {
        // 플레이어 턴 시작 사운드 실행
        sound->PlayerTurn();
        // 카드 드로우
        DrawCard();
        // 플레이어턴 bool변수 값 변경
        playerturn = true;
    }

    // 캐릭터 방어력 초기화
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
            // choes 값 변경
            user->setIntegerForKey("choes_key", 10);
            // 배틀 시작 사운드 실행
            sound->BattelStartMonster();
            // 플레이어턴 bool변수 값 변경
            playerturn = true;
            // 엘리트몹이라면 배경음 변경
            if (Map->MapIcon[Map->floor]->getName() == "Elite")
            {
                sound->PauseBottomTheme();
                sound->EliteTheme();
            }
        }
        else if (Map->MapIcon[Map->floor]->getName() == "Rest")
        {
            // choes 값 변경
            user->setIntegerForKey("choes_key", 11);
            // 장작 타는 소리 실행
            sound->CampFire();
            // 스테이지 백그라운드 일시정지
            sound->PauseBottomTheme();
        }
    }
    // 보스 스테이지
    else if (Map->floor == 14)
    {
        // choes 값 변경
        user->setIntegerForKey("choes_key", 10);
        // 배틀 시작 사운드 실행
        sound->BattelStartBoss();
        // 플레이어턴 bool변수 값 변경
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

        // 방패 부서지는 사운드 방어도가 있을때
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

        // 캐릭터 방어력 계속 0으로 초기화
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

        // 방패 부서지는 사운드 방어도가 있을때
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

        // 캐릭터 방어력 계속 0으로 초기화
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