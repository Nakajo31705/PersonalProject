#include "AoudioManager.h"
#include "DxLib.h"

/// <summary>
/// 解放するための関数
/// </summary>
void AudioManager::Final()
{
    for (auto& pair : handles)
    {
        DeleteSoundMem(pair.second);
    }

    handles.clear();
}

/// <summary>
/// SEをロードする関数
/// </summary>
/// <param name="id">ロードするSEのIDを設定</param>
/// <param name="path">ロードするSEのパスを名前で設定</param>
/// <returns></returns>
bool AudioManager::LoadSE(SoundID id, const std::string& path)
{
    int handle = LoadSoundMem(path.c_str());

    if (handle == -1)
        return false;

    handles[id] = handle;
    return true;
}

/// <summary>
/// 音声を再生するための関数
/// </summary>
/// <param name="id">再生するSEのIDを入力</param>
void AudioManager::PlaySE(SoundID id)
{
    auto it = handles.find(id);

    if (it == handles.end())
        return;

    PlaySoundMem(it->second, DX_PLAYTYPE_BACK);
}
