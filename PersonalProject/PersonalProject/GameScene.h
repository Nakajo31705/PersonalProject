#pragma once
#include "DxLib.h"
#include "Scene.h"
#include "CharacterManager.h"
#include "EffectManager.h"
#include "GameManager.h"
#include "Map.h"

class SceneManager;
class ImageManager;

struct GameContext
{
	SceneManager& sceneManager;
	ImageManager& imageManager;
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
	GameManager gameManager;
	Map map;

	int castleY = 620;
	int charaY = 640;

	int pPosX = 1300;
	int ePosX = 200;
};