#pragma once
#include "gameObject.h"

class Camera :public GameObject
{
protected:
	class Scene* m_Scene{};

	XMFLOAT3 m_TargetPos{};
	XMFLOAT4X4 m_ViewMatrix{};	// カメラ用　どこからどう見てるか

	float m_len{};		// カメラの視点と注視点の距離

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