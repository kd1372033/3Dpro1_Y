#include "Player.h"

#include "../../Camera/CameraBase.h"
#include "../../../Scene/SceneManager.h"

void Player::Update()
{
	// 進行方向をクリア
	m_moveDir = Math::Vector3::Zero;

	// キャラ制御 (進行ベクトルの情報を更新)
	if (GetAsyncKeyState('W') & 0x8000) { m_moveDir.z = 1.0f; }
	if (GetAsyncKeyState('S') & 0x8000) { m_moveDir.z = -1.0f; }
	if (GetAsyncKeyState('A') & 0x8000) { m_moveDir.x = -1.0f; }
	if (GetAsyncKeyState('D') & 0x8000) { m_moveDir.x = 1.0f; }

	// キャラ制御 (回転角度の情報を更新)
	if (!(GetAsyncKeyState(VK_LSHIFT) & 0x8000))
	{
		UpdateRotateByMouse();
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (!m_jumpKeyFlg)
		{
			m_jumpKeyFlg = true;
			m_gravity = -m_jumpPow;
		}
	}
	else
	{
		m_jumpKeyFlg = false;
	}

	// ベクトルの向きをカメラのY軸の回転行列で変換
	/*std::shared_ptr<CameraBase> spCamera = m_wpCamera.lock();
	if (spCamera)
	{
		m_moveDir = m_moveDir.TransformNormal(m_moveDir, spCamera->GetRotationYMatrix());
	}*/

	// ベクトルの向きをY軸の回転行列で変換
	m_moveDir = m_moveDir.TransformNormal(m_moveDir, GetRotationYMatrix());

	// 確定した向き情報を正規化
	m_moveDir.Normalize();

	// 座標更新
	// 座標 += ベクトルの方向(長さ1.0f固定) * ベクトルの大きさ(移動速度)
	m_pos += m_moveDir * m_moveSpeed;

	// 重力をキャラに反映 + 重力を更新
	m_pos.y -= m_gravity;
	m_gravity += m_gravityPow;

	// ワールド行列確定
	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);

	Math::Matrix rotMat;
	rotMat = GetRotationMatrix();

	m_mWorld = rotMat * transMat;
}

void Player::PostUpdate()
{
	// レイ判定用パラメーター
	KdCollider::RayInfo rayInfo;

	// 段差の許容範囲を設定
	static const float enableStepHight = 0.5f;	// 0.5までの高さなら登れる

	// レイの各パラメーターを設定
	rayInfo.m_pos = m_pos;
	rayInfo.m_pos.y = rayInfo.m_pos.y - m_adjustHeight + enableStepHight;
	rayInfo.m_dir = Math::Vector3::Down;
	rayInfo.m_range = m_gravity + enableStepHight;
	rayInfo.m_type = KdCollider::TypeGround;

	// 衝突情報リスト
	std::list<KdCollider::CollisionResult> resultList;

	// 作成したレイ情報でオブジェクトリストと当たり判定
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		obj->Intersects(rayInfo, &resultList);
	}

	// 衝突情報リストから一番近いオブジェクトを検出
	bool isHit = false;
	float maxOverLap = 0.0f;
	Math::Vector3 groundPos = Math::Vector3::Zero;

	for (auto& ret : resultList)
	{
		// レイが当たった場合の貫通した長さが一番長いものを探す
		if (maxOverLap < ret.m_overlapDistance)
		{
			maxOverLap = ret.m_overlapDistance;
			groundPos = ret.m_hitPos;
			isHit = true;
		}
	}

	// 当たっていたら
	if (isHit)
	{
		m_pos = groundPos;
		m_pos.y += m_adjustHeight;
		m_gravity = 0;
	}
}

void Player::Init()
{
	// 地面から補正値分上げる
	m_pos.y += m_adjustHeight;
	if (!m_pDebugWire)
	{
		m_pDebugWire = std::make_unique<KdDebugWireFrame>();
	}
}

void Player::UpdateRotateByMouse()
{

	// マウスでカメラを回転させる処理
	POINT _nowPos;
	GetCursorPos(&_nowPos);

	POINT _mouseMove{};
	_mouseMove.x = _nowPos.x - m_fixMousePos.x;
	_mouseMove.y = _nowPos.y - m_fixMousePos.y;

	SetCursorPos(m_fixMousePos.x, m_fixMousePos.y);

	// 実際にカメラを回転させる処理(0.15はただの補正値)
	m_degAng.x += _mouseMove.y * 0.15f;
	m_degAng.y += _mouseMove.x * 0.15f;

	// 回転制御
	m_degAng.x = std::clamp(m_degAng.x, -45.f, 45.f);

}
