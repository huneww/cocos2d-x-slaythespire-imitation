#include "MainMenu.h"

USING_NS_CC;
using namespace experimental;
const std::string MainTheme = "slaythespire/audio/music/STS_MenuTheme_NewMix_v1.ogg";
const std::string MENUCLICK = "slaythespire/audio/music/SOTE_SFX_UIClick_2_v2.wav";

cocos2d::Scene* MainMenu::createScene()
{
    return MainMenu::create();
}

bool MainMenu::init()
{
    srand(time(NULL));
    if (!Scene::init()) return false;

    choes = 0;
    Charcter_choes = 5;

    sound = new Sound;

    // 사운드 조절 변수 게임시작시 초기화 실행
    auto user = UserDefault::getInstance();
    sound->background_volume = user->getFloatForKey("BackGround");
    sound->effect_volume = user->getFloatForKey("Effect");

    // 사운드 변수 초기화후 백그라운드 사운드 재생
    sound->MainTheme();

    // 로고, 배경 생성
    CreateBackGround();

    // 게임 메뉴 생성
    CreateMenu();
    
    // 폰트 바운딩 박스 생성
    CreateFontBox();

    // 구름 생성
    auto cloud = new CreateCloud;
    cloud->Createcloud();
    this->addChild(cloud);

    // 커서 생성
    {
        cursor = Sprite::create("slaytheSpire/ui/cursors/gold2.png");
        cursor->setScale(0.8f);
        cursor->setZOrder(3);
        this->addChild(cursor);

        cursor_point = Sprite::create("slaytheSpire/ui/cursors/gold2.png", Rect(0, 0, 1, 1));
        cursor_point->setOpacity(0);
        this->addChild(cursor_point);
    }
    
    // 마우스 이벤트 리스너 생성
    _Mouse_listener = EventListenerMouse::create();
    _Mouse_listener->onMouseMove = CC_CALLBACK_1(MainMenu::getMousePoint, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(_Mouse_listener, this);

    // 터치 이벤트 리스너 생성
    _Touch_listener = EventListenerTouchOneByOne::create();
    _Touch_listener->setSwallowTouches(true);
    _Touch_listener->onTouchBegan = CC_CALLBACK_2(MainMenu::onTouchBegan, this);
    _Touch_listener->onTouchMoved = CC_CALLBACK_2(MainMenu::onTouchMoved, this);
    _Touch_listener->onTouchEnded = CC_CALLBACK_2(MainMenu::onTouchEnded, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(_Touch_listener, this);

    return true;
}

bool MainMenu::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
    if (choes == 4)
    {
        // 배경음 조절 클릭
        if (Settingmenu->Slider[0] != nullptr &&
            cursor_point->getBoundingBox().intersectsRect(Settingmenu->Slider[0]->getBoundingBox()))
        {
            // 크기 조절
            Settingmenu->Slider[0]->setScale(1.2f);
            // 메뉴 클릭 사운드 실행
            sound->MenuClick();
        }
        // 이펙트 효과음 조절 클릭
        else if (Settingmenu->Slider[1] != nullptr &&
            cursor_point->getBoundingBox().intersectsRect(Settingmenu->Slider[1]->getBoundingBox()))
        {
            // 크기 조절
            Settingmenu->Slider[1]->setScale(1.2f);
            // 메뉴 클릭 사운드 실행
            sound->MenuClick();
        }
    }
    return true;
}

void MainMenu::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
    if (choes == 4)
    {
        // 배경음 조절 클릭
        if (Settingmenu->Slider[0] != nullptr &&
            cursor_point->getBoundingBox().intersectsRect(Settingmenu->Slider[0]->getBoundingBox()))
        {
                Settingmenu->Slider[0]->setPosition(Vec2(Settingmenu->Slider[0]->getPositionX() + touch->getDelta().x,
                    Settingmenu->Slider[0]->getPositionY()));

                if (Settingmenu->Slider[0]->getPositionX() < 525)
                    Settingmenu->Slider[0]->setPosition(Vec2(525, Settingmenu->Slider[0]->getPositionY()));
                else if (Settingmenu->Slider[0]->getPositionX() > 755)
                    Settingmenu->Slider[0]->setPosition(Vec2(755, Settingmenu->Slider[0]->getPositionY()));
        }
        // 이펙트 효과음 조절 클릭
        else if (Settingmenu->Slider[1] != nullptr &&
            cursor_point->getBoundingBox().intersectsRect(Settingmenu->Slider[1]->getBoundingBox()))
        {
            Settingmenu->Slider[1]->setPosition(Vec2(Settingmenu->Slider[1]->getPositionX() + touch->getDelta().x,
                Settingmenu->Slider[1]->getPositionY()));

            if (Settingmenu->Slider[1]->getPositionX() < 525)
                Settingmenu->Slider[1]->setPosition(Vec2(525, Settingmenu->Slider[1]->getPositionY()));
            else if (Settingmenu->Slider[1]->getPositionX() > 755)
                Settingmenu->Slider[1]->setPosition(Vec2(755, Settingmenu->Slider[1]->getPositionY()));

        }
    }

}

