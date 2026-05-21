#pragma once
#include "../BaseObject.h"

class Enemy : public BaseObject
{
public:
	Enemy() {}
	~Enemy()override { Release(); }

	void Update() override;
	void Draw()	  override;
	void Init()   override;

	// Hit時の処理　※派生先で挙動を変える！
	void OnHit()override;

private:

	void Release() override;

	const float m_moveSpd = 5.0f;
};

