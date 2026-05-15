#include "TitleScene.h"
#include "SceneManager.h"

//コンストラクタで初期化
TitleScene::TitleScene(SceneManager& sm)
	:sceneManager(sm)
{
}

void TitleScene::Init()
{
}

void TitleScene::Update()
{
	static int oldKey = 0;
	int nowKey = CheckHitKey(KEY_INPUT_1);

	//キーが押されたらシーンの移動
	if (nowKey == 1 && oldKey == 0)
	{
		sceneManager.RequestSceneChange(1);//ゲーム画面へ
	}

	oldKey = nowKey;
}

void TitleScene::Draw()
{
	DrawString(100, 100, "タイトル", GetColor(255, 255, 255));
	DrawString(100, 120, "１を押してゲームスタート", GetColor(255, 255, 0));
}