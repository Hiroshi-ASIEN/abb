/**************************************************
* [component.h]
* 
* Author�F���{�h�n
* Date	�F2024�N05��22��
***************************************************/
#pragma once

//==================================================
// �R���|�[�l���g�N���X
//==================================================
class Component
{
protected:

	class GameObject* m_GameObject = nullptr;	// �g�����
	bool m_Enable = true;

public:

	Component() = default;
	Component(GameObject* Object);
	virtual ~Component();

	virtual void Init();	// ���z�֐�
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

	bool GetEnable() 
	{
		return m_Enable;
	}
};

//////////////////// EOF ////////////////////
