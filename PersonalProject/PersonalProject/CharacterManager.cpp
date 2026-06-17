#include "DxLib.h"
#include "CharacterManager.h"
#include "ImageManager.h"
#include "EffectManager.h"

CharacterManager::CharacterManager(ImageManager& img, EffectManager& effect)
	:imageManager(img)
	,effectManager(effect)
{
	InitCharacterData();
}

/// <summary>
/// キャラクター再初期化用
/// </summary>
void CharacterManager::Init()
{
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

	UpdateDead();
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
			"[%d] x=%.1f HP=%d State=%d player=% speed=%f",
			i,
			characters[i].x,
			characters[i].currentHP,
			(int)characters[i].state),
			characters[i].player,
			characters[i].data->speed;
	}
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
	SetCharacterData(heroData, "Hero", 20, 1, 1, 500, 5, true);
	SetCharacterData(vampireData, "Vampire", 150, 1, 1, 250, 5, false);
	SetCharacterData(pCastleData, "pCastle", 500, 0, 0, 0, 0, true);
	SetCharacterData(eCastleData, "eCastle", 500, 0, 0, 0, 0, false);
}

/// <summary>
/// キャラクターの生成
/// </summary>
/// <param name="type">キャラクターの名前</param>
/// <param name="x">生成するX座標</param>
/// <param name="y">生成するX座標</param>
void CharacterManager::Spawn(CharacterType type, EffectType effect, float x, float y,float scale)
{
	Character c;
	const CharacterData* data = nullptr;
	c.type = type;
	c.effect = effect;
	c.x = x;
	c.y = y;
	c.scale = scale;

	switch (type)
	{
	case CharacterType::Hero:
		c.data = &heroData;
		c.effect = EffectType::Cut_left;
		break;
	case CharacterType::Vampire:
		c.data = &vampireData;
		c.effect = EffectType::Fire_right;
		break;
	case CharacterType::pCastle:
		c.data = &pCastleData;
		c.effect = EffectType::None;
		break;
	case CharacterType::eCastle:
		c.data = &eCastleData;
		c.effect = EffectType::None;
		break;
	}

	c.currentHP = c.data->HP;
	c.player = c.data->player;

	characters.push_back(c);
}

/// <summary>
/// キャラクターが死亡しているときの処理
/// </summary>
/// <param name="c"></param>
void CharacterManager::UpdateDead()
{
	characters.erase(
		std::remove_if(
			characters.begin(),
			characters.end(),
			[](const Character& c)
			{ return c.state == CharacterState::Dead; }
		),
		characters.end());
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
	//ターゲットの取得
	Character* target = GetTarget(c);

	//ターゲットがいないときは歩く状態にする
	if (target == nullptr)
	{
		c.state = CharacterState::Walk;
		return;
	}
	//ターゲットとの距離を取得
	float distane = abs(target->x - c.x);

	//ターゲットとの距離が攻撃範囲より大きいときは歩く状態にする
	if (distane > c.data->range)
	{
		c.state = CharacterState::Walk;
	}
	else
	{
		//攻撃してないときは攻撃する
		if (!c.isAttacking)
		{
			Attack(c);
		}
		else
		{
			//攻撃した後なら攻撃のクールタイムを減らす
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
		break;
	}
}

/// <summary>
/// 一番近い敵との距離を取得する関数
/// </summary>
/// <param name="c"></param>
Character* CharacterManager::GetTarget(Character& c)
{
	Character* nearTarget = nullptr;
	float nearDistance = FLT_MAX;

	for (auto& target : characters)
	{
		if (&target == &c) continue;
		if (target.player == c.player) continue;

		float distance = abs(target.x - c.x);

		if (distance < nearDistance)
		{
			nearDistance = distance;
			nearTarget = &target;
		}
	}

	return nearTarget;
}

/// <summary>
/// エフェクトが敵と接触したか確認する関数
/// </summary>
/// <param name="effect">エフェクトデータの構造体を入力</param>
/// <returns></returns>
Character* CharacterManager::GetHitTarget(EffectData& effect)
{
	Character* nearTarget = nullptr;
	float nearDistance = FLT_MAX;

	for (auto& target : characters)
	{
		if (target.player == effect.player) continue;

		float distance = abs(target.x - effect.x);

		if (distance < nearDistance)
		{
			nearDistance = distance;
			nearTarget = &target;
		}
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
	if (target == nullptr) return;

	if (IsDead(c))
	{
		c.state = CharacterState::Walk;
		return;
	}

	//ここでエフェクトを生成
	effectManager.SpawnEffect(c.effect, c, target->x, target->y, 0.2, 0, 1, false);

	c.isAttacking = true;
	//攻撃のクールタイムをリセット
	c.waitTimer = c.data->waitTime;
	c.state = CharacterState::Attack;
}

/// <summary>
/// 攻撃を受ける処理
/// </summary>
/// <param name="target">ダメージを受けるターゲットの設定</param>
/// <param name="damage">攻撃力を設定</param>
void CharacterManager::TakeDamage(Character& target, int damage)
{
	target.currentHP -= damage;
}
