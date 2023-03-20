#include "Sound.h"

USING_NS_CC;
using namespace experimental;

#pragma region 사운드 파일 위치
const std::string MAINTHEME = "slaythespire/audio/STS_MenuTheme_NewMix_v1.mp3";
const std::string MENUCLICK = "slaythespire/audio/SOTE_SFX_UIClick_1_v2.mp3";
const std::string CHDEAD_1 = "slaythespire/audio/STS_DeathStinger_1_v3_MUSIC.mp3";
const std::string CHDEAD_2 = "slaythespire/audio/STS_DeathStinger_2_v3_MUSIC.mp3";
const std::string CHDEAD_3 = "slaythespire/audio/STS_DeathStinger_3_v3_MUSIC.mp3";
const std::string CHDEAD_4 = "slaythespire/audio/STS_DeathStinger_4_v3_MUSIC.mp3";
const std::string ELITETHEME = "slaythespire/audio/STS_EliteBoss_NewMix_v1.mp3";
const std::string BOTTOMTHEME = "slaythespire/audio/STS_Level1_NewMix_v1.mp3";
const std::string BLACKATTACK = "slaythespire/audio/SOTE_SFX_BlockAtk_v2.mp3";
const std::string BREAKDEFEND = "slaythespire/audio/SOTE_SFX_DefenseBreak_v2.mp3";
const std::string BUFF = "slaythespire/audio/SOTE_SFX_Buff_1_v1.mp3";
const std::string DRAWCARD = "slaythespire/audio/STS_SFX_CardDeal8_v1.mp3";
const std::string CARDSELECT = "slaythespire/audio/SOTE_SFX_CardSelect_v2.mp3";
const std::string ENDTURN = "slaythespire/audio/SOTE_SFX_EndTurn_v2.mp3";
const std::string ATTACKSOUND = "slaythespire/audio/SOTE_SFX_FastAtk_v2.mp3";
const std::string HEAVYATTACKSOUND = "slaythespire/audio/SOTE_SFX_HeavyAtk_v2.mp3";
const std::string GETDEFEND = "slaythespire/audio/SOTE_SFX_GainDefense_v2.mp3";
const std::string GETGOLD = "slaythespire/audio/SOTE_SFX_Gold_RR1_v3.mp3";
const std::string CHATTACK_1 = "slaythespire/audio/SOTE_SFX_IronClad_Atk_RR1_v2.mp3";
const std::string CHATTACK_2 = "slaythespire/audio/SOTE_SFX_IronClad_Atk_RR2_v2.mp3";
const std::string CHATTACK_3 = "slaythespire/audio/SOTE_SFX_IronClad_Atk_RR3_v2.mp3";
const std::string OPENMAP_1 = "slaythespire/audio/SOTE_SFX_Map_1_v3.mp3";
const std::string OPENMAP_2 = "slaythespire/audio/SOTE_SFX_Map_2_v3.mp3";
const std::string MAPCLICK_1 = "slaythespire/audio/SOTE_SFX_MapSelect_1_v1.mp3";
const std::string MAPCLICK_2 = "slaythespire/audio/SOTE_SFX_MapSelect_2_v1.mp3";
const std::string MAPCLICK_3 = "slaythespire/audio/SOTE_SFX_MapSelect_3_v1.mp3";
const std::string MAPCLICK_4 = "slaythespire/audio/SOTE_SFX_MapSelect_4_v1.mp3";
const std::string BATTELSTARTMONSTER_1 = "slaythespire/audio/STS_SFX_BattleStart_1_v1.mp3";
const std::string BATTELSTARTMONSTER_2 = "slaythespire/audio/STS_SFX_BattleStart_2_v1.mp3";
const std::string BATTELSTARTBOSS = "slaythespire/audio/STS_SFX_BattleStart_Boss_v1.mp3";
const std::string CAMPFIRE = "slaythespire/audio/CampFire.mp3";
const std::string BOSSTHEME_1 = "slaythespire/audio/STS_Boss1MindBloom_v1.mp3";
const std::string BOSSTHEME_2 = "slaythespire/audio/STS_Boss1_NewMix_v1.mp3";
const std::string ENDINGTHEME = "slaythespire/audio/STS_EndingStinger_v1.mp3";
const std::string VICTORY = "slaythespire/audio/SOTE_SFX_Victory_v1.mp3";
const std::string VIEWDECK_1 = "slaythespire/audio/SOTE_SFX_ViewDeck_v1.mp3";
const std::string VIEWDECK_2 = "slaythespire/audio/SOTE_SFX_ViewDeck_v2.mp3";
const std::string SLIMEATK_1 = "slaythespire/audio/SOTE_SFX_SlimeAtk_1_v1.mp3";
const std::string SLIMEATK_2 = "slaythespire/audio/SOTE_SFX_SlimeAtk_2_v1.mp3";
const std::string BUTCHERATK = "slaythespire/audio/STS_SFX_EnemyAtk_Butcher_v1.mp3";
const std::string DAGGERATK = "slaythespire/audio/STS_SFX_EnemyAtk_Dagger_v1.mp3";
const std::string SCIMITARATK = "slaythespire/audio/STS_SFX_EnemyAtk_Scimitar_v1.mp3";
const std::string SWORDATK = "slaythespire/audio/STS_SFX_EnemyAtk_Sword_v1.mp3";
const std::string ENEMYTURN = "slaythespire/audio/SOTE_SFX_EnemyTurn_v3.mp3";
const std::string PLAYERTURN_1 = "slaythespire/audio/SOTE_SFX_PlayerTurn_v2.mp3";
const std::string PLAYERTURN_2 = "slaythespire/audio/SOTE_SFX_PlayerTurn_v3.mp3";
const std::string PLAYERTURN_3 = "slaythespire/audio/SOTE_SFX_PlayerTurn_v4_1.mp3";
const std::string PLAYERTURN_4 = "slaythespire/audio/SOTE_SFX_PlayerTurn_v4_2.mp3";
const std::string PLAYERTURN_5 = "slaythespire/audio/SOTE_SFX_PlayerTurn_v4_3.mp3";
const std::string DEBUFF_1 = "slaythespire/audio/SOTE_SFX_Debuff_1_v1.mp3";
const std::string DEBUFF_2 = "slaythespire/audio/SOTE_SFX_Debuff_2_v1.mp3";
const std::string DEBUFF_3 = "slaythespire/audio/SOTE_SFX_Debuff_3_v1.mp3";
#pragma endregion

