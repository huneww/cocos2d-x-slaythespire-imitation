#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Sound.h"

#pragma execution_character_set("utf-8")

class Battel : public cocos2d::Scene
{
public:

	void Create(std::string _name);
	void Remove();
	void DrawCard();
	void MonAction(std::string _name);
	void MonActionAnimation(std::string _name);
	void MonDead(std::string _name);
	void ChDead(std::string _name);
	void Remove_reward();
	void Remove_Card();
	void Remove_Use_Card(int number);
	void Stop_Card_Outline(int number);

	cocos2d::Layer* Rest_layer;

	cocos2d::LayerColor* CardBox[5];
	cocos2d::LayerColor* mlayer;

	cocos2d::Label* CardInfo[5][3];
	cocos2d::Label* CostFont;
	cocos2d::Label* Mon_Hp_Font;
	cocos2d::Label* defend_font;
	cocos2d::Label* Character_Hp_Font;
	cocos2d::Label* Sleep_Info;

	cocos2d::Sprite* Card[5][5];
	cocos2d::Sprite* CardOutline[5];
	cocos2d::Sprite* defend_sprite;
	cocos2d::Sprite* buff_sprite;
	cocos2d::Sprite* campfire_choes;
	cocos2d::Sprite* campfire_bg_before;
	cocos2d::Sprite* shoulder_before;
	cocos2d::Sprite* campfire;
	cocos2d::Sprite* choes_bg;
	cocos2d::Sprite* choes_outline;
	cocos2d::Sprite* buff;
	
	cocos2d::ui::LoadingBar* Mon_Hp;
	cocos2d::ui::LoadingBar* Character_Hp;

	Sound* sound;

	int action;
	int card[5];
	int nowCost;
	int MaxCost;
	int NowHp;
	int MaxHp;
	int Mon_Damage;
	int Mon_Defend;
	int Ch_NowHp;
	int Ch_MaxHp;
	int gold;
	int random;
	int check;
	int action_check;

	bool firstturn;

	std::string name;

private:
	void Monster();
	void Elite();
	void Shop();
	void Event();
	void Boss();
	void Rest();
	void Chest();
	void CharacterInfo();
	
	char Hp[100];
	char Damage[100];
	char Defend[100];

	cocos2d::Layer* Reward_layer;

	cocos2d::Sprite* attack;
	cocos2d::Sprite* attack_2;
	cocos2d::Sprite* defend;

	cocos2d::Label* attackfont;
	cocos2d::Label* attackfont_2;
	cocos2d::Label* buff_font;

	cocos2d::Sprite* Monster_sprite;
};