#pragma once
#include <string>
#include <unordered_map>

enum class SoundID
{
	Damage,
	Slash,
	Magic,
	Hit,
};

class AudioManager
{
public:
	void Final();
	bool LoadSE(SoundID id, const std::string& path);
	void PlaySE(SoundID id);

private:
	std::unordered_map<SoundID, int> handles;
};