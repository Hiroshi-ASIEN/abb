#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "title.h"
#include "input.h"
#include "audio.h"
#include "polygon2D.h"
#include "meshField.h"
#include "wave.h"
#include "particleEmitter.h"
#include "gameObject.h"
#include "autoCamera.h"
#include "loading.h"
#include "mosaic.h"
#include "selectScene.h"

#include <thread>

bool Title::m_LoadFinish{};
float Title::m_LoadValue{};

void Title::Init()
{
	// タイトルロード画面作成

	m_TitleLoad = AddGameObject<Mosaic>(goLayerType::Texture2d);
	m_TitleLoad->InitSet(L"asset\\texture\\mosaic.png", XMFLOAT4(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT),0);
	m_TitleLoad->SetColor(XMFLOAT4(0.2f, 0.7f, 0.8f, 1.0f));


	m_LoadGage = AddGameObject<UI>(goLayerType::Texture2d);
	m_LoadGage->InitSet(L"asset\\texture\\white.png", XMFLOAT4(100, 300, 500, 500), 0);
	m_LoadGage->SetPos(XMFLOAT4((SCREEN_WIDTH * 0.5f) - 300.0f, (SCREEN_HEIGHT * 0.5f) + 150.0f, 600.0f * (m_LoadValue / 100), 40));
	m_LoadGage->SetColor({ 0.3f,0.5f, 1.0f, 1.0f });


	m_GageFrame = AddGameObject<UI>(goLayerType::Texture2d);
	m_GageFrame->InitSet(L"asset\\texture\\aGa.png", XMFLOAT4(100, 100, 200, 200), 0);
	m_GageFrame->SetPos(XMFLOAT4((SCREEN_WIDTH * 0.5f) - 300.0f, (SCREEN_HEIGHT * 0.5f) + 150.0f, 600.0f, 40));

	// フェード用
	m_Fade = AddGameObject<Polygon2D>(goLayerType::Texture2d);
	m_Fade->InitSet(L"asset\\texture\\kuro.png", XMFLOAT4(0.0f, 0.0f, 1300.0f, 800.0f));
	m_Fade->SetPosition(XMFLOAT3(100.0f, -100.0f, 100.0f));
	m_Fade->SetFade(FadeIn);

	m_Title = AddGameObject<UI>(goLayerType::Texture2d);
	m_Title->InitSet(L"asset\\texture\\TitleLogo.png", XMFLOAT4(100, 300, 500, 500), 0);
	m_Title->SetPos(XMFLOAT4((SCREEN_WIDTH * 0.25f), (SCREEN_HEIGHT * 0.1f), (SCREEN_WIDTH * 0.5f), (SCREEN_HEIGHT * 0.25f)));
	m_Title->SetColor({ 0.3f,0.5f, 1.0f, 1.0f });

	//====================================================================================================

	// ロード完了フラグfalse
	m_LoadFinish = false;
	m_LoadValue = 0.0f;
	//スレッド (マルチスレッドで複数平行に動かす)
	std::thread th(&Title::Load);
	th.detach();	// 呼び出されたらすぐ戻ってくる


}

