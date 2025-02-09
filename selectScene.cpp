#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "selectScene.h"
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
#include "title.h"

#include "weaponBase.h"
#include "weaponCanon.h"
#include "weaponRifle.h"
#include "weaponMissile.h"
#include "weaponSword.h"

WEAPON_TYPE SelectScene::m_SelectRWeapon;
WEAPON_TYPE SelectScene::m_SelectLWeapon;

void SelectScene::CorsorPositionsSet()
{
	for (int i = 0; i < 4; i++)
	{
		m_CorsorPositions[i].x = SCREEN_WIDTH * 0.2f;
		m_CorsorPositions[i].y = SCREEN_HEIGHT * (0.15f * (i + 1));
	}

	for (int i = 4; i < 10; i++)
	{
		m_CorsorPositions[i].x = SCREEN_WIDTH * (0.21f * (i-3));
		m_CorsorPositions[i].y = SCREEN_HEIGHT * 0.8f;
	}

}

void SelectScene::Init()
{
	// タイトルロード画面作成
	
	/*
	m_SelectSceneLoad = AddGameObject<UI>(goLayerType::Texture2d);
	m_SelectSceneLoad->InitSet(L"asset\\texture\\selectmenu.png", XMFLOAT4(0.0f, 0.0f,0.0f, 0.0f),0);
	m_SelectSceneLoad->SetColor(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	*/
	CorsorPositionsSet();

	// 選択カーソル用
	m_SelectCursor = AddGameObject<UI>(goLayerType::Texture2d);
	m_SelectCursor->InitSet(L"asset\\texture\\white.png", XMFLOAT4(100, 300, 500, 500), 0);
	m_SelectCursor->SetColor({ 0.3f,0.5f, 1.0f, 1.0f });
	m_SelectCursor->SetPos(
		{ m_CorsorPositions[m_NowCorsorPosition].x,
		m_CorsorPositions[m_NowCorsorPosition].y,
		50.0f + m_CorsorPositions[m_NowCorsorPosition].x,
		60.0f });

	// 詳細情報表示用
	m_DiscriptionView = AddGameObject<UI>(goLayerType::Texture2d);
	m_DiscriptionView->InitSet(L"asset\\texture\\aGa.png", XMFLOAT4(100, 100, 200, 200), 0);
	m_DiscriptionView->SetPos(XMFLOAT4((SCREEN_WIDTH * 0.5f) - 300.0f, (SCREEN_HEIGHT * 0.5f) + 150.0f, 600.0f, 40));

	// フェード用
	m_Fade = AddGameObject<Polygon2D>(goLayerType::Texture2d);
	m_Fade->InitSet(L"asset\\texture\\kuro.png", XMFLOAT4(0.0f, 0.0f, 1300.0f, 800.0f));
	m_Fade->SetPosition(XMFLOAT3(100.0f, -100.0f, 100.0f));
	m_Fade->SetFade(FadeIn);

	m_SelectScene = AddGameObject<UI>(goLayerType::Texture2d);
	m_SelectScene->InitSet(L"asset\\texture\\selectmenu.png", XMFLOAT4(100, 300, 500, 500), 0);
	m_SelectScene->SetPos({0.0f,0.0f,SCREEN_WIDTH,SCREEN_HEIGHT});
	m_SelectScene->SetColor({ 0.3f,0.5f, 1.0f, 1.0f });

	//====================================================================================================


	AddGameObject<Camera>(goLayerType::CameraObject)->SetPosition(XMFLOAT3(-3.0f, 2.0f, -5.0f));
	m_DummyRWeapon = AddGameObject<WeaponRifle>(goLayerType::Object3d);
	m_DummyRWeapon->SetPosition({ 3.0f,0.0f,0.0f });
	m_DummyLWeapon = AddGameObject<WeaponRifle>(goLayerType::Object3d);
	m_DummyLWeapon->SetPosition({ -3.0f,0.0f,0.0f });

	m_SelectRWeapon = WEAPON_TYPE::RIFLE;
	m_SelectLWeapon = WEAPON_TYPE::RIFLE;


}

void SelectScene::Uninit()
{
	// 継承元のUninit呼出
	Scene::Uninit();
}

void SelectScene::Update()
{

	// 継承元のUpdate呼出
	Scene::Update();

	if (!m_Fade->GetFadeFrag())
	{
		m_Fade->Fade();
	}


	this->CursorMove();	// カーソル移動処理

	// シーン切替処理
	if (m_NextScene)
	{
		if (m_Fade->Fade())
		{
			if (m_CorsorMenuStatus == CorsorMenuStatus::NextSceneSelect)	Manager::SetScene<Loading>();
			else if (m_CorsorMenuStatus == CorsorMenuStatus::BackSceneSelect)	Manager::SetScene<Title>();
		}
		else
		{
			m_Fade->Fade();
		}
	}
}

