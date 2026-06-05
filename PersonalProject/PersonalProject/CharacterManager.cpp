#include "DxLib.h"
#include "CharacterManager.h"
#include "ImageManager.h"

CharacterManager::CharacterManager(ImageManager* img)
	:imageManager(img)
{
}

/// <summary>
/// キャラクターを初期化
/// </summary>
void CharacterManager::Init()
{
	heroImg = imageManager->Get("Hero");
	castleImg = imageManager->Get("Castle");
}

/// <summary>
/// キャラクターの生成
/// </summary>
/// <param name="type">キャラクターの名前</param>
/// <param name="x">生成するX座標</param>
/// <param name="y">生成するX座標</param>
void CharacterManager::Spawn(CharacterType type, float x, float y)
{
	Character c;
	c.type = type;
	c.x = x;
	c.y = y;
	c.scale = 0.2f;

	if (type == CharacterType::Hero)
		c.imageId = heroImg;
	if(type == CharacterType::Castle)
		c.imageId = castleImg;


	//勇者のステータス
	if (type == CharacterType::Hero)
	{
		c.HP = 100;
		c.power = 20;
		c.speed = 5;
		c.Range = 20;
	}

	characters.push_back(c);
}

void CharacterManager::Update()
{
}

/// <summary>
/// 配列に保存されているキャラクターを描画する
/// </summary>
void CharacterManager::Draw()
{
	for (const auto& c : characters)
	{
		if (c.imageId == -1) continue;

		DrawRotaGraph(
			(int)c.x,
			(int)c.y,
			c.scale,
			0,
			c.imageId,
			TRUE
		);
	}
}

/// <summary>
/// キャラクターのAI処理
/// </summary>
void CharacterManager::CharacterAI()
{
	for (auto& c : characters)
	{

		//勇者のAI
		if (c.type == CharacterType::Hero)
		{
			switch (c.state)
			{
			case CharacterState::Wait:
				break;
			case CharacterState::Walk:
					break;
			case CharacterState::Attack:
				break;
			case CharacterState::Dead:
				break;
			}
		}
	}
}

/// <summary>
/// 死亡処理
/// </summary>
/// <returns></returns>

bool CharacterManager::IsDead(const Character& c)
{
	return c.HP <= 0;
}