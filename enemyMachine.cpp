#include "main.h"
#include "renderer.h"
#include "enemyMachine.h"
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
#include "game.h"
#include "enemyAIState.h"

void EnemyMachine::Init()
{
		
	// モデル
	//------------------------------------------------------------------------------------------------------------------------------------------------------
//	this->AddComponent<ModelRenderer>();
//	this->GetComponent<ModelRenderer>()->Load("asset\\mymodel\\eenemyMachine.obj");
//------------------------------------------------------------------------------------------------------------------------------------------------------

	//------------------------------------------------------------------------------------------------------------------------------------------------------
	// アニメーションモデル
	//------------------------------------------------------------------------------------------------------------------------------------------------------

	this->AddComponent<AnimationModel>();

	// テスト用
	/*
	this->GetComponent<AnimationModel>()->Load("asset\\model\\Akai.fbx");
	this->GetComponent<AnimationModel>()->LoadAnimation("asset\\model\\Akai_Idle.fbx", "Idle");
	this->GetComponent<AnimationModel>()->LoadAnimation("asset\\model\\Akai_Run.fbx", "Run");
	*/

	this->GetComponent<AnimationModel>()->Load("asset\\animationmodel\\Paladin_J_Nordstrom.fbx");
	this->GetComponent<AnimationModel>()->LoadAnimation("asset\\animationmodel\\Warrior_Idle.fbx", "Idle");
	this->GetComponent<AnimationModel>()->LoadAnimation("asset\\animationmodel\\Slow_Run.fbx", "Run");
	this->GetComponent<AnimationModel>()->LoadAnimation("asset\\animationmodel\\Right_Strafe.fbx", "RightRun");
	this->GetComponent<AnimationModel>()->LoadAnimation("asset\\animationmodel\\Left_Strafe.fbx", "LeftRun");
	this->GetComponent<AnimationModel>()->LoadAnimation("asset\\animationmodel\\Run_To_Stop.fbx", "StopRun");
	
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
		m_Particle->SetPosition(XMFLOAT3((this->GetPosition().x), (this->GetPosition().y+50.0f),(this->GetPosition().z)));
		m_Particle->SetType(ParticleType::tJumpBooster);
		m_Particle->SetMaterialColor(XMFLOAT4(0.7f,0.1f,0.1f,0.7f));

		m_MParticle = scene->AddGameObject<ParticleEmitter>(goLayerType::Particle);
		m_MParticle->SetOffSet({0.0f,1.0f,0.0f});
		m_MParticle->SetRotation({0.0f,0.0f,0.0f});
		m_MParticle->SetParent(this);
		m_MParticle->SetType(ParticleType::tBooster);
		m_MParticle->SetMaterialColor(XMFLOAT4(0.5f, 0.5f, 0.3f, 0.3f));

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

	//------------------------------------------------------------------------------------------------------------------------------------------------------
	// サーチ用コリジョン
	//------------------------------------------------------------------------------------------------------------------------------------------------------
		this->AddComponent<SearchCollision>();
		this->GetComponent<SearchCollision>()->SetParent(this);
		this->GetComponent<SearchCollision>()->SetOffSet({ 0.0f,0.0f,15.0f });
		this->GetComponent<SearchCollision>()->SetScale({ 20.0f,10.0f,30.0f });
		this->GetComponent<SearchCollision>()->SetRotation({ 0.0f,0.0f,0.0f });
	
		m_UI = scene->AddGameObject<UI>(goLayerType::Texture2d);
		m_UI->InitSet(L"asset\\texture\\white.png", XMFLOAT4(100, 300, 500, 500), 0);
		m_UI->SetPos(XMFLOAT4(400.0f, 50.0f, 600.0f * (m_BoostEnergy / 250), 25));
		m_UI->SetColor({ 0.5f,0.5f, 0.0f, 1.0f });


		m_GageFrame = scene->AddGameObject<UI>(goLayerType::Texture2d);
		m_GageFrame->InitSet(L"asset\\texture\\aGa.png", XMFLOAT4(100, 100, 200, 200), 0);
		m_GageFrame->SetPos(XMFLOAT4(400.0f, 50.0f, 600.0f, 25));

		m_HpBar = scene->AddGameObject<UI>(goLayerType::Texture2d);
		m_HpBar->InitSet(L"asset\\texture\\white.png", XMFLOAT4(500, 400, 1000, 1000), 0);
		m_HpBar->SetPos(XMFLOAT4(400.0f, 0.0f, 600.0f * (m_Hp / 100), 50));
		m_HpBar->SetColor({ 0.7f,0.3f, 0.3f, 1.0f });


		m_HpFrame = scene->AddGameObject<UI>(goLayerType::Texture2d);
		m_HpFrame->InitSet(L"asset\\texture\\aGa.png", XMFLOAT4(100, 100, 200, 200), 0);
		m_HpFrame->SetPos(XMFLOAT4(400.0f, 0.0f, 600.0f, 50));

		m_Material = { 1.0f,1.0f,1.0f,1.0f };
		m_Target = scene->GetGameObject<Player>();
		targetPos = m_Target->GetPosition();

//		m_ChildModel = new ModelRenderer(this);
//		((ModelRenderer*)m_ChildModel)->Load("asset\\model\\box.obj");
//		m_ChildModel = scene->AddGameObject<WeaponRifle>(goLayerType::Object3d);
//		m_ChildModel->SetParent(this);
//		m_ChildModel->SetOffSet({ 0.0f,3.0f,0.0f });
		WeaponAccept(WEAPON_TYPE::RIFLE, WeaponPosition::WP_L_ARM);
		WeaponAccept(WEAPON_TYPE::MISSILE, WeaponPosition::WP_R_ARM);
		/*
	m_EnemyMovePattern = new EnemyMovePatternNone(this);
	m_EnemyMovePattern->SetTimer(5.0f*60.0f);
		*/


	m_StateManager = new EnemyStateManager(this);
	m_StateManager->Init(this);
//	eAIS = new EnemyAIStateIdle(this);
	/*
	m_BehaviorRoot_Battle = new BehaviorSequence(this);
	// 木構造を作る
	m_BehaviorRoot_Battle->AddChild(new BehaviorTask_Battle_Idle(this));
	m_BehaviorRoot_Battle->AddChild(new BehaviorTask_Battle_Move(this));
	m_BehaviorRoot_Battle->AddChild(new BehaviorTask_Battle_Attack_Gun(this));
	*/
}

