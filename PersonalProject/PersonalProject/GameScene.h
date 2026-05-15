#pragma once
#include "DxLib.h"
#include "Scene.h"

class SceneManager;
class ImageManager;
class GameManager;

class GameScene : public Scene
{
public:
	GameScene(SceneManager& sm, ImageManager* imgmg, GameManager* gm);
	void Init() override;
	void Update() override;
	void Draw() override;

	void ImageDraw();

private:
	SceneManager& sceneManager;
	ImageManager* imageManager;
	GameManager* gameManager;
};