#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "result.h"
#include "input.h"
#include "particleEmitter.h"
#include "score.h"
#include "teamArea.h"
#include "box.h"
#include "meshField.h"
#include "audio.h"
#include "water.h"
#include "menu.h"
#include "wave.h"
#include "testObject.h"
#include "enemyMachine.h"
#include "shadowVolume.h"
#include "shadowPolygon2D.h"
#include "modelRenderer.h"
#include "meshFieldBattle.h"
#include "enemyAIState.h"

bool Game::m_LoadFinish = false;

void Game::Load()
{
	Tree::Load();
	Player::Load();
	Bill::Load();
	Grass::Load();
	ParticleEmitter::Load();
	EnemyStateManager::Load();

	// ロード終了
	m_LoadFinish = true;
}

void Game::Init()
{
	// フェード
	//=================================================================
	m_Fade = AddGameObject<Polygon2D>(goLayerType::Texture2d);
	// テクスチャ名設定
	const wchar_t* fadetex = L"asset\\texture\\kuro.png";
	m_Fade->InitSet(fadetex, XMFLOAT4(0.0f, 0.0f, 1300.0f, 800.0f));
	m_Fade->SetPosition(XMFLOAT3(100.0, -100.0, 100.0));
	m_Fade->SetFade(FadeType::FadeIn);
	//============================================================================


	AddGameObject<Camera>(goLayerType::CameraObject);
	AddGameObject<Menu>(goLayerType::Billboard);

	// マップ生成============================================================================
//	AddGameObject<Field>(goLayerType::Stage);
//	MeshField* meshField=AddGameObject<MeshField>(goLayerType::Stage);
	MeshField_Battle* meshField = AddGameObject<MeshField_Battle>(goLayerType::Stage);
	AddGameObject<Sky>(goLayerType::Stage)->SetScale(XMFLOAT3(150.0f, 150.0f, 150.0f));

	//============================================================================
	AddGameObject<ShadowVolume>(goLayerType::Object3d)->SetPosition(XMFLOAT3(0.0f, -4.0f, 0.0f));
	AddGameObject<ShadowPolygon2D>(goLayerType::Object3d)->SetPosition(XMFLOAT3(0.0f, -4.0f, 0.0f));

//	AddGameObject<Monkey>(goLayerType::Object3d);

	player = AddGameObject<Player>(goLayerType::Object3d);
	player->SetPosition({ 0.0f,1.0f,0.0f });

	AddGameObject<EnemyMachine>(goLayerType::Object3d)->SetPosition({ 0.0f,1.0f,10.0f });

	// オブジェクト配置
	//============================================================================
	AddGameObject<Wave>(goLayerType::wa)->SetPosition({40.0f,-2.0f,40.0f});
//	AddGameObject<TestObject>(goLayerType::Object3d)->SetPosition(XMFLOAT3(0.0f,2.0f,0.0f));

	if (meshField->GetInitFinish())
	{
		{
			Grass* grass = AddGameObject<Grass>(goLayerType::Billboard);
			grass->SetType(1);
			grass->SetPosition({ -80.0f,0.0f,40.0f });

			Grass* grass2 = AddGameObject<Grass>(goLayerType::Billboard);
			grass2->SetType(2);
			grass2->SetPosition({ -40.0f,0.0f,40.0f });

			Grass* grass3 = AddGameObject<Grass>(goLayerType::Billboard);
			grass3->SetType(3);
			grass3->SetPosition({ -80.0f,0.0f,0.0f });
		}

		// ツリー
		{
			AddGameObject<Tree>(goLayerType::Billboard)->SetPosition(XMFLOAT3(-80.0f, 1.0f, -80.0f));
			AddGameObject<Tree>(goLayerType::Billboard)->SetPosition(XMFLOAT3(-40.0f, 1.0f, -80.0f));
			AddGameObject<Tree>(goLayerType::Billboard)->SetPosition(XMFLOAT3(-80.0f, 1.0f, -40.0f));
		}
	}
//	AddGameObject<Tree>(goLayerType::Billboard)->SetPosition(XMFLOAT3(-20.0f, 2.0f, -30.0f));
//	AddGameObject<Tree>(goLayerType::Billboard)->SetPosition(XMFLOAT3(-10.0f, 2.0f, 10.0f));
	/*
	AddGameObject<Tree>(goLayerType::Billboard);
	AddGameObject<Dentou>(goLayerType::Billboard);
	{
		Grass* grass = AddGameObject<Grass>(goLayerType::Billboard);
		grass->SetType(0);
		grass->SetRandomRange(-40, -50, -20, -50);
	}
	{
		Grass* grass = AddGameObject<Grass>(goLayerType::Billboard);
		grass->SetType(2);
		grass->SetRandomRange(100, 70, 100, 70);
	}

	*/
	/*
	{
		// 電灯
		float x = 10.0f;
		float z = -10.0f;
		float zz = -8.0f;

		for (int i = 0; i < 16; i++)
		{
			Dentou* dentou = AddGameObject<Dentou>(goLayerType::Billboard);
			dentou->SetScale({ 1.0f,2.0f,1.0f });
			dentou->SetXZPosition({ x,0.0f,z });

			if (i == 4)		x += 10.0f;
			else if (i == 9)		x += 10.0f;
			else if (i % 5 == 0)	zz *= -1.0f;

			z += zz;
		}
	}
*/	

	{
		// ビル
		float x = 13.0f;
		float z = -10.0f;
		float zz = -4.0f;

		for (int i = 0; i < 31; i++)
		{
			float s = 1.0f * (rand() % 3 + 1);
			Bill* bill = AddGameObject<Bill>(goLayerType::Object3d);
			bill->SetScale(XMFLOAT3(4.0f, 4.0f*s, 4.0f));
			bill->SetXZPosition({ x,0.0f,z });

			if (i == 9)		x += 10.0f;
			else if (i == 19)		x += 10.0f;
			else if (i % 10==0)	zz *= -1.0f;

			z += zz;
		}

	}
	/*
	{
		Cylinder* cylinder = AddGameObject<Cylinder>(goLayerType::Object3d);
		cylinder->SetPosition(XMFLOAT3(20.0f, 0.0f, 10.0f));
		cylinder->SetScale(XMFLOAT3(2.0f, 1.0f, 2.0f));
	}

	{
		Box* box = AddGameObject<Box>(goLayerType::Object3d);
		box->SetPosition(XMFLOAT3(0.0f, 1.0f, 30.0f));
		box->SetScale(XMFLOAT3(1.0f, 1.0f, 1.0f));
		box->SetRotation(XMFLOAT3(0.0f, 90.0f, 0.0f));
	}
	
	player = AddGameObject<Player>(goLayerType::Object3d);
	player->SetPosition({ 0.0f,1.0f,0.0f });

	AddGameObject<EnemyMachine>(goLayerType::Object3d)->SetPosition({ 0.0f,1.0f,3.0f });

	// 敵配置
	//============================================================================

	// スポナー
//	AddGameObject<EnemySpowner>(goLayerType::Object3d)->SetPosition(XMFLOAT3(0.0f, 0.0f, 20.0f));
//	AddGameObject<EnemySpowner>(goLayerType::Object3d)->SetPosition(XMFLOAT3(0.0f, 0.0f, -20.0f));

	// 敵
	/*
	{
		Enemy* enemy = AddGameObject<Enemy>(goLayerType::Object3d);
		enemy->SetPosition(XMFLOAT3(-10.0f, 0.0f, 10.0f));
		enemy->SetAreaNumber(1);
	}
	{
		Enemy* enemy = AddGameObject<Enemy>(goLayerType::Object3d);
		enemy->SetPosition(XMFLOAT3(10.0f, 0.0f, -10.0f));
		enemy->SetAreaNumber(1);
	}
	{
		Enemy* enemy = AddGameObject<Enemy>(goLayerType::Object3d);
		enemy->SetPosition(XMFLOAT3(-10.0f, 0.0f, -20.0f));
		enemy->SetType(EnemyMoveType::AreaTracking);
		enemy->SetAreaNumber(1);
	}
	{
		Enemy* enemy = AddGameObject<Enemy>(goLayerType::Object3d);
		enemy->SetPosition(XMFLOAT3(10.0f, 0.0f, 20.0f));
		enemy->SetType(EnemyMoveType::AreaTracking);
		enemy->SetAreaNumber(3);
	}
	*/
	
//	AddGameObject<Polygon2D>(goLayerType::Texture2d);
//	AddGameObject<ParticleEmitter>(goLayerType::Particle)->SetPosition(XMFLOAT3(-5.0f, 5.0f, -5.0f));

	// UI・画像表示
	//============================================================================
	AddGameObject<Score>(goLayerType::Texture2d)->SetPosition(XMFLOAT3(0.0f, 0.0f, 0.0f));	// スコア表示
	AddGameObject<UI>(goLayerType::Texture2d)->InitSet(L"asset\\texture\\suimoji.png",XMFLOAT4(410,550,460,600),0);	// 時間表示


	/*
	{
		TeamArea* area1 = AddGameObject<TeamArea>(goLayerType::Object3d);
		area1->SetAreaState(PlayerArea);
		area1->SetPosition(XMFLOAT3(20.0f, 0.0f, 20.0f));
		area1->SetAreaNumber(1);

		TeamArea* area2 = AddGameObject<TeamArea>(goLayerType::Object3d);
		area2->SetAreaState(EnemyArea);
		area2->SetPosition(XMFLOAT3(-20.0f, 0.0f, 10.0f));
		area2->SetAreaNumber(2);

		TeamArea* area3 = AddGameObject<TeamArea>(goLayerType::Object3d);
		area3->SetAreaState(EnemyArea);
		area3->SetPosition(XMFLOAT3(-10.0f, 0.0f, -15.0f));
		area3->SetAreaNumber(3);

		TeamArea* area4 = AddGameObject<TeamArea>(goLayerType::Object3d);
		area4->SetAreaState(PlayerArea);
		area4->SetPosition(XMFLOAT3(10.0f, 0.0f, -5.0f));
		area4->SetAreaNumber(4);
	}
	*/
	/*
	ParticleEmitter* pShower{};
	AddGameObject<ParticleEmitter>(goLayerType::Particle);
	pShower->SetPosition(XMFLOAT3((20.0f), (0.0f), ( - 20)));
	pShower->SetType(ParticleType::tShower);

	ParticleEmitter* pWind{};
	AddGameObject<ParticleEmitter>(goLayerType::Particle);
	pWind->SetPosition(XMFLOAT3((- 50.0f), (0.0f), (0.0f)));
	pWind->SetType(ParticleType::tWind);
	pWind->SetMaterialColor(XMFLOAT4(0.1, 0.5, 0.1, 0.7));
	pWind->SetScale(XMFLOAT3(0.3f, 0.1f, 0.3f));

	ParticleEmitter* pRain{};
	AddGameObject<ParticleEmitter>(goLayerType::Particle);
	pRain->SetPosition(XMFLOAT3((0.0f), ( 10.0f), (0.0f)));
	pRain->SetType(ParticleType::tRain);
	pRain->SetMaterialColor(XMFLOAT4(0.1, 0.1, 0.8, 0.7));
	pRain->SetScale(XMFLOAT3(0.2f, 0.5f, 0.2f));

	ParticleEmitter* pFlare{};
	AddGameObject<ParticleEmitter>(goLayerType::Particle);
	pFlare->SetPosition(XMFLOAT3((0.0f), (0.0f), ( 50.0f)));
	pFlare->SetType(ParticleType::tFlare);
	pFlare->SetMaterialColor(XMFLOAT4(0.8, 0.1, 0.1, 0.5));
	pFlare->SetScale(XMFLOAT3(0.2f, 0.2f, 0.2f));

	ParticleEmitter* pFire{};
	AddGameObject<ParticleEmitter>(goLayerType::Particle);
	pFire->SetPosition(XMFLOAT3((10.0f), ( 3.0f), (0.0f)));
	pFire->SetType(ParticleType::tFire);
	pFire->SetMaterialColor(XMFLOAT4(0.7, 0.3, 0.3, 0.8));
	pFire->SetScale(XMFLOAT3(1.5f, 1.5f, 1.5f));
	*/

	// コンポーネント：サウンド
	player->AddComponent<Audio>();
	player->GetComponent<Audio>()->Load("asset\\audio\\maou_neo.wav");
	player->GetComponent<Audio>()->Play(true);
}

