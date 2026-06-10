#include "Enemy.h"

void Enemy::Init()
{
	m_polygon = std::make_shared<KdSquarePolygon>();

	m_polygon->SetMaterial("Asset/Textures/Enemy.png");

	// 板ポリの基準点 (真ん中下段を指定)
	m_polygon->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	// アニメーション分割数：横, 縦
	m_polygon->SetSplit(6, 6);

	// アニメーション初期値
	m_animeCnt = 0;
	m_animeSpeed = 0.1f;

	// 座標・方向・移動速度
	m_pos = {};
	m_dir = {};
	m_speed = 0.05f;

	// 行列
	m_mWorld = Math::Matrix::Identity;

	// デバッグワイヤー生成
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void Enemy::Update()
{
	// アニメーション更新
	int walk[4] = { 3,4,3,5 };						// 使用するコマの配列
	m_polygon->SetUVRect(walk[(int)m_animeCnt]);	// UV座標を設定
	m_animeCnt += m_animeSpeed;						// カウント更新

	// アニメーションをループ
	if (m_animeCnt >= 4)
	{
		m_animeCnt = 0;
	}
}

void Enemy::PostUpdate()
{
	// Update()で確定したパラメーターから座標行列を作成
	m_mWorld = Math::Matrix::CreateTranslation(m_pos);
}

void Enemy::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);

}

void Enemy::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);

}