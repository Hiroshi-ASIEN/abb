#include "main.h"
#include "renderer.h"
#include "player.h"
//#include "modelRenderer.h"
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

#include "movePattern.h"
#include "movePatternWalk.h"
#include "movePatternSlide.h"
#include "meshField.h"

#include "score.h"
#include "modelRenderer.h"
#include <list>

#include "weaponCanon.h"
#include "weaponRifle.h"
#include "weaponMissile.h"
#include "enemyMachine.h"
#include "weaponSword.h"
#include "shadowPolygon2D.h"
#include "shadowVolume.h"
#include "selectScene.h"

#include "game.h"

#include "testObject.h"
//TestObject* test{};



Component* Player::m_ModelComponent{};
void Player::Load()
{
	m_ModelComponent = new AnimationModel;
	((AnimationModel*)m_ModelComponent)->Load("asset\\animationmodel\\Paladin_J_Nordstrom.fbx");
	((AnimationModel*)m_ModelComponent)->LoadAnimation("asset\\animationmodel\\Warrior_Idle.fbx", "Idle");
	((AnimationModel*)m_ModelComponent)->LoadAnimation("asset\\animationmodel\\Slow_Run.fbx", "Run");
	((AnimationModel*)m_ModelComponent)->LoadAnimation("asset\\animationmodel\\Right_Strafe.fbx", "RightRun");
	((AnimationModel*)m_ModelComponent)->LoadAnimation("asset\\animationmodel\\Left_Strafe.fbx", "LeftRun");
	((AnimationModel*)m_ModelComponent)->LoadAnimation("asset\\animationmodel\\Run_To_Stop.fbx", "StopRun");
}

