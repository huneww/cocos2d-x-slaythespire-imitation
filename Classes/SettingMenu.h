#pragma once
#include "cocos2d.h"

#pragma execution_character_set("utf-8")

class SettingMenu : public cocos2d::Scene
{
public:

	void CreateSettingMenu();
	void FromSettingToMenu();
	cocos2d::LayerColor* CancleButton_Box;
	cocos2d::LayerColor* GameEnd_Box;
	cocos2d::Sprite* Slider[2];

private:

	cocos2d::UserDefault* userDefault;

	cocos2d::Sprite* CancleButton;
	cocos2d::Sprite* CancleButtonShadow;
	cocos2d::Sprite* CancleButtonOutLine;
	cocos2d::Sprite* BackGround;
	cocos2d::Sprite* GameEnd;
	cocos2d::Sprite* SliderBg[2];

	cocos2d::Label* BackFont;
	cocos2d::Label* GameEndFont;
	cocos2d::Label* Sound;
	cocos2d::Label* Background_Sound;
	cocos2d::Label* Effect_Sound;

	cocos2d::LayerColor* Blayer;

	cocos2d::Layer* SettingSpriteLayer;
	cocos2d::Layer* SettingFontLayer;

	void CreateSettingSprite();
	void CreateSettingFont();
};