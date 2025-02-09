#include "main.h"
#include "renderer.h"
#include "enemyMachine.h"
#include <list>
#include "game.h"
#include "enemyAIBehavior.h"
#include "enemyAIState.h"

// ビヘイビアツリー

BEHAVIOR_RESULT BehaviorSequence::Update()
{
	BEHAVIOR_RESULT result = m_Child[m_Index]->Update();
	switch (result)
	{
	case BEHAVIOR_RESULT_CONTINUE:
		return BEHAVIOR_RESULT_CONTINUE;

	case BEHAVIOR_RESULT_SUCCESS:
		m_Index++;
		if (m_Index < m_Child.size())
		{
			return BEHAVIOR_RESULT_CONTINUE;
		}
		else
		{
			m_Index = 0;
			return BEHAVIOR_RESULT_SUCCESS;
		}

	case BEHAVIOR_RESULT_FAULURE:
		m_Index = 0;
		return BEHAVIOR_RESULT_FAULURE;
	}
}
BehaviorNode::BehaviorNode(EnemyAIState* enemyAIState):m_EAIS(enemyAIState)
{
}

BehaviorNode::~BehaviorNode()
{

}

void BehaviorNode::Init(EnemyMachine* _enemy)
{
	m_EM = _enemy;
	if (m_EAIS)	m_EAIS->Init(_enemy);

	if (m_Child.empty()) return;

	for (auto child : m_Child)
	{
		child->Init(_enemy);
	}
}

void BehaviorNode::AddChild(BehaviorNode* _child)
{
	m_Child.push_back(_child);
}

void BehaviorNode::Uninit()
{
	if (!m_Child.empty())
	{
		for (auto child : m_Child)
		{
			child->Uninit();
			child = nullptr;
			delete child;
		}
		m_Child.clear();
	}

	if (!m_EAIS) return;

	m_EAIS->Uninit();
	m_EAIS = nullptr;
	delete m_EAIS;
}

BEHAVIOR_RESULT BehaviorTask_Battle_Idle::Update()
{
	if (m_EM->EnemyAILength() < ENEMYMOVE_LENGTH_IDLE)
	{
		return BEHAVIOR_RESULT_SUCCESS;
	}

	return BEHAVIOR_RESULT_CONTINUE;
}

BEHAVIOR_RESULT BehaviorTask_Battle_Move::Update()
{
	//ステートマシンUpdate
	if (m_EAIS)	m_EAIS->Update();

	/*
	if (m_EM->EnemyAILength() < ENEMYMOVE_LENGTH_AWAY)
	{
		return BEHAVIOR_RESULT_FAULURE;
	}
	*/
	return BEHAVIOR_RESULT_SUCCESS;
}

BEHAVIOR_RESULT BehaviorTask_Battle_Attack_Gun::Update()
{
//	m_EM->EnemyTracking();
	m_EM->Attack();
	return BEHAVIOR_RESULT_SUCCESS;
}

BEHAVIOR_RESULT BehaviorSelector::Update()
{
	BEHAVIOR_RESULT result = m_Child[m_Index]->Update();

	switch (result)
	{
	case BEHAVIOR_RESULT_CONTINUE:
		return BEHAVIOR_RESULT_CONTINUE;

	case BEHAVIOR_RESULT_SUCCESS:
		m_Index = 0;
		return BEHAVIOR_RESULT_SUCCESS;

	case BEHAVIOR_RESULT_FAULURE:
		m_Index++;
		if (m_Index < m_Child.size())
		{
			return BEHAVIOR_RESULT_CONTINUE;
		}
		else
		{
			m_Index = 0;
			return BEHAVIOR_RESULT_FAULURE;
		}
	}
}

BEHAVIOR_RESULT BehaviorTask_HealthCheck::Update()
{
	// 体力70未満で次のノードへ
	if (m_EM->GetHp() < 70)
	{
		return BEHAVIOR_RESULT_FAULURE;
	}
	return BEHAVIOR_RESULT_SUCCESS;
}

BEHAVIOR_RESULT BehaviorTask_Battle_Away::Update()
{
	if (m_EM->Away())
	{
		return BEHAVIOR_RESULT_SUCCESS;
	}
	return BEHAVIOR_RESULT_FAULURE;
}

BEHAVIOR_RESULT BehaviorTask_Battle_Tracking::Update()
{
	if (m_EM->GetTarget() == nullptr)
	{
		return BEHAVIOR_RESULT_FAULURE;
	}

	m_EM->EnemyTracking();

	return BEHAVIOR_RESULT_SUCCESS;
}

BEHAVIOR_RESULT BehaviorTask_Battle_Boost::Update()
{
	if (m_EM->Boost())
	{
		return BEHAVIOR_RESULT_SUCCESS;
	}
	return BEHAVIOR_RESULT_FAULURE;
}

BEHAVIOR_RESULT BehaviorTask_Battle_DownMove::Update()
{
	//ステートマシンUpdate
	m_EM->DownMove();

	if (m_EM->EnemyAILength() < ENEMYMOVE_LENGTH_AWAY)
	{
		return BEHAVIOR_RESULT_FAULURE;
	}
	return BEHAVIOR_RESULT_SUCCESS;
}

BEHAVIOR_RESULT BehaviorTask_RangeCheck::Update()
{
	if (m_EM->EnemyAILength() < ENEMYMOVE_LENGTH_AWAY)
	{
		return BEHAVIOR_RESULT_FAULURE;
	}
	return BEHAVIOR_RESULT_SUCCESS;
}

