#pragma once
#include "TitleScene.h"
#include "GameScene.h"

class Scene;

class SceneManager
{
public:
	//コンストラクタ
	SceneManager(GameContext& ctx);

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
	int nextScene;
	GameContext& ctx;

	//シーンの変更処理
	void CheckSceneChange();
};