void MainMenu::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
    // 메인 메뉴
    if (choes == 0)
    {
        // 시작메뉴 클릭
        if (Start_Box->isVisible() == true && cursor_point->getBoundingBox().intersectsRect(Start_Box->getBoundingBox()))
        {
            log("Game Start");
            // 메인 메뉴 선택지 제거
            ChoesMenu();

            // choes 변수 값 변경
            choes = 1;

            // 게임 시작 메뉴 클래스 호출
            Startgamemenu = new StartGameMenu;
            Startgamemenu->CreateStartGameMenu();
            this->addChild(Startgamemenu);

            // 클릭 사운드 실행
            sound->MenuClick();
        }
        // 사전메뉴 클릭
        else if (Encyc_Box->isVisible() == true && cursor_point->getBoundingBox().intersectsRect(Encyc_Box->getBoundingBox()))
        {
            log("Enecyc");
            // 메인 메뉴 선택지 제거
            //ChoesMenu();

            // choes 변수 값 변경
            //choes = 2;

            // 클릭 사운드 실행
            sound->MenuClick();
        }
        // 통계메뉴 클릭
        else if (Stati_Box->isVisible() == true && cursor_point->getBoundingBox().intersectsRect(Stati_Box->getBoundingBox()))
        {
            log("Stati");
            // 메인 메뉴 선택지 제거
            //ChoesMenu();

            // choes 변수 값 변경
            //choes = 3;

            // 클릭 사운드 실행
            sound->MenuClick();
        }
        // 세팅 메뉴 클릭
        else if (Setting_Box->isVisible() == true && cursor_point->getBoundingBox().intersectsRect(Setting_Box->getBoundingBox()))
        {
            log("Setting");
            // 메인 메뉴 선택지 제거
            ChoesMenu();

            // choes 변수 값 변경
            choes = 4;

            // 세팅 메뉴 클래스 호출
            Settingmenu = new SettingMenu;
            Settingmenu->CreateSettingMenu();
            this->addChild(Settingmenu);

            // 클릭 사운드 실행
            sound->MenuClick();
        }
        // 패치 노트 메뉴 클릭
        else if (Patch_Box->isVisible() == true && cursor_point->getBoundingBox().intersectsRect(Patch_Box->getBoundingBox()))
        {
            log("Patch Note");
            // 메인 메뉴 선택지 제거
            //ChoesMenu();

            // choes 변수 값 변경
            //choes = 5;

            // 클릭 사운드 실행
            sound->MenuClick();
        }
        // 종료 메뉴 클릭
        else if (Exit_Box->isVisible() == true && cursor_point->getBoundingBox().intersectsRect(Exit_Box->getBoundingBox()))
        {
            log("End");

            // 클릭 사운드 실행
            sound->MenuClick();

            // 디렉터 클래스의 end함수 호출
            _director->end();
        }
    }

    // 시작 메뉴를 누르고 모드 선택창
    else if (choes == 1)
    {
        // 뒤로가기 버튼 클릭
        if (Startgamemenu->CancleButton_Box != nullptr &&
            cursor_point->getBoundingBox().intersectsRect(Startgamemenu->CancleButton_Box->getBoundingBox()))
        {
            // 클릭 사운드 실행
            sound->MenuClick();
            // 시작 메뉴 객체 제거
            Startgamemenu->Remove();
            // 메인 메뉴 객체 visible true로 변경
            BackToMenu();
            choes = 0;
        }
        // 일반 모드 클릭, 캐릭터 선택창으로 이동
        else if (Startgamemenu->Panel_Box != nullptr &&
            cursor_point->getBoundingBox().intersectsRect(Startgamemenu->Panel_Box->getBoundingBox()))
        {
            log("Normal Game");
            // 클릭 사운드 실행
            sound->MenuClick();
            // 시작 메뉴 객체들 제거
            Startgamemenu->Remove();
            // 캐릭터 선택창 클래스 호출
            CharcterSelector = new CharterSelector;
            CharcterSelector->CreateCharcterScene();
            this->addChild(CharcterSelector);
            choes = 11;
        }
    }

    // 세팅 메뉴를 누르고 난후
    else if (choes == 4)
    {
        // 뒤로가기 버튼 클릭
        if (Settingmenu->CancleButton_Box != nullptr &&
            cursor_point->getBoundingBox().intersectsRect(Settingmenu->CancleButton_Box->getBoundingBox()))
        {
            // 세팅 메뉴 객체 제거
            Settingmenu->FromSettingToMenu();
            // 메인 메뉴 객체 visible true로 변경
            BackToMenu();
            choes = 0;

            // 클릭 사운드 실행
            sound->MenuClick();
        }
        // 게임종료 버튼 클릭
        else if (Settingmenu->GameEnd_Box != nullptr &&
            cursor_point->getBoundingBox().intersectsRect(Settingmenu->GameEnd_Box->getBoundingBox()))
        {
            // 디렉터 클래스의 end함수 호출
            _director->end();

            // 클릭 사운드 실행
            sound->MenuClick();
        }
        // 배경음 조절 클릭
        else if (Settingmenu->Slider[0] != nullptr &&
            Settingmenu->Slider[0]->getScale() == 1.2f)
        {
            // 크기 조절
            Settingmenu->Slider[0]->setScale(1.0f);
            // 사운드 볼륨 조절 변수 값 변경
            sound->background_volume = (Settingmenu->Slider[0]->getPositionX() - 525) / 220;
            // 변경된 사운드 적용
            sound->SetBackGround_volume();
            // 메뉴 클릭 사운드 실행
            sound->MenuClick();
        }
        // 이펙트 효과음 조절 클릭
        else if (Settingmenu->Slider[1] != nullptr &&
            Settingmenu->Slider[1]->getScale() == 1.2f)
        {
            // 크기 조절
            Settingmenu->Slider[1]->setScale(1.0f);
            // 사운드 볼륨 조절 변수 값 변경
            sound->effect_volume = (Settingmenu->Slider[1]->getPositionX() - 525) / 220;
            // 변경된 사운드 적용
            sound->SetEffect_volume();
            // 메뉴 클릭 사운드 실행
            sound->MenuClick();
        }
    }
    // 캐릭터 선택창
    else if (choes == 11)
    {
        // 뒤로가기 버튼 클릭
        if (CharcterSelector->CancleButton_Box != nullptr &&
            cursor_point->getBoundingBox().intersectsRect(CharcterSelector->CancleButton_Box->getBoundingBox()))
        {
            // 클릭 사운드 실행
            sound->MenuClick();
            // 캐릭터 선택창 객체 제거
            CharcterSelector->Remove();
            // 메뉴 객체 visible 변경
            BackToMenu();
            choes = 0;
        }
        // 첫 번째 캐릭터 클릭
        else if (CharcterSelector->CharcterIcon[0] != nullptr &&
            cursor_point->getBoundingBox().intersectsRect(CharcterSelector->CharcterIcon[0]->getBoundingBox()))
        {
            // 캐릭터 선택 사운드 실행
            sound->ChAttack();
            // Charcter_choes 에 선택한 캐릭터 번호 저장
            Charcter_choes = 0;
            // 캐릭터에 맞는 뒷 배경 생성, 다른 배경이 있으면 제거
            CharcterSelector->CheckBackGround(Charcter_choes);
        }
        // 시작 버튼 클릭
        else if (CharcterSelector->CharcterBackGround[0]->isVisible() == true && CharcterSelector->StartButton_Box != nullptr &&
            cursor_point->getBoundingBox().intersectsRect(CharcterSelector->StartButton_Box->getBoundingBox()))
        {
            log("StartGame");
            // 클릭 사운드 실행
            sound->MenuClick();
            auto user = UserDefault::getInstance();

            if (Charcter_choes == 0)
            {
                user->setIntegerForKey("Ch_Hp", 14);
                user->setIntegerForKey("Ch_MaxHp", 80);
                user->setIntegerForKey("Gold", 214);
            }
            // 메인 메뉴 백그라운드 사운드 정지
            this->scheduleOnce(schedule_selector(MainMenu::StopSound), 0.5f);

            auto scene = GameScene::createScene();

            // 유저 디폴트에 선택한 캐릭터 번호 저장
            user->setIntegerForKey("Charcter_choes", Charcter_choes);

            // 모든 자식 객체 제거
            //this->removeAllChildrenWithCleanup(true);

            // 페이드인,아웃으로 장면전환
            _director->replaceScene(TransitionFade::create(1.0f, scene));
        }
    }
}

