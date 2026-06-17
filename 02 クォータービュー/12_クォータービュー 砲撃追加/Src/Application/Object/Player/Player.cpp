#include "Player.h"

#include"../../Scene/SceneManager.h"
#include"../Attack/Attack.h"

void Player::Init()
{
	// デバッグワイヤー生成
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	m_polygon.SetMaterial("Asset/Textures/Player.png");

	// 板ポリの原点 (真ん中下段)
	m_polygon.SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	// アニメーション分割：横, 縦
	m_polygon.SetSplit(4, 8);

	//初期アニメーション
	m_animeInfo.start = 4;		// 開始コマ
	m_animeInfo.end = 7;			// 終了コマ
	m_animeInfo.count = 0.0f;	// 現在のカウント数
	m_animeInfo.speed = 0.2f;	// アニメーションの速度

	// 座標・移動速度
	m_pos = {};
	m_dir = {};
	m_speed = 0.1f;
	m_attackDir = {};

	//重力
	m_gravity = 0.0f;

	// 単位行列　↓ノーマル行列
	m_mWorld = Math::Matrix::Identity;

	m_keyFlg = false;

	// 「当てられる側」の処理======
	// 当たり判定を付けたいから実体化
	m_pCollider = std::make_unique<KdCollider>();
	// 当たり判定用に球登録
	m_pCollider->RegisterCollisionShape
	(
		"pa",				// 識別用の名前
		{ 0,0.5,0 },				// 球の中心座標
		0.2,				// 球の半径
		KdCollider::Type::TypeSight	//当たり判定の種類
	);
	// ============================
}

void Player::CheckAnimation()
{
	//方向別にアニメーション情報セット
	//上下左右

	if (m_dirType & DirType::Up)
	{
		m_animeInfo.start = 24;
		m_animeInfo.end = 27;
	}
	if (m_dirType & DirType::Down)
	{
		m_animeInfo.start = 4;
		m_animeInfo.end = 7;
	}
	if (m_dirType & DirType::Left)
	{
		m_animeInfo.start = 12;
		m_animeInfo.end = 15;
	}
	if (m_dirType & DirType::Right)
	{
		m_animeInfo.start = 16;
		m_animeInfo.end = 19;
	}

	//斜め方向
	if (m_dirType == (DirType::Up | DirType::Left))
	{
		m_animeInfo.start = 20;
		m_animeInfo.end = 23;
	}
	if (m_dirType == (DirType::Up | DirType::Right))
	{
		m_animeInfo.start = 28;
		m_animeInfo.end = 31;
	}
	if (m_dirType == (DirType::Down | DirType::Left))
	{
		m_animeInfo.start = 0;
		m_animeInfo.end = 3;
	}
	if (m_dirType == (DirType::Down | DirType::Right))
	{
		m_animeInfo.start = 8;
		m_animeInfo.end = 11;
	}
	m_animeInfo.count = 0.0f;
	m_animeInfo.speed = 0.2f;
}

void Player::Update()
{
	//移動関係をクリア
	m_dir = {};
	UINT oldDirType = m_dirType;	// 前回の方向タイプを保存しておく
	m_dirType = 0;	//ビット列クリア

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_dir += { 0, 0, 1 };
		m_dirType |= DirType::Up;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_dir += { 0, 0, -1 };
		m_dirType |= DirType::Down;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_dir += { -1, 0, 0 };
		m_dirType |= DirType::Left;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_dir += { 1, 0, 0 };
		m_dirType |= DirType::Right;
	}
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		m_gravity = -0.1f;
	}

	// 当たり判定を見える化
	m_pDebugWire->AddDebugSphere(m_pos + Math::Vector3(0, 0.5, 0), 0.2f, kRedColor);



	//キー入力があった、向きが以前と変わったら
	if (m_dirType != 0 && m_dirType != oldDirType)
	{
		//アニメーション情報変更
		CheckAnimation();

		//最後に変更された向き　＝　攻撃方向なので、保存しておく
		m_attackDir = m_dir;
		m_attackDir.Normalize();
	}
	//変わっていなければ元の向き(保存してたデータ)に戻す
	else
	{
		m_dirType = oldDirType;
	}

	//正規化 ベクトルの長さ1にする　斜め移動のスピード一緒にする
	m_dir.Normalize();

	// 座標更新
	// 先生処理
// 座標 += ベクトルの方向(1.0f固定) * ベクトルの大きさ(向きに対して移動させたい量)
	m_pos += m_dir * m_speed;

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

			// 攻撃オブジェクトを出現させる座標を確定する
			Math::Vector3 attackPos = {};

			attackPos = m_pos;				//プレイヤーの座標
			attackPos += m_attackDir * 0.4f;//攻撃方向へのベクトル

			// 攻撃オブジェクト作成
			std::shared_ptr<Attack> attack;
			attack = std::make_shared<Attack>();
			attack->Init();
			attack->SetPos(attackPos);
			SceneManager::Instance().AddObject(attack);

			// 攻撃SE再生
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
	//アニメーション
	m_polygon.SetUVRect(animeCnt);



	//***********
	//レイ判定　当たり判定
	//***********
	//レイ判定用変数
	KdCollider::RayInfo rayInfo;

	// レイの発射位置（座標）を設定
	rayInfo.m_pos = m_pos;

	// 段差の許容範囲を設定
	static const float enableStepHigh = 0.2f;
	rayInfo.m_pos.y += enableStepHigh;			// 0.2f までの段差は登れる

	// レイの方向を設定
	rayInfo.m_dir = { 0.0f, -1.0f, 0.0f };

	// レイの長さを設定
	rayInfo.m_range = enableStepHigh + m_gravity;

	// 当たり判定をしたいタイプを設定
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
	//***********
}

void Player::PostUpdate()
{
	//座標行列
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	//行列合成
	m_mWorld = transMat;
}

void Player::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon
	(m_polygon, m_mWorld);
}

void Player::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon
	(m_polygon, m_mWorld);
}