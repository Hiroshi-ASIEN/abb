#pragma once
#include "weaponBase.h"
#include "gameObject.h"

class WeaponCanon :public WeaponBase
{

public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void ActiveMove()override;
	void Attack()override;


	void Shot()override;
};