#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "title.h"
#include "result.h"
#include "input.h"
void Result::Init()
{
	// �^�C�g���摜
	//====================================================================================================
	Polygon2D* resultSC = AddGameObject<Polygon2D>(goLayerType::Texture2d);
	// �e�N�X�`�����ݒ�
	const wchar_t* titletex = L"asset\\texture\\Clear.jpeg";
	resultSC->InitSet(titletex, XMFLOAT4(0.0f, 0.0f, 1300.0f, 800.0f));
	resultSC->SetPosition(XMFLOAT3(100.0, -100.0, 100.0));

	//====================================================================================================
		// �t�F�[�h�p
	m_Fade = AddGameObject<Polygon2D>(goLayerType::Texture2d);
	// �e�N�X�`�����ݒ�
	const wchar_t* fadetex = L"asset\\texture\\kuro.png";
	m_Fade->InitSet(fadetex, XMFLOAT4(0.0f, 0.0f, 1300.0f, 800.0f));
	m_Fade->SetPosition(XMFLOAT3(100.0, -100.0, 100.0));
	m_Fade->SetFade(FadeIn);
}

//void Result::Uninit()

void Result::Update()
{
	// �p������Update�ďo
	Scene::Update();

	if (!m_Fade->GetFadeFrag())
	{
		m_Fade->Fade();
	}
	if (Input::GetKeyTrigger(VK_SPACE))
	{
		m_NextScene = true;
		m_Fade->SetFade(FadeOut);
	}
	if (m_NextScene)
	{
		if (m_Fade->Fade() == true)
		{
			Manager::SetScene<Title>();
		}
		else
		{
			m_Fade->Fade();
		}
	}

	/*
	// �G���^�[�L�[��������
	if (Input::GetKeyTrigger(VK_RETURN))
	{
		Manager::SetScene<Title>();
	}
	*/
}

void Result::GameOver()
{
	// �Q�[���I�[�o�[�摜
	//====================================================================================================
	Polygon2D* resultSC = AddGameObject<Polygon2D>(goLayerType::Texture2d);
	// �e�N�X�`�����ݒ�
	const wchar_t* titletex = L"asset\\texture\\Over.jpeg";
	resultSC->InitSet(titletex, XMFLOAT4(0.0f, 0.0f, 1300.0f, 800.0f));
	resultSC->SetPosition(XMFLOAT3(100.0, -100.0, 100.0));
}

void Result::GameClear()
{
	// �Q�[���N���A�摜
	//====================================================================================================
	Polygon2D* resultSC = AddGameObject<Polygon2D>(goLayerType::Texture2d);
	// �e�N�X�`�����ݒ�
	const wchar_t* titletex = L"asset\\texture\\Clear.jpeg";
	resultSC->InitSet(titletex, XMFLOAT4(0.0f, 0.0f, 1300.0f, 800.0f));
	resultSC->SetPosition(XMFLOAT3(100.0, -100.0, 100.0));

}

//void Result::Draw()



void GameClear::Init()
{
	// �Q�[���N���A�摜
	//====================================================================================================
	Polygon2D* resultSC = AddGameObject<Polygon2D>(goLayerType::Texture2d);
	// �e�N�X�`�����ݒ�
	const wchar_t* titletex = L"asset\\texture\\Clear.jpeg";
	resultSC->InitSet(titletex, XMFLOAT4(0.0f, 0.0f, 1300.0f, 800.0f));
	resultSC->SetPosition(XMFLOAT3(100.0, -100.0, 100.0));

	// �t�F�[�h�p
	m_Fade = AddGameObject<Polygon2D>(goLayerType::Texture2d);
	// �e�N�X�`�����ݒ�
	const wchar_t* fadetex = L"asset\\texture\\kuro.png";
	m_Fade->InitSet(fadetex, XMFLOAT4(0.0f, 0.0f, 1300.0f, 800.0f));
	m_Fade->SetPosition(XMFLOAT3(100.0, -100.0, 100.0));
	m_Fade->SetFade(FadeIn);

	m_Clear = AddGameObject<Polygon2D>(goLayerType::Texture2d);
	// �e�N�X�`�����ݒ�
	const wchar_t* cltex = L"asset\\texture\\ster.png";
	m_Clear->InitSet(cltex, XMFLOAT4(300.0f, 50.0f, 1000.0f, 300.0f));
	m_Clear->SetPosition(XMFLOAT3(100.0, -100.0, 100.0));
	m_Clear->SetColor(XMFLOAT4(1.0, 1.0, 1.0, 1.0));
}



