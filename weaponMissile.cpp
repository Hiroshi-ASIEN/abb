#include "weaponMissile.h"
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

void WeaponMissile::Init()
{
	WeaponBase::Init();
	//------------------------------------------------------------------------------------------------------------------------------------------------------
// ƒ‚ƒfƒ‹
//------------------------------------------------------------------------------------------------------------------------------------------------------
	this->GetComponent<ModelRenderer>()->Load("asset\\mymodel\\bill.obj");

}

void WeaponMissile::Uninit()
{
	WeaponBase::Uninit();
}

void WeaponMissile::Update()
{
	WeaponBase::Update();

	if (m_MissileCount < MISSILE_COUNT_MAX)
	{
		m_MissileCount--;
	}
	if (m_MissileCount < 0)
	{
		m_MissileCount = MISSILE_COUNT_MAX;
	}

}

void WeaponMissile::Draw()
{
	WeaponBase::Draw();
}

void WeaponMissile::ActiveMove()
{
}

void WeaponMissile::Attack()
{
	if (m_MissileCount < MISSILE_COUNT_MAX)return;

	m_MissileCount--;

	WeaponBase::Attack();
}

void WeaponMissile::Shot()
{
//	if (!m_Parent->GetTarget()) return;
	if (m_Parent->GetTarget()==nullptr||
		m_Parent->GetTarget()==m_Parent) return;


	Bullet* bullet= CreateBullet(BulletType::Missile);
	bullet->SetTargetObject(m_Parent->GetTarget());
}
