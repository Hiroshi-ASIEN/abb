#pragma once

class CookTrrance	//<======= コピーしたらcpp内も合わせてクラス名を修正する
{					//全部修正したらmanagerに追加して動作するようにする。

private:
	D3DXVECTOR3	m_Position;
	D3DXVECTOR3	m_Rotation;
	D3DXVECTOR3	m_Scale;

	CModel* m_Model;
	//ここに	シェーダー関連の変数を追加
	ID3D11VertexShader* m_VertexShader; //頂点シェーダーオブジェクト
	ID3D11PixelShader* m_PixelShader; //ピクセルシェーダーオブジェクト
	ID3D11InputLayout* m_VertexLayout; //頂点レイアウトオブジェクト

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};