// 메인 메뉴 백그라운드 사운드
void Sound::MainTheme()
{
	if (AudioEngine::getState(maintheme) != AudioEngine::AudioState::PLAYING)
	{
		maintheme = AudioEngine::play2d(MAINTHEME, true, background_volume);
	}
}

// 메인 메뉴 백그라운드 사운드 정지
void Sound::StopMainTheme()
{
	if (AudioEngine::getState(maintheme) == AudioEngine::AudioState::PLAYING)
	{
		AudioEngine::stop(maintheme);
	}
}

// 메뉴 클릭 사운드
void Sound::MenuClick()
{
		menuclick = AudioEngine::play2d(MENUCLICK, false, effect_volume);
}

// 캐릭터 죽은 사운드
void Sound::ChDead()
{
	int random = RandomHelper::random_int(1, 4);

	if (AudioEngine::getState(chdead) != AudioEngine::AudioState::PLAYING)
	{
		if (random == 1)
			chdead = AudioEngine::play2d(CHDEAD_1, false, background_volume);
		else if (random == 2)
			chdead = AudioEngine::play2d(CHDEAD_2, false, background_volume);
		else if (random == 3)
			chdead = AudioEngine::play2d(CHDEAD_3, false, background_volume);
		else if (random == 4)
			chdead = AudioEngine::play2d(CHDEAD_4, false, background_volume);
	}
}

// 엘리트 몬스터 백그라운드 사운드
void Sound::EliteTheme()
{
	if (AudioEngine::getState(elitetheme) != AudioEngine::AudioState::PLAYING)
	{
		elitetheme = AudioEngine::play2d(ELITETHEME, true, background_volume);
	}
}

// 엘리트 몬스터 백그라운드 사운드 정지
void Sound::StopEliteTheme()
{
	if (AudioEngine::getState(elitetheme) == AudioEngine::AudioState::PLAYING)
	{
		AudioEngine::stop(elitetheme);
	}
}

// 1스테이지 백그라운드 사운드
void Sound::BottomTheme()
{
	if (AudioEngine::getState(bottomtheme) != AudioEngine::AudioState::PLAYING)
	{
		bottomtheme = AudioEngine::play2d(BOTTOMTHEME, true, background_volume);
	}
}

// 1스테이지 백그라운드 사운드 정지
void Sound::StopBottomTheme()
{
	if (AudioEngine::getState(bottomtheme) == AudioEngine::AudioState::PLAYING)
	{
		AudioEngine::stop(bottomtheme);
	}
}

