#include "GameScene.h"
#include "SceneManager.h"
#include "ImageManager.h"

//コンストラクタで初期化
GameScene::GameScene(GameContext& ctx, SceneManager& sm)
	:ctx(ctx), sm(sm)
{
}

void GameScene::Init()
{

}

void GameScene::Update()
{
	static int oldKey = 0;
	int nowKey = CheckHitKey(KEY_INPUT_2);

	//キーが入力されたらシーンの移動
	if (nowKey == 1 && oldKey == 0)
	{
		ctx.sceneManager.RequestSceneChange(0);//タイトルに戻る
	}

	oldKey = nowKey;
}

void GameScene::Draw()
{
	ImageDraw();

	DrawString(100, 100, "ゲームシーン", GetColor(255, 255, 255));
	DrawString(100, 120, "2を押してタイトルへ戻る", GetColor(255, 255, 0));
}

void GameScene::ImageDraw()
{
	//No.1
	int monster = ctx.imageManager.Get("Hero");
	if (monster == -1)
	{
		DrawString(10, 750, "読み込み失敗", GetColor(255, 255, 255));
	}
	DrawRotaGraph(
		200, 300,
		0.2,
		0,
		monster,
		TRUE
	);
}
