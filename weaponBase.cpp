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
	// モデル
	//------------------------------------------------------------------------------------------------------------------------------------------------------
	this->AddComponent<ModelRenderer>();
	this->GetComponent<ModelRenderer>()->Load("asset\\mymodel\\testWeapon.obj");

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\unlitTextureVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "shader\\unlitTexturePS.cso");

	//		Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\cookTrranceVS.cso");
	//		Renderer::CreatePixelShader(&m_PixelShader, "shader\\cookTrrancePS.cso");

			// SEロード
			// オーディオインスタンス化
	m_SE = new Audio(this);
	m_SE->Load("asset\\audio\\seshot01free.wav");

	//------------------------------------------------------------------------------------------------------------------------------------------------------
	// パーティクルエミッターセット
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
	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// ワールドマトリクス設定
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

// アタック
// 特定のボタンが押されたら～
void WeaponBase::Attack()
{
	if (m_AttackUse) return;

	if (m_MagazineCapacity <= 0)return;

	m_AttackUse = true;	// 攻撃中フラグtrue
	m_TriggerTime--;	// 発射間隔計測開始
	m_Particle->SetIsUse(true);	//パーティクルon
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
	if (m_TriggerTime >= m_TriggerTimeMax) return;	// 計測値がmaxと同じならここまで

	m_TriggerTime--;
	
	if (m_TriggerTime > 0.0f)return;	// 0に到達してなければここまで

	m_TriggerTime = m_TriggerTimeMax;	// 発射間隔計測値を初期化
	m_AttackUse = false;				// 攻撃中フラグfalse
	m_Particle->SetIsUse(false);		// パーティクルoff
}

// リロード
// 特定のボタンが押されたら～
void WeaponBase::MagazineReload()
{
	if (m_AttackUse) return;				// 攻撃中はリロード出来ない
	if (m_BulletAllCapacity <= 0) return;	// 所持弾数0以下はリロード出来ない

	// 装填上限数から残っていた弾数を引いて、使った弾を計算
	int bullet = m_MagazineCapacityMax - m_MagazineCapacity;

	if (bullet == 0) return;	// 弾未使用ならリロード出来ない

	// 所持弾数から使った弾数を引いた数が0未満になった場合
	if ((m_BulletAllCapacity - bullet) < 0)
	{
		m_MagazineCapacity += m_BulletAllCapacity;	// 装填数に所持弾数を足す
		m_BulletAllCapacity = 0;					// 所持弾数0にする
	}
	else
	{
		m_MagazineCapacity = m_MagazineCapacityMax;	// 装填数を最大にする
		m_BulletAllCapacity -= bullet;			// 所持弾数から使った弾数を引く
	}
}

XMFLOAT3 WeaponBase::GetOffSet()
{
	return m_OffSet;
}

// 座標ずれ設定
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

// 武器の向く方向設定
void WeaponBase::SetDirection(XMFLOAT3 _rot)
{
	if (m_AutoTarget) return;	// 自動方向追従がtrueならreturn

	SetRotation(_rot);
}


// 武器設定
// 引数：再攻撃可能時間、リロードまでの弾数、全ての残弾数
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