// 1스테이지 백그라운드 사운드 일시정지
void Sound::PauseBottomTheme()
{
	if (AudioEngine::getState(bottomtheme) == AudioEngine::AudioState::PLAYING)
	{
		AudioEngine::pause(bottomtheme);
	}
}

// 1스테이지 백그라운드 사운디 재시작
void Sound::ResumeBottomTheme()
{
	if (AudioEngine::getState(bottomtheme) == AudioEngine::AudioState::PAUSED)
	{
		AudioEngine::resume(bottomtheme);
	}
}

// 공격을 하거나 받을때 방어도가 남으면
void Sound::BlackAttack()
{
		blackattack = AudioEngine::play2d(BLACKATTACK, false, effect_volume);
}

// 공격을 하거나 받을때 방어도가 안남으면
void Sound::BreakDefend()
{
		breakdefend = AudioEngine::play2d(BREAKDEFEND, false, effect_volume);
}

// 버프 사운드
void Sound::Buff()
{
	if (AudioEngine::getState(buff) != AudioEngine::AudioState::PLAYING)
	{
		buff = AudioEngine::play2d(BUFF, false, effect_volume);
	}
}

// 카드 드로우 사운드
void Sound::DrawCardSound()
{
	if (AudioEngine::getState(drawcard) != AudioEngine::AudioState::PLAYING)
	{
		drawcard = AudioEngine::play2d(DRAWCARD, false, effect_volume);
	}
}

// 카드 선택 사운드
void Sound::CardSelect()
{
		cardselect = AudioEngine::play2d(CARDSELECT, false, effect_volume);
}

// 턴 종료 사운드
void Sound::EndTurn()
{
	if (AudioEngine::getState(endturn) != AudioEngine::AudioState::PLAYING)
	{
		endturn = AudioEngine::play2d(ENDTURN, false, effect_volume);
	}
}

// 공격 사운드
void Sound::AttackSound()
{
		attacksound = AudioEngine::play2d(ATTACKSOUND, false, effect_volume);
}

// 강공격 사운드
void Sound::HeavyAttackSound()
{
		heavyattacksound = AudioEngine::play2d(HEAVYATTACKSOUND, false, effect_volume);
}

// 방어도 획득 사운드
void Sound::GetDefend()
{
		getdefend = AudioEngine::play2d(GETDEFEND, false, effect_volume);
}

// 골드 획득 사운드
void Sound::GetGold()
{
	if (AudioEngine::getState(getgold) != AudioEngine::AudioState::PLAYING)
	{
		getgold = AudioEngine::play2d(GETGOLD, false, effect_volume);
	}
}

// 캐릭터 공격 사운드
void Sound::ChAttack()
{
	int random = RandomHelper::random_int(1, 3);

		if (random == 1)
		{
			chattack = AudioEngine::play2d(CHATTACK_1, false, effect_volume);
		}
		else if (random == 2)
		{
			chattack = AudioEngine::play2d(CHATTACK_2, false, effect_volume);
		}
		else if (random == 3)
		{
			chattack = AudioEngine::play2d(CHATTACK_3, false, effect_volume);
		}
}

// 맵 오픈 사운드
void Sound::OpenMap()
{
	int random = RandomHelper::random_int(1, 2);

		if (random == 1)
		{
			openmap = AudioEngine::play2d(OPENMAP_1, false, effect_volume);
		}
		else if (random == 2)
		{
			openmap = AudioEngine::play2d(OPENMAP_2, false, effect_volume);
		}
}

// 맵 클릭 사운드
void Sound::MapClick()
{
	int random = RandomHelper::random_int(1, 4);

		if (random == 1)
		{
			mapclick = AudioEngine::play2d(MAPCLICK_1, false, effect_volume);
		}
		else if (random == 2)
		{
			mapclick = AudioEngine::play2d(MAPCLICK_2, false, effect_volume);
		}
		else if (random == 3)
		{
			mapclick = AudioEngine::play2d(MAPCLICK_3, false, effect_volume);
		}
		else if (random == 4)
		{
			mapclick = AudioEngine::play2d(MAPCLICK_4, false, effect_volume);
		}
}

