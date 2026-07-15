#pragma once

class Bullet : public KdGameObject
{
public:

	Bullet() {}
	~Bullet()				override {}

	void Update()			override;
	void DrawLit()			override;
	void Init()				override;

	void Shot(const Math::Vector3 _muzzlePos, const Math::Vector3 _shotDir);

private:

	// モデル情報
	std::shared_ptr<KdModelWork> m_spModel = nullptr;

	// ワールド座標
	Math::Vector3 m_pos = Math::Vector3::Zero;

	// 進行方向 (ベクトルの向き)
	Math::Vector3 m_moveDir = Math::Vector3::Zero;

	// 移動速度 (ベクトルの大きさ)
	const float m_moveSpeed = 0.1f;

	// 照準への回転行列
	Math::Matrix m_rotBulletMat;
};