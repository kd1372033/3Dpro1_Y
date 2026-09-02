#include "Cloud.h"
#include "../../Character/Player/Player.h"

void Cloud::Update()
{
	// プレイヤー(カメラ)の回転角度を取得
	Math::Vector3 rotAngle;
	std::shared_ptr<Player> spPlayer = m_wpPlayer.lock();
	if (spPlayer)
	{
		rotAngle = spPlayer->GetRotateAngle();
	}

	// 座標情報を退避
	Math::Vector3 pos = GetPos();

	// 常に正面を向いてOKな場合はX軸,Y軸で回転させる (Z軸は0)
	// プレイヤー(カメラ)と同じ回転行列を作成＆自身に適応
	m_mWorld = Math::Matrix::CreateFromYawPitchRoll(
		DirectX::XMConvertToRadians(rotAngle.y),
		DirectX::XMConvertToRadians(rotAngle.x),
		0.0f
	);

	// 木や草などX軸回転するとマズイ物体はY軸回転だけ行う
	//m_mWorld = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(rotAngle.y));

	// 座標情報を復元
	m_mWorld.Translation(pos);
}

void Cloud::DrawEffect()
{
	// 加算半透明
	KdShaderManager::Instance().ChangeBlendState(KdBlendState::Add);
	KdShaderManager::Instance().ChangeDepthStencilState(KdDepthStencilState::ZWriteDisable);


	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);

	// 元(半透明)に戻す
	KdShaderManager::Instance().ChangeBlendState(KdBlendState::Alpha);
	KdShaderManager::Instance().ChangeDepthStencilState(KdDepthStencilState::ZEnable);

	// 加算半透明問題
	// 加算半透明にするオブジェクトは最後に描画しないと透過部分が描画順の問題でバグる
	// 解決の方法としては Zソート で奥から順番に描画するように設計する

	// ① 不透明なオブジェクトを描画する

	// ② 半透明オブジェクト (Zソート済み) を描画する
	// 奥から描画する 前から描画すると後ろのオブジェクトが描画されない
}

void Cloud::Init()
{
	m_polygon = std::make_shared<KdSquarePolygon>();
	m_polygon->SetMaterial("Asset/Textures/Effect/Cloud.png");
}
