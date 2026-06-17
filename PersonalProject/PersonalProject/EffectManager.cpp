#include "DxLib.h"
#include "EffectManager.h"
#include "ImageManager.h"
#include "CharacterManager.h"

EffectManager::EffectManager(ImageManager& img, CharacterManager& charaManager)
	:imageManager(img)
	,charaManager(charaManager)
{
	InitEffectData();
}

EffectManager::~EffectManager()
{
}

void EffectManager::Update()
{
	for (auto& effect : effects)
	{
		CheckHit(effect);
		if (effect.isHit)
		{
			effect.life--;
		}
	}
	RemoveEffect();
}

void EffectManager::Draw()
{
	for (const auto& e : effects)
	{
		if (e.imageId == -1) continue;

		DrawRotaGraph(
			(int)e.x,
			(int)e.y,
			e.scale,
			0,
			e.imageId,
			TRUE
		);
	}
}

/// <summary>
/// エフェクトデータの初期化
/// </summary>
void EffectManager::InitEffectData()
{
	SetEffectData(attack_effect, "AttackEffect", 10);
	SetEffectData(cut_left, "CutLeft", 10);
	SetEffectData(cut_right, "CutRight", 10);
	SetEffectData(fire_left, "FireLeft", 10);
	SetEffectData(fire_right, "FireRight", 10);
	SetEffectData(hit, "Hit", 10);
}

/// <summary>
/// エフェクトの生成
/// </summary>
/// <param name="type">エフェクトの名前</param>
/// <param name="chara">攻撃力を取得するキャラクターを設定</param>
/// <param name="x">生成座標X</param>
/// <param name="y">生成座標Y</param>
/// <param name="scale">サイズ</param>
/// <param name="angle">角度</param>
/// <param name="alpha">透明度</param>
/// <param name="life">出現時間</param>
void EffectManager::SpawnEffect(EffectType type, Character& chara, float x, float y, float scale, float angle, int alpha, bool isHit)
{
	EffectData effect;
	effect.type = type;
	effect.x = x;
	effect.y = y;
	effect.scale = scale;
	effect.angle = angle;
	effect.alpha = alpha;
	effect.player = chara.player;
	effect.isHit = isHit;

	switch (type)
	{
	case EffectType::Attack_effect:
		SetEffectData(effect, "AttackEffect", 10);
		break;
	case EffectType::Cut_left:
		SetEffectData(effect, "CutLeft", 10);
		break;
	case EffectType::Cut_right:
		SetEffectData(effect, "CutRight", 10);
		break;
	case EffectType::Fire_left:
		SetEffectData(effect, "FireLeft", 10);
		break;
	case EffectType::Fire_right:
		SetEffectData(effect, "FireRight", 10);
		break;
	case EffectType::Hit:
		SetEffectData(effect, "Hit", 10);
		break;
	}

	//攻撃力をキャラクターから取得
	effect.damage = chara.data->power;

	effects.push_back(effect);
}

/// <summary>
/// エフェクトの名前を設定
/// </summary>
/// <param name="data">エフェクトデータの構造体を入力</param>
/// <param name="imageName">名前を入力</param>
void EffectManager::SetEffectData(EffectData& data, const std::string& imageName, int life)
{
	data.imageId = imageManager.Get(imageName);
	data.life = life;
}

/// <summary>
/// エフェクトがヒットしたときの処理
/// </summary>
/// <param name="effect"></param>
void EffectManager::CheckHit(EffectData& effect)
{
	//ターゲットの取得
	Character* target = charaManager.GetHitTarget(effect);
	if (target == nullptr) return;

	if (!effect.isHit)
	{
		//敵に攻撃
		charaManager.TakeDamage(*target, effect.damage);

		//エフェクトが当たったら攻撃判定を削除
		effect.isHit = true;
	}
}

/// <summary>
/// エフェクト削除の処理
/// </summary>
/// <param name="effect">エフェクトの構造体を入力</param>
void EffectManager::RemoveEffect()
{
	effects.erase(
		std::remove_if(
			effects.begin(),
			effects.end(),
			[](const EffectData& effect)
			{
				return effect.life <= 0;
			}),
		effects.end());
}
