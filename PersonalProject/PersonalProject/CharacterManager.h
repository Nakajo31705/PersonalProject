enum class CharacterType
{
	Hero,
	Castle
};

enum class CharacterState
{
	Wait,
	Walk,
	Attack,
	Dead,
};

struct Character
{
	CharacterType type;
	CharacterState state;
	int imageId;

	//ステータス
	int HP;
	int power;
	int speed;
	float Range;

	//描画関係
	float x;
	float y;
	float scale;
};

class ImageManager;

#include <vector>

class CharacterManager
{
public:
	CharacterManager(ImageManager* img);
	void Init();
	void Spawn(CharacterType type, float x, float y);
	void Update();
	void Draw();

	void CharacterAI();
	bool IsDead(const Character& c);

private:
	ImageManager* imageManager;
	std::vector<Character> characters;

	int heroImg = -1;
	int castleImg = -1;
};