void EnemyMachine::Uninit()
{
//	delete m_BehaviorRoot_Battle;

	delete eAIS;
	for (Component* component : m_Component)
	{
		component->Uninit();
		delete component;
	}
	m_Component.clear();
	delete m_StateManager;
//	m_ChildModel->Uninit();
//	delete m_ChildModel;


	m_SE->Uninit();
	delete m_SE;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

}

void EnemyMachine::Update()
{
//	eAIS->Update();
	m_Particle->SetIsUse(false);		// パーティクルエミッターオフ
	m_MParticle->SetIsUse(false);		// パーティクルエミッターオフ
	m_StateManager->Update();
	Move();
	WeaponMove();
	CheckPosition();


	m_Particle->SetPosition(this->GetPosition());
//	m_AnimeTime += 0.1;		// 簡易アニメーション
//	Attack();


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

	m_UI->SetPos(XMFLOAT4(400.0f, 50.0f, 600.0f * (m_BoostPower / 250), 25));
	m_HpBar->SetPos(XMFLOAT4(400.0f, 0.0f, 600.0f * (m_Hp / 100), 50));

}

void EnemyMachine::Draw()
{

	// c_str()でchar型に変換できる
	this->GetComponent<AnimationModel>()->Update(m_AnimationMovePatern.c_str(), m_AnimationFrame,
													m_NextAnimationMovePatern.c_str(), m_AnimationFrame,m_Blend);
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
	this->GetComponent<AnimationModel>()->Draw();

	
// 子モデル描画
	XMMATRIX childScale, childRot, childTrans, childWorld;
	XMMATRIX rightHandMatrix;
	rightHandMatrix = this->GetComponent<AnimationModel>()->ConvertXMMatrix(this->GetComponent<AnimationModel>()->GetWorldMatrix("mixamorig:RightHandThumb1"));
	childScale = XMMatrixScaling(1.0f / m_Scale.x, 1.0f / m_Scale.y, 1.0f / m_Scale.z);
	childRot = XMMatrixRotationRollPitchYaw(0.0f, 1.0f, 0.0f);
	childTrans = XMMatrixTranslation(0.0f, 0.0f, 3.0f);
	childWorld = childRot * childTrans * childScale * rightHandMatrix * world; 	// 親のworldmatrixを混ぜる
		
	Renderer::SetWorldMatrix(childWorld);

	//	m_ChildModel->Draw();
	m_LArmWepon->Draw();
//	m_RArmWepon->Draw();
	//	m_LShoulderWepon->Draw();
	//	m_RShoulderWepon->Draw();

}

