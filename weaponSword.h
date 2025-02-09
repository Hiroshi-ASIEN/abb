#pragma once
#include "weaponBase.h"
#include "gameObject.h"

class WeaponSword :public WeaponBase
{
	float m_CutRot{};

public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void ActiveMove()override;
	void Attack()override;


	void Shot()override;
	void Cutting();
};