#include "main.h"
#include "renderer.h"
#include "bullet.h"
#include "modelRenderer.h"
#include "input.h"
#include "manager.h"
#include "Collision.h"
#include "score.h"
#include "particleEmitter.h"
#include "box.h"

void Bullet::Init()
{

//	AddComponent<Collision>();

//		Accept(new ModelRenderer(this));		
		m_ModelComponent = new ModelRenderer(this);
		((ModelRenderer*)m_ModelComponent)->Load("asset\\mymodel\\protbullet.obj");

		Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\unlitTextureVS.cso");
		Renderer::CreatePixelShader(&m_PixelShader, "shader\\unlitTexturePS.cso");
		
		Scene* scene = Manager::GetScene();
		m_Particle = scene->AddGameObject<ParticleEmitter>(goLayerType::Particle);
		m_Particle->SetParent(this);
		m_Particle->SetPosition(m_Position);
		m_Particle->SetScale({ 0.5f,0.5f,0.5f });
		m_Particle->SetType(ParticleType::tBullet);
		m_Particle->SetMaterialColor(XMFLOAT4(0.3f,0.3f,0.7f, 0.7f));
		m_Particle->SetIsUse(true);
		
}

void Bullet::Uninit()
{
	// アニメーション表示
	Scene* scene;
	scene = Manager::GetScene();

	Effect* effect;
	effect = scene->AddGameObject<Effect>(goLayerType::EffectBillboard);
	effect->SetPosition(this->m_Position);

//	m_Particle->SetDestroy();

	delete m_ModelComponent;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

}

void Bullet::Update()
{
	m_ModelComponent->Update();

	Move();
	m_Particle->SetPosition(m_Position);

	m_DestroyCount--;
	if (m_DestroyCount < 0)SetDestroy();

	Scene* scene;
	scene = Manager::GetScene();

	// 当たり判定
	/*
	auto enemyList = scene->GetGameObjects<Enemy>();
	for (Enemy* enemy : enemyList)
	{
		XMFLOAT3 enemyPosition = enemy->GetPosition();
		if (Collision(this->GetPosition(), enemy->GetPosition(),
			2.0f))
		{
			this->SetDestroy();
			enemy->SetDestroy();

			break;
		}
	}
*/

	auto objectList = scene->GetGameObjects<GameObject>();
	for (GameObject* object : objectList)
	{
		if (object == scene->GetGameObject<Cylinder>() ||
			object == scene->GetGameObject<Box>() ||
			object == scene->GetGameObject<Bill>())
		{
			XMFLOAT3 objectPosition = object->GetPosition();

			if (OBBobjXscl(object, {2.0f,2.0f,2.0f}))
			{
				this->SetDestroy();
			}
		}
	}


	Player* player = scene->GetGameObject<Player>();
		if (OBBobjXscl(player,XMFLOAT3(2.0f,2.0f,2.0f)))
		{
			this->SetDestroy();
			player->Damage(10);
		}
}

void Bullet::Draw()
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
//	rot = XMMatrixRotationQuaternion(XMLoadFloat4(&m_Quatarnion));

	trans = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(world);

	m_ModelComponent->Draw();

}

void Bullet::Move()
{
	m_Accel = 100.0f;

	m_Velocity.x += m_Rotation.x * m_Accel;
	m_Velocity.y += m_Rotation.y * m_Accel;
	m_Velocity.z += m_Rotation.z * m_Accel;


	// 摩擦処理
	m_Velocity.x -= m_Velocity.x * 1.0f * m_dt;
	m_Velocity.y -= m_Velocity.y * 1.0f * m_dt;
	m_Velocity.z -= m_Velocity.z * 1.0f * m_dt;

	// 移動処理
	m_Position.x += m_Velocity.x * m_dt;
	m_Position.y += m_Velocity.y * m_dt;
	m_Position.z += m_Velocity.z * m_dt;

}

void Bullet::SetQuatarnion(XMFLOAT4 p)
{
	float x = p.x * 10;
	float y = p.y * 10;
	float z = p.z * 10;
	XMVECTOR quat = XMQuaternionRotationRollPitchYaw(x, y, z);
	quat = XMQuaternionMultiply(XMLoadFloat4(&m_Quatarnion), quat);
	XMStoreFloat4(&m_Quatarnion, quat);

//	m_Quatarnion = quatarnion;
}

void Bullet::SetParent(GameObject* parent)
{
	m_Parent = parent;

	m_Rotation = parent->GetForward();


	Scene* scene;
	scene = Manager::GetScene();

	Camera* camera = scene->GetGameObject<Camera>();

}

void Bullet::Accept(Component* component)
{
	m_component.push_back(component);

}
void Bullet::SetTargetPosition(XMFLOAT3 position)
{
	m_TargetPosition = position;
}
void Bullet::SetTargetObject(GameObject* _object)
{
		m_Target = _object;
		SetTargetPosition(m_Target->GetPosition());

}

void Bullet::TrackingBullet()
{
	Scene* scene;
	scene = Manager::GetScene();

	XMFLOAT3 targetPos = scene->GetGameObject<Player>()->GetPosition();

	XMFLOAT3 fofward = GetForward();
	

	m_Rotation.x = targetPos.x - sinf(m_Rotation.y);
	m_Rotation.z = targetPos.z - cosf(m_Rotation.y);

	m_Velocity.x += fofward.x * 0.1f;
	m_Velocity.y += fofward.y * 0.1f;
	m_Velocity.z += fofward.z * 0.1f;

	m_Position.x += m_Velocity.x * m_dt;
	m_Position.y += m_Velocity.y * m_dt;
	m_Position.z += m_Velocity.z * m_dt;
}


void tst()
{
	// ミサイルとターゲットの位置を表すXMFLOAT3
	XMFLOAT3 missilePosition = { 0.0f, 0.0f, 0.0f };
	XMFLOAT3 targetPosition = { 10.0f, 0.0f, 10.0f };

	// ミサイルの現在の向きを表すクォータニオン
	XMVECTOR missileRotation = XMQuaternionIdentity();

	// ミサイルの移動速度と回転速度（適宜調整）
	float missileSpeed = 1.0f;
	float rotationSpeed = 0.1f;

	// 1. ターゲット方向の計算
	XMFLOAT3 direction;
	XMStoreFloat3(&direction, XMVector3Normalize(XMLoadFloat3(&targetPosition) - XMLoadFloat3(&missilePosition)));

	// 2. 目標の向きの計算
	XMVECTOR targetRotation = XMQuaternionRotationMatrix(XMMatrixLookToRH(XMLoadFloat3(&missilePosition), XMLoadFloat3(&direction), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)));

	// 3. ミサイルの向きを補間 (SLERP)
	missileRotation = XMQuaternionSlerp(missileRotation, targetRotation, rotationSpeed);

	// 4. ミサイルの移動
	XMVECTOR forward = XMVector3Rotate(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), missileRotation);
	XMFLOAT3 forwardDirection;
	XMStoreFloat3(&forwardDirection, forward);

	// ミサイル位置の更新
	missilePosition.x += forwardDirection.x * missileSpeed;
	missilePosition.y += forwardDirection.y * missileSpeed;
	missilePosition.z += forwardDirection.z * missileSpeed;

}

