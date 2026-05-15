#pragma once
#include "SceneManager.h"
#include "ImageManager.h"
#include "GameManager.h"

class Game
{
public:
	Game();
	bool Init();
	void Run();
	void ShutDown();
	void InitImage();

private:
	void ProcessInput();
	void Update();
	void Render();

	bool isRunning = true;
	SceneManager sceneManager;
	ImageManager imageManager;
	GameManager gameManager;

};
