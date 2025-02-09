/**************************************************
* EnemyAIBehavior
* [enemyAIBehavior.h]
* Author    �F���{�h�n
* Date      �F2025�N01��25��
***************************************************/
#pragma once

#include <unordered_map>
#include "enemyMachine.h"

// �r�w�C�r�A�c���[�m�[�h�̖߂�l
enum BEHAVIOR_RESULT
{
	BEHAVIOR_RESULT_CONTINUE,
	BEHAVIOR_RESULT_SUCCESS,
	BEHAVIOR_RESULT_FAULURE,
};

// �r�w�C�r�A�c���[�m�[�h�̊�{�N���X
class BehaviorNode
{
protected:
	std::vector<BehaviorNode*> m_Child;	// �q�m�[�h
	class EnemyMachine* m_EM{};
	EnemyAIState* m_EAIS{};	// �X�e�[�g�}�V��

public:
	BehaviorNode() {};
	BehaviorNode(EnemyAIState* enemyAIState);
	~BehaviorNode();

	void Init(EnemyMachine* _enemy);
	void AddChild(BehaviorNode* _child);

	virtual BEHAVIOR_RESULT Update() = 0;
	void Uninit();
};

// �r�w�C�r�A�c���[�̃V�[�P���X
class BehaviorSequence :public BehaviorNode
{
private:
	int m_Index = 0;

public:
	using BehaviorNode::BehaviorNode;	// ��{�N���X�̃R���X�g���N�^�𗘗p
	BEHAVIOR_RESULT Update()override;
};

// �r�w�C�r�A�c���[�̃Z���N�^
class BehaviorSelector :public BehaviorNode
{
private:
	int m_Index = 0;
public:
	using BehaviorNode::BehaviorNode;
	BEHAVIOR_RESULT Update()override;

};

// �r�w�C�r�A�c���[�̃^�X�N(�퓬)

class BehaviorTask_Battle_Idle :public BehaviorNode
{
public:
	using BehaviorNode::BehaviorNode;
	BEHAVIOR_RESULT Update()override;
};

class BehaviorTask_Battle_Move:public BehaviorNode
{
public:
	using BehaviorNode::BehaviorNode;
	BEHAVIOR_RESULT Update()override;
};

class BehaviorTask_Battle_Attack_Gun :public BehaviorNode
{
public:
	using BehaviorNode::BehaviorNode;
	BEHAVIOR_RESULT Update()override;
};

class BehaviorTask_Battle_Tracking :public BehaviorNode
{
public:
	using BehaviorNode::BehaviorNode;
	BEHAVIOR_RESULT Update()override;
};

class BehaviorTask_HealthCheck :public BehaviorNode
{
public:
	using BehaviorNode::BehaviorNode;
	BEHAVIOR_RESULT Update()override;
};

class BehaviorTask_RangeCheck :public BehaviorNode
{
public:
	using BehaviorNode::BehaviorNode;
	BEHAVIOR_RESULT Update()override;
};

class BehaviorTask_Battle_DownMove :public BehaviorNode
{
public:
	using BehaviorNode::BehaviorNode;
	BEHAVIOR_RESULT Update()override;
};
class BehaviorTask_Battle_Away :public BehaviorNode
{
public:
	using BehaviorNode::BehaviorNode;
	BEHAVIOR_RESULT Update()override;
};

class BehaviorTask_Battle_Boost :public BehaviorNode
{
public:
	using BehaviorNode::BehaviorNode;
	BEHAVIOR_RESULT Update()override;
};


//////////////////// EOF ////////////////////