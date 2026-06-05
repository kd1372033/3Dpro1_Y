#pragma once

class Player : public KdGameObject
{
public:
	Player() {}
	~Player()		override {}

	void Init()			override;
	void Update()		override;
	void PostUpdate()	override;
	void GenerateDepthMapFromLight()override;
	void DrawLit()		override;

private:

	// 板ポリゴン
	KdSquarePolygon m_polygon;
	// 座標
	Math::Vector3 m_pos;
	// 方向（ベクトルの向き）
	Math::Vector3 m_dir;
	// 移動量
	float m_speed = 0.0f;
	// 重力
	float m_gravity = 0.0f;

};