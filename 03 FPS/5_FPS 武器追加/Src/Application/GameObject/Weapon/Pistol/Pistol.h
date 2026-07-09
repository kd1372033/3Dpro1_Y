#pragma once

#include"../WeaponBase.h"

class Pistol :public WeaponBase
{
public:
	Pistol()			{}
	~Pistol()  override {}

	void Init();
	void Update()override;

private:
	

};
