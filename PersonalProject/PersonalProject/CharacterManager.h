#include <vector>
#include <string>

/// <summary>
/// キャラクターの種類を表すenum
/// </summary>
enum class CharacterType
{
	Hero,
	Vampire,
	pCastle,
	eCastle,
};

/// <summary>
/// キャラクターの情報を表すenum
/// </summary>
enum class CharacterState
{
	Walk,
	Attack,
	Dead,
};

/// <summary>
/// キャラクターのステータスを持つ構造体
/// </summary>
struct CharacterData
{
	int imageId = -1;
	int HP = 0;
	int power = 0;
	float speed = 0;
	int range = 0;
	float waitTime = 0;
	bool player = true;
};

/// <summary>
/// キャラクターの描画や情報を持つ構造体
/// </summary>
struct Character
{
	CharacterType type;
	CharacterState state = CharacterState::Walk;
	const CharacterData* data;

	int currentHP = 0;
	float waitTimer = 0;
	bool isAttacking = false;
	bool player = true;

	//描画関係
	float x = 0;
	float y = 0;
	float scale = 0;
};

class ImageManager;

class CharacterManager
{
public:
	CharacterManager(ImageManager& img);
	void Init();
	void Spawn(CharacterType type, float x, float y, float scale);
	void Update();
	void Draw();

	//キャラクターの状態ごとの更新関数
	void UpdateDead();
	void UpdateWalk(Character& c);
	void UpdateAttack(Character& c);

	void CharacterAI(Character& c);
	Character* GetTarget(Character& c);
	bool IsDead(Character& c);
	void Attack(Character& c);
	void SetCharacterData(CharacterData& data, const std::string& imageName, int hp, int power, float speed, int range, float waitTime, bool player);
	void InitCharacterData();

private:
	ImageManager& imageManager;
	std::vector<Character> characters;

	//キャラクターのデータ
	CharacterData pCastleData;
	CharacterData eCastleData;
	CharacterData heroData;
	CharacterData vampireData;
};