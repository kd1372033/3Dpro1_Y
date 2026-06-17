#include "Enemy.h"

#include "../../Scene/SceneManager.h"
#include "../Player/Player.h"

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

	// 追尾フラグ
	m_chaseFlg = false;

	// サーチ範囲
	m_searchArea = 3.0f;

	// 行列
	m_mWorld = Math::Matrix::Identity;

	// デバッグワイヤー生成
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	// コライダー(当たり判定情報)の初期化(登録)
	m_pCollider = std::make_unique<KdCollider>();	// 1 生成
	m_pCollider->RegisterCollisionShape				// 2 判定リストに登録
	("Enemy",					// 登録名
		m_polygon,				// モデルデータ
		KdCollider::TypeDamage	// 判定種類
	);
}


void Enemy::Update()
{
	//デバック用のポインタを実体化
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	// アニメーション更新
	int walk[4] = { 3,4,3,5 };						// 使用するコマの配列
	m_polygon->SetUVRect(walk[(int)m_animeCnt]);	// UV座標を設定
	m_animeCnt += m_animeSpeed;						// カウント更新

	// アニメーションをループ
	if (m_animeCnt >= 4)
	{
		m_animeCnt = 0;
	}
	// ==========================================
// 追尾対象が一定範囲にいるか？
// ==========================================
	Math::Vector3 targetPos = {};

	// weak_ptrで所持している m_wpTarget が有効かどうかを調べる
// expired() … shared_ptrとして無効なアドレスならtrueを返す
	if (m_wpTarget.expired() == false)
	{
		// lock() … weakをshared_ptrに変換
		targetPos = m_wpTarget.lock()->GetPos();

		// 対象との距離(ベクトルの長さ)で判定　※球判定
		Math::Vector3 v = targetPos - m_pos;
		// ベクトルの長さが一定値以下なら追尾モードへ
		if (v.Length() < m_searchArea)
		{
			m_chaseFlg = true;
		}
		else
		{
			m_chaseFlg = false;
		}

		// 追尾フラグONの場合は追尾する
		if (m_chaseFlg)
		{
			// y軸を 0 にしておく　※空飛んで追いかけるの防止
			v.y = 0.0f;

			// 対象へのベクトルの長さを 1 に
			v.Normalize();

			// 方向確定
			m_dir = v;
		}
		else
		{
			m_dir = {};
		}
	}

	// デバッグ用にサーチ範囲の球を追加
	m_pDebugWire->AddDebugSphere
	(
		m_pos + Math::Vector3(0, 0.5f, 0),
		m_searchArea,
		kGreenColor
	);

	// 移動処理
	m_pos += m_dir * m_speed;
}

void Enemy::PostUpdate()
{
	// Update()で確定したパラメーターから座標行列を作成
	m_mWorld = Math::Matrix::CreateTranslation(m_pos);
}

void Enemy::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon
	(*m_polygon, m_mWorld);
}

void Enemy::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon
	(*m_polygon, m_mWorld);
}


void Enemy::OnHit()
{
	m_isExpired = true;
}
void Enemy::SetTarget(std::weak_ptr<Player> _target)
{

	m_wpTarget = _target;

}