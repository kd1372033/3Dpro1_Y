#include "Ground.h"

void Ground::Init()
{
	// メモリ確保
	m_model = std::make_shared<KdModelData>();
	// モデル読み込み
	m_model->Load("Asset/Models/Ground/Ground.gltf");
	
	// 行列 
	Math::Matrix scaleMat = Math::Matrix::CreateScale(100.0f);
	Math::Matrix transMat = Math::Matrix::CreateTranslation(0.0f, 0.0f, 0.0f);

	// 行列の合成
	m_mWorld = scaleMat * transMat;

}
void Ground::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}
