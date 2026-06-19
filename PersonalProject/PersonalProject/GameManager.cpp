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
	charaManager.Spawn(CharacterType::pCastle, EffectType::None, pPosX, castleY, 0.2);
	charaManager.Spawn(CharacterType::eCastle, EffectType::None, ePosX, castleY + 10, 0.3);

	currentResetTime = spawnResetTime;
}

void GameManager::Update()
{ 
	if (spawned)
	{
		currentResetTime--;
		if (currentResetTime <= 0)
		{
			spawned = false;
			currentResetTime = spawnResetTime;
		}
	}

	enemySpawnedTime++;
	if (enemySpawnedTime >= secondSpawnTime && firstenemySpawned)
	{
		secondenemySpawned = false;
	}

	if (enemySpawnedTime >= thirdSpawnTime && secondenemySpawned)
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
		DrawFormatString(0, 850, GetColor(255, 255, 255), "キャラクター生産可能");
	}
	else
	{
		DrawFormatString(0, 850, GetColor(255, 255, 255), "キャラクター生産可能まで:%.2f", currentResetTime);
	}
}

void GameManager::Player()
{
	if (CheckHitKey(KEY_INPUT_1))
	{
		if (!spawned)
		{
			charaManager.Spawn(CharacterType::Hero, EffectType::Cut_left, pPosX, charaY, 0.2);
			spawned = true;
		}
	}
	if (CheckHitKey(KEY_INPUT_2))
	{
		if (!spawned)
		{
			charaManager.Spawn(CharacterType::Elf, EffectType::Hit, pPosX, charaY, 0.2);
			spawned = true;
		}
	}
	if (CheckHitKey(KEY_INPUT_3))
	{
		if (!spawned)
		{
			charaManager.Spawn(CharacterType::Madoshi, EffectType::Fire_left, pPosX, charaY, 0.2);
			spawned = true;
		}
	}

}

void GameManager::Enemy()
{
	//一体目の生成
	if (!firstenemySpawned)
	{
		charaManager.Spawn(CharacterType::Vampire, EffectType::Fire_right, ePosX, charaY, 0.2);
		firstenemySpawned = true;
	}

	if (!secondenemySpawned)
	{
		charaManager.Spawn(CharacterType::Kinoko, EffectType::Attack_effect, ePosX, charaY, 0.2);
		secondenemySpawned = true;
	}
	if (!thirdenemySpawned)
	{
		charaManager.Spawn(CharacterType::Minotaur, EffectType::Cut_right, ePosX, charaY, 0.2);
		thirdenemySpawned = true;
	}

}

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
