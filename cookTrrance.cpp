#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "cookTrrance.h"
#include "input.h"

void CookTrrance::Init()
{
	m_Model = new CModel();
	m_Model->Load( "asset\\model\\torus.obj" );

	m_Position = D3DXVECTOR3( 3.0f, 1.0f, 0.0f );//<========表示座標
	m_Rotation = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	m_Scale = D3DXVECTOR3( 1.0f, 1.0f, 1.0f );

	//読み込むシェーダーはcsoファイルであることに注意　あとファイルパスも注意！
	CRenderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "cookTrranceVS.cso");
	CRenderer::CreatePixelShader(&m_PixelShader, "cookTrrancePS.cso");


}

void CookTrrance::Uninit()
{
	m_Model->Unload();
	delete m_Model;


	//ここにシェーダーオブジェクトの解放を追加
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

}


void CookTrrance::Update()
{
	if (CInput::GetKeyPress('A'))
		m_Position.x -= 0.1f;

	if (CInput::GetKeyPress('D'))
		m_Position.x += 0.1f;

	if (CInput::GetKeyPress('W'))
		m_Position.z += 0.1f;

	if (CInput::GetKeyPress('S'))
		m_Position.z -= 0.1f;


	if (CInput::GetKeyPress('R'))
		m_Rotation.x -= 0.1f;
	if (CInput::GetKeyPress('F'))
		m_Rotation.x += 0.1f;

	if (CInput::GetKeyPress('Q'))
		m_Rotation.y -= 0.1f;
	if (CInput::GetKeyPress('E'))
		m_Rotation.y += 0.1f;

}

void CookTrrance::Draw()
{
	//return;
	//インプットレイアウトのセット（DirectXへ頂点の構造を教える）
	CRenderer::GetDeviceContext()->
		IASetInputLayout(m_VertexLayout);

	//バーテックスシェーダーオブジェクトのセット
	CRenderer::GetDeviceContext()->
		VSSetShader(m_VertexShader, NULL, 0);

	//ピクセルシェーダーオブジェクトのセット
	CRenderer::GetDeviceContext()->
		PSSetShader(m_PixelShader, NULL, 0);

	// マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;

	CRenderer::SetWorldMatrix(&world);

	m_Model->Draw();
}


