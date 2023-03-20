#pragma once
#include "cocos2d.h"

class Example_17 : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	CREATE_FUNC(Example_17);

private:
	void Tick(float dt);
};