#include "main.h"
#include "renderer.h"
#include "bulletMissile.h"
#include "modelRenderer.h"
#include "input.h"
#include "manager.h"
#include "Collision.h"
#include "score.h"
#include "box.h"
#include "enemyMachine.h"
#include <iostream>

void BulletMissile::Init()
{

//	AddComponent<Collision>();

//		Accept(new ModelRenderer(this));		
		m_ModelComponent = new ModelRenderer(this);
		((ModelRenderer*)m_ModelComponent)->Load("asset\\mymodel\\protbullet.obj");

		Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\unlitTextureVS.cso");
		Renderer::CreatePixelShader(&m_PixelShader, "shader\\unlitTexturePS.cso");

		m_Quaternion={ 0.0f,0.0f,0.0f,1.0f};


		m_Accel = 4.0f;
}

void BulletMissile::Uninit()
{
	// �A�j���[�V�����\��
		Scene* scene;
		scene = Manager::GetScene();

		Effect* effect;
		effect = scene->AddGameObject<Effect>(goLayerType::Object3d);
		effect->SetPosition(this->m_Position);

	delete m_ModelComponent;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

}

void BulletMissile::Update()
{
	m_ModelComponent->Update(); 
	m_Count--;
	
	/*
	if (m_Count > 0)
	{
		m_Velocity.x += GetForward().x * m_Accel;
		m_Velocity.z += GetForward().z * m_Accel;

		// ���C����
		m_Velocity.x -= m_Velocity.x * 1.0f * m_dt;
		m_Velocity.z -= m_Velocity.z * 1.0f * m_dt;

		// �ړ�����
		m_Position.x += m_Velocity.x * m_dt;
		m_Position.y += m_Velocity.y * m_dt;
		m_Position.z += m_Velocity.z * m_dt;
	}
	else
	{
//		Move();
		TrackingMove();
	}
	*/
	


//	if (m_Position.z >50.0f )	SetDestroy();
	
	if (i <= 0)
	{
/*		// �~�T�C���̏����������^�[�Q�b�g�����ɐݒ�

		// 1. �^�[�Q�b�g�����̌v�Z
		XMStoreFloat3(&m_Direction, XMVector3Normalize(XMLoadFloat3(&m_TargetPosition) - XMLoadFloat3(&m_Position)));

		// 2. �����������^�[�Q�b�g�����ɐݒ�
		// �ȉ��ŁAY��(�����)����ɂ��ă~�T�C�����^�[�Q�b�g�Ɍ������邽�߂̃N�H�[�^�j�I�����v�Z���܂��B
		XMVECTOR forwardVector = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f); // �~�T�C���̑O��
		XMVECTOR targetDirection = XMLoadFloat3(&m_Direction);

		// �~�T�C���̑O���x�N�g���ƃ^�[�Q�b�g�����x�N�g���̊Ԃ̉�]�����v�Z
		XMVECTOR rotationAxis = XMVector3Cross(forwardVector, targetDirection);
		rotationAxis = XMVector3Normalize(rotationAxis);

		// �~�T�C���̑O���x�N�g���ƃ^�[�Q�b�g�����x�N�g���̊Ԃ̊p�x���v�Z
		float angle = acosf(XMVectorGetX(XMVector3Dot(forwardVector, targetDirection)));

		// �N�H�[�^�j�I�����v�Z
		XMVECTOR initialRotation = XMQuaternionRotationAxis(rotationAxis, angle);
		XMStoreFloat4(&m_Quaternion, initialRotation);

*/	}

	TrackingMove();


	Scene* scene;
	scene = Manager::GetScene();

	auto enemyList = scene->GetGameObjects<Player>();
	for (Player* enemy : enemyList)
	{
		if (enemy == m_Parent->GetParent()) continue;

		XMFLOAT3 enemyPosition = enemy->GetPosition();
		if (OBBobjXscl(enemy, {2.0f,2.0f,2.0f}))
		{

			this->SetDestroy();
			enemy->Damage(10);
			/*
			Scene* scene;
			scene = Manager::GetScene();

			Player* player = scene->GetGameObject<Player>();
			player->AddKillCount(1);

			// �X�R�A���Z
			scene->GetGameObject<Score>()->AddScore(1);
			return;
			*/
		}
	}
	auto billList = scene->GetGameObjects<Bill>();
	for (Bill* bill : billList)
	{

		XMFLOAT3 billPosition = bill->GetPosition();
		if (OBBobjXscl(bill, { 2.0f,2.0f,2.0f }))
		{
			this->SetDestroy();
		}
	}

	m_DestroyCount--;
	if (m_DestroyCount < 0)SetDestroy();
}

void BulletMissile::Draw()
{
	// ���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// �V�F�[�_�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// ���[���h�}�g���N�X�ݒ�
	XMMATRIX world, scale, rot, trans;
	scale = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	rot = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);

	trans = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(world);

	m_ModelComponent->Draw();

}

void BulletMissile::SetParent(GameObject* parent)
{
	m_Parent = parent;

	m_Rotation = parent->GetForward();
}

void BulletMissile::Move()
{
	m_Accel = 10.0f;

	m_Velocity.x += m_Rotation.x * m_Accel;
	m_Velocity.z += m_Rotation.z * m_Accel;

	// ���C����
	m_Velocity.x -= m_Velocity.x * 1.0f * m_dt;
	m_Velocity.z -= m_Velocity.z * 1.0f * m_dt;

	// �ړ�����
	m_Position.x += m_Velocity.x * m_dt;
	m_Position.y += m_Velocity.y * m_dt;
	m_Position.z += m_Velocity.z * m_dt;

}

void BulletMissile::TrackingMove()
{
	m_TargetPosition = m_Target->GetPosition();

	m_Direction.x = m_TargetPosition.x - this->m_Position.x;
	m_Direction.y = m_TargetPosition.y - this->m_Position.y;
	m_Direction.z = m_TargetPosition.z - this->m_Position.z;

	XMVECTOR dirVector = XMLoadFloat3(&m_Direction);
	dirVector = XMVector3Normalize(dirVector);
	XMStoreFloat3(&m_Direction, dirVector);

	float newRotation = atan2f(m_Direction.x, m_Direction.z);
	m_Rotation.y = newRotation;

	m_Velocity.x += GetForward().x * m_Accel;
//	m_Velocity.y -= GetForward().y * m_Accel;
	m_Velocity.z += GetForward().z * m_Accel;


	if (m_Count > 5.0f)	m_Velocity.y += 1.0f;
	else if (m_Velocity.y >= -2.0f)m_Velocity.y -= 8.0f;
	else m_Velocity.y = 0.0f;
	
	// �ړ�����
	m_Position.x += m_Velocity.x * m_dt;
	m_Position.y += m_Velocity.y * m_dt;
	m_Position.z += m_Velocity.z * m_dt;

}
