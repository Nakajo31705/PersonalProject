#pragma once
#include "DxLib.h"
#include "Scene.h"

struct GameContext
{
	SceneManager& sceneManager;
	ImageManager& imageManager;
	GameManager& gameManager;
	CharacterManager& charaManager;
};

class SceneManager;
class ImageManager;
class GameManager;
class CharacterManager;

class GameScene : public Scene
{
public:
	GameScene(GameContext& ctx,SceneManager& sm);
	void Init() override;
	void Update() override;
	void Draw() override;

	void ImageDraw();

private:
	GameContext& ctx;
	SceneManager& sm;
};