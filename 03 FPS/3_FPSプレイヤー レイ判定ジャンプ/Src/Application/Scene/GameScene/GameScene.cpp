#include "GameScene.h"
#include"../SceneManager.h"

#include "../../GameObject/Camera/FPSCamera/FPSCamera.h"
#include "../../GameObject/Terrains/Ground/Ground.h"
#include "../../GameObject/Character/Player/Player.h"

void GameScene::Event()
{
	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}
}

void GameScene::Init()
{
	// 地形 地面
	std::shared_ptr<Ground> ground = std::make_shared<Ground>();
	ground->Init();
	m_objList.push_back(ground);

	// プレイヤー
	std::shared_ptr<Player> player = std::make_shared<Player>();
	player->Init();
	m_objList.push_back(player);

	// FPSカメラ
	std::shared_ptr<FPSCamera> camera = std::make_shared<FPSCamera>();
	camera->Init();
	m_objList.push_back(camera);

	// 各オブジェクトに必要なデータを渡しておく
	//player->SetCamera(camera);	// プレイヤーにカメラをセット
	camera->SetTarget(player);	// カメラに注視対象(プレイヤー)をセット
}
