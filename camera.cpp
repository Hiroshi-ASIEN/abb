/**************************************************
* [Camera.cpp]
* カメラ処理
* Author：松本紘始
* Date	：2024年05月15日
***************************************************/

#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "input.h"
#include "gameObject.h"
#include "player.h"
#include "scene.h"
#include "meshField.h"


void Camera::Init()
{
	m_Position = XMFLOAT3(0.0f, 5.0f, -10.0f);
	m_TargetPos = XMFLOAT3(0.0f, 0.0f, 0.0f);

	float 	vx = m_Position.x - m_TargetPos.x;
	float 	vz = m_Position.z - m_TargetPos.z;

	m_len = sqrtf(vx * vx + vz * vz);

	Scene*  scene = Manager::GetScene();
	scene->SetCamera(this);

}

void Camera::Uninit()
{
}

void Camera::Update()
{
	CameraFollow();
	CameraMove();
}

void Camera::Draw()
{
	// ビューマトリクス設定
	XMFLOAT3 up{ 0.0f,1.0f,0.0f };
	XMMATRIX viewMatrix = XMMatrixLookAtLH(XMLoadFloat3(&m_Position), XMLoadFloat3(&m_TargetPos), XMLoadFloat3(&up));

	Renderer::SetViewMatrix(viewMatrix);

	XMStoreFloat4x4(&m_ViewMatrix, viewMatrix);

	// プロジェクションマトリクス設定
	XMMATRIX projextionMatrix;
	projextionMatrix = XMMatrixPerspectiveFovLH(1.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);

	Renderer::SetProjectionMatrix(projextionMatrix);
	Renderer::SetCameraPosition(m_Position);
}

void Camera::CameraMove()
{
	if (Input::GetKeyPress(VK_LEFT))
	{
		m_Rotation.y -= 0.01f;
	}
	if (Input::GetKeyPress(VK_RIGHT))
	{
		m_Rotation.y += 0.01f;
	}

	if (Input::GetKeyPress(VK_UP))
	{
		m_Position.y -= 0.1f;
	}
	if (Input::GetKeyPress(VK_DOWN))
	{
		m_Position.y += 0.1f;
	}

	/*
	if (Input::GetKeyPress(WM_LBUTTONDOWN))
	{
		m_Rotation.y -= 0.01f;
	}
	*/

	// マウスでカメラ移動処理
	POINT MousePoint;
	GetCursorPos(&MousePoint);

	float mouseRot = (MousePoint.x * 0.005) - 3.5;
	m_Rotation.y = mouseRot;
	m_mouseRotY = (MousePoint.y *0.005);// -3.5;

	//if (Input::GetKeyPress(VK_GAMEPAD_A))
	//{
	//	m_Rotation.y -= 0.01f;
	//}
	
	m_Position.x = m_TargetPos.x - sinf(m_Rotation.y) * m_len;
	m_Position.z = m_TargetPos.z - cosf(m_Rotation.y) * m_len;
	m_Position.y = (m_TargetPos.y - cosf(MousePoint.y * 0.005) * m_len);

/*
	if (MousePoint.y > 591)
	{
		m_Position.y = 10.0f;
	}
	*/
//	cylinder->SetPosition(XMFLOAT3 (MousePoint.x * 0.05, -(MousePoint.y * 0.05)+20.0f,10.0f));

}

void Camera::CameraFollow()
{
	if (m_Target == nullptr) return;
//	cylinder->SetPosition(XMFLOAT3(player->GetPosition().x+GetForward().x, player->GetPosition().y + GetForward().y, player->GetPosition().z + GetForward().z));

	m_TargetPos =m_Target->GetPosition();

	//m_TargetPos.y = 0.0f;	// ジャンプ時の縦ブレ制御
	m_Position.x = m_TargetPos.x;
	m_Position.y = m_TargetPos.y + 4.0f;
	m_Position.z = m_TargetPos.z - 6.0f;


	XMFLOAT3 target = m_Target->GetPosition();
	target.y += 2.0f;

	// 線形補完
	m_TargetPos.x += (target.x - m_TargetPos.x) * 0.1f;
	m_TargetPos.y += (target.y - m_TargetPos.y) * 0.1f;
	m_TargetPos.z += (target.z - m_TargetPos.z) * 0.1f;

}

float Camera::GetCameraRotY()
{
	return m_mouseRotY;
}

XMMATRIX Camera::GetViewMatrix()
{
	return XMLoadFloat4x4(&m_ViewMatrix);
}

