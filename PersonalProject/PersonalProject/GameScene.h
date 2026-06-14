#pragma once
#include "DxLib.h"
#include "Scene.h"
#include "CharacterManager.h"
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

private:
	GameContext& ctx;
	CharacterManager charaManager;
	Map map;

	int pPosX = 1700;
	int pPosY = 600;

	int ePosX = 200;
	int ePosY = 600;
};