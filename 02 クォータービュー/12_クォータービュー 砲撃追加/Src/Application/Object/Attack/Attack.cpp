#include "Attack.h"

void Attack::Update()
{
	// アニメーション更新
	m_polygon->SetUVRect((int)m_animeCnt);	// UV座標を設定
	m_animeCnt += m_animeSpeed;				// カウント更新

	// アニメーションが終了したら消滅　※リストから除外
	if (m_animeCnt >= 9)
	{
		m_isExpired = true;
	}
}

void Attack::DrawEffect()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon
	(*m_polygon, m_mWorld);
}

void Attack::Init()
{
	m_polygon = std::make_shared<KdSquarePolygon>();

	// 板ポリにテクスチャ(マテリアル)をロード
	m_polygon->SetMaterial("Asset/Textures/Attack.png");

	// 板ポリの原点 (真ん中下段を指定)
	m_polygon->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	// アニメーション分割数：横, 縦
	m_polygon->SetSplit(9, 1);

	// アニメーション初期値
	m_animeCnt   = 0;
	m_animeSpeed = 1.0f;

	// 攻撃判定のエリア
	m_attackArea = 0.3f;

	// 単位行列
	m_mWorld = Math::Matrix::Identity;

	// デバッグワイヤー生成
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}
