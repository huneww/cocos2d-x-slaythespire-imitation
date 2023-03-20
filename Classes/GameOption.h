#pragma once
#include "cocos2d.h"

#pragma execution_character_set("utf-8")

class GameOption : public cocos2d::Scene
{
public:
	void CreateGameOption();
	void Remove();

	cocos2d::LayerColor* Yes_Button_Box;
	cocos2d::LayerColor* No_Button_Box;

private:

	void OptionSprite();
	void OptionFont();
};