void Player::Unload()
{
	m_ModelComponent->Uninit();
	delete m_ModelComponent;
}
void Player::Init()
{
		
	// モデル
	//------------------------------------------------------------------------------------------------------------------------------------------------------
//	this->AddComponent<ModelRenderer>();
//	this->GetComponent<ModelRenderer>()->Load("asset\\mymodel\\eplayer.obj");
//------------------------------------------------------------------------------------------------------------------------------------------------------

	//------------------------------------------------------------------------------------------------------------------------------------------------------
	// アニメーションモデル
	//------------------------------------------------------------------------------------------------------------------------------------------------------
	/*
	this->AddComponent<AnimationModel>();

	this->GetComponent<AnimationModel>()->Load("asset\\animationmodel\\Paladin_J_Nordstrom.fbx");
	this->GetComponent<AnimationModel>()->LoadAnimation("asset\\animationmodel\\Warrior_Idle.fbx", "Idle");
	this->GetComponent<AnimationModel>()->LoadAnimation("asset\\animationmodel\\Slow_Run.fbx", "Run");
	this->GetComponent<AnimationModel>()->LoadAnimation("asset\\animationmodel\\Right_Strafe.fbx", "RightRun");
	this->GetComponent<AnimationModel>()->LoadAnimation("asset\\animationmodel\\Left_Strafe.fbx", "LeftRun");
	this->GetComponent<AnimationModel>()->LoadAnimation("asset\\animationmodel\\Run_To_Stop.fbx", "StopRun");
	*/
	
	m_AnimationMovePatern = "Idle";
	m_NextAnimationMovePatern = "Idle";

	m_AnimationFrame = 0;
	m_Scale = { 0.01f,0.01f,0.01f };

		Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\unlitTextureVS.cso");
		Renderer::CreatePixelShader(&m_PixelShader, "shader\\unlitTexturePS.cso");

//		Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\cookTrranceVS.cso");
//		Renderer::CreatePixelShader(&m_PixelShader, "shader\\cookTrrancePS.cso");

		// SEロード
		// オーディオインスタンス化
		m_SE = new Audio(this);
		m_SE->Load("asset\\audio\\seshot01free.wav");

		Scene* scene;
		scene = Manager::GetScene();

		//------------------------------------------------------------------------------------------------------------------------------------------------------
		// パーティクルエミッターセット
		//------------------------------------------------------------------------------------------------------------------------------------------------------

		m_Particle = scene->AddGameObject<ParticleEmitter>(goLayerType::Particle);
		m_Particle->SetParent(this);
		m_Particle->SetPosition(XMFLOAT3((this->GetPosition().x), (this->GetPosition().y+50.0f),(this->GetPosition().z)));
		m_Particle->SetType(ParticleType::tJumpBooster);
		m_Particle->SetMaterialColor(XMFLOAT4(0.1f,0.1f,0.7f,0.7f));

		m_MParticle = scene->AddGameObject<ParticleEmitter>(goLayerType::Particle);
		m_MParticle->SetOffSet({0.0f,1.0f,0.0f});
		m_MParticle->SetRotation({0.0f,0.0f,0.0f});
		m_MParticle->SetParent(this);
		m_MParticle->SetType(ParticleType::tBooster);
		m_MParticle->SetMaterialColor(XMFLOAT4(0.3f, 0.5f, 0.7f, 0.3f));

		m_LRParticle = scene->AddGameObject<ParticleEmitter>(goLayerType::Particle);
		m_LRParticle->SetParent(this);
		m_LRParticle->SetOffSet({ 0.0f,0.0f,0.0f });
		m_LRParticle->SetRotation({ 0.0f,0.0f,90.0f });
		m_LRParticle->SetType(ParticleType::tFire);
		m_LRParticle->SetMaterialColor(XMFLOAT4(0.2f, 0.4f, 0.7f, 0.3f));

		m_BParticle = scene->AddGameObject<ParticleEmitter>(goLayerType::Particle);
		m_BParticle->SetParent(this);
		m_BParticle->SetOffSet({ 0.0f,0.0f,0.0f });
		m_BParticle->SetRotation({ 0.0f,0.0f,90.0f });
		m_BParticle->SetType(ParticleType::tFire);
		m_BParticle->SetMaterialColor(XMFLOAT4(0.2f, 0.4f, 0.7f, 0.3f));

//		m_LRParticle->SetIsUse(true);		// パーティクルエミッター起動
		m_Particle->SetIsUse(false);		// パーティクルエミッターオフ
		m_MParticle->SetIsUse(false);		// パーティクルエミッターオフ
		m_BParticle->SetIsUse(false);
		m_LRParticle->SetIsUse(false);		// パーティクルエミッターオフ

		//------------------------------------------------------------------------------------------------------------------------------------------------------

		// m_Quatarnionの初期化
		m_Quatarnion.x = 0.0f;
		m_Quatarnion.y = 0.0f;
		m_Quatarnion.z = 0.0f;
		m_Quatarnion.w = 1.0f;

		m_BEmax = 250.0f;
		m_BoostEnergy = m_BEmax;
		m_BoostPower = 1.0f;
		m_Accel = { 0.5f,0.0f,0.5f };
//		ChangeMovePattern(new MovePatternWalk);

//		Camera* camera = scene->GetGameObject<Camera>();
		camera = scene->GetGameObject<Camera>();
		scene->GetGameObject<Menu>()->SetPlayer(this);
	//------------------------------------------------------------------------------------------------------------------------------------------------------
	// サーチ用コリジョン
	//------------------------------------------------------------------------------------------------------------------------------------------------------
		this->AddComponent<SearchCollision>();
		this->GetComponent<SearchCollision>()->SetParent(this);
//		this->GetComponent<SearchCollision>()->SetOffSet({ 0.0f,0.0f,15.0f });
		this->GetComponent<SearchCollision>()->SetOffSet({ 0.0f,0.0f,0.0f });
		this->GetComponent<SearchCollision>()->SetScale({ 20.0f,10.0f,30.0f });
		this->GetComponent<SearchCollision>()->SetRotation({ 0.0f,0.0f,0.0f });

		m_UI = scene->AddGameObject<UI>(goLayerType::Texture2d);
		m_UI->InitSet(L"asset\\texture\\white.png", XMFLOAT4(100, 300, 500, 500), 0);
		m_UI->SetPos(XMFLOAT4(400.0f, 600.0f, 600.0f * (m_BoostEnergy / 250), 25));
		m_UI->SetColor({ 0.3f,0.5f, 1.0f, 1.0f });


		m_GageFrame = scene->AddGameObject<UI>(goLayerType::Texture2d);
		m_GageFrame->InitSet(L"asset\\texture\\aGa.png", XMFLOAT4(100, 100, 200, 200), 0);
		m_GageFrame->SetPos(XMFLOAT4(400.0f, 600.0f, 600.0f, 25));

		m_HpBar = scene->AddGameObject<UI>(goLayerType::Texture2d);
		m_HpBar->InitSet(L"asset\\texture\\aOga.png", XMFLOAT4(500, 400, 1000, 1000), 0);
		m_HpBar->SetPos(XMFLOAT4(400.0f, 550.0f, 600.0f * (m_Hp / 100), 50));
		m_HpBar->SetColor({ 1.0f,0.5f, 0.3f, 1.0f });


		m_HpFrame = scene->AddGameObject<UI>(goLayerType::Texture2d);
		m_HpFrame->InitSet(L"asset\\texture\\aGa.png", XMFLOAT4(100, 100, 200, 200), 0);
		m_HpFrame->SetPos(XMFLOAT4(400.0f, 550.0f, 600.0f, 50));


		m_Material = { 1.0f,1.0f,1.0f,1.0f };

//		m_ChildModel = new ModelRenderer(this);
//		((ModelRenderer*)m_ChildModel)->Load("asset\\model\\box.obj");


//		WeaponAccept(WEAPON_TYPE::RIFLE, WeaponPosition::WP_L_ARM);
//		WeaponAccept(WEAPON_TYPE::MISSILE, WeaponPosition::WP_R_ARM);
		WeaponAccept(SelectScene::GetSelectLWeapon(), WeaponPosition::WP_L_ARM);
		WeaponAccept(SelectScene::GetSelectRWeapon(), WeaponPosition::WP_R_ARM);

		m_RArmWepon->SetParent(this);
		m_RArmWepon->AutoTarget(false);
		m_RArmWepon->SetOffSet({ 0.0f,3.0f,0.0f });

		m_LArmWepon->SetParent(this);
		m_LArmWepon->AutoTarget(false);
		m_LArmWepon->SetOffSet({ 0.0f,3.0f,0.0f });

		// 影
		m_ShadowVolume = scene->AddGameObject<ShadowVolume>(goLayerType::Object3d);
		m_ShadowPolygon2D = scene->AddGameObject<ShadowPolygon2D>(goLayerType::Object3d);

		camera->SetTarget(this);

//		test = scene->AddGameObject<TestObject>(goLayerType::Object3d);
		
}

