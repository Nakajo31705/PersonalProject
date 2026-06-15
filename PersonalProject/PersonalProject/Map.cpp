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

void Map::CreateMap(MapObjectType type, int x, int y, float scale)
{
	MapObject obj;
	obj.type = type;
	obj.x = x;
	obj.y = y;
	obj.scale = scale;

	switch (type)
	{
	case MapObjectType::pCastle:
		SetMapData(obj, "Castle");
		break;
	case MapObjectType::eCastle:
		SetMapData(obj, "Castle");
		break;
	case MapObjectType::Sky:
		SetMapData(obj, "Sky");
		break;
	case MapObjectType::Ground_c:
		SetMapData(obj, "Ground_c");
		break;
	case MapObjectType::Ground_l:
		SetMapData(obj, "Ground_l");
		break;
	case MapObjectType::Ground_r:
		SetMapData(obj, "Ground_r");
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
void Map::SetMapData(MapObject& data, const std::string& imageName)
{
	data.imageId = imageManager.Get(imageName);
}

/// <summary>
/// マップオブジェクトの初期化
/// </summary>
void Map::InitMapdata()
{
	//自分の城のマップデータを設定
	SetMapData(castle, "Castle");
	SetMapData(sky, "Sky");
	SetMapData(ground_c, "Ground_c");
	SetMapData(ground_l, "Ground_l");
	SetMapData(ground_r, "Ground_r");
}


