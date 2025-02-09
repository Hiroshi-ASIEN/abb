/**************************************************
* Bill�N���X
* [player.h]
* Author    �F���{�h�n
* Date      �F2024�N05��15��
***************************************************/
#pragma once

#include "gameObject.h"
#include "component.h"

#define COMPONENT_INDEX (20)

//==================================================
// Bill�N���X
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
