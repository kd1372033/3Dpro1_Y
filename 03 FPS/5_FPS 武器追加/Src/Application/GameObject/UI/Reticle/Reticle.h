#pragma once

class Reticle : public KdGameObject
{
public :

	Reticle()					 {}
	~Reticle()			override {}

	void DrawSprite()	override;
	void Init()			override;

private :

	KdTexture m_tex;
};
