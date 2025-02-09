#pragma once
/**************************************************
* TestObject�N���X
* object�Ńe�X�g����p
* Author    �F���{�h�n
* Date      �F2024�N11��18��
***************************************************/
#pragma once

#include "gameObject.h"
#include "component.h"


//==================================================
// TestObject�N���X
//==================================================
class TestObject :public GameObject
{
private:

	Component* m_ModelComponent{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	ID3D11ShaderResourceView* m_Texture = NULL;
	ID3D11ShaderResourceView* m_EnvTexture = NULL;
public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};