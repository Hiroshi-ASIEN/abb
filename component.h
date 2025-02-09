/**************************************************
* [component.h]
* 
* Author：松本紘始
* Date	：2024年05月22日
***************************************************/
#pragma once

//==================================================
// コンポーネントクラス
//==================================================
class Component
{
protected:

	class GameObject* m_GameObject = nullptr;	// 使われる先
	bool m_Enable = true;

public:

	Component() = default;
	Component(GameObject* Object);
	virtual ~Component();

	virtual void Init();	// 仮想関数
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

	bool GetEnable() 
	{
		return m_Enable;
	}
};

//////////////////// EOF ////////////////////
