#include "WoodenBox.h"

void WoodenBox::DrawLit()
{
	if (!m_spModel) return;

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}

void WoodenBox::Init()
{
	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelWork>();
		m_spModel->SetModelData("Asset/Models/Terrains/WoodenBox/Wooden_Box.gltf");

		m_pCollider = std::make_unique<KdCollider>();
		m_pCollider->RegisterCollisionShape("WoodenBox", m_spModel, KdCollider::TypeGround);

		m_mWorld = Math::Matrix::CreateScale(10.0f);
	}
}