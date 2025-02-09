#include "scene.h"
#include "menu.h"

void Scene::Init()
{
	m_menu = false;
//	m_Camera = GetGameObject<Camera>();
//	m_Menu = GetGameObject <Menu>();
}

void Scene::Uninit()
{
	for (int i = 0; i < goLayerType::LayerTypeMax; i++)
	{
		for (GameObject* object : m_GameObject[i])
		{
			object->Uninit();			
			delete object;
		}
		m_GameObject[i].clear();
	}
}

void Scene::Update()
{
	

	if (m_Camera != nullptr)
	{
		if (m_menu)
		{
			m_Menu->Update();
			return;	// メニュー中は止める
		}

		Camera* camera = m_Camera;
		for (int i = 0; i < goLayerType::LayerTypeMax; i++)
		{
			m_GameObject[i].sort([camera](GameObject* a, GameObject* b)
				{
					float distanceA = camera->LengthSq(a->GetPosition());
					float distanceB = camera->LengthSq(b->GetPosition());
					return distanceA > distanceB;
					//					return distanceA < distanceB;

				}

			);
		}


		for (int i = 0; i < goLayerType::LayerTypeMax; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				object->Update();	// ポリモフィズム・多態性
			}
		}

		for (int i = 0; i < goLayerType::LayerTypeMax; i++)
		{

			//			for (GameObject* object : m_GameObject[i])
			{
				// ラムダ式...名前のない関数(こうすると関数っぽい)
				// remove_if...戻り値がtrueだったらリストから消す
				m_GameObject[i].remove_if
				(
					[](GameObject* object)
					{
						return object->Destroy();
					}
				);

			}
		}
	}
}

void Scene::Draw()
{



	for (int i = 0; i < goLayerType::LayerTypeMax; i++)
	{
		for (GameObject* object : m_GameObject[i])
		{
			object->Draw();
		}
	}
}

void Scene::SetMenu(Menu* _menu)
{
	m_menu = !m_menu;
	m_Menu = _menu;
}

void Scene::SetCamera(Camera* _camera)
{
	m_Camera = _camera;
}