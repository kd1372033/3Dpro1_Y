#pragma once

//クラスの前方宣言
//class Player;
class BaseObject;

class GameScene
{
public:	//どこからでもアクセス可能
	GameScene() {}	//コンストラクタ　生成時に呼び出される
	~GameScene() { Release(); }	//デストラクタ　破棄時に呼び出される

	void PreUpdate();	// 更新を呼ぶ前の処理
	void Update();		// 更新
	void Draw();		// 描画
	void Init();		// 初期化

private: //このクラス内からのみアクセス可能
	void Release();		//解放処理
	
	//Player* m_player = nullptr;		// 派生クラスのポインタ
	BaseObject* m_player = nullptr;		// 基底クラスのポインタ

};