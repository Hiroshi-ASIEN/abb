/**************************************************
* [Scene.h]
* 
* Author�F���{�h�n
* Date	�F2024�N05��29��
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
// �N���X
//==================================================

class Scene
{
private:
	bool m_menu{};
	class Camera* m_Camera{};
	class GameObject* m_Menu{};
protected:
	std::list <GameObject*> m_GameObject[goLayerType::LayerTypeMax];

	// �����ɂ���ă\�[�g�����z�\�[�g
public:
	Scene() = default;			// �R���X�g���N�^
	virtual ~Scene()	// �f�X�g���N�^
	{
		Uninit();
	}

	virtual void Init();	// ���z�֐�
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();


	template <typename T>	// �e���v���[�g�֐�
	T* AddGameObject(int Layer)	// �`�揇�ǂ��ɒǉ�����̂�
	{
		T* gameObject = new T();
		gameObject->Init();
		m_GameObject[Layer].push_back(gameObject);

		return gameObject;
	}

	template <typename T>	// �e���v���[�g�֐�
	T* GetGameObject()
	{
		for (int i = 0; i < goLayerType::LayerTypeMax; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				// dinamic_cast �ϊ��ł���Ƃ��͕ϊ��B
				// �^���Ⴄ���ŕϊ��ł��Ȃ�����null��Ԃ��B

				T* ret = dynamic_cast<T*>(object);

				if (ret != nullptr)	return ret;

			}
		}
		return nullptr;
	}


	template <typename T>	// �e���v���[�g�֐�
	std::vector<T*> GetGameObjects()
	{
		std::vector<T*> objectList;

		for (int i = 0; i < goLayerType::LayerTypeMax; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				// dinamic_cast �ϊ��ł���Ƃ��͕ϊ��B
				// �^���Ⴄ���ŕϊ��ł��Ȃ�����null��Ԃ��B

				T* ret = dynamic_cast<T*>(object);

				if (ret != nullptr)	objectList.push_back(ret);

			}


		}

		return objectList;
	}


	template <typename T>	// �e���v���[�g�֐�
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