#include "CharcterSelector.h"

USING_NS_CC;

void CharterSelector::CreateCharcterScene()
{
	log("CreateCharcterScene");

    // 함수의 인수 값에 따라 객체 생성을 변경
	CreateCharcterSprite();
    CreateCharcterFont();
}

void CharterSelector::CreateCharcterSprite()
{
	log("CreateCharcterSprite");

    // 캐릭터, 아이콘 스프라이트
    Blayer = LayerColor::create(Color4B::BLACK);
    Blayer->setOpacity(200);
    Blayer->setName("Blayer");
    this->addChild(Blayer);

    // 첫 번째 캐릭터 선택
    log("First");
    CharcterBackGround[0] = Sprite::create("slaythespire/ui/charSelect/ironcladPortrait.jpg");
    CharcterBackGround[0]->setTag(0);
    CharcterBackGround[0]->setLocalZOrder(0);
    CharcterBackGround[0]->setPosition(Vec2(640, 360));
    CharcterBackGround[0]->setContentSize(Size(1280, 720));
    CharcterBackGround[0]->setVisible(false);

    auto BackGround = Layer::create();
    BackGround->addChild(CharcterBackGround[0]);
    BackGround->setPosition(Vec2::ZERO);
    BackGround->setName("BackGround");
    this->addChild(BackGround);
    
    // 뒤로가기 버튼 생성
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

            // 뒤로가기 버튼 바운딩 박스
            CancleButton_Box = LayerColor::create(Color4B::WHITE, 265, 69);
            CancleButton_Box->setAnchorPoint(Vec2::ZERO);
            CancleButton_Box->setScale(0.7f);
            CancleButton_Box->setOpacity(0);
            CancleButton_Box->setPosition(Vec2(0, 70));
            CancleButton_Box->setTag(1);
            //this->addChild(CancleButton_Box);
    }
    
    // 캐릭터 아이콘 1
    {
            CharcterIcon[0] = Sprite::create("slaythespire/ui/charSelect/ironcladButton.png");
            CharcterIcon[0]->setPosition(Vec2(400, 100));
            CharcterIcon[0]->setScale(0.7f);

            CharcterIcon_Shadow[0] = Sprite::create("slaythespire/ui/charSelect/highlightButton.png");
            CharcterIcon_Shadow[0]->setColor(Color3B::BLACK);
            CharcterIcon_Shadow[0]->setOpacity(100);
            CharcterIcon_Shadow[0]->setPosition(Vec2(400, 100));
            CharcterIcon_Shadow[0]->setScale(0.7f);

            CharcterIcon_Outline[0] = Sprite::create("slaythespire/ui/charSelect/highlightButton2.png");
            CharcterIcon_Outline[0]->setColor(Color3B::YELLOW);
            CharcterIcon_Outline[0]->setPosition(Vec2(400, 100));
            CharcterIcon_Outline[0]->setScale(0.7f);
            CharcterIcon_Outline[0]->setVisible(false);
    }
    
    // 캐릭터 아이콘 2
    {
            CharcterIcon[1] = Sprite::create("slaythespire/ui/charSelect/lockedButton.png");
            CharcterIcon[1]->setPosition(Vec2(550, 100));
            CharcterIcon[1]->setScale(0.7f);

            CharcterIcon_Shadow[1] = Sprite::create("slaythespire/ui/charSelect/highlightButton.png");
            CharcterIcon_Shadow[1]->setColor(Color3B::BLACK);
            CharcterIcon_Shadow[1]->setOpacity(100);
            CharcterIcon_Shadow[1]->setPosition(Vec2(550, 100));
            CharcterIcon_Shadow[1]->setScale(0.7f);
        }
    
    // 캐릭터 아이콘 3
    {
            CharcterIcon[2] = Sprite::create("slaythespire/ui/charSelect/lockedButton.png");
            CharcterIcon[2]->setPosition(Vec2(700, 100));
            CharcterIcon[2]->setScale(0.7f);

            CharcterIcon_Shadow[2] = Sprite::create("slaythespire/ui/charSelect/highlightButton.png");
            CharcterIcon_Shadow[2]->setColor(Color3B::BLACK);
            CharcterIcon_Shadow[2]->setOpacity(100);
            CharcterIcon_Shadow[2]->setPosition(Vec2(700, 100));
            CharcterIcon_Shadow[2]->setScale(0.7f);
        }
    
    // 캐릭터 아이콘 4
    {
            CharcterIcon[3] = Sprite::create("slaythespire/ui/charSelect/lockedButton.png");
            CharcterIcon[3]->setPosition(Vec2(850, 100));
            CharcterIcon[3]->setScale(0.7f);

            CharcterIcon_Shadow[3] = Sprite::create("slaythespire/ui/charSelect/highlightButton.png");
            CharcterIcon_Shadow[3]->setColor(Color3B::BLACK);
            CharcterIcon_Shadow[3]->setOpacity(100);
            CharcterIcon_Shadow[3]->setPosition(Vec2(850, 100));
            CharcterIcon_Shadow[3]->setScale(0.7f);
        }
    
    CharcterSprite = Layer::create();
    CharcterSprite->addChild(CancleButtonOutLine);
    CharcterSprite->addChild(CancleButtonShadow);
    CharcterSprite->addChild(CancleButton_Box);
    CharcterSprite->addChild(CancleButton);
    CharcterSprite->addChild(CharcterIcon_Outline[0]);
    CharcterSprite->addChild(CharcterIcon[0]);
    CharcterSprite->addChild(CharcterIcon_Shadow[0]);
    CharcterSprite->addChild(CharcterIcon[1]);
    CharcterSprite->addChild(CharcterIcon_Shadow[1]);
    CharcterSprite->addChild(CharcterIcon[2]);
    CharcterSprite->addChild(CharcterIcon_Shadow[2]);
    CharcterSprite->addChild(CharcterIcon[3]);
    CharcterSprite->addChild(CharcterIcon_Shadow[3]);
    CharcterSprite->setLocalZOrder(1);
    CharcterSprite->setPosition(Vec2::ZERO);
    CharcterSprite->setName("CharcterSprite");
    this->addChild(CharcterSprite);

}

