#include "main.h"
#include "renderer.h"
#include "sky.h"
#include "modelRenderer.h"
#include "input.h"
#include "bullet.h"
#include "manager.h"
#include "camera.h"

void Sky::Init()
{		
		m_ModelComponent = new ModelRenderer(this);
		((ModelRenderer*)m_ModelComponent)->Load("asset\\model\\sky.obj");

		Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\unlitTextureVS.cso");
		Renderer::CreatePixelShader(&m_PixelShader, "shader\\unlitTexturePS.cso");
}

void Sky::Uninit()
{
	m_ModelComponent->Uninit();
	delete m_ModelComponent;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

}

void Sky::Update()
{
	m_ModelComponent->Update();
}

void Sky::Draw()
{

	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// ワールドマトリクス設定
	XMMATRIX world, scale, rot, trans;
	scale = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	rot = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	trans = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(world);

	m_ModelComponent->Draw();

}

void Sky::Move()
{

}
