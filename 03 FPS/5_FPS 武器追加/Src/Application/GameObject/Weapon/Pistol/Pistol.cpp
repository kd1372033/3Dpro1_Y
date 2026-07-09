#include "Pistol.h"

void Pistol::Update()
{
	//基底クラスの更新処理
	WeaponBase::Update();
}

void Pistol::Init()
{
	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelWork>();
		m_spModel->SetModelData("Asset/Models/Weapon/Pistol/Pistol.gltf");

		if (!m_pDebugWire)
		{
			m_pDebugWire = std::make_unique<KdDebugWireFrame>();
		}

		// 親から武器本体へローカル行列 (相対位置)
		m_localMat = Math::Matrix::CreateTranslation(0.35f, -0.25f, 0.2f);
	}
}
