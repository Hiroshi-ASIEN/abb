/**************************************************
* [Scene.h]
* 
* Author：松本紘始
* Date	：2024年05月29日
***************************************************/
#pragma once

#include <list>
#include <vector>

#include "gameObject.h"
#include "polygon2D.h"
#include "camera.h"
#include "field.h"
#include "player.h"
#include "bullet.h"
#include "sky.h"
#include "effect.h"
#include "tree.h"
#include "cylinder.h"
#include "ui.h"
#include "water.h"
#include "grass.h"
#include "bill.h"
#include "dentou.h"
#include "menu.h"

//==================================================
// クラス
//==================================================

class Scene
{
private:
	bool m_menu{};
	class Camera* m_Camera{};
	class GameObject* m_Menu{};
protected:
	std::list <GameObject*> m_GameObject[goLayerType::LayerTypeMax];

	// 距離によってソートすればzソート
public:
	Scene() = default;			// コンストラクタ
	virtual ~Scene()	// デストラクタ
	{
		Uninit();
	}

	virtual void Init();	// 仮想関数
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();


	template <typename T>	// テンプレート関数
	T* AddGameObject(int Layer)	// 描画順どこに追加するのか
	{
		T* gameObject = new T();
		gameObject->Init();
		m_GameObject[Layer].push_back(gameObject);

		return gameObject;
	}

	template <typename T>	// テンプレート関数
	T* GetGameObject()
	{
		for (int i = 0; i < goLayerType::LayerTypeMax; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				// dinamic_cast 変換できるときは変換。
				// 型が違う等で変換できない時はnullを返す。

				T* ret = dynamic_cast<T*>(object);

				if (ret != nullptr)	return ret;

			}
		}
		return nullptr;
	}


	template <typename T>	// テンプレート関数
	std::vector<T*> GetGameObjects()
	{
		std::vector<T*> objectList;

		for (int i = 0; i < goLayerType::LayerTypeMax; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				// dinamic_cast 変換できるときは変換。
				// 型が違う等で変換できない時はnullを返す。

				T* ret = dynamic_cast<T*>(object);

				if (ret != nullptr)	objectList.push_back(ret);

			}


		}

		return objectList;
	}


	template <typename T>	// テンプレート関数
	int GetGameObjectLengs()
	{
		int len = 0;
		for (int i = 0; i < goLayerType::LayerTypeMax; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{

				T* ret = dynamic_cast<T*>(object);

				if (ret != nullptr)	len++;
			}
			return len;
		}
	}


	void SetMenu(Menu* _menu);
	void SetCamera(Camera* _camera);
};

//////////////////// EOF ////////////////////