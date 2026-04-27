#pragma once
// 基本的にヘッダーファイルの中で
// 別のヘッダーファイルをインクルードするのはＮＧ
// 継承元クラスのヘッダーのみインクルードが必須なので可とする
#include "../BaseObject.h"

class Player :public BaseObject
{
public:
	Player() {}
	~Player() override { Release(); }

	// 基底クラスの仮想関数をオーバーライド
// override指定子は無くてもオーバーライドはされるが
// overrideしているかどうかを判別する目的でつけるべき (可読性の問題もある)
	void Update() override;
	void Draw()	  override;
	void Init()   override;

private:

	void Release() override;

};