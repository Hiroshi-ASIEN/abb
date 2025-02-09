#include "main.h"
#include "renderer.h"
#include "cylinder.h"
#include "modelRenderer.h"
#include "input.h"
#include "manager.h"


void Cylinder::Init()
{
//		Accept(new ModelRenderer(this));
	
	m_ModelComponent = new ModelRenderer(this);
//	((ModelRenderer*)m_Component)->Load("asset\\model\\cylinder.obj");
	((ModelRenderer*)m_ModelComponent)->Load("asset\\model\\entyu.obj");
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\unlitTextureVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "shader\\unlitTexturePS.cso");
}


void Cylinder::Uninit()
{
	delete m_ModelComponent;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

}

void Cylinder::Update()
{
	m_ModelComponent->Update();
	
//	Move();
//	TrackingCylinder();
	
}

void Cylinder::Draw()
{
	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// ワールドマトリクス設定
	XMMATRIX world, scale, rot, trans;
	scale = XMMatrixScaling(m_Scale.x*0.4f, m_Scale.y*0.5, m_Scale.z * 0.4f);
//	rot = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	

	rot = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y + XM_PI, m_Rotation.z);

	trans = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(world);

	m_ModelComponent->Draw();

}

void Cylinder::Move()
{
	m_Accel.x = 1.0f;
	m_Accel.z = 1.0f;

	LeftMove();

	if (m_Position.y < 0.0f)
	{
		m_Position.y = 0.0f;
	}

}


void Cylinder::UpMove()
{
	m_Velocity.z = 3.0f;

	m_Velocity.z += m_Accel.z * m_dt;
	m_Position.z += m_Velocity.z * m_dt;
}

void Cylinder::DownMove()
{
	m_Velocity.z = -3.0f;

	m_Velocity.z += (-m_Accel.z) * m_dt;
	m_Position.z += m_Velocity.z * m_dt;
}

void Cylinder::LeftMove()
{
	m_Velocity.x = -3.0f;

	m_Velocity.x += (-m_Accel.x) * m_dt;
	m_Position.x += m_Velocity.x * m_dt;
}

void Cylinder::RightMove()
{
	m_Velocity.x = 3.0f;

	m_Velocity.x += m_Accel.x * m_dt;
	m_Position.x += m_Velocity.x * m_dt;
}

void Cylinder::Accept(Component* component)
{
//	m_component.push_back(component);

}

void Cylinder::TrackingCylinder()
{
	Scene* scene;
	scene = Manager::GetScene();

	XMFLOAT3 targetPos = scene->GetGameObject<Player>()->GetPosition();

	float x = targetPos.x - this->m_Position.x ;
	float z = targetPos.z - this->m_Position.z ;
	float len = x * x + z * z;

	m_Rotation.y = len * 180 / 3.14;
//	m_Rotation.y += (m_Rotation.y + sinf(targetPos.x));
//	m_Rotation.y -= (m_Rotation.y - cosf(targetPos.z));

//	m_Rotation.y = (cosf(m_Position.x -targetPos.x))*(-sinf(m_Position.z -targetPos.z));

	
	

	//XMFLOAT3 fofward = GetForward();

	//m_Velocity.x += fofward.x * 0.1f;
	//m_Velocity.y += fofward.y * 0.1f;
	//m_Velocity.z += fofward.z * 0.1f;

	//m_Position.x += m_Velocity.x * m_dt;
	//m_Position.y += m_Velocity.y * m_dt;
	//m_Position.z += m_Velocity.z * m_dt;

//	m_Position.x = targetPos.x - sinf(m_Rotation.y);// *m_len;
//	m_Position.z = targetPos.z - cosf(m_Rotation.y);// *m_len;

}