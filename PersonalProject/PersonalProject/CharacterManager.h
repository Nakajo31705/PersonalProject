enum class CharacterType
{
	Hero,
	Vampire
};

struct Character
{
	CharacterType type;
	int imageId;

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

private:
	ImageManager* imageManager;
	std::vector<Character> characters;

	int heroImg = -1;
	int vampireImg = -1;
};