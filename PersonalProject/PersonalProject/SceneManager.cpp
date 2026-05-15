#include "SceneManager.h"

SceneManager::SceneManager(ImageManager* img, GameManager* gm)
	:imageManager(img),
	gameManager(gm)
{
	scene = new TitleScene(*this);
	nextScene = -1;
}

SceneManager::~SceneManager()
{
	if (scene)
	{
		delete scene;
		scene = nullptr;
	}
}

void SceneManager::Init()
{
	scene->Init();
}

void SceneManager::Update()
{
	scene->Update();
	CheckSceneChange();
}

void SceneManager::Draw()
{
	scene->Draw();
}

/// <summary>
/// シーンの切替のリクエストを送る
/// </summary>
/// <param name="id">シーンナンバー</param>
void SceneManager::RequestSceneChange(int id)
{
	nextScene = id;
}

/// <summary>
/// シーン変更の処理をする
/// </summary>
void SceneManager::CheckSceneChange()
{
	//次のシーンが設定されてないときはreturn
	if (nextScene == -1) return;
	delete scene;

	if (nextScene == 0)
	{
		scene = new TitleScene(*this);
	}
	else if (nextScene == 1)
	{
		scene = new GameScene(*this, imageManager,gameManager);
	}

	nextScene = -1;
}