// 배틀 시작 사운드 (몬스터)
void Sound::BattelStartMonster()
{
	int random = RandomHelper::random_int(1, 2);

	if (AudioEngine::getState(battelstartmonster) != AudioEngine::AudioState::PLAYING)
	{
		if (random == 1)
		{
			battelstartmonster = AudioEngine::play2d(BATTELSTARTMONSTER_1, false, background_volume);
		}
		else if (random == 2)
		{
			battelstartmonster = AudioEngine::play2d(BATTELSTARTMONSTER_2, false, background_volume);
		}
	}
}

// 배틀 시작 사운드 (보스)
void Sound::BattelStartBoss()
{
	if (AudioEngine::getState(battelstartboss) != AudioEngine::AudioState::PLAYING)
	{
		battelstartboss = AudioEngine::play2d(BATTELSTARTBOSS, false, background_volume);
	}
}

// 장작 타는 소리
void Sound::CampFire()
{
	if (AudioEngine::getState(campfire) != AudioEngine::AudioState::PLAYING)
	{
		campfire = AudioEngine::play2d(CAMPFIRE, true, background_volume);
	}
}

// 장작 타는 소리 정지
void Sound::StopCampFire()
{
	if (AudioEngine::getState(campfire) == AudioEngine::AudioState::PLAYING)
	{
		AudioEngine::stop(campfire);
	}
}

// 보스 백그라운드 사운드
void Sound::BossTheme()
{
	int random = RandomHelper::random_int(1, 2);

	if (AudioEngine::getState(bosstheme) != AudioEngine::AudioState::PLAYING)
	{
		if (random == 1)
			bosstheme = AudioEngine::play2d(BOSSTHEME_1, true, background_volume);
		else if (random == 2)
			bosstheme = AudioEngine::play2d(BOSSTHEME_2, true, background_volume);
	}
}

// 보스 백그라운드 사운드 정지
void Sound::StopBossTheme()
{
	if (AudioEngine::getState(bosstheme) == AudioEngine::AudioState::PLAYING)
	{
		AudioEngine::stop(bosstheme);
	}
}

// 엔딩 백그라운드 사운드
void Sound::EndingTheme()
{
	if (AudioEngine::getState(endingtheme) != AudioEngine::AudioState::PLAYING)
	{
		endingtheme = AudioEngine::play2d(ENDINGTHEME, true, background_volume);
	}
}

// 엔딩 백그라운드 사운드 정지
void Sound::StopEndingTheme()
{
	if (AudioEngine::getState(endingtheme) == AudioEngine::AudioState::PLAYING)
	{
		AudioEngine::stop(endingtheme);
	}
}

// 승리 사운드
void Sound::Victory()
{
	if (AudioEngine::getState(victory) != AudioEngine::AudioState::PLAYING)
	{
		victory = AudioEngine::play2d(VICTORY, false, background_volume);
	}
}

// 덱 오픈 사운드
void Sound::ViewDeck()
{
	int random = RandomHelper::random_int(1, 2);

	if (AudioEngine::getState(viewdeck) != AudioEngine::AudioState::PLAYING)
	{
		if (random == 1)
			viewdeck = AudioEngine::play2d(VIEWDECK_1, false, effect_volume);
		else if (random == 2)
			viewdeck = AudioEngine::play2d(VIEWDECK_2, false, effect_volume);
	}
}

// 슬라임 공격 사운드
void Sound::SlimeAtk()
{
	int random = RandomHelper::random_int(1, 2);

	if (AudioEngine::getState(slimeatk) != AudioEngine::AudioState::PLAYING)
	{
		if (random == 1)
			slimeatk = AudioEngine::play2d(SLIMEATK_1, false, effect_volume);
		else if (random == 2)
			slimeatk = AudioEngine::play2d(SLIMEATK_2, false, effect_volume);
	}
}

// 도축용 칼
void Sound::ButcherAtk()
{
	butcheratk = AudioEngine::play2d(BUTCHERATK, false, effect_volume);
}

// 대거
void Sound::DaggerAtk()
{
	if (AudioEngine::getState(daggeratk) != AudioEngine::AudioState::PLAYING)
	{
		daggeratk = AudioEngine::play2d(DAGGERATK, false, effect_volume);
	}
}

// 초승달 처럼 굽은 칼
void Sound::ScimitarAtk()
{
	if (AudioEngine::getState(scimitaratk) != AudioEngine::AudioState::PLAYING)
	{
		scimitaratk = AudioEngine::play2d(SCIMITARATK, false, effect_volume);
	}
}

// 검
void Sound::SwordAtk()
{
		swordatk = AudioEngine::play2d(SWORDATK, false, effect_volume);
}