// 마우스 좌표 받아서 커서 스프라이트 이동
void MainMenu::getMousePoint(cocos2d::Event* event)
{
    _point = (EventMouse*)event;

    cursor->setPosition(Vec2(_point->getCursorX() + 27, _point->getCursorY() - 27));
    cursor_point->setPosition(Vec2(_point->getCursorX(), _point->getCursorY()));
}

// 배경 스프라이트 생성
void MainMenu::CreateBackGround()
{
    auto visibleSize = _director->getVisibleSize();

    // 배경
    BackGround = Sprite::create("slaythespire/title/title.jpg");
    BackGround->setContentSize(Size(visibleSize.width, visibleSize.height));
    BackGround->setPosition(Vec2(visibleSize) * 0.5f);
    this->addChild(BackGround);

    // 타워
    Tower = Sprite::create("slaythespire/title/title2.png");
    Tower->setScale(0.8f);
    Tower->setAnchorPoint(Vec2::ZERO);
    Tower->setPosition(Vec2(0, -100));
    this->addChild(Tower);

    // 메인 로고
    MainLogo = Sprite::create("slaythespire/title/MainLogo.png");
    MainLogo->setScale(0.6f);
    MainLogo->setPosition(Size(visibleSize.width * 0.5, visibleSize.height * 0.5f));
    MainLogo->setZOrder(1);
    this->addChild(MainLogo);
}

