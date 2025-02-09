/**************************************************
* Menuクラス
* [player.h]
* Author    ：松本紘始
* Date      ：2024年05月15日
***************************************************/
#pragma once
#include "gameObject.h"
#include "menuViewObject.h"

//==================================================
// Menuクラス
//==================================================
class Menu:public GameObject
{
private:
	bool m_isMenu{};
	class UI* m_UI{};
	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11ShaderResourceView* m_Texture = NULL;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;
	XMFLOAT4 m_Material{};
	std::list<Component*> m_Components;

	XMFLOAT3	m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);	// 座標
	XMFLOAT3	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);	// 回転
	XMFLOAT3	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);		// 拡縮

	int m_IndexCursor{};
	XMFLOAT2 m_CursorPosition{};

	MenuVireObject* m_Weapons{};
	class Player* m_Player;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void MenuView();
	void MenuStart();
	void MenuEnd();
	void ComponentUpdate();

	void SelectModel(int index);
	void SetPlayer(Player* _player);

	template <typename T>	// テンプレート関数
	T* AddComponent()
	{
		T* component = new T(this);
		component->Init();

		m_Component.push_back(component);

		return component;
	}

	template <typename T>	// テンプレート関数
	T* GetComponent()
	{
		for (Component* component : m_Component)
		{
			// dinamic_cast 変換できるときは変換。
			// 型が違う等で変換できない時はnullを返す。

			T* ret = dynamic_cast<T*>(component);

			if (ret != nullptr)	return ret;

		}
		return nullptr;
	}

};


//////////////////// EOF ////////////////////
