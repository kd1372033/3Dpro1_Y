#include "GameScene.h"
#include "../Object/Player/Player.h"
#include "../Object/Enemy/Enemy.h"

void GameScene::PreUpdate()
{

}

void GameScene::Update()
{
	/*m_player->Update();
	m_enemy->Update();*/
	// 全オブジェクトの更新関数を呼ぶ
	for (int i = 0; i < m_objList.size(); ++i)
	{
		m_objList[i]->Update();
	}
}

void GameScene::Draw()
{
	/*m_player->Draw();
	m_enemy->Draw();*/
	// 全オブジェクトの更新関数を呼ぶ
	for (int i = 0; i < m_objList.size(); ++i)
	{
		m_objList[i]->Draw();
	}
}

void GameScene::Init()
{
	// プレイヤー 生ポインタ
	//m_player = new Player();	// ①インスタンス確保 基底クラス→派生クラスの順で呼び出される
	//m_player->Init();			// ②初期化

	//プレイヤー　スマートポインタ
	/*m_player = std::make_shared<Player>();
	m_player->Init();*/

	/*m_enemy = std::make_shared<Enemy>();
	m_enemy->Init();*/

	// プレイヤー
	std::shared_ptr<Player> player;
	player = std::make_shared<Player>();	//①インスタンスを生成
	player->Init();							//②初期化
	m_objList.push_back(player);			//③リストへ追加

	// エネミー
	std::shared_ptr<Enemy> enemy;	//forの外で宣言すればOK
	for (int i = 0; i < 10; i++)
	{
		enemy = std::make_shared<Enemy>();
		enemy->Init();
		m_objList.push_back(enemy);
	}
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
