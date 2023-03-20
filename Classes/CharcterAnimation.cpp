#include "CharcterAnimation.h"

USING_NS_CC;

void CharacterAnimation::CharacterIdelAnimation(int _Character_choes)
{
    // 각 캐릭터별 아이들 상태 애니메이션
    Character_Box = LayerColor::create(Color4B::MAGENTA);
    Character_Box->setContentSize(Size(260, 240));
    Character_Box->setPosition(Vec2(170, 200));
    Character_Box->setOpacity(0);
    this->addChild(Character_Box);

    if (_Character_choes == 0)
    {
        auto cache = SpriteFrameCache::getInstance();
        cache->addSpriteFramesWithFile("slaythespire/characters/ironclad/idle/Idle.plist");

        Vector<SpriteFrame*> animFrames;

        for (int i = 0; i < 55; i++)
        {
            std::string _frames = StringUtils::format("skeleton_I_120_0%02d.png", i);
            SpriteFrame* frame = cache->getSpriteFrameByName(_frames);
            animFrames.pushBack(frame);
        }

        Character_Idle = Sprite::createWithSpriteFrameName("skeleton_I_120_000.png");
        Character_Idle->setPosition(Vec2(300, 340));
        Character_Idle->setScale(0.75f);
        this->addChild(Character_Idle);

        auto animation = Animation::createWithSpriteFrames(animFrames, 0.075f);
        auto animate = Animate::create(animation);
        auto rep = RepeatForever::create(animate);

        Character_Idle->runAction(rep);
    }
}

void CharacterAnimation::CharacterHitAnimation(int _Character_choes)
{
    // 각 캐릭터별 히트 애니메이션
    if (_Character_choes == 0)
    {
        auto Character_Hit = Sprite::create("slaythespire/characters/ironclad/Hit/skeleton_H_60_000.png");
        Character_Hit->setPosition(Vec2(640, 360));
        Character_Hit->setScale(0.75f);
        this->addChild(Character_Hit);

        auto animation = Animation::create();
        animation->setDelayPerUnit(0.1f);
        animation->addSpriteFrameWithFile("slaythespire/characters/ironclad/Hit/skeleton_H_60_001.png");
        animation->addSpriteFrameWithFile("slaythespire/characters/ironclad/Hit/skeleton_H_60_002.png");
        animation->addSpriteFrameWithFile("slaythespire/characters/ironclad/Hit/skeleton_H_60_003.png");
        animation->addSpriteFrameWithFile("slaythespire/characters/ironclad/Hit/skeleton_H_60_004.png");
        animation->addSpriteFrameWithFile("slaythespire/characters/ironclad/Hit/skeleton_H_60_005.png");

        auto animate = Animate::create(animation);
        auto rep = RepeatForever::create(animate);
        Character_Hit->runAction(rep);
    }
}

void CharacterAnimation::Remove()
{
    this->removeAllChildren();
}
