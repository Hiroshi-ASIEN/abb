#include "weaponRifle.h"
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
#include "particleEmitter.h"

#include "audio.h"

#include "modelRenderer.h"
#include <list>

void WeaponRifle::Init()
{
	WeaponBase::Init();
	SetWeaponConfig(60.0f * 0.5f, 30, 100);
//------------------------------------------------------------------------------------------------------------------------------------------------------
// ƒ‚ƒfƒ‹
//------------------------------------------------------------------------------------------------------------------------------------------------------
	this->GetComponent<ModelRenderer>()->Load("asset\\mymodel\\testWeapon.obj");

	m_TriggerTimeMax = 60.0f * 1.0f;
	m_TriggerTime = m_TriggerTime;
}

void WeaponRifle::Uninit()
{
	WeaponBase::Uninit();
}

void WeaponRifle::Update()
{
	WeaponBase::Update();
}

void WeaponRifle::Draw()
{
	WeaponBase::Draw();
}

void WeaponRifle::ActiveMove()
{
}

void WeaponRifle::Attack()
{
	WeaponBase::Attack();
}

void WeaponRifle::Shot()
{
	CreateBullet(BulletType::Nomal);
}
