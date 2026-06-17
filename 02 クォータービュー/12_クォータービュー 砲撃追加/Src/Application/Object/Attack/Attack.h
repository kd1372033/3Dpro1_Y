#pragma once

class Attack : public KdGameObject
{
public :

	Attack() {}
	~Attack() override {}

	void Update()	  override;

	void DrawEffect() override;

	void Init()		  override;

private :

	// 板ポリゴン
	std::shared_ptr<KdSquarePolygon> m_polygon;

	// アニメーション情報
	float m_animeCnt   = 0.0f;
	float m_animeSpeed = 0.0f;

	// 攻撃判定のエリア
	float m_attackArea = 0.0f;
};
