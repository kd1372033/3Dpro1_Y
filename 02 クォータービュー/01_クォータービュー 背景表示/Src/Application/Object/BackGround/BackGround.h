#pragma once
#include "../../../Framework/GameObject/KdGameObject.h"

class BackGround : public KdGameObject
{
public:
	BackGround() {}
	~BackGround()		override { Release(); }

	void Init();
	void DrawUnLit()	override;

private:

	KdSquarePolygon	m_polygon;

};