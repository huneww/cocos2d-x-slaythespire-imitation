#pragma once
#include "cocos2d.h"
#include "Sound.h"

class test : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	CREATE_FUNC(test);

	void callback_1(Ref* pSender);
	void callback_2(Ref* pSender);
	void callback_3(Ref* pSender);

	void tick(float dt);
	void tick2(float dt);

	int count;

	cocos2d::Sprite* sprite1;
	cocos2d::Sprite* sprite2;
	cocos2d::Sprite* sprite3;
};