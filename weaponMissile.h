#pragma once
#include "weaponBase.h"
#include "gameObject.h"

#define MISSILE_COUNT_MAX (60 * 3)

class WeaponMissile :public WeaponBase
{
	float m_MissileCount = MISSILE_COUNT_MAX;

public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void ActiveMove()override;
	void Attack()override;
	void SetTargetObject(GameObject* object);	// 追従ターゲット設定

	void Shot()override;
};