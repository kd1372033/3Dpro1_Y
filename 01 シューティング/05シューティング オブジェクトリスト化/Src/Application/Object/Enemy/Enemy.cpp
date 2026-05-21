#include "Enemy.h"

void Enemy::Update()
{
	m_pos.y -= m_moveSpd;
	if (m_pos.y <= -360 - 32)
	{
		m_pos.y = 360 + 32;
	}
}

void Enemy::Draw()
{
	Math::Rectangle rc;
	rc = { 0,0,64,64 };
	// 2D描画
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_pos.x, m_pos.y, 64, 64, &rc);
	// テクスチャ,X座標,Y座標,幅,高さ,切り取り範囲
}

void Enemy::Init()
{
	m_tex.Load("Asset/Textures/Enemy.png");

	// x座標をランダムで取得
	float x = KdRandom::GetFloat(-640.0f, 640.0f);

	m_pos = {x,360.0f,0.0f};		//0,0で初期化
	m_aliveFlg = true;
}

void Enemy::Release()
{
	// テクスチャはKdTexture型のデストラクタで
	//　自動Releaseされるのでここでは特に何もしなくていい
}