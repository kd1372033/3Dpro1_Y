#include "Player.h"

#include "../../Scene/SceneManager.h"

void Player::Init()
{
	// 板ポリにテクスチャ(マテリアル)をセット
	m_polygon.SetMaterial("Asset/Textures/player.png");

	// 板ポリの原点 (真ん中下段)
	m_polygon.SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	// アニメーション分割：横, 縦
	m_polygon.SetSplit(4, 8);

	// 初期アニメーション情報
	m_animeInfo.start = 4;		// 開始コマ
	m_animeInfo.end = 7;		// 終了コマ
	m_animeInfo.count = 0;		// 現在のカウント数
	m_animeInfo.speed = 0.2f;	// アニメーションの速度

	// 座標・移動速度
	m_pos = {};
	m_dir = {};
	m_speed = 0.1f;

	// 重力
	m_gravity = 0.0f;

	// 行列
	m_mWorld = Math::Matrix::Identity;

	// デバッグワイヤー生成
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void Player::Update()
{
	// 移動関係をクリア
	m_dir = {};
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_dir += { 0, 0, 1 };
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_dir += { 0, 0, -1 };
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_dir += { -1, 0, 0 };
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_dir += { 1, 0, 0 };
	}
	// 正規化
	m_dir.Normalize();

	// 座標更新
	// 座標 += ベクトルの方向(1.0f固定) * ベクトルの大きさ(向きに対して移動させたい量)
	m_pos += m_dir * m_speed;

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		// ジャンプ力
		m_gravity = -0.1f;
	}

	// 重力を更新
	m_gravity += 0.005f;
	// 重力をキャラに反映
	m_pos.y -= m_gravity;

	// 攻撃
	if (GetAsyncKeyState('Z') & 0x8000)
	{
		if (!m_keyFlg)
		{
			m_keyFlg = true;

			// 攻撃SE再生												↓BGMの場合はtrue
			KdAudioManager::Instance().Play("Asset/Sounds/Attack.WAV", false);
		}
	}
	else
	{
		m_keyFlg = false;
	}

	// アニメーション更新　開始コマ数＋進んだコマ数で現在のコマ数を算出（intに型変換）
	m_animeInfo.count += m_animeInfo.speed;
	int animeCnt = static_cast<int>(m_animeInfo.start + m_animeInfo.count);

	// 最後のコマまで表示し終えたらループさせる
	if (animeCnt > m_animeInfo.end)
	{
		animeCnt = m_animeInfo.start;
		m_animeInfo.count = 0;
	}
	// UV(切り取るコマ)を設定
	m_polygon.SetUVRect(animeCnt);

	// ========================================
	//	当たり判定　・・・レイ判定　ここから
	// ========================================

	// レイ判定用に必要パラメーターを設定する構造体
	KdCollider::RayInfo rayInfo;

	// レイの発射位置（座標）を設定 どこから？
	rayInfo.m_pos = m_pos;

	// 段差の許容範囲を設定
	static const float enableStepHigh = 0.2f;
	rayInfo.m_pos.y += enableStepHigh;			// 0.2f までの段差は登れる

	// レイの方向を設定	どの方向へ？
	rayInfo.m_dir = { 0.0f, -1.0f, 0.0f };

	// レイの長さを設定	長さは？
	rayInfo.m_range = enableStepHigh + m_gravity;

	// 当たり判定をしたいタイプを設定	どれと判定？
	rayInfo.m_type = KdCollider::TypeGround;

	// デバッグ用の情報としてライン描画を追加
	m_pDebugWire->AddDebugLine
	(
		rayInfo.m_pos,	// 線の開始位置
		rayInfo.m_dir,	// 線の方向
		rayInfo.m_range	// 線の長さ
	);

	// レイに当たったオブジェクト情報を格納するリスト
	std::list<KdCollider::CollisionResult> retRayList;

	// 作成したレイ情報でオブジェクトリストと当たり判定をする
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		obj->Intersects(rayInfo, &retRayList);
	}

	// レイに当たったリストから一番近いオブジェクトを検出
	bool hit = false;
	float maxOverLap = 0;
	Math::Vector3 groundPos = {};	// レイが遮断された(Hitした)座標

	for (auto& ret : retRayList)
	{
		// レイが当たったオブジェクトの中から
		// 「m_overlapDistance = 貫通した長さ」が一番長いものを探す
		// 「m_overlapDistance が一番長い = 一番近くで当たった」と判定できる
		if (maxOverLap < ret.m_overlapDistance)
		{
			maxOverLap = ret.m_overlapDistance;
			groundPos = ret.m_hitPos;
			hit = true;
		}
	}

	// 当たっていたら
	if (hit)
	{
		m_pos = groundPos;	// レイの着弾地点に着地
		m_gravity = 0.0f;
	}

	// ========================================
	//	当たり判定　・・・レイ判定　ここまで
	// ========================================

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
