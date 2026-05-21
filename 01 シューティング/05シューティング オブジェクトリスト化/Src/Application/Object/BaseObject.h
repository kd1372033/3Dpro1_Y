#pragma once

//　全てのゲーム内オブジェクトの基底クラス
class BaseObject
{
public:
	BaseObject() {}
	virtual ~BaseObject() { Release(); }
	//基底クラスのデストラクタは絶対に仮想関数にする！！！

	virtual void Update();
	virtual void Draw();
	virtual void Init();

protected: // このクラスと派生先のクラス内からアクセス可能
	virtual void Release();

	KdTexture		m_tex;				//テクスチャ
	Math::Vector3	m_pos;				//座標
	bool			m_aliveFlg = true;	//生存フラグ
};