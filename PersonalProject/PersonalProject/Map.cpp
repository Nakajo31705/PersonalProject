#include "Map.h"
#include "ImageManager.h"
#include <DxLib.h>

Map::Map(ImageManager& img)
	:imageManager(img)
{
	InitMapdata();
}

/// <summary>
/// マップのデストラクタ
/// </summary>
Map::~Map()
{
}

/// <summary>
/// マップの再初期化用
/// </summary>
void Map::Init()
{
}

void Map::Update()
{
}



void Map::Draw()
{
	for (const auto& obj : mapObjects)
	{
		if (obj.imageId == -1) continue;
		DrawRotaGraph(
			(int)obj.x,
			(int)obj.y,
			obj.scale,
			0,
			obj.imageId,
			TRUE
		);
	}
}

void Map::CreateMap(MapObjectType type, int x, int y)
{
	MapObject obj;
	obj.type = type;
	obj.x = x;
	obj.y = y;
	obj.scale = 0.2f;

	switch (type)
	{
	case MapObjectType::pCastle:
		SetMapdata(obj, "Castle");
		break;
	case MapObjectType::eCastle:
		SetMapdata(obj, "Castle");
		break;
	}

	mapObjects.push_back(obj);
}

/// <summary>
/// マップデータの設定関数
/// </summary>
/// <param name="data">マップのオブジェクトの構造体を入力</param>
/// <param name="imageName">オブジェクト名を入力</param>
/// <param name="x">配置するX座標を入力</param>
/// <param name="y">配置するY座標を入力</param>
/// <param name="scale">オブジェクトの大きさを入力</param>
void Map::SetMapdata(MapObject& data, const std::string& imageName)
{
	data.imageId = imageManager.Get(imageName);
}

/// <summary>
/// マップオブジェクトの初期化
/// </summary>
void Map::InitMapdata()
{
	//自分の城のマップデータを設定
	SetMapdata(castle, "Castle");
}


