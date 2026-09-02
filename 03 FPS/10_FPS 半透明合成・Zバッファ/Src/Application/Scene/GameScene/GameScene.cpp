#include "GameScene.h"
#include"../SceneManager.h"
#include"../../GameObject/Camera/FPSCamera/FPSCamera.h"
#include"../../GameObject/Terrains/Ground/Ground.h"
#include"../../GameObject/Character/Player/Player.h"
#include"../../GameObject/Terrains/WoodenBox/WoodenBox.h"
#include"../../GameObject/UI/Reticle/Reticle.h"
#include"../../GameObject/Weapon/Pistol/Pistol.h"

#include"../../GameObject/Terrains/Cloud/Cloud.h"

void GameScene::Event()
{

}

void GameScene::Init()
{
	//道
	std::shared_ptr< Ground> ground;
	ground = std::make_shared< Ground>();
	ground->Init();
	m_objList.push_back(ground);

	//プレイヤー
	std::shared_ptr< Player> player;
	player = std::make_shared< Player>();
	player->Init();
	m_objList.push_back(player);


	// 地形 木箱
	std::shared_ptr<WoodenBox> box;
	for (int i = 0; i < 5; ++i)
	{
		box = std::make_shared<WoodenBox>();
		box->Init();
		box->SetPos({ -60.0f + i * 30.0f, 0.0f, 50.0f });
		m_objList.push_back(box);
	}

	//ピストル
	std::shared_ptr<Pistol> pistol;
	pistol = std::make_shared<Pistol>();
	pistol->Init();
	m_objList.push_back(pistol);

	// レティクル
	std::shared_ptr<Reticle> reticle = std::make_shared<Reticle>();
	reticle->Init();
	m_objList.push_back(reticle);

	// FPSカメラ
	std::shared_ptr<FPSCamera> camera = std::make_shared<FPSCamera>();
	camera->Init();
	m_objList.push_back(camera);

	// 雲
	std::shared_ptr<Cloud> cloud;
	for (int i = 0; i < 5; ++i)
	{
		cloud = std::make_shared<Cloud>();
		cloud->Init();
		cloud->SetPos({ 0.0f,10.0f,0.0f + (i * 2.0f) });
		m_objList.push_back(cloud);
		cloud->SetPlayer(player);
	}

	//データを渡す　プレイヤーの座標
	// 各オブジェクトに必要なデータを渡しておく
	//player->SetCamera(camera);	// プレイヤーにカメラをセット
	camera->SetTarget(player);	// カメラに注視対象(プレイヤー)をセット
	pistol->SetParent(player);	// プレイヤーを親にする
	player->SetWeapon(pistol);	// プレイヤーに武器をセット
}
