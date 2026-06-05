#pragma once

#include"../BaseScene/BaseScene.h"

class BackGround;

class GameScene : public BaseScene
{
public :

	GameScene()  { Init(); }
	~GameScene() {}

private:

	void Event() override;
	void Init()  override;

	Math::Matrix m_mWorld;
};
