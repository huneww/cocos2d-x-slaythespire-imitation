#pragma once
#include "cocos2d.h"

struct Relics_Info
{
	std::string name = "none";
};

enum Relics_Code
{
	BurningBlood
};


class Relics : public cocos2d::Scene
{
public:

	Relics_Code relics;
	cocos2d::UserDefault* user;
	cocos2d::Sprite* Relics_sprite[300];
	cocos2d::LayerColor* relics_box[300];

	void Create_Have_Relics();
};