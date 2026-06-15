#include <string>
#include <vector>

class ImageManager;

enum class EffectType
{
	Attack_effect,
	Cut_left,
	Cut_right,
	Fire_left,
	Fire_right,
	Hit
};

struct EffectData
{
	EffectType type;
	float x, y;
	float scale;
	float angle;
	int alpha;
	int life;
};

class EffectManager
{
public:
	EffectManager();
	~EffectManager();
	void Update();
	void Draw();
private:

};