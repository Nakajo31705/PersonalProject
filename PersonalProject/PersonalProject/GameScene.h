#pragma once
#include "DxLib.h"
#include "Scene.h"
#include "CharacterManager.h"
#include "EffectManager.h"
#include "Map.h"

class SceneManager;
class ImageManager;
class GameManager;

struct GameContext
{
	SceneManager& sceneManager;
	ImageManager& imageManager;
	GameManager& gameManager;
};

class GameScene : public Scene
{
public:
	GameScene(GameContext& ctx);
	void Init() override;
	void Update() override;
	void Draw() override;

	void RetrunTitle();
	void DrawMap();
	void DrawCharacter();
	void DrawUI();
	void DrawEffect();

private:
	GameContext& ctx;
	CharacterManager charaManager;
	EffectManager effectManager;
	Map map;

	int castleY = 620;
	int charaY = 640;

	int pPosX = 1700;
	int ePosX = 200;

	bool spawned = false;
};