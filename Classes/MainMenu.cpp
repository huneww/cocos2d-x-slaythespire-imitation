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

    // ���� ���� ���� ���ӽ��۽� �ʱ�ȭ ����
    auto user = UserDefault::getInstance();
    sound->background_volume = user->getFloatForKey("BackGround");
    sound->effect_volume = user->getFloatForKey("Effect");

    // ���� ���� �ʱ�ȭ�� ��׶��� ���� ���
    sound->MainTheme();

    // �ΰ�, ��� ����
    CreateBackGround();

    // ���� �޴� ����
    CreateMenu();
    
    // ��Ʈ �ٿ�� �ڽ� ����
    CreateFontBox();

    // ���� ����
    auto cloud = new CreateCloud;
    cloud->Createcloud();
    this->addChild(cloud);

    // Ŀ�� ����
    {
        cursor = Sprite::create("slaytheSpire/ui/cursors/gold2.png");
        cursor->setScale(0.8f);
        cursor->setZOrder(3);
        this->addChild(cursor);

        cursor_point = Sprite::create("slaytheSpire/ui/cursors/gold2.png", Rect(0, 0, 1, 1));
        cursor_point->setOpacity(0);
        this->addChild(cursor_point);
    }
    
    // ���콺 �̺�Ʈ ������ ����
    _Mouse_listener = EventListenerMouse::create();
    _Mouse_listener->onMouseMove = CC_CALLBACK_1(MainMenu::getMousePoint, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(_Mouse_listener, this);

    // ��ġ �̺�Ʈ ������ ����
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
        // ����� ���� Ŭ��
        if (Settingmenu->Slider[0] != nullptr &&
            cursor_point->getBoundingBox().intersectsRect(Settingmenu->Slider[0]->getBoundingBox()))
        {
            // ũ�� ����
            Settingmenu->Slider[0]->setScale(1.2f);
            // �޴� Ŭ�� ���� ����
            sound->MenuClick();
        }
        // ����Ʈ ȿ���� ���� Ŭ��
        else if (Settingmenu->Slider[1] != nullptr &&
            cursor_point->getBoundingBox().intersectsRect(Settingmenu->Slider[1]->getBoundingBox()))
        {
            // ũ�� ����
            Settingmenu->Slider[1]->setScale(1.2f);
            // �޴� Ŭ�� ���� ����
            sound->MenuClick();
        }
    }
    return true;
}

