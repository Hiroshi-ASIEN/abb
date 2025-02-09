#include "weaponCanon.h"
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

void WeaponCanon::Init()
{
	WeaponBase::Init();
	//------------------------------------------------------------------------------------------------------------------------------------------------------
// ƒ‚ƒfƒ‹
//------------------------------------------------------------------------------------------------------------------------------------------------------
	this->GetComponent<ModelRenderer>()->Load("asset\\mymodel\\bill.obj");
	m_TriggerTimeMax = 60.0f * 3.0f;
	m_TriggerTime = m_TriggerTime;
}

void WeaponCanon::Uninit()
{
	WeaponBase::Uninit();
}

void WeaponCanon::Update()
{
	WeaponBase::Update();
}

void WeaponCanon::Draw()
{
	WeaponBase::Draw();
}

void WeaponCanon::ActiveMove()
{
}

void WeaponCanon::Attack()
{
	WeaponBase::Attack();
}

void WeaponCanon::Shot()
{
	if (m_TriggerTime < m_TriggerTimeMax) return;

	CreateBullet(BulletType::Missile);
}
