#include "Player.h"

#include "../../Camera/CameraBase.h"

void Player::Update()
{
	// 進行方向をクリア
	m_moveDir = Math::Vector3::Zero;

	// キャラ制御 (進行ベクトルの情報を更新)
	if (GetAsyncKeyState('W') & 0x8000) { m_moveDir.z = 1.0f; }
	if (GetAsyncKeyState('S') & 0x8000) { m_moveDir.z = -1.0f; }
	if (GetAsyncKeyState('A') & 0x8000) { m_moveDir.x = -1.0f; }
	if (GetAsyncKeyState('D') & 0x8000) { m_moveDir.x = 1.0f; }

	// ベクトルの向きをカメラのY軸の回転行列で変換
	std::shared_ptr<CameraBase> spCamera = m_wpCamera.lock();
	if (spCamera)
	{
		m_moveDir = m_moveDir.TransformNormal(m_moveDir, spCamera->GetRotationYMatrix());
	}

	// 確定した向き情報を正規化
	m_moveDir.Normalize();

	// 座標更新
	// 座標 += ベクトルの方向(長さ1.0f固定) * ベクトルの大きさ(移動速度)
	m_pos += m_moveDir * m_moveSpeed;

	// ワールド行列確定
	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = transMat;
}

void Player::Init()
{
	if (!m_pDebugWire)
	{
		m_pDebugWire = std::make_unique<KdDebugWireFrame>();
	}
}
