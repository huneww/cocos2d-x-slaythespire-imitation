#include "StartGameMenu.h"

USING_NS_CC;

void StartGameMenu::CreateStartMenuSprite()
{
	log("StartGameMenuSprite");
    // �������� ���̾� ����
    BLayer = LayerColor::create(Color4B::BLACK);
    BLayer->setOpacity(200);
    BLayer->setName("BLayer");
    this->addChild(BLayer);

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

    // ������ ������ ����
    {
        Left = Sprite::create("slaythespire/ui/mainMenu/menuPanel2.png");
        Left->setPosition(Vec2(340, 360));
        Left->setScale(0.65f);
        //this->addChild(Left);
        PanelFrame[0] = Sprite::create("slaythespire/ui/mainMenu/MenuPanelFrame.png");
        PanelFrame[0]->setPosition(Vec2(340, 360));
        PanelFrame[0]->setScale(0.65f);
        //this->addChild(PanelFrame[0]);

        Midle = Sprite::create("slaythespire/ui/mainMenu/MenuPanel.png");
        Midle->setPosition(Vec2(640, 360));
        Midle->setScale(0.65f);
        //this->addChild(Midle);
        PanelFrame[1] = Sprite::create("slaythespire/ui/mainMenu/MenuPanelFrame.png");
        PanelFrame[1]->setPosition(Vec2(640, 360));
        PanelFrame[1]->setScale(0.65f);
        //this->addChild(PanelFrame[1]);

        Right = Sprite::create("slaythespire/ui/mainMenu/MenuPanel3.png");
        Right->setPosition(Vec2(940, 360));
        Right->setScale(0.65f);
        //this->addChild(Right);
        PanelFrame[2] = Sprite::create("slaythespire/ui/mainMenu/MenuPanelFrame.png");
        PanelFrame[2]->setPosition(Vec2(940, 360));
        PanelFrame[2]->setScale(0.65f);
        //this->addChild(PanelFrame[2]);
    }

    // ������ ��������Ʈ ����
    {
        Normal_Sprite = Sprite::create("slaythespire/ui/mainMenu/portrait/standard.jpg");
        Normal_Sprite->setPosition(Vec2(340, 452));
        Normal_Sprite->setScale(0.64f);
        //this->addChild(Normal_Sprite);

        Daily_Sprite = Sprite::create("slaythespire/ui/mainMenu/portrait/daily.jpg");
        Daily_Sprite->setPosition(Vec2(640, 452));
        Daily_Sprite->setScale(0.64f);
        //this->addChild(Daily_Sprite);
        Lock[0] = Sprite::create("slaythespire/ui/mainMenu/portrait/lock.png");
        Lock[0]->setPosition(Vec2(640, 452));
        Lock[0]->setScale(0.65f);
        //this->addChild(Lock[0]);

        Custom_Sprite = Sprite::create("slaythespire/ui/mainMenu/portrait/loop.jpg");
        Custom_Sprite->setPosition(Vec2(940, 452));
        Custom_Sprite->setScale(0.64f);
        //this->addChild(Custom_Sprite);
        Lock[1] = Sprite::create("slaythespire/ui/mainMenu/portrait/lock.png");
        Lock[1]->setPosition(Vec2(940, 452));
        Lock[1]->setScale(0.65f);
        //this->addChild(Lock[1]);
    }

    // ������ �ٿ�� �ڽ� ����
    {
        Panel_Box = LayerColor::create(Color4B::WHITE);
        Panel_Box->setOpacity(0);
        Panel_Box->setContentSize(Size(512, 800));
        Panel_Box->setScale(0.51f);
        Panel_Box->setPosition(Vec2(80, -30));
    }

    SpriteLayer = Layer::create();
    SpriteLayer->addChild(CancleButtonOutLine);
    SpriteLayer->addChild(CancleButtonShadow);
    SpriteLayer->addChild(CancleButton_Box);
    SpriteLayer->addChild(CancleButton);
    SpriteLayer->addChild(Left);
    SpriteLayer->addChild(Midle);
    SpriteLayer->addChild(Right);
    SpriteLayer->addChild(PanelFrame[0]);
    SpriteLayer->addChild(PanelFrame[1]);
    SpriteLayer->addChild(PanelFrame[2]);
    SpriteLayer->addChild(Normal_Sprite);
    SpriteLayer->addChild(Daily_Sprite);
    SpriteLayer->addChild(Custom_Sprite);
    SpriteLayer->addChild(Lock[0]);
    SpriteLayer->addChild(Lock[1]);
    SpriteLayer->addChild(Panel_Box);
    SpriteLayer->setName("StartMenuLayer");
    SpriteLayer->setPosition(Vec2::ZERO);
    this->addChild(SpriteLayer);
}

