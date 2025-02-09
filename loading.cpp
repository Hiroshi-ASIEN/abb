#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "loading.h"
#include "input.h"
#include "audio.h"
#include "polygon2D.h"
#include "gameObject.h"
#include "loadLogo.h"

#include <thread>


void Loading::Init()
{
	m_Loading = AddGameObject<LoadLogo>(goLayerType::Texture2d);
	m_Loading->SetPosition(XMFLOAT3(1000.0, 600.0, 0.0));
	m_Loading->SetColor(XMFLOAT4(1.0, 1.0, 1.0, 1.0));

	// �t�F�[�h�p
	m_Fade = AddGameObject<Polygon2D>(goLayerType::Texture2d);
	// �e�N�X�`�����ݒ�
	const wchar_t* fadetex = L"asset\\texture\\kuro.png";
	m_Fade->InitSet(fadetex, XMFLOAT4(0.0f, 0.0f, 1300.0f, 800.0f));
	m_Fade->SetPosition(XMFLOAT3(100.0, -100.0, 100.0));
	m_Fade->SetFade(FadeIn);

	//�X���b�h (�}���`�X���b�h�ŕ������s�ɓ�����)
	std::thread th(&Game::Load);
	th.detach();	// �Ăяo���ꂽ�炷���߂��Ă���

}

//void Loading::Uninit()


void Loading::Update()
{
	if (!m_Fade->GetFadeFrag())
	{
		m_Fade->Fade();
	}

	// �p������Update�ďo
	Scene::Update();
	z += 0.1f;
	m_Loading->SetRotation({ 0,0,z });

	if(!Game::GetFinish()) return;

	if (x >= 1.0f)  i *= -1;
	else if (x < 0.0f) i *= -1;

	x += i;

	// �G���^�[�L�[��������
//	if (Input::GetKeyTrigger(VK_RETURN))
	m_Loading->SetColor(XMFLOAT4(x, 1.0, 1.0, x));

	if (Input::GetKeyTrigger(VK_SPACE))
	{
		m_NextScene = true;
		m_Fade->SetFade(FadeOut);
	}
	if (m_NextScene)
	{
		if (m_Fade->Fade())
		{
			Manager::SetScene<Game>();
		}
		else
		{
			m_Fade->Fade();
		}
	}
}
void Loading::Fade()
{
}
//void Loading::Draw()

