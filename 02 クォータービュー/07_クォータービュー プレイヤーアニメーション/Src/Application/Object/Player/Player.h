#pragma once

class Player : public KdGameObject
{
public:

	// アニメーション情報
	struct AnimationInfo
	{
		int   start;	// 開始コマ
		int   end;		// 終了コマ
		float count;	// 現在のカウント数
		float speed;	// アニメーションの速度
	};

	Player() {}
	~Player()	override {}

	void Init()						override;
	void Update()					override;
	void PostUpdate()				override;
	void GenerateDepthMapFromLight()override;
	void DrawLit()					override;

private:

	// 板ポリゴン
	KdSquarePolygon m_polygon;

	// アニメーション情報
	AnimationInfo m_animeInfo = {};

	// 座標
	Math::Vector3 m_pos;
	// 方向（ベクトルの向き）
	Math::Vector3 m_dir;
	// 移動量
	float m_speed = 0.0f;
	// 重力
	float m_gravity = 0.0f;
	// 押しっぱ防止
	bool m_keyFlg = false;


};