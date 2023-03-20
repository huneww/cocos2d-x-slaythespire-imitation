#include "CreateCloud.h"

USING_NS_CC;

void CreateCloud::Createcloud()
{
    log("Cloud");
    CloudAnimation_1(0.0f);
    CloudAnimation_2(0.0f);
}

void CreateCloud::CloudAnimation_1(float dt)
{
    this->schedule(schedule_selector(CreateCloud::CloudAnimation_1, this), 5.0f);

    auto Cloud_1 = Sprite::create("slaythespire/title/cloud/cloud_1.png");
    Cloud_1->setPosition(Vec2(random(-50, 0), random(0, 400)));
    Cloud_1->setScale(0.6f);
    Cloud_1->setAnchorPoint(Vec2(1.0f, 0.0f));
    auto move_1 = MoveBy::create(30.0f, Vec2(3000, 0));
    auto sequence_1 = Sequence::create(move_1, RemoveSelf::create(), nullptr);
    Cloud_1->runAction(sequence_1);
    this->addChild(Cloud_1);

    auto Cloud_2 = Sprite::create("slaythespire/title/cloud/cloud_2.png");
    Cloud_2->setPosition(Vec2(random(-50, 0), random(0, 400)));
    Cloud_2->setAnchorPoint(Vec2(1.0f, 0.0f));
    auto move_2 = MoveBy::create(30.0f, Vec2(3000, 0));
    auto sequence_2 = Sequence::create(move_2, RemoveSelf::create(), nullptr);
    Cloud_2->runAction(sequence_2);
    this->addChild(Cloud_2);

    auto Cloud_3 = Sprite::create("slaythespire/title/cloud/cloud_3.png");
    Cloud_3->setPosition(Vec2(random(-50, 0), random(0, 400)));
    Cloud_3->setScale(0.7f);
    Cloud_3->setAnchorPoint(Vec2(1.0f, 0.0f));
    auto move_3 = MoveBy::create(30.0f, Vec2(3000, 0));
    auto sequence_3 = Sequence::create(move_3, RemoveSelf::create(), nullptr);
    Cloud_3->runAction(sequence_3);
    this->addChild(Cloud_3);
}

void CreateCloud::CloudAnimation_2(float dt)
{
    this->schedule(schedule_selector(CreateCloud::CloudAnimation_2, this), 5.0f);

    auto Cloud_4 = Sprite::create("slaythespire/title/cloud/cloud_10.png");
    Cloud_4->setPosition(Vec2(random(1280, 1350), random(100, 500)));
    Cloud_4->setAnchorPoint(Vec2(0.0, 1.0f));
    auto move_4 = MoveBy::create(30.0f, Vec2(-3000, 0));
    auto sequence_4 = Sequence::create(move_4, RemoveSelf::create(), nullptr);
    Cloud_4->runAction(sequence_4);
    this->addChild(Cloud_4);

    auto Cloud_5 = Sprite::create("slaythespire/title/cloud/cloud_5.png");
    Cloud_5->setPosition(Vec2(random(1280, 1350), random(100, 500)));
    Cloud_5->setAnchorPoint(Vec2(0.0f, 1.0f));
    auto move_5 = MoveBy::create(30.0f, Vec2(-3000, 0));
    auto sequence_5 = Sequence::create(move_5, RemoveSelf::create(), nullptr);
    Cloud_5->runAction(sequence_5);
    this->addChild(Cloud_5);

    auto Cloud_6 = Sprite::create("slaythespire/title/cloud/cloud_6.png");
    Cloud_6->setPosition(Vec2(random(1280, 1350), random(100, 500)));
    Cloud_6->setAnchorPoint(Vec2(0.0f, 1.0f));
    auto move_6 = MoveBy::create(30.0f, Vec2(-3000, 0));
    auto sequence_6 = Sequence::create(move_6, RemoveSelf::create(), nullptr);
    Cloud_6->runAction(sequence_6);
    this->addChild(Cloud_6);

    auto Cloud_7 = Sprite::create("slaythespire/title/cloud/cloud_7.png");
    Cloud_7->setPosition(Vec2(random(1280, 1350), random(100, 500)));
    Cloud_7->setAnchorPoint(Vec2(0.0f, 1.0f));
    auto move_7 = MoveBy::create(30.0f, Vec2(-3000, 0));
    auto sequence_7 = Sequence::create(move_7, RemoveSelf::create(), nullptr);
    Cloud_7->runAction(sequence_7);
    this->addChild(Cloud_7);

    auto Cloud_8 = Sprite::create("slaythespire/title/cloud/cloud_8.png");
    Cloud_8->setAnchorPoint(Vec2(0.0f, 1.0f));
    Cloud_8->setPosition(Vec2(random(1280, 1350), random(100, 500)));
    auto move_8 = MoveBy::create(30.0f, Vec2(-3000, 0));
    auto sequence_8 = Sequence::create(move_8, RemoveSelf::create(), nullptr);
    Cloud_8->runAction(sequence_8);
    this->addChild(Cloud_8);

    auto Cloud_9 = Sprite::create("slaythespire/title/cloud/cloud_9.png");
    Cloud_9->setScale(0.3f);
    Cloud_9->setPosition(Vec2(random(1280, 1350), random(100, 500)));
    Cloud_9->setAnchorPoint(Vec2(0.0f, 1.0f));
    auto move_9 = MoveBy::create(30.0f, Vec2(-3000, 0));
    auto sequence_9 = Sequence::create(move_9, RemoveSelf::create(), nullptr);
    Cloud_9->runAction(sequence_9);
    this->addChild(Cloud_9);
}

void CreateCloud::RemoveCloud()
{
    this->unschedule(schedule_selector(CreateCloud::CloudAnimation_1));
    this->unschedule(schedule_selector(CreateCloud::CloudAnimation_2));
}
