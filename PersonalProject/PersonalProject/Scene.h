#pragma once

//シーン関係の基底クラス
class Scene
{
public:
	virtual ~Scene() {}
	virtual void Init() {}
	virtual void Update() = 0;
	virtual void Draw() = 0;
};