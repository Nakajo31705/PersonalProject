#include <string>
#include <vector>

class ImageManager;

/// <summary>
/// マップのオブジェクトの種類を表すenum
/// </summary>
enum class MapObjectType
{
	pCastle,
	eCastle,
};

/// <summary>
/// マップオブジェクトの構造体
/// </summary>
struct MapObject
{
	MapObjectType type;

	int imageId;
	float x;
	float y;
	float scale;
};

class Map
{
public:
	Map(ImageManager& img);
	~Map();
	void Init();
	void Update();
	void Draw();

	void CreateMap(MapObjectType type, int x, int y);
	void SetMapdata(MapObject& data, const std::string& imageName);
	void InitMapdata();

private:
	ImageManager& imageManager;
	std::vector<MapObject> mapObjects;

	//オブジェクトデータ
	MapObject castle;
};