void MainMenu::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
    if (choes == 4)
    {
        // ����� ���� Ŭ��
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
        // ����Ʈ ȿ���� ���� Ŭ��
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
    // ���� �޴�
    if (choes == 0)
    {
        // ���۸޴� Ŭ��
        if (Start_Box->isVisible() == true && cursor_point->getBoundingBox().intersectsRect(Start_Box->getBoundingBox()))
        {
            log("Game Start");
            // ���� �޴� ������ ����
            ChoesMenu();

            // choes ���� �� ����
            choes = 1;

            // ���� ���� �޴� Ŭ���� ȣ��
            Startgamemenu = new StartGameMenu;
            Startgamemenu->CreateStartGameMenu();
            this->addChild(Startgamemenu);

            // Ŭ�� ���� ����
            sound->MenuClick();
        }
        // �����޴� Ŭ��
        else if (Encyc_Box->isVisible() == true && cursor_point->getBoundingBox().intersectsRect(Encyc_Box->getBoundingBox()))
        {
            log("Enecyc");
            // ���� �޴� ������ ����
            //ChoesMenu();

            // choes ���� �� ����
            //choes = 2;

            // Ŭ�� ���� ����
            sound->MenuClick();
        }
        // ���޴� Ŭ��
        else if (Stati_Box->isVisible() == true && cursor_point->getBoundingBox().intersectsRect(Stati_Box->getBoundingBox()))
        {
            log("Stati");
            // ���� �޴� ������ ����
            //ChoesMenu();

            // choes ���� �� ����
            //choes = 3;

            // Ŭ�� ���� ����
            sound->MenuClick();
        }
        // ���� �޴� Ŭ��
        else if (Setting_Box->isVisible() == true && cursor_point->getBoundingBox().intersectsRect(Setting_Box->getBoundingBox()))
        {
            log("Setting");
            // ���� �޴� ������ ����
            ChoesMenu();

            // choes ���� �� ����
            choes = 4;

            // ���� �޴� Ŭ���� ȣ��
            Settingmenu = new SettingMenu;
            Settingmenu->CreateSettingMenu();
            this->addChild(Settingmenu);

            // Ŭ�� ���� ����
            sound->MenuClick();
        }
        // ��ġ ��Ʈ �޴� Ŭ��
        else if (Patch_Box->isVisible() == true && cursor_point->getBoundingBox().intersectsRect(Patch_Box->getBoundingBox()))
        {
            log("Patch Note");
            // ���� �޴� ������ ����
            //ChoesMenu();

            // choes ���� �� ����
            //choes = 5;

            // Ŭ�� ���� ����
            sound->MenuClick();
        }
        // ���� �޴� Ŭ��
        else if (Exit_Box->isVisible() == true && cursor_point->getBoundingBox().intersectsRect(Exit_Box->getBoundingBox()))
        {
            log("End");

            // Ŭ�� ���� ����
            sound->MenuClick();

            // ���� Ŭ������ end�Լ� ȣ��
            _director->end();
        }
    }

    // ���� �޴��� ������ ��� ����â
    else if (choes == 1)
    {
        // �ڷΰ��� ��ư Ŭ��
        if (Startgamemenu->CancleButton_Box != nullptr &&
            cursor_point->getBoundingBox().intersectsRect(Startgamemenu->CancleButton_Box->getBoundingBox()))
        {
            // Ŭ�� ���� ����
            sound->MenuClick();
            // ���� �޴� ��ü ����
            Startgamemenu->Remove();
            // ���� �޴� ��ü visible true�� ����
            BackToMenu();
            choes = 0;
        }
        // �Ϲ� ��� Ŭ��, ĳ���� ����â���� �̵�
        else if (Startgamemenu->Panel_Box != nullptr &&
            cursor_point->getBoundingBox().intersectsRect(Startgamemenu->Panel_Box->getBoundingBox()))
        {
            log("Normal Game");
            // Ŭ�� ���� ����
            sound->MenuClick();
            // ���� �޴� ��ü�� ����
            Startgamemenu->Remove();
            // ĳ���� ����â Ŭ���� ȣ��
            CharcterSelector = new CharterSelector;
            CharcterSelector->CreateCharcterScene();
            this->addChild(CharcterSelector);
            choes = 11;
        }
    }

    // ���� �޴��� ������ ����
    else if (choes == 4)
    {
        // �ڷΰ��� ��ư Ŭ��
        if (Settingmenu->CancleButton_Box != nullptr &&
            cursor_point->getBoundingBox().intersectsRect(Settingmenu->CancleButton_Box->getBoundingBox()))
        {
            // ���� �޴� ��ü ����
            Settingmenu->FromSettingToMenu();
            // ���� �޴� ��ü visible true�� ����
            BackToMenu();
            choes = 0;

            // Ŭ�� ���� ����
            sound->MenuClick();
        }
        // �������� ��ư Ŭ��
        else if (Settingmenu->GameEnd_Box != nullptr &&
            cursor_point->getBoundingBox().intersectsRect(Settingmenu->GameEnd_Box->getBoundingBox()))
        {
            // ���� Ŭ������ end�Լ� ȣ��
            _director->end();

            // Ŭ�� ���� ����
            sound->MenuClick();
        }
        // ����� ���� Ŭ��
        else if (Settingmenu->Slider[0] != nullptr &&
            Settingmenu->Slider[0]->getScale() == 1.2f)
        {
            // ũ�� ����
            Settingmenu->Slider[0]->setScale(1.0f);
            // ���� ���� ���� ���� �� ����
            sound->background_volume = (Settingmenu->Slider[0]->getPositionX() - 525) / 220;
            // ����� ���� ����
            sound->SetBackGround_volume();
            // �޴� Ŭ�� ���� ����
            sound->MenuClick();
        }
        // ����Ʈ ȿ���� ���� Ŭ��
        else if (Settingmenu->Slider[1] != nullptr &&
            Settingmenu->Slider[1]->getScale() == 1.2f)
        {
            // ũ�� ����
            Settingmenu->Slider[1]->setScale(1.0f);
            // ���� ���� ���� ���� �� ����
            sound->effect_volume = (Settingmenu->Slider[1]->getPositionX() - 525) / 220;
            // ����� ���� ����
            sound->SetEffect_volume();
            // �޴� Ŭ�� ���� ����
            sound->MenuClick();
        }
    }
    // ĳ���� ����â
    else if (choes == 11)
    {
        // �ڷΰ��� ��ư Ŭ��
        if (CharcterSelector->CancleButton_Box != nullptr &&
            cursor_point->getBoundingBox().intersectsRect(CharcterSelector->CancleButton_Box->getBoundingBox()))
        {
            // Ŭ�� ���� ����
            sound->MenuClick();
            // ĳ���� ����â ��ü ����
            CharcterSelector->Remove();
            // �޴� ��ü visible ����
            BackToMenu();
            choes = 0;
        }
        // ù ��° ĳ���� Ŭ��
        else if (CharcterSelector->CharcterIcon[0] != nullptr &&
            cursor_point->getBoundingBox().intersectsRect(CharcterSelector->CharcterIcon[0]->getBoundingBox()))
        {
            // ĳ���� ���� ���� ����
            sound->ChAttack();
            // Charcter_choes �� ������ ĳ���� ��ȣ ����
            Charcter_choes = 0;
            // ĳ���Ϳ� �´� �� ��� ����, �ٸ� ����� ������ ����
            CharcterSelector->CheckBackGround(Charcter_choes);
        }
        // ���� ��ư Ŭ��
        else if (CharcterSelector->CharcterBackGround[0]->isVisible() == true && CharcterSelector->StartButton_Box != nullptr &&
            cursor_point->getBoundingBox().intersectsRect(CharcterSelector->StartButton_Box->getBoundingBox()))
        {
            log("StartGame");
            // Ŭ�� ���� ����
            sound->MenuClick();
            auto user = UserDefault::getInstance();

            if (Charcter_choes == 0)
            {
                user->setIntegerForKey("Ch_Hp", 14);
                user->setIntegerForKey("Ch_MaxHp", 80);
                user->setIntegerForKey("Gold", 214);
            }
            // ���� �޴� ��׶��� ���� ����
            this->scheduleOnce(schedule_selector(MainMenu::StopSound), 0.5f);

            auto scene = GameScene::createScene();

            // ���� ����Ʈ�� ������ ĳ���� ��ȣ ����
            user->setIntegerForKey("Charcter_choes", Charcter_choes);

            // ��� �ڽ� ��ü ����
            //this->removeAllChildrenWithCleanup(true);

            // ���̵���,�ƿ����� �����ȯ
            _director->replaceScene(TransitionFade::create(1.0f, scene));
        }
    }
}

