#pragma once
class CameraBase;
class WeaponBase;

class Player : public KdGameObject
{
public:

	Player() {}
	~Player()		override {}

	void Update()	override;
	void PostUpdate()	override;
	void Init()		override;

	//カメラセット知れないからいらなーい
	//void SetCamera(const std::shared_ptr<CameraBase>& _camera)
	//{
	//	m_wpCamera = _camera;
	//}
	//武器
	void SetWeapon(const std::shared_ptr<WeaponBase>& _weapon)
	{
		m_wpWeapon = _weapon;
	}

	void UpdateRotateByMouse();

private:
	const Math::Matrix GetRotationMatrix()const
		{
			return Math::Matrix::CreateFromYawPitchRoll(
			       DirectX::XMConvertToRadians(m_DegAng.y),
			       DirectX::XMConvertToRadians(m_DegAng.x),
			       DirectX::XMConvertToRadians(m_DegAng.z));
		}

	const Math::Matrix GetRotationYMatrix() const
	{
		return Math::Matrix::CreateRotationY(
			   DirectX::XMConvertToRadians(m_DegAng.y));
	}


	// カメラ情報
	//std::weak_ptr<CameraBase> m_wpCamera;

	//武器情報
	std::weak_ptr<WeaponBase> m_wpWeapon;
	// ワールド座標
	Math::Vector3 m_pos = Math::Vector3::Zero;

	// カメラ回転用角度
	Math::Vector3 m_DegAng = Math::Vector3::Zero;

	
	// 進行方向 (ベクトルの向き)
	Math::Vector3 m_moveDir = Math::Vector3::Zero;

	// 移動速度 (ベクトルの大きさ)
	const float m_moveSpeed = 0.6f;

	// プレイヤー座標補正
	const float m_adjustHeight = 10.0f;

	// ジャンプ力
	const float m_jumpPow = 1.0f;

	// 重力
	const float m_gravityPow = 0.04f;
	float m_gravity = 0.0f;

	// キーフラグ
	bool m_jumpKeyFlg = false;
	bool m_leftClickFlg = false;

	// 回転用マウス座標の原点
	POINT m_fixMousePos = { 640, 360 };
};