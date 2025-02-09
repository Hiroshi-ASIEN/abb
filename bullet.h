/**************************************************
* Bullet�N���X
* [bullet.h]
* Author    �F���{�h�n
* Date      �F2024�N05��15��
***************************************************/
#pragma once

#include "gameObject.h"
#include "component.h"
#include <list>

#include "Collision.h"
#define COMPONENT_INDEX (20)
#define DESTROY_COUNT_MAX (60.0f*1.0f)

enum BulletType
{
	Nomal=0,
	Missile,

	Max,
};

//==================================================
// Bullet�N���X
//==================================================
class Bullet :public GameObject
{
protected:
	Component* m_ModelComponent;
	std::list<Component*> m_component;	// �R���|�[�l���g


	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	bool m_JumpUse = false;
	XMFLOAT3 m_Velocity = XMFLOAT3(0.0f, 0.0f, 0.0f);
	float m_Accel = 1.0f;
	float m_dt = 1.0f / 60.0f;		// �o�ߎ���

	XMFLOAT4 m_Quatarnion{};
	float m_DestroyCount = DESTROY_COUNT_MAX;

	XMFLOAT3 m_TargetPosition{};
	class ParticleEmitter* m_Particle{};
public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void Move();

	void SetQuatarnion(XMFLOAT4 quatarnion);
	void SetParent(GameObject* parent);
	void Accept(Component* component);

	void SetTargetPosition(XMFLOAT3 position);
	void SetTargetObject(GameObject* _object);

	void TrackingBullet();
//	void UnderBullet();

};




//////////////////// EOF ////////////////////