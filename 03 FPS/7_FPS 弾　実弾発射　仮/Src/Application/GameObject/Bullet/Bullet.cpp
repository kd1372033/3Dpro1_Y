#include "Bullet.h"

void Bullet::Update()
{
	// 座標更新
	// 座標 += 向き情報(1.0f) * 移動速度
	m_pos += m_moveDir * m_moveSpeed;

	// ワールド行列確定
	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = transMat;
}

void Bullet::DrawLit()
{
	if (!m_spModel) return;

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}

void Bullet::Init()
{
	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelWork>();
		m_spModel->SetModelData("Asset/Models/Bullet/Arrow.gltf");
	}
}

void Bullet::Shot(const Math::Vector3 _muzzlePos, const Math::Vector3 _shotDir)
{
	// 弾の初期座標をコピー
	m_pos = _muzzlePos;

	// 進行ベクトルをコピー
	m_moveDir = _shotDir;
	m_moveDir.Normalize();
}
