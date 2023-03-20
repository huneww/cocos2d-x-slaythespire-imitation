#pragma once
#include "cocos2d.h"

class CharacterAnimation : public cocos2d::Scene
{
public:
	void CharacterIdelAnimation(int _Character_choes);
	void CharacterHitAnimation(int _Character_choes);
	void Remove();

	cocos2d::LayerColor* Character_Box;

private:
	cocos2d::Sprite* Character_Idle;
	cocos2d::Sprite* Character_Hit;
};