// ���콺 ��ǥ �޾Ƽ� Ŀ�� ��������Ʈ �̵�
void MainMenu::getMousePoint(cocos2d::Event* event)
{
    _point = (EventMouse*)event;

    cursor->setPosition(Vec2(_point->getCursorX() + 27, _point->getCursorY() - 27));
    cursor_point->setPosition(Vec2(_point->getCursorX(), _point->getCursorY()));
}

// ��� ��������Ʈ ����
void MainMenu::CreateBackGround()
{
    auto visibleSize = _director->getVisibleSize();

    // ���
    BackGround = Sprite::create("slaythespire/title/title.jpg");
    BackGround->setContentSize(Size(visibleSize.width, visibleSize.height));
    BackGround->setPosition(Vec2(visibleSize) * 0.5f);
    this->addChild(BackGround);

    // Ÿ��
    Tower = Sprite::create("slaythespire/title/title2.png");
    Tower->setScale(0.8f);
    Tower->setAnchorPoint(Vec2::ZERO);
    Tower->setPosition(Vec2(0, -100));
    this->addChild(Tower);

    // ���� �ΰ�
    MainLogo = Sprite::create("slaythespire/title/MainLogo.png");
    MainLogo->setScale(0.6f);
    MainLogo->setPosition(Size(visibleSize.width * 0.5, visibleSize.height * 0.5f));
    MainLogo->setZOrder(1);
    this->addChild(MainLogo);
}

