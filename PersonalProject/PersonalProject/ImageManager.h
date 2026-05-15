#pragma once
#include <unordered_map>
#include <string>

class ImageManager
{
public:
	int Load(const std::string& key, const std::string& path);
	int Get(const std::string& key);
	void Release(const std::string& key);
	void ReleaseAll();
private:
	//画像データの構造体
	struct ImageData
	{
		int handle;		//画像の識別番号
		int refCount;	//画像の使用回数
	};

	std::unordered_map<std::string, ImageData> images;
};