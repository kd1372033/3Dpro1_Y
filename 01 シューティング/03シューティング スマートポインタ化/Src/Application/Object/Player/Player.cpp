#include "Player.h"

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
}

void Player::Draw()
{
	Math::Rectangle rc;
	rc = { 0,0,64,64};
	// 2D描画
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_pos.x, m_pos.y,64,64, &rc);
	// テクスチャ,X座標,Y座標,幅,高さ,切り取り範囲
}

void Player::Init()
{
	m_tex.Load("Asset/Textures/player.png");
	m_pos = {};		//0,0で初期化
	m_aliveFlg = true;
}

void Player::Release()
{
	// テクスチャはKdTexture型のデストラクタで
	//　自動Releaseされるのでここでは特に何もしなくていい
}