void Game::Uninit()
{



	// アンロード
	Player::Unload();
	Bill::Unload();
	Grass::Unload();
	Tree::Unload();
	ParticleEmitter::Unload();
	EnemyStateManager::Unload();
	ModelRenderer::UnloadAll();

	// 継承元のUninit呼出
	Scene::Uninit();
	m_LoadFinish = false;
}

void Game::Update()
{
	// 継承元のUpdate呼出
	Scene::Update();

	GameObject* camera = GetGameObject<Camera>();
	

	if (!m_Fade->GetFadeFrag())
	{
		m_Fade->Fade();
	}
	if (Input::GetKeyTrigger(VK_RETURN))
	{
		m_NextScene = true;
		m_Fade->SetFade(FadeType::FadeOut);
	}
	if (m_NextScene)
	{
		if (m_Fade->Fade())
		{
			Manager::SetScene<Result>();
		}
		else
		{
			m_Fade->Fade();
		}
	}

	// エンターキー押したら
	if (Input::GetKeyTrigger(VK_RETURN))
//	if(GetGameObject<Score>()->GetScore()>30)
	{
		Manager::SetScene<GameClear>();
	}

/*	if (GetGameObject<Score>()->GetEnemyScore() > 30)
	{
		Manager::SetScene<GameOver>();
		m_NextScene = true;
	}
	*/
}

bool Game::GetFinish()
{
	return m_LoadFinish;
}

void Game::GameEnd(bool _win)
{
	if (_win)
	{
		Manager::SetScene<GameClear>();
	}
	else
	{
		Manager::SetScene<GameOver>();
	}

}

