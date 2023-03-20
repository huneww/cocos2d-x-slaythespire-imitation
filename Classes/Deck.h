#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

#pragma execution_character_set("utf-8")

class Deck : public cocos2d::Scene
{
public:
	
	void Create();
	void Remove();

	cocos2d::LayerColor* CancleButton_Box;

private:

	cocos2d::UserDefault* user;

	cocos2d::LayerColor* layer;
	cocos2d::LayerColor* blayer;

	cocos2d::Sprite* Card[12][5];
	cocos2d::Sprite* CancleButtonShadow;
	cocos2d::Sprite* CancleButtonOutLine;
	cocos2d::Sprite* CancleButton;

	cocos2d::Label* CardInfo[12][3];
	cocos2d::Label* CancleFont;

};