void Title::SecondInit()
{
	if (m_LoadValue < 100.0f)return;

	if (!m_LoadFinish)return;

	AddGameObject<AutoCamera>(goLayerType::CameraObject)->SetPosition(XMFLOAT3(-3.0f, 2.0f, -5.0f));
	MeshField* meshField = AddGameObject<MeshField>(goLayerType::Stage);
	meshField->SetPosition(XMFLOAT3(0.0f, 0.0f, 0.0f));
	AddGameObject<Sky>(goLayerType::Stage)->SetScale(XMFLOAT3(80.0f, 80.0f, 80.0f));
	AddGameObject<Wave>(goLayerType::wa)->SetPosition(XMFLOAT3(0.0f, 0.0f, 0.0f));

	{
		Grass* grass = AddGameObject<Grass>(goLayerType::Billboard);
		grass->SetType(1);
		grass->SetRandomRange(150, -50, 100, -50);
	}


	
		AddGameObject<Tree>(goLayerType::Billboard);
	/*
	{
		// ビル
		float x = -45.0f;
		float z = -10.0f;
		float zz = -4.0f;

		for (int i = 0; i < 51; i++)
		{
			float s = 1.0f * (rand() % 3 + 1);
			Bill* bill = AddGameObject<Bill>(goLayerType::Object3d);
			bill->SetScale(XMFLOAT3(4.0f, 4.0f * s, 4.0f));
			bill->SetXZPosition({ x,0.0f,z });

			if (i == 19)		x += 10.0f;
			else if (i == 39)		x += 10.0f;
			else if (i % 20 == 0)	zz *= -1.0f;

			z += zz;
		}

	}
		// 雨
	ParticleEmitter* pRain = AddGameObject<ParticleEmitter>(goLayerType::Particle);
	pRain->SetPosition(XMFLOAT3(0.0f, 0.0f, 0.0f));
	pRain->SetType(ParticleType::tRain);
	pRain->SetMaterialColor(XMFLOAT4(0.1, 0.4, 0.8, 0.7));
	pRain->SetScale(XMFLOAT3(0.1f, 0.5f, 0.1f));

	// 火の粉
	ParticleEmitter* pFlare = AddGameObject<ParticleEmitter>(goLayerType::Particle);
	pFlare->SetPosition(XMFLOAT3(-10.0f, 0.0f, 20.0f));
	pFlare->SetType(ParticleType::tFlare);
	pFlare->SetMaterialColor(XMFLOAT4(0.8, 0.1, 0.1, 0.8));
	pFlare->SetScale(XMFLOAT3(0.2f, 0.2f, 0.2f));

	float n = 0.0f;
	// 焚火
	for (int i = 0; i < 21; i++)
	{
		{
			ParticleEmitter* pFire = AddGameObject<ParticleEmitter>(goLayerType::Particle);
			XMFLOAT3 pos = { -20.0f + n,0.0f,33.0f+((i%10)*1.0f)};
			pos.y = meshField->GetHeight(pos);
			pFire->SetPosition(pos);
			pFire->SetType(ParticleType::tFire);
			pFire->SetMaterialColor(XMFLOAT4(0.7, 0.3, 0.3, 0.2));
			pFire->SetScale(XMFLOAT3(0.5f, 0.5f, 0.5f));
		}
		{
			ParticleEmitter* pFire = AddGameObject<ParticleEmitter>(goLayerType::Particle);
			XMFLOAT3 pos = { -20.0f + (n + 1.0f),0.0f,33.5f + ((i % 10) * 1.0f) };
			pos.y = meshField->GetHeight(pos);
			pFire->SetPosition(pos);
			pFire->SetType(ParticleType::tFire);
			pFire->SetMaterialColor(XMFLOAT4(0.7, 0.3, 0.3, 0.2));
			pFire->SetScale(XMFLOAT3(1.0f, 0.5f, 1.0f));
		}
		{
			ParticleEmitter* pFire = AddGameObject<ParticleEmitter>(goLayerType::Particle);
			XMFLOAT3 pos = { -20.0f + (n + 2.0f),0.0f,34.0f + ((i % 10) * 1.0f) };
			pos.y = meshField->GetHeight(pos);
			pFire->SetPosition(pos);
			pFire->SetType(ParticleType::tFire);
			pFire->SetMaterialColor(XMFLOAT4(0.7, 0.3, 0.3, 0.2));
			pFire->SetScale(XMFLOAT3(0.5f, 0.5f, 0.5f));
		}
		n += 0.5f;
	}
	for (int i = 0; i < 21; i++)
	{
		{
			ParticleEmitter* pFire = AddGameObject<ParticleEmitter>(goLayerType::Particle);
			XMFLOAT3 pos = { 10.0f + n,0.0f,33.0f + ((i % 10) * n) };
			pos.y = meshField->GetHeight(pos);
			pFire->SetPosition(pos);
			pFire->SetType(ParticleType::tFire);
			pFire->SetMaterialColor(XMFLOAT4(0.7, 0.3, 0.3, 0.2));
			pFire->SetScale(XMFLOAT3(0.5f, 0.5f, 0.5f));
		}
		{
			ParticleEmitter* pFire = AddGameObject<ParticleEmitter>(goLayerType::Particle);
			XMFLOAT3 pos = { 10.0f + (n + 1.0f),0.0f,33.5f + ((i % 10) * n) };
			pos.y = meshField->GetHeight(pos);
			pFire->SetPosition(pos);
			pFire->SetType(ParticleType::tFire);
			pFire->SetMaterialColor(XMFLOAT4(0.7, 0.3, 0.3, 0.2));
			pFire->SetScale(XMFLOAT3(1.0f, 0.5f, 1.0f));
		}
		{
			ParticleEmitter* pFire = AddGameObject<ParticleEmitter>(goLayerType::Particle);
			XMFLOAT3 pos = { 10.0f + (n + 2.0f),0.0f,34.0f + ((i % 10) * n) };
			pos.y = meshField->GetHeight(pos);
			pFire->SetPosition(pos);
			pFire->SetType(ParticleType::tFire);
			pFire->SetMaterialColor(XMFLOAT4(0.7, 0.3, 0.3, 0.2));
			pFire->SetScale(XMFLOAT3(0.5f, 0.5f, 0.5f));
		}
		n += 0.5f;
	}
	/*
	ParticleEmitter* pWind = AddGameObject<ParticleEmitter>(goLayerType::Particle);
	pWind->SetPosition(XMFLOAT3(0.0f, 0.0f, 0.0f));
	pWind->SetType(ParticleType::tWind);
	pWind->SetMaterialColor(XMFLOAT4(0.1, 0.5, 0.1, 0.7));
	pWind->SetScale(XMFLOAT3(0.3f, 0.1f, 0.3f));
	*/

	//emptyObject->AddComponent<Audio>();
	//emptyObject->GetComponent<Audio>()->Load("asset\\audio\\Strategy-Meeting.wav");
	//emptyObject->GetComponent<Audio>()->Play(true);
//	m_TitleLoad->SetColor({ 0.0f,0.0f,0.0f,0.0f, });

	m_Push = AddGameObject<UI>(goLayerType::Texture2d);
	m_Push->InitSet(L"asset\\texture\\push.png", XMFLOAT4(100, 300, 500, 500), 0);
	m_Push->SetPos(XMFLOAT4((SCREEN_WIDTH * 0.3f), (SCREEN_HEIGHT * 0.8f), (SCREEN_WIDTH * 0.4f), (SCREEN_HEIGHT * 0.1f)));
	m_Push->SetColor({ 0.3f,0.3f, 0.3f, 1.0f });

	m_Title->AddComponent<Audio>();
	m_Title->GetComponent<Audio>()->Load("asset\\audio\\Strategy-Meeting.wav");
	m_Title->GetComponent<Audio>()->Play(true);

	m_LoadGage->SetColor({ 0.0f,0.0f,0.0f,0.0f, });
	m_GageFrame->SetColor({ 0.0f,0.0f,0.0f,0.0f, });

	m_LoadValue = 100.0f;
	m_LoadFinish = false;
}

