/**************************************************
* [AutoCamera.cpp]
* カメラ処理
* Author：松本紘始
* Date	：2024年05月15日
***************************************************/

#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "autoCamera.h"
#include "input.h"
#include "gameObject.h"
#include "player.h"
#include "scene.h"
#include "meshField.h"

void AutoCamera::Init()
{
	m_Position = XMFLOAT3(0.0f, 5.0f, -10.0f);
	m_TargetPos = XMFLOAT3(0.0f, 0.0f, 0.0f);

	float 	vx = m_Position.x - m_TargetPos.x;
	float 	vz = m_Position.z - m_TargetPos.z;

	m_len = sqrtf(vx * vx + vz * vz);

	Scene* scene = Manager::GetScene();
	scene->SetCamera(this);
	m_TargetPos = { 1.0f,1.0f,1.0f };
}

void AutoCamera::Uninit()
{
}

void AutoCamera::Update()
{
//	AutoCameraFollow();
	AutoCameraMove();
}

void AutoCamera::Draw()
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

void AutoCamera::AutoCameraMove()
{
	m_Rotation.y -= 0.001f;
	m_Rotation.z -= 0.001f;

	m_Position.x = m_TargetPos.x - sinf(m_Rotation.y) * m_len;
	m_Position.z = m_TargetPos.z - cosf(m_Rotation.y) * m_len;
}

void AutoCamera::AutoCameraFollow()
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