void EnemyMachine::Move()
{
	if (m_Target != nullptr)
	{
		// ターゲット座標を入れて向きを決める
//		m_CameraRotation = Tracking(m_Target);
//		m_Rotation.y = m_CameraRotation.y;	// 自身の左右の向きをターゲットに向ける
	}

	// 移動状態
	if (m_Move)
	{
		ChangeAnimation("Run");
	}
	else
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

	if (m_JumpUse == false)
	{
		if (m_BoostEnergy < m_BEmax)	m_BoostEnergy += 5.0f;
		else m_BoostEnergy = m_BEmax;
	}

	// 重力
	if (m_MoveType == Slide)	m_Velocity.y -= 0.015f;
	else m_Velocity.y -= 0.02f;

	// 移動処理
	m_Position.y += m_Velocity.y;


	//// 摩擦処理
	m_Velocity.x -= m_Velocity.x * 1.0f * m_dt;
	m_Velocity.z -= m_Velocity.z * 1.0f * m_dt;

	//// 移動処理
	m_Position.x += (m_Velocity.x * m_BoostPower)* m_dt ;
	m_Position.z += (m_Velocity.z * m_BoostPower)* m_dt ;

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
//	this->GetComponent<SearchCollision>()->UpdatePositionBasedOnEnemyMachineRotation();
	this->GetComponent<SearchCollision>()->SetRotation({ -sinf(m_Rotation.y),m_Rotation.y,-cosf(m_Rotation.y) });

}

bool EnemyMachine::Damage(int damage)
{
	if (m_InvisibleTime < PLAYER_INVINSIBLE_TIME_MAX)return false;
	if (damage < 0)return false;

	m_Hp -= damage;
	m_InvisibleTime--;
	m_Material = { 1.0f,1.0f,1.0f,1.0f };
	m_HpBar->SetColor({ m_Material });

	return true;
}

void EnemyMachine::Attack()
{
	LArmAttack();
	RArmAttack();
}

bool EnemyMachine::Defeated()
{
	if (m_Hp > 0.0f) return false;

	if (m_Rotation.x < 90.0f)
	{
		m_Rotation.x += 1.0f;
		m_Rotation.y += 2.0f;
	}

	m_DestroyCount++;
	if (m_DestroyCount < DESTROY_COUNT) return false;

	Game::GameEnd(true);
	return true;

}

void EnemyMachine::SetAccel(XMFLOAT3 _accel)
{
	m_Accel = _accel;
}

void EnemyMachine::SetLRAwayCountMax(int _countMax)
{
	m_AwayTimeCountMax = _countMax;
}

bool EnemyMachine::Boost()
{
	if (m_BoostEnergy <= 0) return false;
	m_BoostEnergy -= 2.0f;
	m_BoostPower = 2.0f;
	/*
	m_Accel.x = 1.8f;
	m_Accel.z = 1.8f;
	*/
	m_MParticle->SetIsUse(true);		// パーティクルエミッター起動

	return true;
}
void EnemyMachine::UpMove()
{
	m_Move = true;
	m_Velocity.x += this->GetForward().x * m_Accel.x * m_BoostPower;
	m_Velocity.z += this->GetForward().z * m_Accel.z * m_BoostPower;
}

