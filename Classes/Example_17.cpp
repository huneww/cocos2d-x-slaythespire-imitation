#include "Example_17.h"

#include "Sound.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

cocos2d::Scene* Example_17::createScene()
{
    return Example_17::create();
}

bool Example_17::init()
{
    if (!Scene::init()) return false;

    float delay = 0.1f;

    for (int i = 0; i < 4; i++)
    {
        this->scheduleOnce(schedule_selector(Example_17::Tick), delay);
        delay += 0.1f;
    }

    return true;
}

void Example_17::Tick(float dt)
{
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("slaythespire/audio/STS_SFX_EnemyAtk_Butcher_v1.mp3", false);
}
