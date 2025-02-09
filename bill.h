/**************************************************
* Billクラス
* [player.h]
* Author    ：松本紘始
* Date      ：2024年05月15日
***************************************************/
#pragma once

#include "gameObject.h"
#include "component.h"

#define COMPONENT_INDEX (20)

//==================================================
// Billクラス
//==================================================
class Bill :public GameObject
{
private:
	static Component* m_ModelComponent;
	static ID3D11ShaderResourceView* m_EnvTexture;
	
	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};
public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void SetXZPosition(XMFLOAT3 pos);
 	static void Load();
	static void Unload();
};




//////////////////// EOF ////////////////////
