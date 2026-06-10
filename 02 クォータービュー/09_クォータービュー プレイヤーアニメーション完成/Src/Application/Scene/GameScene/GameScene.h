#pragma once

#include"../BaseScene/BaseScene.h"

// 前方宣言
class Player;

class BackGround;

class GameScene : public BaseScene
{
public:

	GameScene() { Init(); }
	~GameScene() {}

private:

	void Event() override;
	void Init()  override;

	Math::Matrix m_mWorld;

	// プレイヤーの情報
	std::weak_ptr<Player> m_wpPlayer;
};

/*
 スマートポインタの種類は３つ

 shared_ptr … 複数のポインタでアドレスを所有できる
 　　　　　　　参照カウントが増減する、常にアクセス可能

 weak_ptr　 … shared_ptrのアドレスを保持できるが、アクセスする権利は無い
 　　　　　　　参照カウントが増減しない
			   一時的にshared_ptrへ格上げできる

 unique_ptr … １つのポインタでしかアドレスを所有できない
 */