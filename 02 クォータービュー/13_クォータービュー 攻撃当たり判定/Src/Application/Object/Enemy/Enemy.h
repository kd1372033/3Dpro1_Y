#pragma once

class Player;
class Enemy : public KdGameObject
{
public:

	Enemy() {}
	~Enemy() override {}

	void Update()					 override;
	void PostUpdate()				 override;

	void GenerateDepthMapFromLight() override;
	void DrawLit()					 override;

	void Init()						 override;

	void OnHit()       override;

	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }
	void SetTarget(std::weak_ptr<Player> _target);

private:

	// 板ポリゴン
	std::shared_ptr<KdSquarePolygon> m_polygon;

	// アニメーション情報
	float m_animeCnt = 0;
	float m_animeSpeed = 0.0f;

	// 座標
	Math::Vector3 m_pos;

	// 方向 (ベクトルの向き)
	Math::Vector3 m_dir;

	// 移動量 (ベクトルの大きさ)
	float m_speed = 0.0f;

	bool m_chaseFlg;
	float m_searchArea;

	//ターゲットポインタ
	std::weak_ptr<KdGameObject> m_target;

	std::weak_ptr<Player> m_wpTarget;

};