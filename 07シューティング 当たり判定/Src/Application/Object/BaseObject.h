#pragma once

//　全てのゲーム内オブジェクトの基底クラス
class BaseObject
{
public:

	// オブジェクトの種類
	enum class ObjectType
	{
		None,		// 0:タイプ無し
		Player,		// 1:プレイヤー
		Enemy,		// 2:エネミー
	};

	BaseObject() {}
	virtual ~BaseObject() { Release(); }
	//基底クラスのデストラクタは絶対に仮想関数にする！！！

	virtual void Update();
	virtual void Draw();
	virtual void Init();
	// Hit時の処理　※派生先で挙動を変える！
	virtual void OnHit() {}

	ObjectType GetObjType() { return m_objType; }
	Math::Vector3 GetPos() { return m_pos; }
	bool GetAliveFlg() { return m_aliveFlg; }

protected: // このクラスと派生先のクラス内からアクセス可能
	virtual void Release();

	KdTexture		m_tex;				//テクスチャ
	Math::Vector3	m_pos;				//座標
	bool			m_aliveFlg = true;	//生存フラグ

	// オブジェクトの種類
	ObjectType		m_objType = ObjectType::None;

};