void CharterSelector::CreateCharcterFont()
{
    log("CreateCharcterFont");
    TTFConfig ttfConfig("slaythespire/GyeonggiCheonnyeonBatangBold.ttf", 25);
    CharcterFont = Layer::create();
    
    // 돌아가기 폰트
    {
        BackFont = Label::createWithTTF(ttfConfig, "돌아가기");
        BackFont->setPosition(Vec2(80, 90));
        BackFont->setTextColor(Color4B::YELLOW);
        BackFont->enableOutline(Color4B::BLACK, 2);
        CharcterFont->addChild(BackFont);
    }

    // 캐릭터 선택
    SelectorCharcter = Label::createWithTTF(ttfConfig, "캐릭터를  선택하십시오");
    SelectorCharcter->setPosition(Vec2(640, 200));
    SelectorCharcter->enableOutline(Color4B::GRAY, 1);
    CharcterFont->addChild(SelectorCharcter);

    CharcterFont->setPosition(Vec2::ZERO);
    CharcterFont->setLocalZOrder(2);
    CharcterFont->setName("CharcterFont");
    this->addChild(CharcterFont);
}

void CharterSelector::CreateCharcterInfo(int charter)
{
    TTFConfig ttfConfig_1("slaythespire/GyeonggiCheonnyeonBatangBold.ttf", 50);
    TTFConfig ttfConfig_2("slaythespire/GyeonggiCheonnyeonBatangBold.ttf", 20);
    TTFConfig ttfConfig_3("slaythespire/GyeonggiCheonnyeonBatangBold.ttf", 25);

    if (CharcterIcon_Outline[charter]->isVisible() == false)
    {
        if (charter == 0)
        {
            CharcterName = Label::createWithTTF(ttfConfig_1, "아이언클래드");
            CharcterName->setPosition(Vec2(250, 500));
            CharcterName->setTextColor(Color4B(239, 200, 81, 255));

            Heart = Sprite::create("slaythespire/ui/topPanel/panelHeart.png");
            Heart->setPosition(Vec2(130, 450));

            Heart_Font = Label::createWithTTF(ttfConfig_2, "체력: 80/80");
            Heart_Font->setAnchorPoint(Vec2::ZERO);
            Heart_Font->setTextColor(Color4B(253, 100, 98, 255));
            Heart_Font->setPosition(Vec2(152, 435));

            Gold = Sprite::create("slaythespire/ui/topPanel/panelGoldBag.png");
            Gold->setPosition(Vec2(280, 445));

            Gold_Font = Label::createWithTTF(ttfConfig_2, "골드: 99");
            Gold_Font->setAnchorPoint(Vec2::ZERO);
            Gold_Font->setTextColor(Color4B(238, 199, 81, 255));
            Gold_Font->setPosition(Vec2(310, 435));

            CharcterInfo = Label::createWithTTF(ttfConfig_2, 
                "아이언클래드의 살아남은 병사입니다.\n악마의 힘을 사용하기 위해 영혼을 팔았습니다.");
            CharcterInfo->setPosition(Vec2(310, 400));

            Item = Sprite::create("slaythespire/relics/burningBlood.png");
            Item->setPosition(Vec2(130, 320));
            Item->setScale(0.8f);

            ItemInfo[0] = Label::createWithTTF(ttfConfig_2, "불타는 혈액");
            ItemInfo[0]->setPosition(Vec2(230, 330));
            ItemInfo[0]->setTextColor(Color4B(239, 200, 81, 255));

            ItemInfo[1] = Label::createWithTTF(ttfConfig_2, "전투 종료 시 체력을 6 회복합니다.");
            ItemInfo[1]->setPosition(Vec2(325, 300));
        }

        // 캐릭터를 선택하면 시작 버튼 생성
        StartButton = Sprite::create("slaythespire/ui/topPanel/confirmButton.png");
        StartButton->setScale(0.7f);
        StartButton->setPosition(Vec2(1110, 50));

        StartButtonOutline = Sprite::create("slaythespire/ui/topPanel/confirmButtonOutline.png");
        StartButtonOutline->setScale(0.7f);
        StartButtonOutline->setPosition(Vec2(1110, 50));
        StartButtonOutline->setColor(Color3B(113, 93, 44));

        auto Fadein = FadeIn::create(1.0f);
        auto Fadeout = FadeOut::create(1.0f);
        auto OutLineAction = Sequence::create(Fadeout, Fadein, nullptr);
        auto rep = RepeatForever::create(OutLineAction);
        StartButtonOutline->runAction(rep);
        CharcterIcon_Outline[charter]->runAction(rep->clone());

        StartButtonShadow = Sprite::create("slaythespire/ui/topPanel/confirmButtonShadow.png");
        StartButtonShadow->setScale(0.7f);
        StartButtonShadow->setPosition(Vec2(1110, 50));

        StartFont = Label::createWithTTF(ttfConfig_3, "출정");
        StartFont->setPosition(Vec2(1200, 90));
        StartFont->enableOutline(Color4B::BLACK, 2);
        StartFont->setTextColor(Color4B::YELLOW);

        StartButton_Box = LayerColor::create(Color4B::WHITE, 265, 69);
        StartButton_Box->setScale(0.7f);
        StartButton_Box->setPosition(Vec2(1070, 55));
        StartButton_Box->setOpacity(0);
    }

    if (CharcterIcon_Outline[charter]->isVisible() == false)
    {
        auto Infolayer = Layer::create();
        Infolayer->addChild(StartButtonShadow);
        Infolayer->addChild(StartButtonOutline);
        Infolayer->addChild(StartButton);
        Infolayer->addChild(StartButton_Box);
        Infolayer->addChild(StartFont);
        Infolayer->addChild(CharcterName);
        Infolayer->addChild(Heart);
        Infolayer->addChild(Heart_Font);
        Infolayer->addChild(Gold);
        Infolayer->addChild(Gold_Font);
        Infolayer->addChild(CharcterInfo);
        Infolayer->addChild(Item);
        Infolayer->addChild(ItemInfo[0]);
        Infolayer->addChild(ItemInfo[1]);
        Infolayer->setPosition(Vec2::ZERO);
        Infolayer->setName("Infolayer");
        this->addChild(Infolayer);
    }
}

void CharterSelector::RemoveCharcterInfo(int charter)
{
    CharcterBackGround[charter]->setVisible(false);
    this->removeChildByName("Infolayer");
}

// 백그라운드가 있는지 확인후 있으면 제거
void CharterSelector::CheckBackGround(int charter)
{
    log("CheckBackGround");

    // 캐릭터 선택하시오 폰트 제거
    SelectorCharcter->setVisible(false);

    if (charter == 0)
    {
        CharcterBackGround[charter]->setVisible(true);
        CreateCharcterInfo(charter);
        CharcterIcon_Outline[charter]->setVisible(true);
        CharcterIcon_Shadow[charter]->setVisible(false);
    }
    else
    {
        CharcterBackGround[charter]->setVisible(false);
        RemoveCharcterInfo(charter);
        CharcterIcon_Outline[charter]->setVisible(false);
        CharcterIcon_Shadow[charter]->setVisible(true);
    }
}

void CharterSelector::Remove()
{
    log("Disable");
    this->removeChildByName("Blayer");
    this->removeChildByName("CharcterSprite");
    this->removeChildByName("CharcterFont");
    this->removeChildByName("BackGround");
    this->removeChildByName("Infolayer");
}