void SelectScene::CursorMove()
{
	if (m_CorsorMenuStatus == CorsorMenuStatus::RArmMenuSelect ||
		m_CorsorMenuStatus == CorsorMenuStatus::LArmMenuSelect)
	{
		CursorWeaponMenuMove();
	}
	else 	CursorMenuMove();

	m_SelectCursor->SetPos(
		{ m_CorsorPositions[m_NowCorsorPosition].x,
		m_CorsorPositions[m_NowCorsorPosition].y,
		60.0f,
		60.0f });

}
void SelectScene::CursorMenuMove()
{
	if (m_CorsorMenuStatus != CorsorMenuStatus::MenuSelect)return;

	if (Input::GetKeyTrigger(VK_DOWN))
	{
		m_NowCorsorPosition++;
		if (m_NowCorsorPosition > 3) m_NowCorsorPosition = 3;
	}
	if (Input::GetKeyTrigger(VK_UP))
	{
		m_NowCorsorPosition--;
		if (m_NowCorsorPosition < 0) m_NowCorsorPosition = 0;
	}

	if (Input::GetKeyTrigger(VK_SPACE))
	{
		switch (m_NowCorsorPosition)
		{
		case 0:
			m_CorsorMenuStatus = CorsorMenuStatus::NextSceneSelect;
			m_NextScene = true;
			m_Fade->SetFade(FadeOut);
			break;
		case 1:
			m_CorsorMenuStatus = CorsorMenuStatus::RArmMenuSelect;
			m_NowCorsorPosition = 4;
			break;
		case 2:
			m_CorsorMenuStatus = CorsorMenuStatus::LArmMenuSelect;
			m_NowCorsorPosition = 4;
			break;
		case 3:
			m_CorsorMenuStatus = CorsorMenuStatus::BackSceneSelect;
			m_NextScene = true;
			m_Fade->SetFade(FadeOut);
			break;
		default:
			break;
		}
	}

}
void SelectScene::CursorWeaponMenuMove()
{
	if (Input::GetKeyTrigger(VK_RIGHT))
	{
		m_NowCorsorPosition++;
		if (m_NowCorsorPosition > 9) m_NowCorsorPosition = 9;
	}
	if (Input::GetKeyTrigger(VK_LEFT))
	{
		m_NowCorsorPosition--;
		if (m_NowCorsorPosition < 4)
		{
			m_CorsorMenuStatus = CorsorMenuStatus::MenuSelect;

			if (m_CorsorMenuStatus == CorsorMenuStatus::RArmMenuSelect)	m_NowCorsorPosition = 1;
			else if (m_CorsorMenuStatus == CorsorMenuStatus::LArmMenuSelect)	m_NowCorsorPosition = 2;

			return;
		}
	}


	if (Input::GetKeyTrigger(VK_SPACE))
	{
		switch (m_NowCorsorPosition)
		{
		case 4:
			WeaponSelect(WEAPON_TYPE::CANON);
			break;
		case 5:
			WeaponSelect(WEAPON_TYPE::RIFLE);
			break;
		case 6:
			WeaponSelect(WEAPON_TYPE::MISSILE);
			break;
		case 7:
			WeaponSelect(WEAPON_TYPE::Sword);
			break;
		case 8:
			WeaponSelect(WEAPON_TYPE::CANON);
			break;
		case 9:
			WeaponSelect(WEAPON_TYPE::CANON);
			break;
		default:
			break;
		}


		if (m_CorsorMenuStatus == CorsorMenuStatus::RArmMenuSelect)	m_NowCorsorPosition = 1;
		else if (m_CorsorMenuStatus == CorsorMenuStatus::LArmMenuSelect)	m_NowCorsorPosition = 2;

		m_CorsorMenuStatus = CorsorMenuStatus::MenuSelect;
		return;
	}
}
void SelectScene::WeaponSelect(WEAPON_TYPE _weaponType)
{
	WeaponBase* weapon{};

	switch (_weaponType)
	{
	case CANON:
		weapon = AddGameObject<WeaponCanon>(goLayerType::Object3d);
		break;
	case RIFLE:
		weapon = AddGameObject<WeaponRifle>(goLayerType::Object3d);
		break;
	case MISSILE:
		weapon = AddGameObject<WeaponMissile>(goLayerType::Object3d);
		break;
	case Sword:
		weapon = AddGameObject<WeaponSword>(goLayerType::Object3d);
		break;
	case WT_MAX:
		break;
	default:
		break;
	}

	if (m_CorsorMenuStatus == CorsorMenuStatus::RArmMenuSelect)
	{
		m_SelectRWeapon = _weaponType;

		m_DestroyWeapon = m_DummyRWeapon;
		m_DummyRWeapon = weapon;
		m_DummyRWeapon->SetPosition({ 3.0f,0.0f,0.0f });
	}
	else if (m_CorsorMenuStatus == CorsorMenuStatus::LArmMenuSelect)
	{
		m_SelectLWeapon = _weaponType;

		m_DestroyWeapon = m_DummyLWeapon;
		m_DummyLWeapon = weapon;
		m_DummyLWeapon->SetPosition({ -3.0f,0.0f,0.0f });
	}
	m_DestroyWeapon->SetDestroy();
}

WEAPON_TYPE SelectScene::GetSelectRWeapon()
{
	return m_SelectRWeapon;
}

WEAPON_TYPE SelectScene::GetSelectLWeapon()
{
	return m_SelectLWeapon;
}
