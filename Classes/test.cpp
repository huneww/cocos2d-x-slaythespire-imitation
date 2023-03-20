#include "test.h"

USING_NS_CC;

cocos2d::Scene* test::createScene()
{
    return test::create();
}

bool test::init()
{
    if (!Scene::init()) return false;

    MenuItemFont::setFontName("Marker Felt.ttf");
    MenuItemFont::setFontSize(40);

    auto menu1 = MenuItemFont::create("RemoveChlid", CC_CALLBACK_1(test::callback_1, this));

    auto menu2 = MenuItemFont::create("RemoveChildByName", CC_CALLBACK_1(test::callback_2, this));

    auto menu3 = MenuItemFont::create("RemoveChildByTag", CC_CALLBACK_1(test::callback_3, this));

    auto pMenu = Menu::create(menu1, menu2, menu3, nullptr);
    pMenu->alignItemsVertically();
    pMenu->setPosition(Vec2(220, 360));
    this->addChild(pMenu);

    sprite1 = Sprite::create("Emoticons/ClanChat_Emoji_01_kr.png");
    sprite1->setPosition(Vec2(740, 700));
    this->addChild(sprite1);

    sprite2 = Sprite::create("Emoticons/ClanChat_Emoji_02_kr.png");
    sprite2->setPosition(Vec2(740, 360));
    sprite2->setName("sprite2");
    this->addChild(sprite2);

    sprite3 = Sprite::create("Emoticons/ClanChat_Emoji_03_kr.png");
    sprite3->setPosition(Vec2(740, 30));
    sprite3->setTag(3);
    this->addChild(sprite3);

    count = 0;

    this->schedule(schedule_selector(test::tick), 2.5f);
    this->schedule(schedule_selector(test::tick2), 3.0f);


    return true;
}

void test::callback_1(Ref* pSender)
{
    this->removeChild(sprite1);
}

void test::callback_2(Ref* pSender)
{
    this->removeChildByName("sprite2");
}

void test::callback_3(Ref* pSender)
{
    this->removeChildByTag(3);
}

void test::tick(float dt)
{
    log("tick");
    if (count == 2)
        this->removeChild(sprite1);
}

void test::tick2(float dt)
{
    log("tick2");
    log("count : %d", count);
    count++;
}