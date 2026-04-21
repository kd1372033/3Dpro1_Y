#pragma once

//　全てのゲーム内オブジェクトの基底クラス
class BaseObject
{
public:
	BaseObject() {}
	~BaseObject() { Release(); }

	void Update();
	void Draw();
	void Init();

protected: // このクラスと派生先のクラス内からアクセス可能
	void Release();

	KdTexture		m_tex;				//テクスチャ
	Math::Vector3	m_pos;				//座標
	bool			m_aliveFlg = true;	//生存フラグ
};