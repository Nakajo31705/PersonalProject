#include "DxLib.h"
#include "GameScene.h"
#include "SceneManager.h"
#include "ImageManager.h"
#include "EffectType.h"
#include "Game.h"

//コンストラクタで初期化
GameScene::GameScene(GameContext& ctx)
	:ctx(ctx)
	, charaManager(ctx.imageManager, effectManager)
	, map(ctx.imageManager)
	, effectManager(ctx.imageManager,charaManager)
	, gameManager(charaManager)
{
}

void GameScene::Init()
{
	gameManager.Init();
	map.Init();
	DrawMap();
	charaManager.Init();
}

void GameScene::Update()
{
	RetrunTitle();
	gameManager.Update();
	map.Update();
	charaManager.Update();
	effectManager.Update();
}

void GameScene::Draw()
{
	map.Draw();
	charaManager.Draw();
	effectManager.Draw();
	gameManager.Draw();

	DrawString(0, 0, "ゲームシーン", GetColor(255, 255, 255));
	DrawString(0, 20, "SPACEを押してタイトルへ戻る", GetColor(255, 255, 0));
}

/// <summary>
/// 2キーを押してタイトルに戻る
/// </summary>
void GameScene::RetrunTitle()
{
	static int oldKey = 0;
	int nowKey = CheckHitKey(KEY_INPUT_SPACE);

	//キーが入力されたらシーンの移動
	if (nowKey == 1 && oldKey == 0)
	{
		ctx.sceneManager.RequestSceneChange(0);//タイトルに戻る
	}

	oldKey = nowKey;

	//ゲームリザルト状態の時にリクエストが来たらタイトルへ戻る
	if (gameManager.GetReStart())
	{
		ctx.sceneManager.RequestSceneChange(0);
	}
}

/// <summary>
/// マップの描画
/// </summary>
void GameScene::DrawMap()
{
	map.CreateMap(MapObjectType::Sky, 700, 300, 0.8);
	map.CreateMap(MapObjectType::Ground_r, 1880, 735, 0.2);
	map.CreateMap(MapObjectType::Ground_l, 50, 735, 0.2);
	for (int i = 0; i < 18; i++)
	{
		map.CreateMap(MapObjectType::Ground_c, 150 + i * 100, 735, 0.2);
	}
}

void GameScene::DrawCharacter()
{
}

void GameScene::DrawUI()
{
}

void GameScene::DrawEffect()
{
}
