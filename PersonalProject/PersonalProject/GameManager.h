#pragma once

enum class EnemyPhase
{
	First,
	Second,
	Third,
	End
};

class CharacterManager;

class GameManager
{
public:
	GameManager(CharacterManager& cm);
	~GameManager();
	void Init();
	void Update();
	void Draw();

	void Player();
	void Enemy();
	void Result();
	void ReStart();
	bool GetReStart();
private:
	EnemyPhase phase;
	CharacterManager& charaManager;
	bool spawned = false;
	bool firstenemySpawned = false;
	bool secondenemySpawned = true;
	bool thirdenemySpawned = true;
	bool Restart = false;

	int castleY = 620;
	int charaY = 640;

	int pPosX = 1300;
	int ePosX = 200;

	float spawnResetTime = 500;
	float currentResetTime = 0;

	float enemySpawnedTime = 0;
	float firstSpawnTime = 0;
	float secondSpawnTime = 2500;
	float thirdSpawnTime = 5000;
};