void Player::Uninit()
{

	for (Component* component : m_Component)
	{
		component->Uninit();
		delete component;
	}
	m_Component.clear();

//	m_ChildModel->Uninit();
//	delete m_ChildModel;


	m_SE->Uninit();
	delete m_SE;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

}

void Player::Update()
{
	if (Defeated()) return;

	Move();
	CheckPosition();
	WeaponMove();
	m_Particle->SetPosition(this->GetPosition());
//	 m_AnimeTime += 0.1;		// 簡易アニメーション
	Attack();

	if (Input::GetKeyPress('0')) m_Hp--;


	if (m_InvisibleTime < PLAYER_INVINSIBLE_TIME_MAX)
	{
		m_InvisibleTime--;
	}
	if (m_InvisibleTime < 0)
	{
		m_InvisibleTime = PLAYER_INVINSIBLE_TIME_MAX;
		m_Material = { 1.0f,0.5f,0.3f,1.0f };
		m_HpBar->SetColor({ m_Material });
	}


	m_UI->SetPos(XMFLOAT4(400.0f, 600.0f, 600.0f * (m_BoostEnergy / 250), 25));
	m_HpBar->SetPos(XMFLOAT4(400.0f, 550.0f, 600.0f * (m_Hp / 100), 50));
	
//	m_ChildModel->SetPosition(XMFLOAT3(this->m_Position.x - GetRight().x, this->m_Position.y + 3.0f, this->m_Position.z - GetRight().z));
//	m_ChildModel->SetRotation(m_CameraRotation);


//	m_LShoulderWepon->SetRotation(m_CameraRotation);
//	m_RShoulderWepon->SetRotation(m_CameraRotation);

}

void Player::Draw()
{
	// c_str()でchar型に変換できる
	((AnimationModel*)m_ModelComponent)->Update(m_AnimationMovePatern.c_str(), m_AnimationFrame,
		m_NextAnimationMovePatern.c_str(), m_AnimationFrame, m_Blend);

//	this->GetComponent<AnimationModel>()->Update(m_AnimationMovePatern.c_str(), m_AnimationFrame,
//													m_NextAnimationMovePatern.c_str(), m_AnimationFrame,m_Blend);
//	this->GetComponent<AnimationModel>()->Update("Idle", m_AnimationFrame,"Run",m_AnimationFrame,0.0f);

	m_AnimationFrame++;

	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	Renderer::SetMaterial(MATERIAL{ m_Material });
	// シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// ワールドマトリクス設定
	XMMATRIX world, scale, rot, trans;
	scale = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);	

	// 通常
	rot = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
//	rot = XMMatrixRotationQuaternion(XMLoadFloat4(&m_Quatarnion));

// 180度モデルを回転させて描画（軸）
//	rot = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y + XM_PI, m_Rotation.z);

//	trans = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
  	trans = XMMatrixTranslation(m_Position.x, m_Position.y+sinf(m_AnimeTime)*0.1f, m_Position.z);
	// sinf(m_AnimeTime)*0.1
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(world);

//	m_Component->Draw();
//	this->GetComponent<ModelRenderer>()->Draw();
//	this->GetComponent<AnimationModel>()->Draw();
	((AnimationModel*)m_ModelComponent)->Draw();
	
	/*
// 子モデル描画
	XMMATRIX childScale, childRot, childTrans, childWorld;
	XMMATRIX rightHandMatrix;
	rightHandMatrix = this->GetComponent<AnimationModel>()->ConvertXMMatrix(this->GetComponent<AnimationModel>()->GetWorldMatrix("mixamorig:RightHandThumb1"));
	childScale = XMMatrixScaling(1.0f / m_Scale.x, 1.0f / m_Scale.y, 1.0f / m_Scale.z);
	childRot = XMMatrixRotationRollPitchYaw(0.0f, 1.0f, 0.0f);
	childTrans = XMMatrixTranslation(0.0f, 0.0f, 3.0f);
	childWorld = childRot * childTrans * childScale * rightHandMatrix * world; 	// 親のworldmatrixを混ぜる
		
	Renderer::SetWorldMatrix(childWorld);
	 */

