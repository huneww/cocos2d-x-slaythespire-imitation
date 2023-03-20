#pragma once
#include "cocos2d.h"

#include "CreateCloud.h"
#include "StartGameMenu.h"
#include "CharcterSelector.h"
#include "SettingMenu.h"
#include "GameScene.h"
#include "Sound.h"

#pragma execution_character_set("utf-8")

class MainMenu : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	CREATE_FUNC(MainMenu);


	cocos2d::Sprite* cursor_point;
private:

#pragma region ¸Þ´º

	cocos2d::Sprite* BackGround;
	cocos2d::Sprite* Tower;
	cocos2d::Sprite* MainLogo;
	cocos2d::Sprite* cursor;

	cocos2d::Sprite* Start_Hlight;
	cocos2d::Sprite* Ency_Hlight;
	cocos2d::Sprite* Stati_Hlight;
	cocos2d::Sprite* Setting_Hlight;
	cocos2d::Sprite* Patch_Hlight;
	cocos2d::Sprite* Exit_Hllight;

	cocos2d::Label* pStartGame;
	cocos2d::Label* pEncyclopedia;
	cocos2d::Label* pStatistics;
	cocos2d::Label* pSetting;
	cocos2d::Label* pPatchNote;
	cocos2d::Label* pExitGame;

	cocos2d::EventListenerMouse* _Mouse_listener;
	cocos2d::EventMouse* _point;

	cocos2d::LayerColor* Blayer;
	cocos2d::LayerColor* Start_Box;
	cocos2d::LayerColor* Encyc_Box;
	cocos2d::LayerColor* Stati_Box;
	cocos2d::LayerColor* Setting_Box;
	cocos2d::LayerColor* Patch_Box;
	cocos2d::LayerColor* Exit_Box;


	cocos2d::Layer* Font_Layer;
	cocos2d::Layer* Font_Box_Layer;

	cocos2d::EventListenerTouchOneByOne* _Touch_listener;

	StartGameMenu* Startgamemenu;
	SettingMenu* Settingmenu;
	CharterSelector* CharcterSelector;
	CharterSelector* CharcterSelectorChoes;
	Sound* sound;

	int choes;
	int Charcter_choes;

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	
	void getMousePoint(cocos2d::Event* event);

	void CreateBackGround();
	void CreateMenu();
	void CreateFontBox();

	void ChoesMenu();
	void BackToMenu();

	void StopSound(float dt);

#pragma endregion
};