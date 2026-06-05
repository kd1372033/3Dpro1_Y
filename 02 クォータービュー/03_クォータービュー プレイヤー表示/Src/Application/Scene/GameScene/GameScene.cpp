#include "GameScene.h"
#include "../SceneManager.h"

#include "../../Object/BackGround/BackGround.h"
#include "../../Object/Ground/Ground.h"
#include "../../Object/Player/Player.h"

void GameScene::Event()
{
	// カメラの更新 
	Math::Matrix rotateMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(30));
	Math::Matrix transMat = Math::Matrix::CreateTranslation(0.0f, 3.0f, -3.0f);
	m_mWorld = rotateMat * transMat;
	m_camera->SetCameraMatrix(m_mWorld);


}

void GameScene::Init()
{
	// カメラ　生成 & 視野角
	m_camera = std::make_unique<KdCamera>();	// 1 メモリ確保
	m_camera->SetProjectionMatrix(60.0f);		// 2 視野角設定

	std::shared_ptr<BackGround> backGround;			// 1 メモリ確保
	backGround = std::make_shared<BackGround>();
	backGround->Init();
	m_objList.push_back(backGround);

	std::shared_ptr<Ground> ground;			// 1 メモリ確保
	ground = std::make_shared<Ground>();
	ground->Init();
	m_objList.push_back(ground);

	std::shared_ptr<Player> player;
	player = std::make_shared<Player>();
	player->Init();
	m_objList.push_back(player);
}

/*
	ユニークポインタ
	ユニーク･･･唯一無二
	アクセスが一つしかないポインタ
	譲渡のみでしかアクセスできない
*/
