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



void WeaponBase::Init()
{

	Scene* scene;
	scene = Manager::GetScene();

	//------------------------------------------------------------------------------------------------------------------------------------------------------
	// ���f��
	//------------------------------------------------------------------------------------------------------------------------------------------------------
	this->AddComponent<ModelRenderer>();
	this->GetComponent<ModelRenderer>()->Load("asset\\mymodel\\testWeapon.obj");

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\unlitTextureVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "shader\\unlitTexturePS.cso");

	//		Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\cookTrranceVS.cso");
	//		Renderer::CreatePixelShader(&m_PixelShader, "shader\\cookTrrancePS.cso");

			// SE���[�h
			// �I�[�f�B�I�C���X�^���X��
	m_SE = new Audio(this);
	m_SE->Load("asset\\audio\\seshot01free.wav");

	//------------------------------------------------------------------------------------------------------------------------------------------------------
	// �p�[�e�B�N���G�~�b�^�[�Z�b�g
	//------------------------------------------------------------------------------------------------------------------------------------------------------
/*
	m_Particle = scene->AddGameObject<ParticleEmitter>(goLayerType::Particle);
	m_Particle->SetParent(this);
	m_Particle->SetPosition(XMFLOAT3((this->GetPosition().x), (this->GetPosition().y), (this->GetPosition().z + 5.0f)));
	m_Particle->SetType(ParticleType::tBurst);
	m_Particle->SetMaterialColor(XMFLOAT4(0.7, 0.1, 0.1, 0.7));
	m_Particle->SetIsUse(false);
*/

	m_Particle = scene->AddGameObject<ParticleEmitter>(goLayerType::Particle);
	m_Particle->SetParent(this);
	m_Particle->SetPosition(XMFLOAT3((this->GetPosition().x), (this->GetPosition().y), (this->GetPosition().z + 5.0f)));
	m_Particle->SetType(ParticleType::tShot);
	m_Particle->SetMaterialColor(XMFLOAT4(0.7f, 0.1f, 0.1f, 0.7f));
	m_Particle->SetIsUse(false);

	m_AutoTarget = true;
}