//	m_ChildModel->Draw();
	m_LArmWepon->Draw();
	m_RArmWepon->Draw();
//	m_LShoulderWepon->Draw();
//	m_RShoulderWepon->Draw();

}


void Player::Move()
{
	XMFLOAT3 oldPosition = this->m_Position;
	int oldMoveType = m_MoveType;

	Scene* scene;
	scene = Manager::GetScene();

	XMFLOAT3 cForward = camera->GetForward();
	XMFLOAT3 cRight= camera->GetRight();
	m_Particle->SetIsUse(false);		// パーティクルエミッターオフ
	m_MParticle->SetIsUse(false);		// パーティクルエミッターオフ

	if (Input::GetKeyTrigger(VK_LCONTROL))
//	if (Input::GetKeyTrigger('Q'))
	{
//		m_MovePattern->Update(this);
	}
	
	if (m_MoveType == Walk)
	{
		m_Accel.x = 0.05f;
		m_Accel.z = 0.05f;

		if (Input::GetKeyTrigger(VK_LCONTROL))
		{
			m_BParticle->SetIsUse(true);
			m_MoveType = Slide;
		}
	}
	else if (m_MoveType == Slide)
	{
//		m_Accel.x = 0.2f;
//		m_Accel.z = 0.2f;
//		m_Accel.x = 0.5f;	// 5が気持ちいい
//		m_Accel.z = 0.5f;

		if (Input::GetKeyTrigger(VK_LCONTROL))
	{
			m_BParticle->SetIsUse(false);
			m_MoveType = Walk;
		}
	}

//	if (Input::GetKeyTrigger(VK_LSHIFT))				// 回避

	if (Input::GetKeyTrigger(WM_RBUTTONDOWN))				// 回避
	{
		Away();
		GetComponent<SearchCollision>()->Uninit();
	}
	if (Input::GetKeyPress(VK_LSHIFT))				// 上入力
	{
		Boost();
	}
	if (Input::GetKeyPress('W'))				// 上入力
	{
		UpMove(cForward);
	}
	if (Input::GetKeyPress('A'))				// 左入力
	{
		LeftMove(cRight);
	}
	if (Input::GetKeyPress('S'))				// 下入力
	{
		DownMove(cForward);
	}
	if (Input::GetKeyPress('D'))				// 右入力
	{
		RightMove(cRight);
	}
	// 移動状態
	if (Input::GetKeyPress('W') ||
		Input::GetKeyPress('A') ||
		Input::GetKeyPress('S') ||
		Input::GetKeyPress('D'))
	{
		ChangeAnimation("Run");
	}
	// 無移動状態
	if (!Input::GetKeyPress('W') &&
		!Input::GetKeyPress('A') &&
		!Input::GetKeyPress('S') &&
		!Input::GetKeyPress('D'))				// 十字移動未入力
	{
		// 摩擦処理
		m_Velocity.x -= m_Velocity.x * 5.0f * m_dt;
		m_Velocity.z -= m_Velocity.z * 5.0f * m_dt;

		ChangeAnimation("Idle");
	}
	m_Blend += 0.1f;
	if (m_Blend >= 1.0f)
	{
		m_Blend = 1.0f;
	}

	
	if (m_MoveTriger)
	{
		m_AnimationMovePatern = "StopRun";
		if (m_AnimationFrame>60)
		{
			m_MoveTriger = false;
		}
	}


	if (Input::GetKeyPress(VK_SPACE))
	{
		PJump();
	}
	if (m_JumpUse == false)
	{
//		m_BoostPower = m_BPmax;
		if (m_BoostEnergy < m_BEmax)	m_BoostEnergy += 2.5f;
		else m_BoostEnergy = m_BEmax;
	}

	// 重力
	if (m_MoveType == Slide)	m_Velocity.y -= 0.015f;
	else m_Velocity.y -= 0.02f;



	// 移動処理
	m_Position.y += m_Velocity.y;

//	m_Rotation.y = scene->GetGameObject<Camera>()->GetRotation().y;

	//// 摩擦処理
	m_Velocity.x -= m_Velocity.x * 1.0f * m_dt;
	m_Velocity.z -= m_Velocity.z * 1.0f * m_dt;

	//// 移動処理
	m_Position.x += m_Velocity.x * m_dt;
	m_Position.z += m_Velocity.z * m_dt;

	if (m_BoostPower > 1.0f)m_BoostPower *= 0.8f;
	else m_BoostPower = 1.0f;

	if (m_Accel.y > 0.5f) m_Accel.y *= 0.8f;
	else	m_Accel.y = 0.5f;
/*
	if (m_Accel.x > 0.5f) m_Accel.x *= 0.8f;
	else	m_Accel.x = 0.5f;


	if (m_Accel.z > 0.5f) m_Accel.z *= 0.8f;
	else	m_Accel.z = 0.5f;
	*/

	if (m_PCRotate)
	{
		// 常にカメラが向いている方向を向き続ける
		m_Rotation.y = camera->GetRotation().y;
//		m_Rotation.x = camera->GetCameraRotY() - 4.8f;
		m_CameraRotation.x = camera->GetCameraRotY() + 4.3f;// -0.5f;
		m_CameraRotation.y = m_Rotation.y;
	}
	else if (!m_PCRotate)
	{
//		if (Input::GetKeyTrigger(VK_RCONTROL)) { m_PCRotate = true; }
		if (Input::GetKeyTrigger('I')) { m_PCRotate = false; }
	}

	if (Input::GetKeyTrigger('1'))
	{
		int i = 0;
	}
	// 地面の高さ
	float groundHeight = 0.0f;
	float skyHeight = 50.0f;
	

	XMFLOAT3 p;
	p.x = this->GetPosition().x;
	p.y = this->GetPosition().y;
	p.z = this->GetPosition().z;

	groundHeight = scene->GetGameObject<MeshField>()->GetHeight(p);

	if (Input::GetKeyTrigger('O'))
	{
		int i = 0;
	}
	// 円柱との衝突判定
	auto cylinderList = scene->GetGameObjects<Cylinder>();

	for (Cylinder* cylinder : cylinderList)
	{
		XMFLOAT3 cylinderPosition = cylinder->GetPosition();
		XMFLOAT3 cylinderScale = cylinder->GetScale();

		XMFLOAT3 direction = {};
		direction.x = this->m_Position.x - cylinderPosition.x;
		direction.y = this->m_Position.y - cylinderPosition.y;
		direction.x = this->m_Position.z - cylinderPosition.z;

		if (CollisionCircle(this->GetPosition(), cylinder->GetPosition(),
			cylinderScale.x))
		{
			if (-direction.y < cylinderScale.y - 0.5f)
			{
				groundHeight = cylinderPosition.y + cylinderScale.y;
			}
			else
			{
				this->m_Position.x = oldPosition.x;
				this->m_Position.z = oldPosition.z;

			}
		}
	}

	// 箱との衝突判定
	auto boxList = scene->GetGameObjects<Box>();

	for (Box* box : boxList)
	{

		XMFLOAT3 boxPosition = box->GetPosition();
		XMFLOAT3 boxScale = box->GetScale();
		if (OBB(m_Position, boxPosition,boxScale,box->GetForward(),box->GetUp(),box->GetRight()))
		{
			groundHeight = boxPosition.y + boxScale.y;// *0.5;
//			this->m_Position.x = oldPosition.x;
//			this->m_Position.z = oldPosition.z;

		}
		else
		{
		}

	}
	// 箱との衝突判定
	auto billList = scene->GetGameObjects<Bill>();

	for (Bill* bill : billList)
	{

		XMFLOAT3 billPosition = bill->GetPosition();
		XMFLOAT3 billScale = { bill->GetScale().x * 0.7f, bill->GetScale().y, bill->GetScale().z * 0.7f };
		if (OBBobjXscl(bill,billScale))
		{
			groundHeight = billPosition.y + billScale.y *0.5;
//			this->m_Position.x = oldPosition.x;
//			this->m_Position.z = oldPosition.z;

		}
		else
		{
		}
	}
		/*
	// 箱との衝突判定
	auto billList = scene->GetGameObjects<Bill>();

	for (Bill* bill : billList)
	{
		XMFLOAT3 billPosition = bill->GetPosition();
		XMFLOAT3 billScale = bill->GetScale();

		XMFLOAT3 direction = {};
		direction.x = this->m_Position.x - billPosition.x;
		direction.y = this->m_Position.y - billPosition.y;
		direction.x = this->m_Position.z - billPosition.z;

		if (CollisionBB(this->GetPosition(), bill->GetPosition(),
			this->GetScale(), bill->GetScale()))
		{
			if (-direction.y < billScale.y - 0.5f)
			{
				groundHeight = billPosition.y + billScale.y * 0.5;
			}
			else
			{
				this->m_Position.x = oldPosition.x;
				this->m_Position.z = oldPosition.z;

			}
		}
	}
		*/

	if (m_Position.y < groundHeight)
	{
		m_Position.y = groundHeight; 	// 着地時処理
		m_Velocity.y = 0.0f;
		m_Accel.y = 0.0f;
		m_JumpUse = false;		// 着地したらジャンプ可能になる
	}
	if (m_Position.y >skyHeight)
	{
		m_Position.y = skyHeight; 	// 着空？時処理
		m_Velocity.y = 0.0f;
		m_Accel.y = 0.0f;
	}




	this->GetComponent<SearchCollision>()->UpdateSearchCollisionPositionRotation();// ->UpdatePositionPlayerRotation();
//	this->GetComponent<SearchCollision>()->SetRotation({ -sinf(m_Rotation.y),m_Rotation.y,-cosf(m_Rotation.y) });
//	test->SetPosition(this->GetComponent<SearchCollision>()->GetPosition());	// サーチコリジョン視覚化用


	m_ShadowVolume->SetPosition({ m_Position.x,groundHeight,m_Position.z });
	m_ShadowPolygon2D->SetPosition({ m_Position.x,groundHeight,m_Position.z });
}

