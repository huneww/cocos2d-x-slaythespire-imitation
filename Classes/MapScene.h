#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

#pragma execution_character_set("utf-8")

class MapScene : public cocos2d::Scene
{
public:
	void CreateMap();
	void Visiblefalse();
	void Visibletrue();

	int floor;
	int circlecount;

	cocos2d::LayerColor* CancleButton_Box;
	cocos2d::Sprite* Map[4];
	cocos2d::Sprite* IconCircle[14];
	cocos2d::Sprite* MapIcon[14];
	cocos2d::Sprite* BossIcon;
	cocos2d::LayerColor* IconBox[14];
	cocos2d::LayerColor* BossBox;
	cocos2d::LayerColor* MaplayerC;

	void MenuCallBack();
private:

	cocos2d::UserDefault* user;

	cocos2d::Sprite* CancleButtonShadow;
	cocos2d::Sprite* CancleButtonOutLine;
	cocos2d::Sprite* CancleButton;
	cocos2d::Sprite* IconInfo[6];
	cocos2d::Sprite* IconInfoBG;

	cocos2d::Label* BackFont;
	cocos2d::Label* IconFont;
	cocos2d::Label* IconInfoFont[6];

	cocos2d::Layer* MapIconlayer;
	cocos2d::Layer* MapSpritelayer;
	cocos2d::Layer* Fontlayer;

	cocos2d::LayerColor* blayer;

	cocos2d::ui::ScrollView* scrollView;

	cocos2d::Sequence* seq;

	void MapSprite();
	void MapFont();
};