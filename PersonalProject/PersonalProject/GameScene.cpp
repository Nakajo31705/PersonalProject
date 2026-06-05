#include "GameScene.h"
#include "SceneManager.h"
#include "ImageManager.h"
#include "Game.h"

//コンストラクタで初期化
GameScene::GameScene(GameContext& ctx, SceneManager& sm)
	:ctx(ctx), sm(sm)
{
}

void GameScene::Init()
{
	printfDx("Spawn called\n", 100, 100);
	ctx.charaManager.Spawn(CharacterType::Hero, 900, 500);
	ctx.charaManager.Spawn(CharacterType::Castle, 1200,500);
}

void GameScene::Update()
{
	RetrunTitle();
}

void GameScene::Draw()
{
	ImageDraw();

	DrawString(100, 100, "ゲームシーン", GetColor(255, 255, 255));
	DrawString(100, 120, "2を押してタイトルへ戻る", GetColor(255, 255, 0));
}

void GameScene::ImageDraw()
{
}

/// <summary>
/// 2キーを押してタイトルに戻る
/// </summary>
void GameScene::RetrunTitle()
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