void Player::Attack()
{
	if (Input::GetKeyPress(WM_LBUTTONDOWN))
	{
		EnemyMachine* target = this->GetComponent<SearchCollision>()->GetNearEnemy(1);
		if (target != nullptr)
		{
			m_Target = target;
		}

		LArmAttack();
	}
//	if (Input::GetKeyTrigger(WM_RBUTTONDOWN))
	if (Input::GetKeyPress('E'))
	{
		EnemyMachine* target = this->GetComponent<SearchCollision>()->GetNearEnemy(1);
		if (target != nullptr)
		{
			m_Target = target;
		}

		RArmAttack();
	}

	if (Input::GetKeyTrigger('Z'))
	{
		m_LArmWepon->MagazineReload();
	}
	if (Input::GetKeyTrigger('C'))
	{
		m_RArmWepon->MagazineReload();
	}
	/*
	if (Input::GetKeyTrigger('Q'))
	{
		LShoulderAttack();
	}
	if (Input::GetKeyTrigger('E'))
	{
		RShoulderAttack();
	}
	*/
	if (Input::GetKeyTrigger('P'))
	{
		PAttack();
		m_MParticle->SetIsUse(true);		// パーティクルエミッター起動

	}
}

bool Player::Boost()
{
	if (m_BoostEnergy <= m_BEmax*0.1f)return false;

		m_BoostEnergy -= 10.0f;
		m_BoostPower = 2.0f;

		m_MParticle->SetIsUse(true);		// パーティクルエミッター起動

		return true;
}

