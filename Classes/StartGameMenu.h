#pragma once
#include "cocos2d.h"

#pragma execution_character_set("utf-8")

class StartGameMenu : public cocos2d::Scene
{
private:
	cocos2d::Sprite* CancleButton;
	cocos2d::Sprite* CancleButtonShadow;
	cocos2d::Sprite* CancleButtonOutLine;
	cocos2d::Sprite* Left;
	cocos2d::Sprite* Midle;
	cocos2d::Sprite* Right;
	cocos2d::Sprite* PanelFrame[3];
	cocos2d::Sprite* Normal_Sprite;
	cocos2d::Sprite* Daily_Sprite;
	cocos2d::Sprite* Custom_Sprite;
	cocos2d::Sprite* Lock[2];


	cocos2d::Label* BackFont;
	cocos2d::Label* Normal;
	cocos2d::Label* Normal_Ex;
	cocos2d::Label* Daily;
	cocos2d::Label* Daily_Ex;
	cocos2d::Label* Custom;
	cocos2d::Label* Custom_Ex;

	cocos2d::Layer* SpriteLayer;
	cocos2d::Layer* FontLayer;

	cocos2d::LayerColor* BLayer;

	void CreateStartMenuSprite();
	void CreateStartMenuFont();

public:

	cocos2d::LayerColor* CancleButton_Box;
	cocos2d::LayerColor* Panel_Box;

	void Remove();
	void CreateStartGameMenu();
};