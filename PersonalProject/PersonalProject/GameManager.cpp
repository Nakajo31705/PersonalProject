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
}

void GameManager::Update()
{ 
	Player();
}

void GameManager::Draw()
{
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
			charaManager.Spawn(CharacterType::Hero, EffectType::Cut_left, pPosX, charaY, 0.2);
			spawned = true;
		}
	}
}