// 적 턴 시작 사운드
void Sound::EnemyTurn()
{
	if (AudioEngine::getState(enemyturn) != AudioEngine::AudioState::PLAYING)
	{
		enemyturn = AudioEngine::play2d(ENEMYTURN, false, effect_volume);
	}
}

// 플레이어 턴 시작 사운드
void Sound::PlayerTurn()
{
	int random = RandomHelper::random_int(1, 5);

	if (AudioEngine::getState(playerturn) != AudioEngine::AudioState::PLAYING)
	{
		if (random == 1)
			playerturn = AudioEngine::play2d(PLAYERTURN_1, false, effect_volume);
		else if (random == 2)
			playerturn = AudioEngine::play2d(PLAYERTURN_2, false, effect_volume);
		else if (random == 3)
			playerturn = AudioEngine::play2d(PLAYERTURN_3, false, effect_volume);
		else if (random == 4)
			playerturn = AudioEngine::play2d(PLAYERTURN_4, false, effect_volume);
		else if (random == 5)
			playerturn = AudioEngine::play2d(PLAYERTURN_5, false, effect_volume);
	}
}

// 디버프 사운드
void Sound::Debuff()
{
	int random = RandomHelper::random_int(1, 3);

	if (AudioEngine::getState(debuff) != AudioEngine::AudioState::PLAYING)
	{
		if (random == 1)
			debuff = AudioEngine::play2d(DEBUFF_1, false, effect_volume);
		else if (random == 2)
			debuff = AudioEngine::play2d(DEBUFF_2, false, effect_volume);
		else if (random == 3)
			debuff = AudioEngine::play2d(DEBUFF_3, false, effect_volume);
	}
}

// 백그라운드 사운드 조절
void Sound::SetBackGround_volume()
{
	// 변경된 사운드 유저 디폴트에 저장
	auto user = UserDefault::getInstance();
	user->setFloatForKey("BackGround", background_volume);

	user->flush();

	AudioEngine::setVolume(maintheme, background_volume);
	AudioEngine::setVolume(chdead, background_volume);
	AudioEngine::setVolume(elitetheme, background_volume);
	AudioEngine::setVolume(bottomtheme, background_volume);
	AudioEngine::setVolume(battelstartmonster, background_volume);
	AudioEngine::setVolume(battelstartboss, background_volume);
	AudioEngine::setVolume(campfire, background_volume);
	AudioEngine::setVolume(bosstheme, background_volume);
	AudioEngine::setVolume(endingtheme, background_volume);
}

// 이펙트 사운드 조절
void Sound::SetEffect_volume()
{
	// 변경된 사운드 유저 디폴트에 저장
	auto user = UserDefault::getInstance();
	user->setFloatForKey("Effect", effect_volume);
	log("Effect volume : %f", effect_volume);
	log("user Effect volume : %f", user->getFloatForKey("Effect"));

	user->flush();

	AudioEngine::setVolume(menuclick, effect_volume);
	AudioEngine::setVolume(blackattack, effect_volume);
	AudioEngine::setVolume(breakdefend, effect_volume);
	AudioEngine::setVolume(buff, effect_volume);
	AudioEngine::setVolume(drawcard, effect_volume);
	AudioEngine::setVolume(cardselect, effect_volume);
	AudioEngine::setVolume(endturn, effect_volume);
	AudioEngine::setVolume(attacksound, effect_volume);
	AudioEngine::setVolume(heavyattacksound, effect_volume);
	AudioEngine::setVolume(getdefend, effect_volume);
	AudioEngine::setVolume(getgold, effect_volume);
	AudioEngine::setVolume(chattack, effect_volume);
	AudioEngine::setVolume(openmap, effect_volume);
	AudioEngine::setVolume(mapclick, effect_volume);
	AudioEngine::setVolume(victory, effect_volume);
	AudioEngine::setVolume(viewdeck, effect_volume);
	AudioEngine::setVolume(slimeatk, effect_volume);
	AudioEngine::setVolume(butcheratk, effect_volume);
	AudioEngine::setVolume(daggeratk, effect_volume);
	AudioEngine::setVolume(scimitaratk, effect_volume);
	AudioEngine::setVolume(swordatk, effect_volume);
	AudioEngine::setVolume(enemyturn, effect_volume);
	AudioEngine::setVolume(playerturn, effect_volume);
	AudioEngine::setVolume(debuff, effect_volume);
}