void StartGameMenu::CreateStartMenuFont()
{
    log("CreateStartMenuFont");
    TTFConfig ttfConfig("slaythespire/GyeonggiCheonnyeonBatangBold.ttf", 25);

    // ���ư��� ��Ʈ
    {
        BackFont = Label::createWithTTF(ttfConfig, "���ư���");
        BackFont->setPosition(Vec2(80, 90));
        BackFont->setTextColor(Color4B::YELLOW);
        BackFont->enableOutline(Color4B::BLACK, 2);
    }

    // �Ϲ� ��� ��Ʈ
    {
        Normal = Label::createWithTTF(ttfConfig, "�� ��");
        Normal->setPosition(Vec2(340, 550));
        Normal->setTextColor(Color4B::YELLOW);
        Normal->enableOutline(Color4B::BLACK, 2);

        Normal_Ex = Label::createWithTTF("÷ž�� ����� ���� ������ ��������.", "slaythespire/GyeonggiCheonnyeonBatangBold.ttf"
            , 20, Size(200, 300), TextHAlignment::CENTER, TextVAlignment::CENTER);
        Normal_Ex->setPosition(Vec2(340, 300));
    }

    // ���� ���� ��� ��Ʈ
    {
        Daily = Label::createWithTTF(ttfConfig, "���� ����");
        Daily->setPosition(Vec2(640, 550));
        Daily->setTextColor(Color4B::YELLOW);
        Daily->enableOutline(Color4B::BLACK, 2);

        Daily_Ex = Label::createWithTTF("�Ϸ翡 �� ��, ���ο� ������ �����˴ϴ�.", "slaythespire/GyeonggiCheonnyeonBatangBold.ttf",
            20, Size(200, 300), TextHAlignment::CENTER, TextVAlignment::CENTER);
        Daily_Ex->setPosition(Vec2(640, 300));
    }
    
    // Ŀ���� ��� ��Ʈ
    {
        Custom = Label::createWithTTF(ttfConfig, "Ŀ����");
        Custom->setPosition(Vec2(940, 550));
        Custom->setTextColor(Color4B::YELLOW);
        Custom->enableOutline(Color4B::BLACK, 2);

        Custom_Ex = Label::createWithTTF("Ư���� ��带 ����Ͽ� �ڽ��� ���ϴ� ���·� ������ �� �ֽ��ϴ�.", "slaythespire/GyeonggiCheonnyeonBatangBold.ttf",
            20, Size(200, 300), TextHAlignment::CENTER, TextVAlignment::CENTER);
        Custom_Ex->setPosition(940, 300);
    }

    
    FontLayer = Layer::create();
    FontLayer->addChild(BackFont);
    FontLayer->addChild(Normal);
    FontLayer->addChild(Normal_Ex);
    FontLayer->addChild(Daily);
    FontLayer->addChild(Daily_Ex);
    FontLayer->addChild(Custom);
    FontLayer->addChild(Custom_Ex);
    FontLayer->setPosition(Vec2::ZERO);
    FontLayer->setZOrder(5);
    FontLayer->setName("FontLayer");
    this->addChild(FontLayer);
}

void StartGameMenu::Remove()
{
    log("Disable");
    this->removeChildByName("BLayer");
    this->removeChildByName("StartMenuLayer");
    this->removeChildByName("FontLayer");
}

void StartGameMenu::CreateStartGameMenu()
{
	log("StartGameMenu");
	CreateStartMenuFont();
	CreateStartMenuSprite();
}