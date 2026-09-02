#pragma once

#include"../WeaponBase.h"

class Pistol :public WeaponBase
{
public:
	Pistol()			{}
	~Pistol()  override {}

	void Init();
	void Update()override;

	// 弾発射関数
	void ShotBullet(const bool _rayFlg = false) override;

private:
	

};
