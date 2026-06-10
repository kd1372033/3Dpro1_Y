#include "GameScene.h"
#include "../SceneManager.h"

#include "../../Object/BackGround/BackGround.h"
#include "../../Object/Ground/Ground.h"
#include "../../Object/Player/Player.h"

void GameScene::Event()
{
	// プレイヤーの最新の座標を取得する
	Math::Vector3 playerPos = {};

	// weak_ptrで所持している m_player が有効かどうかを調べる
	// expired() … 既に無効なアドレスならtrueを返す 賞味期限を確認
	if (m_wpPlayer.expired() == false)
	{
		// weak_ptrを lock() で shared_ptr として取得
		std::shared_ptr<Player> spPlayer = m_wpPlayer.lock();
		// shared_ptrならアドレスの先にアクセス可能
		playerPos = spPlayer->GetPos();
	}
	// カメラの更新 
	Math::Matrix rotateMat = Math::Matrix::CreateRotationX
	(DirectX::XMConvertToRadians(30));

	Math::Matrix transMat = Math::Matrix::CreateTranslation
	(Math::Vector3(0.0f, 3.0f, -3.0f) + playerPos);
	Math::Matrix mat = rotateMat * transMat;
	m_camera->SetCameraMatrix(mat);
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

	// プレイヤーの情報をシーンが保持しておく
	m_wpPlayer = player;
}

/*
	ユニークポインタ
	ユニーク･･･唯一無二
	アクセスが一つしかないポインタ
	譲渡のみでしかアクセスできない
*/
