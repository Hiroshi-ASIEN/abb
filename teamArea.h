/**************************************************
* TeamAreaクラス
* [player.h]
* Author    ：松本紘始
* Date      ：2024年05月15日
***************************************************/
#pragma once

#include "gameObject.h"
#include "component.h"

#define COMPONENT_INDEX (20)
#define COUNT_MAX (60*5)
#define SCORE_COUNT_MAX (60*5)
#define AREA_MIN (1)
#define AREA_MAX (4)

enum AreaState
{
	Non = 0,
	PlayerArea,
	EnemyArea,

	AreaStateMax,
};

//==================================================
// TeamAreaクラス
//==================================================
class TeamArea :public GameObject
{
private:
	Component* m_ComponentModel;

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	XMFLOAT3 m_Velocity = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 m_Accel = XMFLOAT3(0.0f, 0.0f, 0.0f);
	float m_dt = 1.0f / 60.0f;		// 経過時間

	class TeamAreaHead* m_Crystal;

	float m_ScoreCount{};
	float m_ChangeCount{};
	AreaState m_AreaState{};

	XMFLOAT4 m_Color{};

	int m_AreaNumber = 0;

	class EnemySpowner* se = nullptr;
public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void AreaTeamSearch();
	void ChangeType(AreaState type);

	void SetAreaNumber(int num);
	int GetAreaNumber();
	AreaState GetAreaState();
	void SetAreaState(AreaState state);

	void ColorChange();
};

//////////////////// EOF ////////////////////
