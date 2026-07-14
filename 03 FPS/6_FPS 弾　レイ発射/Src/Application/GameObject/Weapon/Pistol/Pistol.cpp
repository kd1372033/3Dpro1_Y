#include "Pistol.h"

#include "../../../Scene/SceneManager.h"
#include "../../Effect/Explosion/Explosion.h"

void Pistol::Update()
{
	//弾発射
	if (m_shotFlg)
	{
		// 親（プレイヤー）の行列を取得
		// 親(プレイヤー)の行列を取得
		Math::Matrix parentMat = Math::Matrix::Identity;
		const std::shared_ptr<const KdGameObject> spParent = m_wpParent.lock();
		if (spParent)
		{
			// 親の行列を取得
			parentMat = spParent->GetMatrix();
		}
		// レイ判定用パラメーター
		KdCollider::RayInfo rayInfo;

		// レイの各パラメーターを設定
		rayInfo.m_pos = spParent->GetPos();
		rayInfo.m_dir = parentMat.Backward();
		rayInfo.m_range = 1000.0f;
		rayInfo.m_type = KdCollider::TypeDamage;

		// 衝突情報リスト
		std::list<KdCollider::CollisionResult> resultList;

		// 作成したレイ情報でオブジェクトリストと当たり判定
		for (auto& obj : SceneManager::Instance().GetObjList())
		{
			obj->Intersects(rayInfo, &resultList);
		}

		// 衝突情報リストから一番近いオブジェクトを検出
		bool isHit = false;
		float maxOverLap = 0.0f;
		Math::Vector3 hitPos = Math::Vector3::Zero;
		
		for (auto& ret : resultList)
		{
			// レイが当たった場合の貫通した長さが一番長いものを探す
			if (maxOverLap < ret.m_overlapDistance)
			{
				maxOverLap = ret.m_overlapDistance;
				hitPos = ret.m_hitPos;
				isHit = true;
			}
		}

		// レイHit時
		if (isHit)
		{
			// レイを弾として扱う場合
			if (m_rayBulletFlg)
			{
				std::shared_ptr< Explosion> explosion;
				explosion = std::make_shared<Explosion>();
				explosion->Init();
				explosion->SetPos(hitPos);
				SceneManager::Instance().AddObject(explosion);
				
			}
		}

		
		//弾の発射が終わったらフラグを未発射に戻す
		m_shotFlg = false;
		m_rayBulletFlg = false;

	}

	//基底クラスの更新処理
	WeaponBase::Update();
}

void Pistol::ShotBullet(const bool _rayFlg)
{
	// 発射フラグON
	m_shotFlg = true;
	// レイ = 弾とするか？
	m_rayBulletFlg = _rayFlg;

}

void Pistol::Init()
{
	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelWork>();
		m_spModel->SetModelData("Asset/Models/Weapon/Pistol/Pistol.gltf");

		if (!m_pDebugWire)
		{
			m_pDebugWire = std::make_unique<KdDebugWireFrame>();
		}

		// 親から武器本体へローカル行列 (相対位置)
		m_localMat = Math::Matrix::CreateTranslation(0.35f, -0.25f, 0.2f);
	}
}
