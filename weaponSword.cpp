#include "weaponSword.h"
#include "weaponBase.h"
#include "main.h"
#include "renderer.h"
#include "player.h"
#include "animationModel.h"

#include "input.h"
#include "bullet.h"
#include "bulletMissile.h"

#include "manager.h"
#include "camera.h"
#include "box.h"
#include "result.h"
#include "particleEmitter.h"

#include "audio.h"

#include "meshField.h"

#include "score.h"
#include "modelRenderer.h"
#include <list>
#include "math.h"
#include "enemyMachine.h"


void WeaponSword::Init()
{
	WeaponBase::Init();
	//------------------------------------------------------------------------------------------------------------------------------------------------------
// モデル
//------------------------------------------------------------------------------------------------------------------------------------------------------
	this->GetComponent<ModelRenderer>()->Load("asset\\mymodel\\testWeapon.obj");
	m_TriggerTimeMax = 30.0f;
	m_TriggerTime = m_TriggerTimeMax;
}

void WeaponSword::Uninit()
{
	WeaponBase::Uninit();
}

void WeaponSword::Update()
{
	WeaponBase::Update();
	Cutting();
}

void WeaponSword::Draw()
{
	WeaponBase::Draw();
}

void WeaponSword::ActiveMove()
{
}

void WeaponSword::Attack()
{
	WeaponBase::Attack();
	m_CutRot = 0.2f;
	// パーティクル発生

	Scene* scene = Manager::GetScene();
	auto characters = scene->GetGameObjects<EnemyMachine>();
	for (auto character : characters)
	{
		if (character == m_Parent) continue;

		if (OBBobjXscl(character, XMFLOAT3(5.0f, 5.0f, 5.0f)))
		{
//			this->SetDestroy();
			character->Damage(10);
			// パーティクル発生
		}
	}
}

void WeaponSword::Shot()
{
	if (m_TriggerTime < m_TriggerTimeMax) return;

//	CreateBullet(BulletType::Missile);
}

void WeaponSword::Cutting()
{
	if (m_TriggerTime >= m_TriggerTimeMax) return;

	m_CutRot *=1.1f;
	m_Rotation.x -= cos(m_CutRot);
	m_Rotation.y -= cos(m_CutRot);

//	if (m_Target == nullptr) return;

}