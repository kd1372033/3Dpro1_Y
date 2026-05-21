#include "GameScene.h"
#include"../SceneManager.h"

void GameScene::Event()
{
	
}

void GameScene::Init()
{
	// カメラ　生成 & 視野角
	m_camera = std::make_unique<KdCamera>();	// 1 メモリ確保
	m_camera->SetProjectionMatrix(60.0f);		// 2 視野角設定
}

/*
	ユニークポインタ
	ユニーク･･･唯一無二
	アクセスが一つしかないポインタ
	譲渡のみでしかアクセスできない
*/