void WeaponBase::Uninit()
{
	for (Component* component : m_Component)
	{
		component->Uninit();
		delete component;
	}
	m_Component.clear();

	m_Particle->SetDestroy();
	m_SE->Uninit();
	delete m_SE;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void WeaponBase::Update()
{
	ReSetTriggerTime();

	if (m_Parent == nullptr)return;
	m_Particle->SetPosition(XMFLOAT3((this->GetPosition().x), (this->GetPosition().y-1.0f), (this->GetPosition().z + (GetForward().z*2.0f))));

	if (!m_AutoTarget) return;

	m_Rotation = Tracking(m_Parent->GetTarget());
}

void WeaponBase::Draw()
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


//	rot = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y + XM_PI, m_Rotation.z);

	trans = XMMatrixTranslation(m_Position.x, (m_Position.y - m_Scale.y), m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(world);

	this->GetComponent<ModelRenderer>()->Draw();
//	m_Component->Draw();


}


void WeaponBase::ActiveMove()
{
}

// �A�^�b�N
// ����̃{�^���������ꂽ��`
void WeaponBase::Attack()
{
	if (m_AttackUse) return;

	if (m_MagazineCapacity <= 0)return;

	m_AttackUse = true;	// �U�����t���Otrue
	m_TriggerTime--;	// ���ˊԊu�v���J�n
	m_Particle->SetIsUse(true);	//�p�[�e�B�N��on
	m_SE->Play();

	m_MagazineCapacity--;
	Shot();
}

void WeaponBase::Shot()
{
	CreateBullet(BulletType::Nomal);
}

void WeaponBase::ReSetTriggerTime()
{
	if (m_TriggerTime >= m_TriggerTimeMax) return;	// �v���l��max�Ɠ����Ȃ炱���܂�

	m_TriggerTime--;
	
	if (m_TriggerTime > 0.0f)return;	// 0�ɓ��B���ĂȂ���΂����܂�

	m_TriggerTime = m_TriggerTimeMax;	// ���ˊԊu�v���l��������
	m_AttackUse = false;				// �U�����t���Ofalse
	m_Particle->SetIsUse(false);		// �p�[�e�B�N��off
}

// �����[�h
// ����̃{�^���������ꂽ��`
void WeaponBase::MagazineReload()
{
	if (m_AttackUse) return;				// �U�����̓����[�h�o���Ȃ�
	if (m_BulletAllCapacity <= 0) return;	// �����e��0�ȉ��̓����[�h�o���Ȃ�

	// ���U���������c���Ă����e���������āA�g�����e���v�Z
	int bullet = m_MagazineCapacityMax - m_MagazineCapacity;

	if (bullet == 0) return;	// �e���g�p�Ȃ烊���[�h�o���Ȃ�

	// �����e������g�����e��������������0�����ɂȂ����ꍇ
	if ((m_BulletAllCapacity - bullet) < 0)
	{
		m_MagazineCapacity += m_BulletAllCapacity;	// ���U���ɏ����e���𑫂�
		m_BulletAllCapacity = 0;					// �����e��0�ɂ���
	}
	else
	{
		m_MagazineCapacity = m_MagazineCapacityMax;	// ���U�����ő�ɂ���
		m_BulletAllCapacity -= bullet;			// �����e������g�����e��������
	}
}

XMFLOAT3 WeaponBase::GetOffSet()
{
	return m_OffSet;
}

// ���W����ݒ�
void WeaponBase::SetOffSet(XMFLOAT3 _sizeoff)
{
	m_OffSet.x = _sizeoff.x;
	m_OffSet.y = _sizeoff.y;
	m_OffSet.z = _sizeoff.z;
}

void WeaponBase::SetParent(GameObject* _parent)
{
	m_Parent = _parent;
}


void WeaponBase::AutoTarget(bool _frag)
{
	m_AutoTarget = _frag;
}

// ����̌��������ݒ�
void WeaponBase::SetDirection(XMFLOAT3 _rot)
{
	if (m_AutoTarget) return;	// ���������Ǐ]��true�Ȃ�return

	SetRotation(_rot);
}


// ����ݒ�
// �����F�čU���\���ԁA�����[�h�܂ł̒e���A�S�Ă̎c�e��
void WeaponBase::SetWeaponConfig(float _triggerTime, int _magazineCapacity, int _allCapacity)
{
	m_TriggerTimeMax = _triggerTime;
	m_MagazineCapacityMax = _magazineCapacity;
	m_BulletAllCapacityMax = _allCapacity;

	m_TriggerTime = m_TriggerTimeMax;
	m_MagazineCapacity = m_MagazineCapacityMax;
	m_BulletAllCapacity = m_BulletAllCapacityMax;
}


WeaponBase* WeaponBase::GetWeapon()
{
	return this;
}

void WeaponBase::CreateParticle()
{
}

Bullet* WeaponBase::CreateBullet(BulletType _bullet)
{
	Scene* scene;
	scene = Manager::GetScene();
	Bullet* bullet{};

	switch (_bullet)
	{
	case Nomal:
		bullet = scene->AddGameObject<Bullet>(goLayerType::Object3d);
		bullet->SetPosition(m_Position);

		break;
	case Missile:
		bullet = scene->AddGameObject<BulletMissile>(goLayerType::Object3d);
		bullet->SetPosition(XMFLOAT3(this->m_Position.x + GetForward().x, this->m_Position.y + 1.0f, this->m_Position.z + GetForward().z));
		bullet->SetTargetObject(m_Parent->GetTarget());
		break;
	case Max:
		break;
	default:
		break;
	}
	bullet->SetRotation(this->m_Parent->GetRotation());
	bullet->SetParent(this);
	bullet->SetScale(XMFLOAT3(0.5f, 0.5f, 0.5f));

	return bullet;
}
