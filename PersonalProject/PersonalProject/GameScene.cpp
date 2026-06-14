#include "DxLib.h"
#include "GameScene.h"
#include "SceneManager.h"
#include "ImageManager.h"
#include "Game.h"

//コンストラクタで初期化
GameScene::GameScene(GameContext& ctx)
	:ctx(ctx)
	, charaManager(ctx.imageManager)
	, map(ctx.imageManager)
{
}

void GameScene::Init()
{
	charaManager.Init();
	map.Init();
	charaManager.Spawn(CharacterType::Vampire, ePosX, ePosY);
}

void GameScene::Update()
{
	RetrunTitle();
	charaManager.Update();
	map.Update();

	if (CheckHitKey(KEY_INPUT_3))
	{
		charaManager.Spawn(CharacterType::Hero, pPosX, pPosY + 10);
	}
}

void GameScene::Draw()
{
	
	map.Draw();
	charaManager.Draw();

	map.CreateMap(MapObjectType::pCastle, pPosX, pPosY);
	map.CreateMap(MapObjectType::pCastle, ePosX, ePosY);

	DrawString(100, 100, "ゲームシーン", GetColor(255, 255, 255));
	DrawString(100, 120, "2を押してタイトルへ戻る", GetColor(255, 255, 0));
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
