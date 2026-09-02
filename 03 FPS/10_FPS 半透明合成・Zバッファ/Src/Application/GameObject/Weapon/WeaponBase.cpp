#include "WeaponBase.h"

void WeaponBase::Update()
{
	std::shared_ptr< KdGameObject> spParent = m_wpParent.lock();
	if (spParent)
	{
		// 親の行列を取得
		Math::Matrix parentMat = spParent->GetMatrix();

		// 親の行列を反映したワールド行列を作成
		//基準になるものを後ろにかける
		m_mWorld = m_localMat * parentMat;
	}

}

void WeaponBase::DrawLit()
{
	if (!m_spModel) return;

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}