void Title::Uninit()
{
	// 継承元のUninit呼出
	Scene::Uninit();

	m_LoadValue = 0.0f;

	Title::Unload();
}

void Title::Update()
{

	// 継承元のUpdate呼出
	Scene::Update();

	if (!m_Fade->GetFadeFrag())
	{
		m_Fade->Fade();
	}


	if (m_LoadValue < 100.0f)
	{	
		m_LoadValue += 1.0f;
		m_LoadGage->SetPos(XMFLOAT4((SCREEN_WIDTH * 0.5f) - 300.0f, (SCREEN_HEIGHT * 0.5f) + 150.0f, 600.0f * (m_LoadValue / 100), 40));
		m_TitleLoad->Update();

		return;
	}
	else if(1.0f-i>=0.0f)
	{
		m_TitleLoad->SetColor({ 1.0f,1.0f,1.0f,(1.0f - (i)) });
	}

	SecondInit();

	if(m_Push!=nullptr) m_Push->SetColor(XMFLOAT4(0.1f, 0.1f, 0.1f, x));

	i += 1.0f / 60.0f;
	x = sinf(i) * 0.5f + 0.5f;


	if (Input::GetKeyTrigger(VK_SPACE))
	{
		m_NextScene = true;
		m_Fade->SetFade(FadeOut);
	}
	if (m_NextScene)
	{
		if (m_Fade->Fade())
		{
//			Manager::SetScene<Loading>();
			Manager::SetScene<SelectScene>();
		}
		else
		{
			m_Fade->Fade();
		}
	}
}
void Title::Fade()
{
}

void Title::Load()
{

	// 2D系ロード
	Tree::Load();
	Grass::Load();
	ParticleEmitter::Load();
	if (m_LoadValue < 20.0f)	m_LoadValue = 20.0f;

	// 3D系ロード
	Bill::Load();

	m_LoadValue = 90.0f;
	m_LoadFinish = true;
}
void Title::Unload()
{
	Tree::Unload();
	Bill::Unload();
	Grass::Unload();
	ParticleEmitter::Unload();
}
//void Title::Draw()

