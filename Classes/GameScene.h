#pragma once
#include "cocos2d.h"

#include "MapScene.h"
#include "GameOption.h"
#include "CharcterAnimation.h"
#include "Battel.h"
#include "Deck.h"

#include "Sound.h"

#include "MainMenu.h"

#pragma execution_character_set("utf-8")

class GameScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	CREATE_FUNC(GameScene);

	int choes;

private:

	int Charcter_choes;
	int ItemInfo[299] = { 1 };
	int Ch_Defend;
	int Ch_Weekening;
	int Ch_Damage;
	int Ch_Impairment;
	int count;
	int cardnumber;
	bool playerturn;

	cocos2d::UserDefault* user;

	cocos2d::Sprite* BackGround;
	cocos2d::Sprite* Wall;
	cocos2d::Sprite* Floor;
	cocos2d::Sprite* Pillar;
	cocos2d::Sprite* Decor;
	cocos2d::Sprite* Ceiling;
	cocos2d::Sprite* TopBar;
	cocos2d::Sprite* Item[299];
	cocos2d::Sprite* Heart;
	cocos2d::Sprite* Gold;
	cocos2d::Sprite* TopDeck;
	cocos2d::Sprite* TopMenu;
	cocos2d::Sprite* TopMap;
	cocos2d::Sprite* cursor;
	cocos2d::Sprite* cursor_point;
	cocos2d::Sprite* ChCheck;
	cocos2d::Sprite* MonCheck;
	cocos2d::Sprite* Ch_Defend_sprite;
	cocos2d::Sprite* Ch_Weekening_Debuff_sprite;
	cocos2d::Sprite* Ch_Impairment_Debuff_sprite;

	cocos2d::LayerColor* TopDeck_Box;
	cocos2d::LayerColor* TopMenu_Box;
	cocos2d::LayerColor* TopMap_Box;
	cocos2d::LayerColor* DeckBox;
	cocos2d::LayerColor* DisDeckBox;
	cocos2d::LayerColor* CardBox[5];
	cocos2d::LayerColor* EndTurnBox;
	cocos2d::LayerColor* CoutinueBox;
	cocos2d::LayerColor* rewardBox;
	cocos2d::LayerColor* nextfloorBox;
	cocos2d::LayerColor* CardLayer;

	cocos2d::Label* CharcterName;
	cocos2d::Label* HeartFont;
	cocos2d::Label* GoldFont;
	cocos2d::Label* Ch_Defend_font;
	cocos2d::Label* Ch_Weekening_Debuff_font;
	cocos2d::Label* Ch_Impairment_Debuff_font;

	MapScene* Map;
	GameOption* Gameoption;
	CharacterAnimation* ChAnimation;
	Battel* battel;
	Deck* deck;
	Sound* sound;

	cocos2d::EventListenerMouse* Mouse_listener;
	cocos2d::EventMouse* _point;
	cocos2d::EventListenerTouchOneByOne* Touch_listener;

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void onMouseMove(cocos2d::Event* event);

	void Create_Sprite();
	void Create_Font();
	void DrawCard();

	void Check(float dt);
	void MonAction(float dt);
	void CheckHp(float dt);
	void CreateBattelScene(float dt);
	void StopSound(float dt);
	void EnemyTurn(float dt);
	void Whirlwind(float dt);
	void DoubleAtk(float dt);

};