void GameClear::Update()
{
	// �p������Update�ďo
	Scene::Update();
	if (x >= 1.0f)  i *= -1;
	else if (x < 0.0f) i *= -1;

	x += i;
	m_Clear->SetColor(XMFLOAT4(x, 1.0, 1.0, x));

	if (!m_Fade->GetFadeFrag())
	{
		m_Fade->Fade();
	}
	if (Input::GetKeyTrigger(VK_SPACE))
	{
		m_NextScene = true;
		m_Fade->SetFade(FadeOut);
	}
	if (m_NextScene)
	{
		if (m_Fade->Fade() == true)
		{
			Manager::SetScene<Title>();
		}
		else
		{
			m_Fade->Fade();
		}
	}

	/*
	// �G���^�[�L�[��������
	if (Input::GetKeyTrigger(VK_RETURN))
	{
		Manager::SetScene<Title>();
	}
	*/
}



void GameOver::Init()
{
	// �Q�[���I�[�o�[�摜
//====================================================================================================
	Polygon2D* resultSC = AddGameObject<Polygon2D>(goLayerType::Texture2d);
	// �e�N�X�`�����ݒ�
	const wchar_t* titletex = L"asset\\texture\\Over.jpeg";
	resultSC->InitSet(titletex, XMFLOAT4(0.0f, 0.0f, 1300.0f, 800.0f));
	resultSC->SetPosition(XMFLOAT3(100.0, -100.0, 100.0));

	m_Over = AddGameObject<Polygon2D>(goLayerType::Texture2d);
	// �e�N�X�`�����ݒ�
	const wchar_t* ovtex = L"asset\\texture\\ster.png";
	m_Over->InitSet(ovtex, XMFLOAT4(300.0f, 50.0f, 1000.0f, 300.0f));
	m_Over->SetPosition(XMFLOAT3(100.0, -100.0, 100.0));
	m_Over->SetColor(XMFLOAT4(1.0, 1.0, 1.0, 1.0));
	// �t�F�[�h�p
	m_Fade = AddGameObject<Polygon2D>(goLayerType::Texture2d);
	// �e�N�X�`�����ݒ�
	const wchar_t* fadetex = L"asset\\texture\\kuro.png";
	m_Fade->InitSet(fadetex, XMFLOAT4(0.0f, 0.0f, 1300.0f, 800.0f));
	m_Fade->SetPosition(XMFLOAT3(100.0, -100.0, 100.0));
	m_Fade->SetFade(FadeIn);
}

void GameOver::Update()
{
	// �p������Update�ďo
	Scene::Update();
	if (x >= 1.0f)  i *= -1;
	else if (x < 0.0f) i *= -1;

	x += i;
	m_Over->SetColor(XMFLOAT4(x, 1.0, 1.0, x));

	if (!m_Fade->GetFadeFrag())
	{
		m_Fade->Fade();
	}
	if (Input::GetKeyTrigger(VK_SPACE))
	{
		m_NextScene = true;
		m_Fade->SetFade(FadeOut);
	}
	if (m_NextScene)
	{
		if (m_Fade->Fade() == true)
		{
			Manager::SetScene<Title>();
		}
		else
		{
			m_Fade->Fade();
		}
	}
	/*
	// �G���^�[�L�[��������
	if (Input::GetKeyTrigger(VK_RETURN))
	{
		Manager::SetScene<Title>();
	}
	*/
}
