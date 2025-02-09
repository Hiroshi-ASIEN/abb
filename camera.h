#pragma once
#include "gameObject.h"

class Camera :public GameObject
{
protected:
	class Scene* m_Scene{};

	XMFLOAT3 m_TargetPos{};
	XMFLOAT4X4 m_ViewMatrix{};	// �J�����p�@�ǂ�����ǂ����Ă邩

	float m_len{};		// �J�����̎��_�ƒ����_�̋���

	float m_mouseRotY{};
	class Player* m_Target{};
public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void CameraMove();
	void CameraFollow();

	virtual  float GetCameraRotY();

	virtual XMMATRIX GetViewMatrix();

	virtual bool CheckView(XMFLOAT3 _position, float _size);

	virtual void SetTarget(Player* _player);
};