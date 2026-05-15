#include "DxLib.h"
#include "Game.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Game game;
	if (!game.Init())
		return -1;
	game.Run();
	return 0;				// ソフトの終了 
}