/**************************************************
* Manager�N���X-�V���O���g��
* [Manager.h]
* Author    �F���{�h�n
* Date      �F�N����
***************************************************/

#pragma once

#include <list>
#include "scene.h"

//--------------------------------------------------
// �Q�[���S�̂��Ǘ�
//--------------------------------------------------
class Manager
{
private:
	static Manager* manager;
	static Scene* m_Scene;
	static Scene* m_NextScene;

public:
	Manager();
	static Manager* Instance();

	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	static Scene* GetScene() { return m_Scene; }

	template<typename T>	// �e���v���[�g�֐�
	static void SetScene()
	{
		m_NextScene = new T();
		
	}
};