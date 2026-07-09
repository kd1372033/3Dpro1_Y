#pragma once

class WoodenBox : public KdGameObject
{
public:

	WoodenBox() {}
	~WoodenBox()	override {}

	void DrawLit()	override;
	void Init()		override;

private:

	std::shared_ptr<KdModelWork> m_spModel = nullptr;

};