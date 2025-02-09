#include "eMovePatternPTracking.h"
#include "eMovePatternSearch.h"
#include "enemy.h"

EnemyMovePatternPTracking::EnemyMovePatternPTracking()
{
}

void EnemyMovePatternPTracking::Update(Enemy* object,XMFLOAT3 targetPos)
{
	// �����^�C�v�ֈڍs
//	object->ChangeMovePattern(new MovePatternWalk);
	if (!Collision(object->GetPosition(), targetPos,
		30.0f))
	{
		object->ChangeMovePattern(new EnemyMovePatternSearch);
	}
	

	m_Velocity.x = this->GetForward().x * m_Accel.x;
	m_Velocity.z = this->GetForward().z * m_Accel.z;

}
