#include "main.h"
#include "renderer.h"
#include "bill.h"
#include "modelRenderer.h"
#include "input.h"
#include "manager.h"
#include "meshField.h"

Component* Bill::m_ModelComponent;
ID3D11ShaderResourceView* Bill::m_EnvTexture;

void Bill::Init()
{
	
//	m_ModelComponent = new ModelRenderer(this);
//	((ModelRenderer*)m_ModelComponent)->Load("asset\\mymodel\\bill.obj");

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\unlitTextureVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "shader\\unlitTexturePS.cso");
//	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\envMappingVS.cso");
//	Renderer::CreatePixelShader(&m_PixelShader, "shader\\envMappingPS2.cso");

	/*

	TexMetadata metadata;
	ScratchImage image;
	LoadFromWICFile(L"asset\\texture\\canary_wharf.jpg", WIC_FLAGS_NONE, &metadata, image);
	CreateShaderResourceView(Renderer::GetDevice(), image.GetImages(), image.GetImageCount(), metadata, &m_EnvTexture);
	assert(m_EnvTexture);
	*/
}

void Bill::Uninit()
{
//	delete m_ModelComponent;

//	m_EnvTexture->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

}

void Bill::Update()
{
	m_ModelComponent->Update();
	
//	Move();
//	TrackingBill();
	
}

void Bill::Draw()
{
	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// ワールドマトリクス設定
	XMMATRIX world, scale, rot, trans;
	scale = XMMatrixScaling(m_Scale.x, m_Scale.y*0.5, m_Scale.z);
//	rot = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	
		// テクスチャ設定(特殊なテクスチャを1に設定してみる
	Renderer::GetDeviceContext()->PSSetShaderResources(1, 1, &m_EnvTexture);
	rot = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y + XM_PI, m_Rotation.z);

	trans = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(world);

	((ModelRenderer*)m_ModelComponent)->Draw();

}
void Bill::SetXZPosition(XMFLOAT3 pos)
{
	Scene* scene = Manager::GetScene();
	float groundHeight;	// 地面の高さ
	groundHeight = scene->GetGameObject<MeshField>()->GetHeight(pos);
	groundHeight += 1.0f * (this->m_Scale.y / 2);
	this->SetPosition({ pos.x,groundHeight,pos.z });
}

void Bill::Load()
{
	m_ModelComponent = new ModelRenderer();
	((ModelRenderer*)m_ModelComponent)->Load("asset\\mymodel\\bill.obj");

	TexMetadata metadata;
	ScratchImage image;
	LoadFromWICFile(L"asset\\texture\\canary_wharf.jpg", WIC_FLAGS_NONE, &metadata, image);
	CreateShaderResourceView(Renderer::GetDevice(), image.GetImages(), image.GetImageCount(), metadata, &m_EnvTexture);
	assert(m_EnvTexture);
}

void Bill::Unload()
{
	m_ModelComponent->Uninit();
	delete m_ModelComponent;

	m_EnvTexture->Release();
}
