#pragma once

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
private:
	CharacterManager& charaManager;
	bool spawned = false;

	int castleY = 620;
	int charaY = 640;

	int pPosX = 1700;
	int ePosX = 200;
};