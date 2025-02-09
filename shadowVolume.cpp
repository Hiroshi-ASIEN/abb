#include "main.h"
#include "renderer.h"
#include "shadowVolume.h"
#include "modelRenderer.h"
#include "input.h"
#include "manager.h"


void ShadowVolume::Init()
{
	m_ModelComponent = new ModelRenderer(this);
	((ModelRenderer*)m_ModelComponent)->Load("asset\\model\\sphere_smooth.obj");

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\envMappingVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "shader\\envMappingPS.cso");


}

void ShadowVolume::Uninit()
{
	delete m_ModelComponent;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

}

void ShadowVolume::Update()
{
//	m_Rotation.x += 0.01f;
	m_Rotation.z += 0.01f;
}

void ShadowVolume::Draw()
{
	// ���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// �V�F�[�_�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// ���[���h�}�g���N�X�ݒ�
	XMMATRIX world, scale, rot, trans;
	scale = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	//	rot = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);



	rot = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y + XM_PI, m_Rotation.z);

	trans = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(world);



	// �J���[�o�b�t�@�}�X�N�L��
	Renderer::SetBlendMaskEnable(true);

	// �X�e���V�������ݗL��
	Renderer::SetStencilEnable(true);

	// �J�����O����
	Renderer::SetCulEnable(false);

	m_ModelComponent->Draw();

	// �J���[�o�b�t�@�}�X�N����
	Renderer::SetBlendMaskEnable(false);

	// �X�e���V�������ݖ���
	Renderer::SetDepthEnable(true);

	// �J�����O����
	Renderer::SetCulEnable(true);

}