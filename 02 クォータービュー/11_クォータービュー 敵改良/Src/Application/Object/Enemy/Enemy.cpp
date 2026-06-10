#include "Enemy.h"

#include "../../Scene/SceneManager.h"

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
	m_chaseFlg = false;
	m_searchArea = 3.0f;
}

void Enemy::Update()
{
	// 移動
	if (m_chaseFlg)
	{
		Math::Vector3 targetPos;
		if (m_wptarget.expired() == false)
		{
			// 領域が存在している
			targetPos = m_wptarget.lock()->GetPos();
			//					 ↑shared_ptrに変換
		}
		// ターゲットの方向を算出
		Math::Vector3 dir = (targetPos + Math::Vector3(0.0f, 0.5f, 0.0f)) - m_pos;
		// 方向ベクトルの長さは絶対に「1」
		dir.Normalize();
		// ターゲットの方向に向かって移動
		m_pos += dir * m_speed;
	}

	// アニメーション更新
	int walk[4] = { 3,4,3,5 };						// 使用するコマの配列
	m_polygon->SetUVRect(walk[(int)m_animeCnt]);	// UV座標を設定
	m_animeCnt += m_animeSpeed;						// カウント更新

	// アニメーションをループ
	if (m_animeCnt >= 4)
	{
		m_animeCnt = 0;
	}

	// スフィア判定
	KdCollider::SphereInfo sphere;
	sphere.m_sphere.Center = m_pos;
	sphere.m_sphere.Center.y += 0.5;
	sphere.m_sphere.Radius = m_searchArea;
	sphere.m_type = KdCollider::Type::TypeEvent;
	m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius,kGreenColor);
	std::list<KdCollider::CollisionResult> retSphereList;
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		// 球と当たり判定!!!!!!
		obj->Intersects(sphere, &retSphereList);
	}
	float maxOverLap = 0;	// 球の時はめり込んだ長さ
	//	↓こいつ　レイ判定の時に宣言してるので使いまわす
	bool hit = false;
	// 当たった方向を格納する変数
	Math::Vector3 hitDir;
	for (auto& ret : retSphereList)
	{
		// 球にめり込んだ長さが一番長いものを探す
		if (maxOverLap < ret.m_overlapDistance)
		{
			// 更新
			maxOverLap = ret.m_overlapDistance;
			hitDir = ret.m_hitDir;
			hit = true;
		}
	}

	if (hit == true)
	{
		m_chaseFlg = true;
		// 正規化（長さを１にする）
		hitDir.Normalize();
		// 押し戻し処理			↓めり込んだ長さ
		m_pos += hitDir * maxOverLap;
		//		↑当たった方向(方向ベクトルは長さ１)
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