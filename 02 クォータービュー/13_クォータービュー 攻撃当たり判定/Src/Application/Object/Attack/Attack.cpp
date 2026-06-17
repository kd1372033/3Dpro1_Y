#include "Attack.h"
#include"../../Scene/SceneManager.h"

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

	// ======================================
// 当たり判定 ・・・ 球判定　ここから
// ======================================

// 球判定用の変数作成
	KdCollider::SphereInfo sphereInfo;

	// 球の中心位置を設定
	sphereInfo.m_sphere.Center = GetPos() + Math::Vector3(0, 0.5f, 0);

	// 球の半径を設定
	sphereInfo.m_sphere.Radius = m_attackArea;

	// 当たり判定をしたいタイプを設定
	sphereInfo.m_type = KdCollider::TypeDamage;

	// デバッグ用
	m_pDebugWire->AddDebugSphere
	(
		sphereInfo.m_sphere.Center,
		sphereInfo.m_sphere.Radius,
		kRedColor
	);
	// 球情報と当たり判定
	bool hit = false;
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		// 戻り値 … 当たっていたら true
		hit = obj->Intersects(sphereInfo, nullptr);

		// 攻撃が当たった場合
		if (hit)
		{
			// Hit時の相手オブジェクトの処理
			obj->OnHit();

			// Hit時の自分の処理
			OnHit();

			// ループから抜ける
			break;
		}
	}

	// ======================================
	// 当たり判定 ・・・ 球判定　ここまで
	// ======================================

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
	m_animeCnt = 0;
	m_animeSpeed = 1.0f;

	// 攻撃判定のエリア
	m_attackArea = 0.3f;

	// 単位行列
	m_mWorld = Math::Matrix::Identity;

	// デバッグワイヤー生成
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void Attack::OnHit()
{

	m_isExpired = true;
}