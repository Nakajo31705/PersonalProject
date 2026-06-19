#include "DxLib.h"
#include "GameManager.h"
#include "CharacterManager.h"
#include "EffectType.h"

GameManager::GameManager(CharacterManager&cm)
	:charaManager(cm)
{
}

GameManager::~GameManager()
{
}

void GameManager::Init()
{
	phase = EnemyPhase::First;
	charaManager.Spawn(CharacterType::pCastle, EffectType::None, pPosX, castleY, 0.2);
	charaManager.Spawn(CharacterType::eCastle, EffectType::None, ePosX, castleY + 10, 0.3);

	currentResetTime = spawnResetTime;
}

void GameManager::Update()
{ 
	//プレイヤーの生成待機時間
	if (spawned)
	{
		currentResetTime--;
		if (currentResetTime <= 0)
		{
			spawned = false;
			currentResetTime = spawnResetTime;
		}
	}

	//エネミーの生成フェーズの切り替え時間
	enemySpawnedTime++;
	if (enemySpawnedTime >= secondSpawnTime)
	{
		secondenemySpawned = false;
	}

	if (enemySpawnedTime >= thirdSpawnTime)
	{
		thirdenemySpawned = false;
	}

	Player();
	Enemy();
}

void GameManager::Draw()
{
	Result();

	if (!spawned)
	{
		DrawFormatString(0, 850, GetColor(255, 255, 255), "キャラクター召喚可能");
	}
	else
	{
		DrawFormatString(0, 850, GetColor(255, 255, 255), "キャラクター召喚可能まで:%.2f", currentResetTime);
	}

	DrawFormatString(0, 870, GetColor(255, 255, 255), "1を押して勇者を召喚");
	DrawFormatString(0, 890, GetColor(255, 255, 255), "2を押してエルフを召喚");
	DrawFormatString(0, 910, GetColor(255, 255, 255), "3を押して魔導士を召喚");
}

void GameManager::Player()
{
	//勇者の生成
	if (CheckHitKey(KEY_INPUT_1))
	{
		if (!spawned)
		{
			charaManager.Spawn(CharacterType::Hero, EffectType::Cut_left, pPosX, charaY, 0.2);
			spawned = true;
		}
	}
	//エルフの生成
	if (CheckHitKey(KEY_INPUT_2))
	{
		if (!spawned)
		{
			charaManager.Spawn(CharacterType::Elf, EffectType::Hit, pPosX, charaY, 0.2);
			spawned = true;
		}
	}
	//魔導士の生成
	if (CheckHitKey(KEY_INPUT_3))
	{
		if (!spawned)
		{
			charaManager.Spawn(CharacterType::Madoshi, EffectType::Fire_left, pPosX, charaY, 0.2);
			spawned = true;
		}
	}

}

/// <summary>
/// 敵の生成処理
/// </summary>
void GameManager::Enemy()
{
	switch (phase)
	{
	case EnemyPhase::First:
			break;
	case EnemyPhase::Second:
		break;
	case EnemyPhase::Third:
		break;
	case EnemyPhase::End:
		break;
	}

	//1体目の生成
	if (phase == EnemyPhase::First && !firstenemySpawned)
	{
		charaManager.Spawn(CharacterType::Vampire, EffectType::Fire_right, ePosX, charaY, 0.2);
		phase = EnemyPhase::Second;
	}
	//2体目の生成
	if (phase == EnemyPhase::Second && !secondenemySpawned)
	{
		charaManager.Spawn(CharacterType::Kinoko, EffectType::Attack_effect, ePosX, charaY, 0.2);
		phase = EnemyPhase::Third;
	}
	//3体目の生成
	if (phase == EnemyPhase::Third && !thirdenemySpawned)
	{
		charaManager.Spawn(CharacterType::Minotaur, EffectType::Cut_right, ePosX, charaY, 0.2);
		phase = EnemyPhase::End;
	}
}

//リザルト演出
void GameManager::Result()
{
	if (charaManager.GetPlayerLose())
	{
		float scale = 0.0f;

		scale += 5.0f;
		if (scale > 100.0f) scale = 100.0f;

		DrawExtendString(
			600,
			300,
			scale,
			scale,
			"LOSE",
			GetColor(255, 255, 0)
		);

		DrawFormatString(550, 400, GetColor(255, 255, 255), "SPACEを押してタイトルへ戻る");
	}

	if (charaManager.GetEnemyLose())
	{
		float scale = 0.0f;

		scale += 5.0f;
		if (scale > 100.0f) scale = 100.0f;

		DrawExtendString(
			600,
			300,
			scale,
			scale,
			"WIN",
			GetColor(255, 255, 0)
		);

		DrawFormatString(550, 400, GetColor(255, 255, 255), "SPACEを押してタイトルへ戻る");
	}
}

//リザルト中のリセット処理
void GameManager::ReStart()
{
	if (charaManager.GetPlayerLose() || charaManager.GetEnemyLose())
	{
		if (CheckHitKey(KEY_INPUT_RETURN))
		{
			Restart = true;
		}
	}
}

bool GameManager::GetReStart()
{
	return Restart;
}
