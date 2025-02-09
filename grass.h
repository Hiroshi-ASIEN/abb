#pragma once

#include "gameObject.h"

// エフェクトは3dで座標指定するので3dオブジェクト
class Grass :public GameObject
{
private:
	ID3D11ShaderResourceView* m_Texture;	// テクスチャ使用用
	static ID3D11ShaderResourceView* m_GrassTexture0;
	static ID3D11ShaderResourceView* m_GrassTexture1;
	static ID3D11ShaderResourceView* m_GrassTexture2;
	static ID3D11ShaderResourceView* m_GrassTexture3;

	ID3D11Buffer* m_VertexBuffer = NULL;

	// ID3D11Bufferは汎用性が高い何でも入れれる
	ID3D11Buffer* m_PositionBuffer{};			// GPUへ座標情報送信用...実際に値が入っている
	ID3D11ShaderResourceView* m_PositionSRV{};	// PositionBufferへアクセスするための窓口用

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;


public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void SetXZPosition(XMFLOAT3 pos);

	void SetType(int i);

	void SetRandomRange(int _xRange, int _xOffSet, int _zRange, int _zOffSet);


	static void Load();
	static void Unload();
};