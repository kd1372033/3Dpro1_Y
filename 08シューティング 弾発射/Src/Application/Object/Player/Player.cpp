#include "Player.h"

#include "../../Scene/GameScene.h"
#include "../Bullet/Bullet.h"

void Player::Update()
{
	// 移動
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_pos.x -= 5;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_pos.x += 5;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_pos.y += 5;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_pos.y -= 5;
	}

	// 弾発射
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		// 弾１個分のインスタンスを生成 & 初期化してリストへ追加
		std::shared_ptr<Bullet> bullet;
		bullet = std::make_shared<Bullet>();	// ①生成
		bullet->Init();							// ②初期化
		bullet->SetPos(m_pos);
		m_owner->AddObject(bullet);				// ③リストへ追加

	}

	//===================================================================
	// 当たり判定　プレイヤー vs 敵
	//===================================================================
	for (auto& obj : m_owner->GetObjList())
	{
		// オブジェクトリストの中から「敵」とだけ当たり判定をする
		if (obj->GetObjType() == ObjectType::Enemy)
		{
			// 対象の座標（ベクトル） - 自分の座標（ベクトル） = 対象へのベクトル（矢印）
			Math::Vector3 v;
			v = obj->GetPos() - m_pos;

			// 球判定･･･ベクトルの長さで判定
			if (v.Length() < 64.0f)
			{
				// Hit時の処理を行う
				obj->OnHit();
			}
		}
	}

}

void Player::Draw()
{
	Math::Rectangle rc;
	rc = { 0,0,64,64 };
	// 2D描画
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_pos.x, m_pos.y, 64, 64, &rc);
	// テクスチャ,X座標,Y座標,幅,高さ,切り取り範囲
}

void Player::Init()
{
	m_tex.Load("Asset/Textures/player.png");
	m_pos = {};		//0,0で初期化
	m_aliveFlg = true;
	m_objType = ObjectType::Player;	// オブジェクトの種類は「プレイヤー」
}

void Player::Release()
{
	// テクスチャはKdTexture型のデストラクタで
	//　自動Releaseされるのでここでは特に何もしなくていい
}