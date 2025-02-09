#pragma once

#include "gameObject.h"

// ó˚èKópÉNÉâÉX
class Score:public GameObject
{
private:
	ID3D11Buffer*				m_VertexBuffer = NULL;
	ID3D11ShaderResourceView*	m_Texture = NULL;

	ID3D11VertexShader*			m_VertexShader;
	ID3D11PixelShader*			m_PixelShader;
	ID3D11InputLayout*			 m_VertexLayout;

	int m_Score = 0;
	int m_EnemyScore = 0;
	int m_Time;
	int m_Second;
	int m_Minutes;
	//	class Component*			m_BGM{};

public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void SetTexture(ID3D11ShaderResourceView*);

	void AddScore(int score);
	int GetScore();

	void AddEnemyScore(int score);
	int GetEnemyScore();

};