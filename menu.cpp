#include "main.h"
#include "renderer.h"
#include "menu.h"

#include "input.h"

#include "manager.h"

#include "audio.h"
#include "modelRenderer.h"


#include <list>

#include "weaponBase.h"
#include "weaponRifle.h"
#include "weaponCanon.h"
#include "menuViewObject.h"

void Menu::Init()
{
	m_isMenu = false;// menuは最初起動しない
	Scene* scene = Manager::GetScene();

		m_UI = scene->AddGameObject<UI>(goLayerType::Texture2d);
		m_UI->InitSet(L"asset\\texture\\aOga.png", XMFLOAT4(100, 300, 500, 500), 0);
		m_UI->SetPos(XMFLOAT4(0.0f, 0.0f, 1000.0f, 1000.0f));
		m_UI->SetColor({ 0.2f,0.2f, 1.0f, 0.0f });
		m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
//		m_Weapons[1] = scene->AddGameObject<WeaponCanon>(goLayerType::Object3d);
}

void Menu::Uninit()
{

	for (Component* component : m_Component)
	{
		component->Uninit();
		delete component;
	}
	m_Component.clear();
}

void Menu::Update()
{
	MenuView();


}

void Menu::Draw()
{
	if (!m_isMenu) return;
	
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

	trans = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	// sinf(m_AnimeTime)*0.1
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(world);

	 m_Weapons->Draw();
}

void Menu::MenuView()
{
	if (Input::GetKeyTrigger('1'))
	{
		if (!m_isMenu)		MenuStart();
		else if (m_isMenu)	MenuEnd();
	}

	if (!m_isMenu) return;
	m_Weapons->Update();
	if (Input::GetKeyTrigger('2'))
	{
		Scene* scene = Manager::GetScene();
		Player* player;
		player=scene->GetGameObject<Player>();
		player->WeaponAccept(WEAPON_TYPE::MISSILE, WeaponPosition::WP_L_ARM);
	}
	if (Input::GetKeyTrigger('3'))
	{
		Scene* scene = Manager::GetScene();
		Player* player;
		player = scene->GetGameObject<Player>();
		player->WeaponAccept(WEAPON_TYPE::RIFLE, WeaponPosition::WP_L_ARM);
	}

	if (Input::GetKeyTrigger(VK_RIGHT))
	{
		m_IndexCursor++;
		if (m_IndexCursor < 1) m_IndexCursor = 1;
		else
		{
			m_Weapons->SetRotation(XMFLOAT3(0.0f, 0.0f, 0.0f));
			SelectModel(m_IndexCursor);
		}
	}
	if (Input::GetKeyTrigger(VK_LEFT))
	{
		m_IndexCursor--;
		if (m_IndexCursor < 0) m_IndexCursor = 0;
		else
		{
			m_Weapons->SetRotation(XMFLOAT3(0.0f, 0.0f, 0.0f));
			SelectModel(m_IndexCursor);
		}
	}
}

void Menu::MenuStart()
{
	if (m_isMenu) return;


	m_isMenu = true;
	Scene* scene = Manager::GetScene();
	m_Weapons = scene->AddGameObject<MenuVireObject>(goLayerType::Object3d);
	m_UI->SetColor({ 0.2f,0.2f, 1.0f, 0.7f });

	scene->SetMenu(this);
}
void Menu::MenuEnd()
{
	if (!m_isMenu)return;

	m_isMenu = false;
	Scene* scene = Manager::GetScene();

	m_Weapons->SetDestroy();
	m_UI->SetColor({ 0.2f,0.2f, 1.0f, 0.0f });

	scene->SetMenu(this);
}

void Menu::ComponentUpdate()
{
	for (Component* component : m_Component)
	{
		component->Update();
	}
}

void Menu::SelectModel(int index)
{
	switch (index)
	{
	case 0:
		m_Weapons->SetModel("asset\\mymodel\\testWeapon.obj");
		break;
	case 1:
		m_Weapons->SetModel("asset\\mymodel\\bill.obj");
		break;
	default:
		break;
	}
}

void Menu::SetPlayer(Player* _player)
{
	m_Player = _player;
}