// 메뉴 생성
void MainMenu::CreateMenu()
{
    TTFConfig ttfConfig("slaythespire/GyeonggiCheonnyeonBatangBold.ttf", 24);

    pStartGame = Label::createWithTTF(ttfConfig, "게임 시작");
    pStartGame->setPosition(Vec2(100, 250));
    pStartGame->enableGlow(Color4B::BLACK);
    pStartGame->setTag(1);
    //this->addChild(pStartGame);

    Start_Hlight = Sprite::create("slaythespire/ui/mainMenu/menu_option_highlight.png");
    Start_Hlight->setPosition(Vec2(100, 253));
    Start_Hlight->setScale(0.5f);
    Start_Hlight->setOpacity(0);

    pEncyclopedia = Label::createWithTTF(ttfConfig, "백과 사전");
    pEncyclopedia->setPosition(Vec2(100, 215));
    pEncyclopedia->enableGlow(Color4B::BLACK);
    pEncyclopedia->setTag(2);
    //this->addChild(pEncyclopedia);

    Ency_Hlight = Sprite::create("slaythespire/ui/mainMenu/menu_option_highlight.png");
    Ency_Hlight->setPosition(Vec2(100, 253));
    Ency_Hlight->setScale(0.5f);
    Ency_Hlight->setOpacity(0);

    pStatistics = Label::createWithTTF(ttfConfig, "통계");
    pStatistics->setPosition(Vec2(75, 180));
    pStatistics->enableGlow(Color4B::BLACK);
    pStatistics->setTag(3);
    //this->addChild(pStatistics);

    Stati_Hlight = Sprite::create("slaythespire/ui/mainMenu/menu_option_highlight.png");
    Stati_Hlight->setPosition(Vec2(100, 253));
    Stati_Hlight->setScale(0.5f);
    Stati_Hlight->setOpacity(0);

    pSetting = Label::createWithTTF(ttfConfig, "설정");
    pSetting->setPosition(Vec2(75, 145));
    pSetting->enableGlow(Color4B::BLACK);
    pSetting->setTag(4);
    //this->addChild(pSetting);
  
    Setting_Hlight = Sprite::create("slaythespire/ui/mainMenu/menu_option_highlight.png");
    Setting_Hlight->setPosition(Vec2(100, 253));
    Setting_Hlight->setScale(0.5f);
    Setting_Hlight->setOpacity(0);

    pPatchNote = Label::createWithTTF(ttfConfig, "패치 노트");
    pPatchNote->setPosition(Vec2(100, 110));
    pPatchNote->enableGlow(Color4B::BLACK);
    pPatchNote->setTag(5);
    //this->addChild(pPatchNote);

    Patch_Hlight = Sprite::create("slaythespire/ui/mainMenu/menu_option_highlight.png");
    Patch_Hlight->setPosition(Vec2(100, 253));
    Patch_Hlight->setScale(0.5f);
    Patch_Hlight->setOpacity(0);

    pExitGame = Label::createWithTTF(ttfConfig, "게임 종료");
    pExitGame->setPosition(Vec2(100, 75));
    pExitGame->enableGlow(Color4B::BLACK);
    pExitGame->setTag(6);
    //this->addChild(pExitGame);

    Exit_Hllight = Sprite::create("slaythespire/ui/mainMenu/menu_option_highlight.png");
    Exit_Hllight->setPosition(Vec2(100, 253));
    Exit_Hllight->setScale(0.5f);
    Exit_Hllight->setOpacity(0);

    Font_Layer = Layer::create();
    Font_Layer->addChild(Start_Hlight);
    Font_Layer->addChild(Ency_Hlight);
    Font_Layer->addChild(Stati_Hlight);
    Font_Layer->addChild(Patch_Hlight);
    Font_Layer->addChild(Setting_Hlight);
    Font_Layer->addChild(Exit_Hllight);
    Font_Layer->addChild(pStartGame);
    Font_Layer->addChild(pEncyclopedia);
    Font_Layer->addChild(pStatistics);
    Font_Layer->addChild(pSetting);
    Font_Layer->addChild(pPatchNote);
    Font_Layer->addChild(pExitGame);
    Font_Layer->setLocalZOrder(1);
    this->addChild(Font_Layer);
}

