#include "SettingMenu.h"

USING_NS_CC;

void SettingMenu::CreateSettingMenu()
{
	CreateSettingSprite();
	CreateSettingFont();
}

void SettingMenu::FromSettingToMenu()
{
    this->removeChildByName("Blayer");
    this->removeChildByName("SettingSpriteLayer");
    this->removeChildByName("FontLayer");
}

void SettingMenu::CreateSettingSprite()
{
    Blayer = LayerColor::create(Color4B::BLACK);
    Blayer->setOpacity(200);
    Blayer->setName("Blayer");
    this->addChild(Blayer);

	Size s = _director->getVisibleSize();

    BackGround = Sprite::create("slaythespire/ui/option/confirm.png");
    BackGround->setPosition(Vec2(s.width / 2, s.height / 2));

    // 뒤로가기 버튼 생성
    {
        CancleButtonShadow = Sprite::create("slaythespire/ui/topPanel/cancelButtonShadow.png");
        CancleButtonShadow->setPosition(Vec2(170, 50));
        CancleButtonShadow->setScale(0.7f);

        CancleButtonOutLine = Sprite::create("slaythespire/ui/topPanel/cancelButtonOutline.png");
        CancleButtonOutLine->setPosition(Vec2(180, 50));
        CancleButtonOutLine->setScale(0.7f);
        CancleButtonOutLine->setColor(Color3B(113, 93, 44));
        auto Fadein = FadeIn::create(1.0f);
        auto Fadeout = FadeOut::create(1.0f);
        auto OutLineAction = Sequence::create(Fadeout, Fadein, nullptr);
        auto rep = RepeatForever::create(OutLineAction);
        CancleButtonOutLine->runAction(rep);

        CancleButton = Sprite::create("slaythespire/ui/topPanel/cancelButton.png");
        CancleButton->setPosition(Vec2(180, 50));
        CancleButton->setScale(0.7f);

        // 뒤로가기 버튼 바운딩 박스
        CancleButton_Box = LayerColor::create(Color4B::WHITE, 265, 69);
        CancleButton_Box->setAnchorPoint(Vec2::ZERO);
        CancleButton_Box->setScale(0.7f);
        CancleButton_Box->setOpacity(0);
        CancleButton_Box->setPosition(Vec2(0, 70));
    }

    // 게임 종료 버튼
    {
        GameEnd = Sprite::create("slaythespire/ui/option/quitButton.png");
        GameEnd->setPosition(Vec2(760, 277));
        GameEnd->setScale(0.5f);

        GameEnd_Box = LayerColor::create(Color4B::WHITE, 265, 60);
        GameEnd_Box->setPosition(Vec2(635, 160));
        GameEnd_Box->setOpacity(0);
        GameEnd_Box->setScale(0.7f);
    }

    // 음량 조절 바
    {
        // 0% = 525
        // 100% = 755
        // 220
        // 100 / 퍼센트 * 전체

        auto user = UserDefault::getInstance();
        float background = user->getFloatForKey("BackGround");
        float effect = user->getFloatForKey("Effect");
        int back_pos = background * 220;
        int effect_pos = effect * 220;
        back_pos += 535;
        effect_pos += 535;

        // 배경음
        SliderBg[0] = Sprite::create("slaythespire/ui/option/sliderBg.png");
        SliderBg[0]->setPosition(Vec2(640, 400));
        Slider[0] = Sprite::create("slaythespire/ui/option/slider.png");
        Slider[0]->setPosition(Vec2(525, 400));
        if (background == 0)
            Slider[0]->setPosition(Vec2(525, 400));
        else
            Slider[0]->setPosition(Vec2(back_pos, 400));

        // 이펙트
        SliderBg[1] = Sprite::create("slaythespire/ui/option/sliderBg.png");
        SliderBg[1]->setPosition(Vec2(640, 300));
        Slider[1] = Sprite::create("slaythespire/ui/option/slider.png");
        if (effect == 0)
            Slider[1]->setPosition(Vec2(525, 300));
        else
            Slider[1]->setPosition(Vec2(effect_pos, 300));
    }

    SettingSpriteLayer = Layer::create();
    SettingSpriteLayer->addChild(CancleButtonOutLine);
    SettingSpriteLayer->addChild(CancleButtonShadow);
    SettingSpriteLayer->addChild(CancleButton);
    SettingSpriteLayer->addChild(CancleButton_Box);
    SettingSpriteLayer->addChild(BackGround);
    SettingSpriteLayer->addChild(GameEnd);
    SettingSpriteLayer->addChild(GameEnd_Box);
    SettingSpriteLayer->addChild(SliderBg[0]);
    SettingSpriteLayer->addChild(Slider[0]);
    SettingSpriteLayer->addChild(SliderBg[1]);
    SettingSpriteLayer->addChild(Slider[1]);
    SettingSpriteLayer->setZOrder(1);
    SettingSpriteLayer->setName("SettingSpriteLayer");
    this->addChild(SettingSpriteLayer);
}

void SettingMenu::CreateSettingFont()
{
    TTFConfig ttfConfig("slaythespire/GyeonggiCheonnyeonBatangBold.ttf", 25);

    BackFont = Label::createWithTTF(ttfConfig, "돌아가기");
    BackFont->setPosition(Vec2(80, 90));
    BackFont->setTextColor(Color4B::YELLOW);
    BackFont->enableOutline(Color4B::BLACK, 2);

    GameEndFont = Label::createWithTTF(ttfConfig, "게임 종료");
    GameEndFont->setPosition(Vec2(780, 190));
    GameEndFont->setTextColor(Color4B::YELLOW);
    GameEndFont->enableOutline(Color4B::BLACK, 2);

    // 사운드 폰트
    {
        Sound = Label::createWithTTF(ttfConfig, "음 량");
        Sound->setPosition(Vec2(640, 500));
        Sound->setTextColor(Color4B::YELLOW);
        Sound->enableOutline(Color4B::BLACK, 2);

        Background_Sound = Label::createWithTTF(ttfConfig, "배경음");
        Background_Sound->setPosition(Vec2(580, 440));
        Background_Sound->setTextColor(Color4B::YELLOW);
        Background_Sound->enableOutline(Color4B::BLACK, 2);

        Effect_Sound = Label::createWithTTF(ttfConfig, "효과음");
        Effect_Sound->setPosition(Vec2(580, 340));
        Effect_Sound->setTextColor(Color4B::YELLOW);
        Effect_Sound->enableOutline(Color4B::BLACK, 2);
    }

    SettingFontLayer = Layer::create();
    SettingFontLayer->addChild(BackFont);
    SettingFontLayer->addChild(GameEndFont);
    SettingFontLayer->addChild(Sound);
    SettingFontLayer->addChild(Background_Sound);
    SettingFontLayer->addChild(Effect_Sound);
    SettingFontLayer->setPosition(Vec2::ZERO);
    SettingFontLayer->setZOrder(5);
    SettingFontLayer->setName("FontLayer");
    this->addChild(SettingFontLayer);
}