bool Camera::CheckView(XMFLOAT3 _position,float _size)
{
	// ビューマトリクス設定
	XMFLOAT3 up{ 0.0f,1.0f,0.0f };
	XMMATRIX viewMatrix = XMMatrixLookAtLH(XMLoadFloat3(&m_Position), XMLoadFloat3(&m_TargetPos), XMLoadFloat3(&up));

	// プロジェクションマトリクス設定
	XMMATRIX projextionMatrix;
	projextionMatrix = XMMatrixPerspectiveFovLH(1.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);

	XMMATRIX viewProjection, inverseViewProjection;
	XMVECTOR det;

	viewProjection = viewMatrix * projextionMatrix;
	inverseViewProjection = XMMatrixInverse(&det, viewProjection);

	XMFLOAT3 vpos[4];
	XMFLOAT3 wpos[4];

	vpos[0] = XMFLOAT3(-1.0f, 1.0f, 1.0f);
	vpos[1] = XMFLOAT3(1.0f, 1.0f, 1.0f);
	vpos[2] = XMFLOAT3(-1.0f, -1.0f, 1.0f);
	vpos[3] = XMFLOAT3(1.0f, -1.0f, 1.0f);

	XMVECTOR vposv[4];
	XMVECTOR wposv[4];

	vposv[0] = XMLoadFloat3(&vpos[0]);
	vposv[1] = XMLoadFloat3(&vpos[1]);
	vposv[2] = XMLoadFloat3(&vpos[2]);
	vposv[3] = XMLoadFloat3(&vpos[3]);

	wposv[0] = XMVector3TransformCoord(vposv[0], inverseViewProjection);
	wposv[1] = XMVector3TransformCoord(vposv[1], inverseViewProjection);
	wposv[2] = XMVector3TransformCoord(vposv[2], inverseViewProjection);
	wposv[3] = XMVector3TransformCoord(vposv[3], inverseViewProjection);

	XMStoreFloat3(&wpos[0], wposv[0]);
	XMStoreFloat3(&wpos[1], wposv[1]);
	XMStoreFloat3(&wpos[2], wposv[2]);
	XMStoreFloat3(&wpos[3], wposv[3]);


	XMFLOAT3 v, v1, v2, n;
	v.x = _position.x - m_Position.x;
	v.y = _position.y - m_Position.y;
	v.z = _position.z - m_Position.z;

	// 左面判定
	{
		// [0]は左上
		v1.x = wpos[0].x - m_Position.x;
		v1.y = wpos[0].y - m_Position.y;
		v1.z = wpos[0].z - m_Position.z;

		// [2]は左下
		v2.x = wpos[2].x - m_Position.x;
		v2.y = wpos[2].y - m_Position.y;
		v2.z = wpos[2].z - m_Position.z;

		// 外積
		n.x = v1.y * v2.z - v1.z * v2.y;
		n.y = v1.z * v2.x - v1.x * v2.z;
		n.z = v1.x * v2.y - v1.y * v2.x;

		// 左面から点までの距離を求める
		// 内積
		float dot = n.x * v.x + n.y * v.y + n.z * v.z;
		
		// nの正規化(長さ1にする)が必要
		// 正規化

		// 長さがゼロでないことを確認してから正規化
		dot /= sqrt(n.x * n.x + n.y * n.y + n.z * n.z);

		// マイナスの場合は見えていない
//		if (dot < 0.0f)	return false;
		if (dot < -_size)	return false;

		// プラスなら見えてる
	}

	// 右面判定
	{
		// [1]は右上
		v1.x = wpos[3].x - m_Position.x;
		v1.y = wpos[3].y - m_Position.y;
		v1.z = wpos[3].z - m_Position.z;

		// [3]は右下
		v2.x = wpos[1].x - m_Position.x;
		v2.y = wpos[1].y - m_Position.y;
		v2.z = wpos[1].z - m_Position.z;

		// 外積
		n.x = v1.y * v2.z - v1.z * v2.y;
		n.y = v1.z * v2.x - v1.x * v2.z;
		n.z = v1.x * v2.y - v1.y * v2.x;

		// 左面から点までの距離を求める
		// 内積
		float dot = n.x * v.x + n.y * v.y + n.z * v.z;
		// 長さがゼロでないことを確認してから正規化
		dot /= sqrt(n.x * n.x + n.y * n.y + n.z * n.z);

		// マイナスの場合は見えていない
		if (dot < 0.0f)	return false;

		// プラスなら見えてる
	}

	// 奥判定
	{

		// [0]は左上
		v1.x = wpos[0].x - m_Position.x;
		v1.y = wpos[0].y - m_Position.y;
		v1.z = wpos[0].z - m_Position.z;

		// [1]は右上
		v2.x = wpos[1].x - m_Position.x;
		v2.y = wpos[1].y - m_Position.y;
		v2.z = wpos[1].z - m_Position.z ;

		// 外積
		n.x = v1.y * v2.z - v1.z * v2.y;
		n.y = v1.z * v2.x - v1.x * v2.z;
		n.z = v1.x * v2.y - v1.y * v2.x;

		// 左面から点までの距離を求める
		// 内積
		float dot = n.x * v.x + n.y * v.y + n.z * v.z;
		// 長さがゼロでないことを確認してから正規化
		dot /= sqrt(n.x * n.x + n.y * n.y + n.z * n.z);

		// マイナスの場合は見えていない
		if (dot > 0.0f)	return false;

		// プラスなら見えてる
		return true;
	}

	// すべて通過したら見えてる
	return true;
}

void Camera::SetTarget(Player* _player)
{
	m_Target = _player;
}

