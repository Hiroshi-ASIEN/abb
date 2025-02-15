/**************************************************
* Rendererクラス-シングルトン
* [Renderer.h]
* Author    ：松本紘始
* Date      ：年月日
***************************************************/

#pragma once


struct VERTEX_3D
{
	XMFLOAT3 Position;
	XMFLOAT3 Normal;
	XMFLOAT4 Diffuse;
	XMFLOAT2 TexCoord;
};



struct MATERIAL
{
	XMFLOAT4	Ambient;
	XMFLOAT4	Diffuse;
	XMFLOAT4	Specular;
	XMFLOAT4	Emission;
	float		Shininess;
	BOOL		TextureEnable;
	float		Dummy[2];
};



struct LIGHT
{
	BOOL		Enable;
	BOOL		Dummy[3];
	XMFLOAT4	Direction;
	XMFLOAT4	Diffuse;
	XMFLOAT4	Ambient;

	XMFLOAT4 Position;			// 光源の座標
	XMFLOAT4 PointLightParam;	// 光の範囲
};


//==================================================
// Renderer クラス
//==================================================
 class Renderer
{
private:
	static Renderer* renderer;

	static D3D_FEATURE_LEVEL       m_FeatureLevel;

	static ID3D11Device*           m_Device;
	static ID3D11DeviceContext*    m_DeviceContext;
	static IDXGISwapChain*         m_SwapChain;
	static ID3D11RenderTargetView* m_RenderTargetView;
	static ID3D11DepthStencilView* m_DepthStencilView;

	static ID3D11Buffer*			m_WorldBuffer;
	static ID3D11Buffer*			m_ViewBuffer;
	static ID3D11Buffer*			m_ProjectionBuffer;
	static ID3D11Buffer*			m_MaterialBuffer;
	static ID3D11Buffer*			m_LightBuffer;
	static ID3D11Buffer*			m_ParameterBuffer;

	static ID3D11Buffer* m_CameraBuffer;

	static ID3D11DepthStencilState* m_DepthStateEnable;
	static ID3D11DepthStencilState* m_DepthStateDisable;

	// ステンシルバッファ
	static ID3D11DepthStencilState* m_StencilWrite;
	static ID3D11DepthStencilState* m_StencilRead;

	static ID3D11BlendState*		m_BlendState;
	static ID3D11BlendState*		m_BlendStateAdd;	// 加算合成用ブレンドステート
	static ID3D11BlendState*		m_BlendStateATC;
	static ID3D11BlendState*		m_BlendStateMask;

	static ID3D11RasterizerState*	m_RasterizerStateCullBack;
	static ID3D11RasterizerState*	m_RasterizerStateCullNone;

	static	ID3D11ShaderResourceView* m_PEShaderResourceView;

public:
	Renderer();

	static void Init();
	static void Uninit();
	static void Begin();
	static void End();

	static void SetDepthEnable(bool Enable);
	static void SetATCEnable(bool Enable);
	static void SetStencilEnable(bool Enable);	// <<<<<<<<<<<<<
	static void SetBlendAddEnable(bool Enable);
	static void SetBlendMaskEnable(bool Enable);
	static void SetCulEnable(bool Enable);
	
	static void SetWorldViewProjection2D();
	static void SetWorldMatrix(XMMATRIX WorldMatrix);
	static void SetViewMatrix(XMMATRIX ViewMatrix);
	static void SetProjectionMatrix(XMMATRIX ProjectionMatrix);
	static void SetParameter(XMFLOAT4 Parameter);
	static void SetMaterial(MATERIAL Material);
	static void SetLight(LIGHT Light);
	
	static void SetCameraPosition(XMFLOAT3 CameraPosition);

	static ID3D11Device* GetDevice( void ){ return m_Device; }
	static ID3D11DeviceContext* GetDeviceContext( void ){ return m_DeviceContext; }
	static ID3D11ShaderResourceView* GetPETexture() { return m_PEShaderResourceView; }


	static void CreateVertexShader(ID3D11VertexShader** VertexShader, ID3D11InputLayout** VertexLayout, const char* FileName);
	static void CreatePixelShader(ID3D11PixelShader** PixelShader, const char* FileName);

	static Renderer* GetInstance();
};
