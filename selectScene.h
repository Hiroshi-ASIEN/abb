#pragma once

#include "scene.h"
#include "weaponBase.h"
enum CorsorMenuStatus
{
MenuSelect=0,
NextSceneSelect,
RArmMenuSelect,
LArmMenuSelect,
BackSceneSelect,
SelectStatusMax,
};

class SelectScene :public Scene
{
private:
	Polygon2D* m_Fade{};
	UI* m_SelectScene{};
	UI* m_Push{};
	class UI* m_SelectSceneLoad{};

	UI* m_SelectCursor{};		// �J�[�\���\���p
	UI* m_DiscriptionView{};	// ��������p
	UI* m_SelectRArmWeapon{};		// �I���ς݉E����\���p
	UI* m_SelectLArmWeapon{};		// �I���ςݍ�����\���p

	static WEAPON_TYPE m_SelectRWeapon;
	static WEAPON_TYPE m_SelectLWeapon;

	class WeaponBase* m_DestroyWeapon{};
	WeaponBase* m_DummyRWeapon{};
	WeaponBase* m_DummyLWeapon{};

	float x = 1.0f;

	XMFLOAT2 m_CorsorPositions[10];
	int m_NowCorsorPosition{};
	CorsorMenuStatus m_CorsorMenuStatus{};
	float i{};

	bool m_NextScene = false;

	void CorsorPositionsSet();
public:
	void Init()override;
	void Uninit()override;
	void Update()override;

	void CursorMove();
	void CursorMenuMove();
	void CursorWeaponMenuMove();
	void WeaponSelect(WEAPON_TYPE i);

	static WEAPON_TYPE GetSelectRWeapon();
	static WEAPON_TYPE GetSelectLWeapon();

};