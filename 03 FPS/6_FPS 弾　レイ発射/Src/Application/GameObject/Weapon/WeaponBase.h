#pragma once

class WeaponBase : public KdGameObject
{
public:

	WeaponBase() {}
	virtual ~WeaponBase()	override {}

	virtual void Update()	override;
	void DrawLit()	override;

	// 弾発射関数 … 純粋仮想関数なのでオーバーライド必須！！！
	virtual void ShotBullet(const bool _rayFlg = false) = 0;


	void SetParent(const std::shared_ptr<KdGameObject>& _parent)
	{
		m_wpParent = _parent;
	}

protected:
	//モデル情報
	std::shared_ptr<KdModelWork> m_spModel = nullptr;

	//親の情報
	std::weak_ptr< KdGameObject> m_wpParent;

	//親から武器本体へのローカル行列
	Math::Matrix m_localMat;

	// 弾発射フラグ
	bool m_shotFlg = false;
	// レイ弾フラグ
	bool m_rayBulletFlg = false;

};