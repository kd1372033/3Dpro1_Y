#include "Bullet.h"

void Bullet::Update()
{
	// 座標更新
	// 座標 += 向き情報(1.0f) * 移動速度
	m_pos += m_moveDir * m_moveSpeed;

	// ワールド行列確定
	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = m_rotBulletMat * transMat;
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

	//======================================================================
	// 照準へのベクトルと弾の進行ベクトルから弾の向き(回転行列)を作成
	//======================================================================

	// ① ベクトルＡ　・・・　弾の現在の進行ベクトル
	Math::Vector3 vecA = m_mWorld.Backward();
	vecA.Normalize();

	// ② ベクトルＢ　・・・　照準への進行ベクトル
	Math::Vector3 vecB = m_moveDir;
	vecB.Normalize();

	// ①と②のベクトルの内積値から角度を算出
	float dot = vecA.Dot(vecB);	// 内積値を算出
	float angle = acos(dot);		// 内積値からacosで２つのベクトルの角度を算出
	
	// ①と②のベクトルの外積を利用して、回転する為のベクトル(回転軸)を作成
	Math::Vector3 rotAxis = vecA.Cross(vecB);

	// 内積で算出した角度分、外積で算出したベクトル(回転軸)で回転する行列を作成
	// 弾がレティクルの方向を向く
	m_rotBulletMat = Math::Matrix::CreateFromAxisAngle(rotAxis, angle);
}