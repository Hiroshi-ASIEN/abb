#pragma once
#include "eMovePattern.h"

class EnemyMovePatternSearch :public EnemyMovePattern
{
public:
	EnemyMovePatternSearch();
	virtual ~EnemyMovePatternSearch() = default;
	virtual void Update(Enemy* object, XMFLOAT3 targetPos) override;
};