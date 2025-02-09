/**************************************************
* Managerクラス-シングルトン
* [Manager.h]
* Author    ：松本紘始
* Date      ：年月日
***************************************************/

#pragma once

#include <list>
#include "scene.h"

//--------------------------------------------------
// ゲーム全体を管理
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

	template<typename T>	// テンプレート関数
	static void SetScene()
	{
		m_NextScene = new T();
		
	}
};