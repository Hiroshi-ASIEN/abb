/**************************************************
* BulletMissile�N���X
* [bullet.h]
* Author    �F���{�h�n
* Date      �F2024�N05��15��
***************************************************/
#pragma once

#include "gameObject.h"
#include "component.h"
#include <list>
#include "bullet.h"

#include "Collision.h"
#define COMPONENT_INDEX (20)
#define M_DESTROY_COUNT_MAX (60*2)

//==================================================
// BulletMissile�N���X
//==================================================
class BulletMissile :public Bullet
{
private:
	float m_RotationSpeed = 1.0f;	// ��]���x

	XMFLOAT4 m_Quaternion{};

	float m_MissileSpeed = 1.0f;

	XMFLOAT3 m_Direction{0.0f,0.0f,0.0f};

	int i = 0;
	float m_Count = 20.0f;
	float m_DestroyCount = M_DESTROY_COUNT_MAX;

public:
	void Init()override;	// ����������
	void Uninit()override;	// �I������
	void Update()override;	// �X�V����
	void Draw()override;	// �`�揈��

	void Move();			// �ړ�����
	void TrackingMove();
	void SetParent(GameObject* parent);

//	void SetTargetObject(GameObject* object);	// �Ǐ]�^�[�Q�b�g�ݒ�
//	void SetTargetPosition(XMFLOAT3 position);	// ���e�|�W�V�����ݒ�i�����������X�V����H�j

};




//////////////////// EOF ////////////////////