#include "DxLib.h"
#include "CharacterManager.h"
#include "ImageManager.h"

CharacterManager::CharacterManager(ImageManager& img)
	:imageManager(img)
{
	InitCharacterData();
}

/// <summary>
/// キャラクター再初期化用
/// </summary>
void CharacterManager::Init()
{
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
	const CharacterData* data = nullptr;
	c.type = type;
	c.x = x;
	c.y = y;
	c.scale = 0.2f;

	switch (type)
	{
	case CharacterType::Hero:
		c.data = &heroData;
		break;
	case CharacterType::Vampire:
		c.data = &vampireData;
		break;
	}

	c.currentHP = c.data->HP;
	c.player = c.data->player;

	characters.push_back(c);
}

void CharacterManager::Update()
{
	for (auto& c : characters)
	{
		if (IsDead(c))
		{
			c.state = CharacterState::Dead;
			continue;
		}

		CharacterAI(c);
	}
}

/// <summary>
/// 配列に保存されているキャラクターを描画する
/// </summary>
void CharacterManager::Draw()
{
	for (const auto& c : characters)
	{
		if (c.data->imageId == -1) continue;

		DrawRotaGraph(
			(int)c.x,
			(int)c.y,
			c.scale,
			0,
			c.data->imageId,
			TRUE
		);
	}

	DrawFormatString(
		100,
		150,
		GetColor(255, 255, 255),
		"キャラクター数: %d",
		(int)characters.size());

	for (int i = 0; i < characters.size(); i++)
	{
		DrawFormatString(
			100,
			170 + i * 20,
			GetColor(255, 255, 255),
			"[%d] x=%.1f HP=%d State=%d player=%d",
			i,
			characters[i].x,
			characters[i].currentHP,
			(int)characters[i].state),
			characters[i].player;
	}

}

/// <summary>
/// キャラクターが死亡しているときの処理
/// </summary>
/// <param name="c"></param>
void CharacterManager::UpdateDead(Character& c)
{
	if (IsDead(c))
	{
		c.state = CharacterState::Dead;
		return;
	}

	c.state = CharacterState::Walk;
}

/// <summary>
/// キャラクターが歩いているときの処理
/// </summary>
/// <param name="c"></param>
void CharacterManager::UpdateWalk(Character& c)
{
	Character* target = GetTarget(c);
	
	if (target != nullptr)
	{
		float distane = abs(target->x - c.x);
		if (distane <= c.data->range)
		{
			c.state = CharacterState::Attack;
		}
	}

	if (c.player)
	{
		c.x -= c.data->speed;
	}
	else
	{
		c.x += c.data->speed;
	}
}

/// <summary>
/// キャラクターが攻撃しているときの処理
/// </summary>
/// <param name="c"></param>
void CharacterManager::UpdateAttack(Character& c)
{
	Character* target = GetTarget(c);
	float distane = abs(target->x - c.x);

	if (distane > c.data->range)
	{
		c.state = CharacterState::Walk;
	}
	else
	{
		if (!c.isAttacking)
		{
			Attack(c);
		}
		else
		{
			c.waitTimer--;
			if (c.waitTimer <= 0)
			{
				c.isAttacking = false;
			}
		}
	}
}

/// <summary>
/// キャラクターのAI処理
/// </summary>
void CharacterManager::CharacterAI(Character& c)
{
	switch (c.state)
	{
	case CharacterState::Walk:
		UpdateWalk(c);
		break;
	case CharacterState::Attack:
		UpdateAttack(c);
		break;
	case CharacterState::Dead:
		UpdateDead(c);
		break;
	}
}

/// <summary>
/// 敵との距離を取得する関数
/// </summary>
/// <param name="c"></param>
Character* CharacterManager::GetTarget(Character& c)
{
	Character* nearTarget = nullptr;

	for (auto& target : characters)
	{
		if (&target == &c) continue;
		if (target.player == c.player) continue;

		nearTarget = &target;
	}

	return nearTarget;
}

/// <summary>
/// 死亡処理
/// </summary>
/// <returns></returns>
bool CharacterManager::IsDead(Character& c)
{
	return c.currentHP <= 0;
}

/// <summary>
/// 攻撃処理
/// </summary>
/// <param name="c"></param>
void CharacterManager::Attack(Character& c)
{
	Character* target = GetTarget(c);

	if (IsDead(c))
	{
		c.state = CharacterState::Dead;
		return;
	}

	//攻撃処理
	target->currentHP -= c.data->power;
	c.isAttacking = true;
	//攻撃のクールタイムをリセット
	c.waitTimer = c.data->waitTime;
	c.state = CharacterState::Attack;
}

/// <summary>
/// キャラクターのステータスを設定する関数
/// </summary>
/// <param name="data">表示するキャラクターの構造体</param>
/// <param name="data">表示するキャラクターの名前を入力</param>
/// <param name="hp">HPを入力</param>
/// <param name="power">攻撃力を入力</param>
/// <param name="speed">移動速度を入力</param>
/// <param name="range">射程を入力</param>
/// /// <param name="waitTime">攻撃硬直時間を入力</param>
/// /// <param name="player">プレイヤー陣営かどうかのフラグ</param>
void CharacterManager::SetCharacterData(CharacterData& data, const std::string& imageName, int hp, int power, float speed, int range, float waitTime, bool player)
{
	data.imageId = imageManager.Get(imageName);
	data.HP = hp;
	data.power = power;
	data.speed = speed;
	data.range = range;
	data.waitTime = waitTime;
	data.player = player;
}

/// <summary>
/// キャラクターデータの初期化
/// 構造体、キャラクター名、HP、攻撃力、移動速度、射程を入力
/// </summary>
void CharacterManager::InitCharacterData()
{
	//勇者のデータを初期化
	SetCharacterData(heroData, "Hero", 100, 1, 1, 3, 3, true);
	SetCharacterData(vampireData, "Vampire", 150, 15, 1, 2, 5, false);
}
