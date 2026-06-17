#include <string>
#include <vector>
#include "EffectType.h"

class ImageManager;
class CharacterManager;
struct Character;

struct EffectData
{
	EffectType type;
	int imageId;
	float x, y;
	float scale;
	float angle;
	int alpha;
	int life;
	int damage;
	bool player;
	bool isHit;
};

class EffectManager
{
public:
	EffectManager(ImageManager& img, CharacterManager& charaManager);
	~EffectManager();
	void Update();
	void Draw();

	void InitEffectData();
	void SpawnEffect(EffectType type, Character& chara, float x, float y, float scale, float angle, int alpha, bool isHit);
	void SetEffectData(EffectData& data, const std::string& imageName, int life);
	void CheckHit(EffectData& effect);
	void RemoveEffect();
private:
	ImageManager& imageManager;
	CharacterManager& charaManager;
	std::vector<EffectData> effects;

	EffectData  attack_effect;
	EffectData  cut_left;
	EffectData  cut_right;
	EffectData  fire_left;
	EffectData  fire_right;
	EffectData  hit;
};