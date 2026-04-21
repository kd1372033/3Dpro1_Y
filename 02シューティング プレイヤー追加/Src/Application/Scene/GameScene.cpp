#include "GameScene.h"
#include "../Object/Player/Player.h"	

void GameScene::PreUpdate()
{

}

void GameScene::Update()
{
	m_player->Update();
}

void GameScene::Draw()
{
	m_player->Draw();
}

void GameScene::Init()
{
	// プレイヤー
	m_player = new Player();	// ①インスタンス確保
	m_player->Init();			// ②初期化
}

void GameScene::Release()
{
	//nullチェック
	if(m_player)
	{
		delete m_player;
		m_player = nullptr;
	}
}
