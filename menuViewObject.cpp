#include "menuViewObject.h"
#include "manager.h"
#include "renderer.h"
#include "modelRenderer.h"
#include "player.h"

void MenuVireObject::Init()
{
	Scene* scene = Manager::GetScene();
	AddComponent<ModelRenderer>()->Load("asset\\mymodel\\Crystal.obj");
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\unlitTextureVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "shader\\unlitTexturePS.cso");

	m_Entity = false;


}

void MenuVireObject::Uninit()
{

}

void MenuVireObject::Update()
{
	m_Rotation.y += 0.01f;
	Scene* scene = Manager::GetScene();

	m_Position = scene->GetGameObject<Player>()->GetPosition();
}

void MenuVireObject::Draw()
{
	// ���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	Renderer::SetMaterial(MATERIAL{ m_Material });
	// �V�F�[�_�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// ���[���h�}�g���N�X�ݒ�
	XMMATRIX world, scale, rot, trans;
	scale = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);

	// �ʏ�
	rot = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	//	rot = XMMatrixRotationQuaternion(XMLoadFloat4(&m_Quatarnion));

	// 180�x���f������]�����ĕ`��i���j
	//	rot = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y + XM_PI, m_Rotation.z);

	trans = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	// sinf(m_AnimeTime)*0.1
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(world);
		this->GetComponent<ModelRenderer>()->Draw();
}

void MenuVireObject::SetModel(const char* FileName)
{
	GetComponent<ModelRenderer>()->Load(FileName);
}