bool Player::Away()
{
	if (m_BoostEnergy <= 0) return false;

	m_BoostEnergy -= 100.0f;
	m_BoostPower = 20.0f;
	/*
	m_Accel.x = 10.0f;
	m_Accel.z = 10.0f;
*/
	m_Particle->SetIsUse(true);

	return true;
}

void Player::LArmAttack()
{
	// 攻撃 (falseは弾不足で攻撃できなかった場合)
	m_LArmWepon->Attack();
	// 攻撃できなかった場合リロード
}
void Player::RArmAttack()
{

	m_RArmWepon->Attack();
	/*
	Scene* scene;
	scene = Manager::GetScene();

	Bullet* bullet;
	bullet = scene->AddGameObject<BulletMissile>(goLayerType::Object3d);
	bullet->SetParent(this);
	bullet->SetPosition(XMFLOAT3(this->m_Position.x + GetRight().x, this->m_Position.y + 1.0f, this->m_Position.z + GetRight().z));
	bullet->SetTargetObject(target);

//	bullet->SetTargetPosition(XMFLOAT3(10.0f,3.0f,10.0f));
	bullet->SetScale(XMFLOAT3(1.0f, 1.0f, 1.0f));
	*/


//	m_SE->Play();
}
void Player::LShoulderAttack()
{
	Scene* scene;
	scene = Manager::GetScene();

	Bullet* bullet;
	bullet = scene->AddGameObject<Bullet>(goLayerType::Object3d);
	bullet->SetParent(this);
	bullet->SetPosition(XMFLOAT3(this->m_Position.x - GetRight().x, this->m_Position.y + 3.0f, this->m_Position.z - GetRight().z));
	bullet->SetScale(XMFLOAT3(1.0f, 1.0f, 1.0f));

	m_SE->Play();

}
void Player::RShoulderAttack()
{
	Scene* scene;
	scene = Manager::GetScene();

	Bullet* bullet;
	bullet = scene->AddGameObject<Bullet>(goLayerType::Object3d);
	bullet->SetParent(this);
	bullet->SetPosition(XMFLOAT3(this->m_Position.x + GetRight().x, this->m_Position.y + 1.0f, this->m_Position.z + GetRight().z));
	bullet->SetScale(XMFLOAT3(1.0f, 1.0f, 1.0f));

	m_SE->Play();
}
void Player::PAttack()
{
	Scene* scene;
	scene = Manager::GetScene();

	Bullet* bullet;
	bullet = scene->AddGameObject<Bullet>(goLayerType::Object3d);
	bullet->SetParent(this);
	bullet->SetPosition(XMFLOAT3(this->m_Position.x, this->m_Position.y, this->m_Position.z));
	bullet->SetScale(XMFLOAT3(1.0f, 1.0f, 1.0f));

	m_SE->Play();
}


