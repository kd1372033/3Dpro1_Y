#include "GameScene.h"
#include "../Object/Player/Player.h"
#include "../Object/Enemy/Enemy.h"

void GameScene::PreUpdate()
{

}

void GameScene::Update()
{
	m_player->Update();
	m_enemy->Update();
}

void GameScene::Draw()
{
	m_player->Draw();
	m_enemy->Draw();
}

void GameScene::Init()
{
	// プレイヤー 生ポインタ
	//m_player = new Player();	// ①インスタンス確保 基底クラス→派生クラスの順で呼び出される
	//m_player->Init();			// ②初期化

	//プレイヤー　スマートポインタ
	m_player = std::make_shared<Player>();
	m_player->Init();

	m_enemy = std::make_shared<Enemy>();
	m_enemy->Init();
}

void GameScene::Release()
{
	//nullチェック
	/*if(m_player)
	{
		delete m_player;
		m_player = nullptr;
	}*/
}
