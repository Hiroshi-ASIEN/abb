#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "modelRenderer.h"
#include "input.h"
#include "audio.h"

#include "scene.h"
#include "game.h"
#include "title.h"

Manager* Manager::manager = 0;

Scene* Manager::m_Scene{};
Scene* Manager::m_NextScene{};


Manager::Manager()
{
}

Manager* Manager::Instance()
{
	return manager;
}

void Manager::Init()
{
	Renderer::Init();
	Input::Init();
	Audio::InitMaster();

//	m_Scene = new Scene();
//	m_Scene = new Game();
	m_Scene = new Title();
	m_Scene->Init();

//	SetScene<Title>();

}


void Manager::Uninit()
{
	m_Scene->Uninit();
	delete m_Scene;

	ModelRenderer::UnloadAll();

	Audio::UninitMaster();
	Input::Uninit();
	Renderer::Uninit();
}

void Manager::Update()
{
	Input::Update();
//	ClipMouseCursorToWindow();
//	ClipMouseCursorToSmallerArea();
	ShowCursor(FALSE); // カーソルを非表示にする

	m_Scene->Update();
}

void Manager::Draw()
{
	Renderer::Begin();

	m_Scene->Draw();

	Renderer::End();

	// 画面遷移
	if (m_NextScene != nullptr)
	{
		if (m_Scene)
		{
			m_Scene->Uninit();
			delete m_Scene;
		}

//		ModelRenderer::UnloadAll();

		m_Scene = m_NextScene;
		m_Scene->Init();

		m_NextScene = nullptr;
	}

}
