/**************************************************
* Weapon �x�[�X�N���X
* [WeaponBase.h]
* Author    �F���{�h�n
* Date      �F2024�N11��07��
***************************************************/
#pragma once

#include "gameObject.h"
#include "bullet.h"
#include "bulletMissile.h"
#include "component.h"
#include <string>
//#include "player.h"

#define TRIGGER_TIME_MAX (60.0f*1.0f)

enum WeaponPosition;

enum WEAPON_TYPE
{
	CANON = 0,
	RIFLE,
	MISSILE,
	Sword,
	WT_MAX,
};

class WeaponBase :public GameObject
{
protected:
	// �g�p�n
	bool m_AutoTarget{};	// �^�[�Q�b�g�̂ق��������Ō����� ���� true
	bool m_AttackUse = false;	// ��������
	float m_TriggerTimeMax = TRIGGER_TIME_MAX;
	float m_TriggerTime = TRIGGER_TIME_MAX;	// ���ˊԊu
	int m_MagazineCapacityMax = 500;	// 1�}�K�W�����U�\��
	int m_MagazineCapacity = 500;		// ���݂̃}�K�W�����U��
	int m_BulletAllCapacityMax = 100;		// �����e�����
	int m_BulletAllCapacity = 100;			// �����e��

	// ���f���n
	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	XMFLOAT4 m_Material{};
	
	XMFLOAT3 m_OffSet{};	// �e����̍��W�̂���ʒu
	GameObject* m_Target{};
	// �p�[�e�B�N���G�~�b�^�[
	class ParticleEmitter* m_Particle;

	//
	class Audio* m_SE;

public:
	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

	virtual void ActiveMove();			// �쓮���̓���
	virtual void Shot() = 0;			// ���ˊ֘A
	virtual void ReSetTriggerTime();	// ���˂ł���܂ł�timer�Ǘ�

	virtual void CreateParticle();		// �p�[�e�B�N������
	virtual Bullet* CreateBullet(BulletType _bullet);		// �e����

	virtual WeaponBase* GetWeapon();	// ������擾�p
public:
	virtual void Attack();				// �U��
	virtual void MagazineReload();		// �����[�h
	XMFLOAT3 GetOffSet();
	virtual void SetOffSet(XMFLOAT3 _sizeoff);	// ������W�ݒ�
	virtual void SetParent(GameObject* _parent);

	void AutoTarget(bool _frag);

	void SetDirection(XMFLOAT3 _rot);
protected:
	void SetWeaponConfig(float _triggerTime, int _magazineCapacity, int _allCapacity);
};

