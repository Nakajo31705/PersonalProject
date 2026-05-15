#include "DxLib.h"
#include "ImageManager.h"

/// <summary>
/// 画像データを読み込む、すでに読み込んでいるなら再利用する
/// </summary>
/// <param name="path">画像データのパス</param>
/// <returns>DxLibの画像ハンドル(失敗時は-1)</returns>
int ImageManager::Load(const std::string& key, const std::string& path)
{
    //すでに読み込んでいるか確認
    //２重ロード対策
    auto it = images.find(key);
    if (it != images.end())
    {
        it->second.refCount++;
        return it->second.handle;
    }

    //新規読み込み
    int handle = LoadGraph(path.c_str());
    if (handle == 1)
    {
        return -1;  //エラーなら-1を返す
    }

    //登録(保存)
    images[key] = { handle, 1 };

    return handle;
}

/// <summary>
/// 読み込み済みの画像のハンドルを取得
/// </summary>
/// <param name="path">画像データのパス</param>
/// <returns>画像ハンドル(存在しない場合は-1)</returns>
int ImageManager::Get(const std::string& key)
{
    auto it = images.find(key);
    if (it == images.end())
    {
        return -1;  //エラーなら-1を返す
    }
    return it->second.handle;
}

/// <summary>
/// 使用した画像のカウントを減らし、0になったら開放
/// </summary>
/// <param name="path">画像データのパス</param>
void ImageManager::Release(const std::string& key)
{
    auto it = images.find(key);
    if (it == images.end()) return;

    it->second.refCount--;

    if (it->second.refCount <= 0)
    {
        DeleteGraph(it->second.handle);
        images.erase(it);
    }
}

/// <summary>
/// ゲーム終了時に全画像リソースを開放
/// </summary>
void ImageManager::ReleaseAll()
{
    for (auto& pair : images)
    {
        DeleteGraph(pair.second.handle);
    }

    images.clear();
}
