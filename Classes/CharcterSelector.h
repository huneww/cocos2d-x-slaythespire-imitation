#pragma once
#include "cocos2d.h"

#pragma execution_character_set("utf-8")

class CharterSelector : public cocos2d::Scene
{
public:

	void CreateCharcterScene();
	void Remove();
	void CheckBackGround(int charter);

	cocos2d::LayerColor* CancleButton_Box;
	cocos2d::LayerColor* StartButton_Box;
	cocos2d::Sprite* CharcterIcon[4];
	cocos2d::Sprite* CharcterBackGround[4];

private:

	cocos2d::LayerColor* Blayer;

	cocos2d::Layer* CharcterSprite;
	cocos2d::Layer* CharcterFont;

	cocos2d::Sprite* CancleButton;
	cocos2d::Sprite* CancleButtonShadow;
	cocos2d::Sprite* CancleButtonOutLine;
	cocos2d::Sprite* CharcterIcon_Shadow[4];
	cocos2d::Sprite* CharcterIcon_Outline[4];
	cocos2d::Sprite* StartButton;
	cocos2d::Sprite* StartButtonShadow;
	cocos2d::Sprite* StartButtonOutline;
	cocos2d::Sprite* Heart;
	cocos2d::Sprite* Gold;
	cocos2d::Sprite* Item;

	cocos2d::Label* BackFont;
	cocos2d::Label* SelectorCharcter;
	cocos2d::Label* CharcterName;
	cocos2d::Label* CharcterInfo;
	cocos2d::Label* Heart_Font;
	cocos2d::Label* Gold_Font;
	cocos2d::Label* ItemInfo[2];
	cocos2d::Label* StartFont;

	void CreateCharcterSprite();
	void CreateCharcterFont();
	void CreateCharcterInfo(int charter);
	void RemoveCharcterInfo(int charter);
};