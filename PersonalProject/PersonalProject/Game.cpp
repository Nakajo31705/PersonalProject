#include <DxLib.h>
#include "Game.h"

Game::Game()
    : imageManager(),
    sceneManager(&imageManager,&gameManager),
    gameManager()
{
}

/// <summary>
/// 初期化処理
/// </summary>
/// <returns>初期化が成功した場合はtrue、失敗した場合はfalse</returns>
bool Game::Init()
{
    //---ウィンドウ設定---
    int winWidth = 1920;
    int winHeight = 1080;
    int bitColor = 0;
    SetGraphMode(winWidth, winHeight, bitColor);
    ChangeWindowMode(TRUE);

    //DxLib初期化
    if (DxLib_Init() == -1)
        return false;

    SetDrawScreen(DX_SCREEN_BACK);

    InitImage();
    sceneManager.Init();
    gameManager.Init();

    isRunning = true;
    return true;
}

/// <summary>
/// ゲーム全体の実行ループ
/// 初期化→メインループ→終了処理の流れを管理
/// </summary>
void Game::Run()
{
    //初期化できていないときはゲームを開始しない
    if (!Init())
    {
        return;
    }

    while (isRunning && ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        ProcessInput(); //入力処理
        Update();       //状態更新
        Render();       //描画
    }

    //ゲーム終了処理
    if (!isRunning)
    {
        ShutDown();
    }
}

//ゲームの終了処理
void Game::ShutDown()
{
    DxLib_End();
}

/// <summary>
/// 表示する画像などの初期化
/// </summary>
void Game::InitImage()
{
    imageManager.Load("Monster", "Data/Monster.png");
}

/// <summary>
/// 入力状態の取得
/// ESCを押してゲームループを抜ける(ゲーム終了)
/// </summary>
void Game::ProcessInput()
{
    if (CheckHitKey(KEY_INPUT_ESCAPE))
    {
        isRunning = false;
    }
}

/// <summary>
/// ゲームの状態更新処理
/// </summary>
void Game::Update()
{
    sceneManager.Update();
    gameManager.Update();
}

/// <summary>
/// 描画の処理
/// </summary>
void Game::Render()
{
    ClearDrawScreen();
    sceneManager.Draw();
    gameManager.Draw();
    ScreenFlip();
}