void Player::AddKillCount(int count)
{
	m_KillCount += count;

}

int Player::GetKillCount()
{
	return m_KillCount;
}


void Player::UpMove(XMFLOAT3 cForward)
{
	m_Velocity.x += cForward.x *m_Accel.x* m_BoostPower;
	m_Velocity.z += cForward.z *m_Accel.z* m_BoostPower;

//	m_Rotation.y = scene->GetGameObject<Camera>()->GetRotation().y;
	m_Rotation.y = camera->GetRotation().y;
}

void Player::DownMove(XMFLOAT3 cForward)
{
	m_Velocity.x -= cForward.x * m_Accel.x* m_BoostPower;
	m_Velocity.z -= cForward.z * m_Accel.z* m_BoostPower;

	m_Rotation.y = camera->GetRotation().y - 110.0f;

}


void Player::LeftMove(XMFLOAT3 cRight)
{
	m_Velocity.x -= cRight.x * m_Accel.x* m_BoostPower;
	m_Velocity.z -= cRight.z * m_Accel.z* m_BoostPower;

	m_Rotation.y = camera->GetRotation().y - 90.0f;

//	m_AnimationMovePatern = "LeftRun";
}

void Player::RightMove(XMFLOAT3 cRight)
{
	m_Velocity.x += cRight.x * m_Accel.x* m_BoostPower;
	m_Velocity.z += cRight.z * m_Accel.z* m_BoostPower;

	m_Rotation.y = camera->GetRotation().y + 90.0f;

//	m_AnimationMovePatern = "RightRun";
}

// 所持している武器の動き(主に追従移動系）
void Player::WeaponMove()
{
	if (m_LArmWepon == nullptr)return;

	m_LArmWepon->SetDirection(m_CameraRotation);
	m_LArmWepon->SetPosition(XMFLOAT3
	((GetPosition().x - GetRight().x) + m_LArmWepon->GetOffSet().x,
	 GetPosition().y + m_LArmWepon->GetOffSet().y,
	 (GetPosition().z - GetRight().z) + m_LArmWepon->GetOffSet().z));

	if (m_RArmWepon == nullptr)return;

	m_RArmWepon->SetDirection(m_CameraRotation);
	m_RArmWepon->SetPosition(XMFLOAT3
	((GetPosition().x + GetRight().x) + m_RArmWepon->GetOffSet().x,
		GetPosition().y + m_RArmWepon->GetOffSet().y,
		(GetPosition().z + GetRight().z) + m_RArmWepon->GetOffSet().z));

}

int Player::GetHp()
{
	return m_Hp;
}

void Player::ChangeMovePattern(MovePattern* movepattern)
{
	delete m_MovePattern;
	m_MovePattern = movepattern;
}

bool Player::Defeated()
{
	if (m_Hp > 0.0f) return false;

	m_DestroyCount++;

	if (m_Rotation.x < 90.0f)
	{
		m_Rotation.x += 1.0f;
	}

	if (m_DestroyCount < DESTROY_COUNT) return false;

	Game::GameEnd(false);
	return true;
}

void Player::PJump()
{
	if (m_BoostEnergy <= 0.0f)return;
	m_JumpUse = true;
	m_BoostEnergy -= 2.0f;

	if (m_MoveType == Slide)	m_Velocity.y += 0.025f;
	else m_Velocity.y += 0.021f;

	m_Particle->SetIsUse(true);		// パーティクルエミッター起動
}

void Player::ChangeAnimation(std::string nextAnimation)
{
	if (m_NextAnimationMovePatern != nextAnimation)
	{
		m_AnimationMovePatern = m_NextAnimationMovePatern;
		m_NextAnimationMovePatern = nextAnimation;
		m_Blend = 0.0f;
	}
}

bool Player::Damage(int damage)
{
	if (m_InvisibleTime < PLAYER_INVINSIBLE_TIME_MAX)return false;
	if (damage < 0)return false;

	m_Hp -= damage;
	m_InvisibleTime--;
	m_Material = { 1.0f,1.0f,1.0f,1.0f };
	m_HpBar->SetColor({ m_Material });

	return true;
}

