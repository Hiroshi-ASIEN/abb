#pragma once
#include "movePattern.h"

class MovePatternSlide:public MovePattern
{
public:
	MovePatternSlide();
	virtual ~MovePatternSlide() = default;
	virtual void Update(Player* object) override;
};