// 폰트 바운딩 박스 생성
void MainMenu::CreateFontBox()
{
    Size s = pStartGame->getContentSize();

    Start_Box = LayerColor::create(Color4B::WHITE);
    Start_Box->setContentSize(Size(s.width + 30, s.height));
    Start_Box->setPosition(Vec2(53, 240));
    Start_Box->setOpacity(0);
    //this->addChild(Start_Box);

    Encyc_Box = LayerColor::create(Color4B::WHITE);
    Encyc_Box->setContentSize(Size(s.width + 30, s.height));
    Encyc_Box->setPosition(Vec2(53, 205));
    Encyc_Box->setOpacity(0);
    //this->addChild(Encyc_Box);

    Stati_Box = LayerColor::create(Color4B::WHITE);
    Stati_Box->setContentSize(Size(s.width + 30, s.height));
    Stati_Box->setPosition(Vec2(53, 170));
    Stati_Box->setOpacity(0);
    //this->addChild(Stati_Box);

    Setting_Box = LayerColor::create(Color4B::WHITE);
    Setting_Box->setContentSize(Size(s.width + 30, s.height));
    Setting_Box->setPosition(Vec2(53, 135));
    Setting_Box->setOpacity(0);
    //this->addChild(Setting_Box);

    Patch_Box = LayerColor::create(Color4B::WHITE);
    Patch_Box->setContentSize(Size(s.width + 30, s.height));
    Patch_Box->setPosition(Vec2(53, 100));
    Patch_Box->setOpacity(0);
    //this->addChild(Patch_Box);

    Exit_Box = LayerColor::create(Color4B::WHITE);
    Exit_Box->setContentSize(Size(s.width + 30, s.height));
    Exit_Box->setPosition(Vec2(53, 65));
    Exit_Box->setOpacity(0);
    //this->addChild(Exit_Box);

    Font_Box_Layer = Layer::create();
    Font_Box_Layer->addChild(Start_Box);
    Font_Box_Layer->addChild(Encyc_Box);
    Font_Box_Layer->addChild(Stati_Box);
    Font_Box_Layer->addChild(Setting_Box);
    Font_Box_Layer->addChild(Patch_Box);
    Font_Box_Layer->addChild(Exit_Box);
    Font_Box_Layer->setLocalZOrder(1);
    this->addChild(Font_Box_Layer);

}

// 메뉴 선택시 메인 메뉴 폰트, 폰트 바운딩 박스 화면상에서 제거
void MainMenu::ChoesMenu()
{
    Font_Layer->setVisible(false);

    Start_Box->setVisible(false);
    Encyc_Box->setVisible(false);
    Stati_Box->setVisible(false);
    Setting_Box->setVisible(false);
    Patch_Box->setVisible(false);
    Exit_Box->setVisible(false);

    MainLogo->setLocalZOrder(0);
}

// 다시 메인 메뉴 화면으로 돌아와면 메뉴 폰트, 폰트 바운딩 박스 다시 visible 변경
void MainMenu::BackToMenu()
{
    Font_Layer->setVisible(true);

    Start_Box->setVisible(true);
    Encyc_Box->setVisible(true);
    Stati_Box->setVisible(true);
    Setting_Box->setVisible(true);
    Patch_Box->setVisible(true);
    Exit_Box->setVisible(true);
}

// 배경음 정지
void MainMenu::StopSound(float dt)
{
    sound->StopMainTheme();
}