void Player::WeaponAccept(WEAPON_TYPE _weapon, WeaponPosition _position)
{
	WeaponBase* wp{};
	Scene* scene = Manager::GetScene();
	//if (m_LArmWepon != nullptr)
	//{
	//	m_LArmWepon->SetDestroy();
	//	m_LArmWepon->Destroy();
	//}
	switch (_weapon)
	{
	case CANON:
		wp = scene->AddGameObject<WeaponCanon>(goLayerType::Object3d);
//		wp->AutoTarget(false);
		break;
	case RIFLE:
		wp = scene->AddGameObject<WeaponRifle>(goLayerType::Object3d);
//		wp->AutoTarget(false);
		break;
	case MISSILE:

		wp = scene->AddGameObject<WeaponMissile>(goLayerType::Object3d);
		break;
	case Sword:
		wp = scene->AddGameObject<WeaponSword>(goLayerType::Object3d);
		break;

	case WT_MAX:
		break;
	default:
		break;
	}
	switch (_position)
	{
	case WP_Center:
		m_CenterWepon = wp;
		break;
	case WP_L_ARM:

		m_LArmWepon = wp;
		m_LArmWepon->SetOffSet({ 0.0f,3.0f,0.0f });

		break;
	case WP_R_ARM:
		m_RArmWepon = wp;
		m_RArmWepon->SetOffSet({ 0.0f,3.0f,0.0f });

		break;
	case WP_L_SHOULDER:
		m_LShoulderWepon = wp;
		break;
	case WP_R_SHOULDER:
		m_RShoulderWepon = wp;
		break;
	case WP_MAX:
		m_ChildModel->SetDestroy();
		m_ChildModel = wp;
		break;
	default:
		break;
	}
	wp->SetParent(this);

}


float Player::CheckPosition()
{
	int oldMoveType = m_MoveType;

	Scene* scene;
	scene = Manager::GetScene();

	// 地面の高さ
	float groundHeight = 0.0f;
	float skyHeight = 50.0f;


	XMFLOAT3 p;
	p.x = this->GetPosition().x;
	p.y = this->GetPosition().y;
	p.z = this->GetPosition().z;

	// 地面との衝突判定
	groundHeight = scene->GetGameObject<MeshField>()->GetHeight(p);


	// 円柱との衝突判定
	auto cylinderList = scene->GetGameObjects<Cylinder>();

	for (Cylinder* cylinder : cylinderList)
	{
		XMFLOAT3 cylinderPosition = cylinder->GetPosition();
		XMFLOAT3 cylinderScale = cylinder->GetScale();

		XMFLOAT3 direction = {};
		direction.x = this->m_Position.x - cylinderPosition.x;
		direction.y = this->m_Position.y - cylinderPosition.y;
		direction.x = this->m_Position.z - cylinderPosition.z;

		if (CollisionCircle(this->GetPosition(), cylinder->GetPosition(),
			cylinderScale.x))
		{
			if (-direction.y < cylinderScale.y - 0.5f)
			{
				groundHeight = cylinderPosition.y + cylinderScale.y;
			}
			else
			{
				this->m_Position.x = oldPosition.x;
				this->m_Position.z = oldPosition.z;

			}
		}
	}

	// 箱との衝突判定
	auto boxList = scene->GetGameObjects<Box>();

	for (Box* box : boxList)
	{

		XMFLOAT3 boxPosition = box->GetPosition();
		XMFLOAT3 boxScale = box->GetScale();
		if (OBB(m_Position, boxPosition, boxScale, box->GetForward(), box->GetUp(), box->GetRight()))
		{
			groundHeight = boxPosition.y + boxScale.y;// *0.5;
			//			this->m_Position.x = oldPosition.x;
			//			this->m_Position.z = oldPosition.z;

		}
		else
		{
		}
	}

	// 箱との衝突判定
	auto billList = scene->GetGameObjects<Bill>();

	for (Bill* bill : billList)
	{
		XMFLOAT3 billPosition = bill->GetPosition();
		XMFLOAT3 billScale = bill->GetScale();

		XMFLOAT3 direction = {};
		direction.x = this->m_Position.x - billPosition.x;
		direction.y = this->m_Position.y - billPosition.y;
		direction.x = this->m_Position.z - billPosition.z;

		if (CollisionBB(this->GetPosition(), bill->GetPosition(),
			this->GetScale(), bill->GetScale()))
		{
			if (-direction.y < billScale.y - 0.5f)
			{
				groundHeight = billPosition.y + billScale.y * 0.5f;
			}
			else
			{
				this->m_Position.x = oldPosition.x;
				this->m_Position.z = oldPosition.z;

			}
		}
	}
	XMFLOAT3 field = scene->GetGameObject<MeshField>()->GetFieldScale();
	if (m_Position.x < -field.x || m_Position.x > field.x) m_Position.x = oldPosition.x;
	if (m_Position.z < -field.z || m_Position.z > field.z) m_Position.z = oldPosition.z;

	if (m_Position.y < groundHeight)
	{
		m_Position.y = groundHeight; 	// 着地時処理
		m_Velocity.y = 0.0f;
		m_Accel.y = 0.0f;
		m_JumpUse = false;		// 着地したらジャンプ可能になる
	}
	if (m_Position.y > skyHeight)
	{
		m_Position.y = skyHeight; 	// 着空？時処理
		m_Velocity.y = 0.0f;
		m_Accel.y = 0.0f;
	}
	oldPosition = this->m_Position;
	return groundHeight;
}



void Player::ModelCreate()
{
}