// �޴� ����
void MainMenu::CreateMenu()
{
    TTFConfig ttfConfig("slaythespire/GyeonggiCheonnyeonBatangBold.ttf", 24);

    pStartGame = Label::createWithTTF(ttfConfig, "���� ����");
    pStartGame->setPosition(Vec2(100, 250));
    pStartGame->enableGlow(Color4B::BLACK);
    pStartGame->setTag(1);
    //this->addChild(pStartGame);

    Start_Hlight = Sprite::create("slaythespire/ui/mainMenu/menu_option_highlight.png");
    Start_Hlight->setPosition(Vec2(100, 253));
    Start_Hlight->setScale(0.5f);
    Start_Hlight->setOpacity(0);

    pEncyclopedia = Label::createWithTTF(ttfConfig, "��� ����");
    pEncyclopedia->setPosition(Vec2(100, 215));
    pEncyclopedia->enableGlow(Color4B::BLACK);
    pEncyclopedia->setTag(2);
    //this->addChild(pEncyclopedia);

    Ency_Hlight = Sprite::create("slaythespire/ui/mainMenu/menu_option_highlight.png");
    Ency_Hlight->setPosition(Vec2(100, 253));
    Ency_Hlight->setScale(0.5f);
    Ency_Hlight->setOpacity(0);

    pStatistics = Label::createWithTTF(ttfConfig, "���");
    pStatistics->setPosition(Vec2(75, 180));
    pStatistics->enableGlow(Color4B::BLACK);
    pStatistics->setTag(3);
    //this->addChild(pStatistics);

    Stati_Hlight = Sprite::create("slaythespire/ui/mainMenu/menu_option_highlight.png");
    Stati_Hlight->setPosition(Vec2(100, 253));
    Stati_Hlight->setScale(0.5f);
    Stati_Hlight->setOpacity(0);

    pSetting = Label::createWithTTF(ttfConfig, "����");
    pSetting->setPosition(Vec2(75, 145));
    pSetting->enableGlow(Color4B::BLACK);
    pSetting->setTag(4);
    //this->addChild(pSetting);
  
    Setting_Hlight = Sprite::create("slaythespire/ui/mainMenu/menu_option_highlight.png");
    Setting_Hlight->setPosition(Vec2(100, 253));
    Setting_Hlight->setScale(0.5f);
    Setting_Hlight->setOpacity(0);

    pPatchNote = Label::createWithTTF(ttfConfig, "��ġ ��Ʈ");
    pPatchNote->setPosition(Vec2(100, 110));
    pPatchNote->enableGlow(Color4B::BLACK);
    pPatchNote->setTag(5);
    //this->addChild(pPatchNote);

    Patch_Hlight = Sprite::create("slaythespire/ui/mainMenu/menu_option_highlight.png");
    Patch_Hlight->setPosition(Vec2(100, 253));
    Patch_Hlight->setScale(0.5f);
    Patch_Hlight->setOpacity(0);

    pExitGame = Label::createWithTTF(ttfConfig, "���� ����");
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

// ��Ʈ �ٿ�� �ڽ� ����
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

// �޴� ���ý� ���� �޴� ��Ʈ, ��Ʈ �ٿ�� �ڽ� ȭ��󿡼� ����
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

// �ٽ� ���� �޴� ȭ������ ���ƿ͸� �޴� ��Ʈ, ��Ʈ �ٿ�� �ڽ� �ٽ� visible ����
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

// ����� ����
void MainMenu::StopSound(float dt)
{
    sound->StopMainTheme();
}