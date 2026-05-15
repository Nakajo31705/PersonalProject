#include "GameScene.h"
#include "SceneManager.h"
#include "ImageManager.h"

//コンストラクタで初期化
GameScene::GameScene(SceneManager& sm, ImageManager* imgmg, GameManager* gm)
	:sceneManager(sm),
	imageManager(imgmg),
	gameManager(gm)
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
		sceneManager.RequestSceneChange(0);//タイトルに戻る
	}

	oldKey = nowKey;
}

void GameScene::Draw()
{
	//ImageManagerのnullチェック
	if (imageManager == nullptr)
		DrawString(10, 700, "ImageManagerがnullです", GetColor(255, 255, 255));
	else
		DrawString(10, 700, "ImageManagerがあります", GetColor(255, 255, 255));

	ImageDraw();

	DrawString(100, 100, "ゲームシーン", GetColor(255, 255, 255));
	DrawString(100, 120, "2を押してタイトルへ戻る", GetColor(255, 255, 0));
}

void GameScene::ImageDraw()
{
	//モンスター１
	int monster = imageManager->Get("Monster");
	if (monster == -1)
	{
		DrawString(10, 750, "読み込み失敗", GetColor(255, 255, 255));
	}
	DrawRotaGraph(
		200, 300,
		0.1,
		0,
		monster,
		TRUE
	);
}