void EnemyMachine::DownMove()
{
	m_Move = true;
	m_Velocity.x += (-this->GetForward().x) * m_Accel.x * m_BoostPower;
	m_Velocity.z += (-this->GetForward().z) * m_Accel.z * m_BoostPower;
}

void EnemyMachine::LeftMove()
{
	m_Move = true;
	m_Velocity.x += (-this->GetRight().x) * m_Accel.x * m_BoostPower;
	m_Velocity.z += (-this->GetRight().z) * m_Accel.z * m_BoostPower;
}

void EnemyMachine::RightMove()
{
	m_Move = true;
	m_Velocity.x += this->GetRight().x * m_Accel.x * m_BoostPower;
	m_Velocity.z += this->GetRight().z * m_Accel.z * m_BoostPower;
}
void EnemyMachine::AddKillCount(int count)
{
	m_KillCount += count;

}

int EnemyMachine::GetKillCount()
{
	return m_KillCount;
}

// ターゲットを視点追従
void EnemyMachine::EnemyTracking()
{
	if (m_Target == nullptr) return;

	// ターゲット座標を入れて向きを決める
	m_CameraRotation = Tracking(m_Target);
	m_Rotation.y = m_CameraRotation.y;	// 自身の左右の向きをターゲットに向ける
}

bool EnemyMachine::DistanceRange(XMFLOAT3 _distance)
{
	if (OBBobjXscl(m_Target, _distance)) return true;

	return false;
}

void EnemyMachine::EnemyAI()
{
	// プレイヤーとの距離を調べる
	XMFLOAT3 playerPosition = m_Target->GetPosition();// player->GetPosition();
	XMFLOAT3 direction;	// 方向ベクトルを求める
	direction.x = playerPosition.x - m_Position.x;
	direction.y = playerPosition.y - m_Position.y;
	direction.z = playerPosition.z - m_Position.z;

	float length = sqrtf(direction.x * direction.x
		+ direction.y * direction.y
		+ direction.z * direction.z);

	// 距離が数値未満なら何か行動
	if (length < 5.0f)
	{
		Attack();
	}
	else if (length < 15.0f)
	{
		m_Position.z += 0.02f;
		/*
		*/
		// 正規化(長さ１にする)
		direction.x /= length;
		direction.y /= length;
		direction.z /= length;

		m_Position.x += direction.x * 0.02f;
		//		m_Position.y += direction.y * 0.02f;
		m_Position.z += direction.z * 0.02f;
	}
	
//	m_Position.y= CheckPosition();
}

// 距離調べ
XMFLOAT3 EnemyMachine::EnemyAIDistance()
{
	XMFLOAT3 playerPosition = m_Target->GetPosition();// player->GetPosition();
	XMFLOAT3 distance;	// 方向ベクトルを求める
	distance.x = playerPosition.x - m_Position.x;
	distance.y = playerPosition.y - m_Position.y;
	distance.z = playerPosition.z - m_Position.z;
	return distance;
}

// 距離取得して長さに変換して正規化して返す
float EnemyMachine::EnemyAILength()
{
	XMFLOAT3 distance = EnemyAIDistance();
	float length = sqrtf(distance.x * distance.x
		+ distance.y * distance.y
		+ distance.z * distance.z);

	// 正規化(長さ１にする)
	distance.x /= length;
	distance.y /= length;
	distance.z /= length;

	return length;
}


void EnemyMachine::SetState(EnemyAIState* _state)
{
	delete eAIS;
	eAIS = _state;
}

void EnemyMachine::LRAwayMove()
{
	if (m_AwayTimeCount < 0.0f)
	{
		m_AwayTimeCount = (rand() % (m_AwayTimeCountMax * 60)) * 1.0f;
		m_nextAwayDirection = !m_nextAwayDirection;
	}

	if (m_nextAwayDirection) LeftMove();
	else RightMove();

	m_AwayTimeCount -= 1.0f;
}
