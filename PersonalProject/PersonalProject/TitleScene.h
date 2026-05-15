#pragma once
#include "DxLib.h"
#include "Scene.h"

class SceneManager;

class TitleScene : public Scene
{
public:
	TitleScene(SceneManager& sm);
	void Init() override;
	void Update() override;
	void Draw() override;
private:
	SceneManager& sceneManager;
};
