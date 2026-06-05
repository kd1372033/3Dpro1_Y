#include "Player.h"

void Player::Init()
{
	// 板ポリにテクスチャ(マテリアル)をセット
	m_polygon.SetMaterial("Asset/Textures/player.png");

	// 板ポリの原点 (真ん中下段)
	m_polygon.SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	// アニメーション分割：横, 縦
	m_polygon.SetSplit(4, 8);

	// 座標・移動速度
	m_pos = {};
	m_speed = 0.1f;

	// 行列
	m_mWorld = Math::Matrix::Identity;
}

void Player::Update()
{
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_pos.z += m_speed;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_pos.z -= m_speed;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_pos.x -= m_speed;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_pos.x += m_speed;
	}

	// UV(切り取るコマ)を設定
	m_polygon.SetUVRect(0);

}
void Player::PostUpdate()
{
	// Update()で確定したパラメーターからワールド行列を作成
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = transMat;
}

void Player::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_mWorld);
}

void Player::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_mWorld);

}
