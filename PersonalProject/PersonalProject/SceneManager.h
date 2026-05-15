#pragma once
#include "TitleScene.h"
#include "GameScene.h"

class Scene;
class ImageManager;
class GameManager;

class SceneManager
{
public:
	//コンストラクタ
	SceneManager(ImageManager* img, GameManager* gm);

	//デストラクタ
	~SceneManager();

	//初期化
	void Init();

	void Update();

	void Draw();

	//シーン切替のリクエスト
	void RequestSceneChange(int id);

private:
	Scene* scene;
	ImageManager* imageManager;
	GameManager* gameManager;
	int nextScene;

	//シーンの変更処理
	void CheckSceneChange();
};
