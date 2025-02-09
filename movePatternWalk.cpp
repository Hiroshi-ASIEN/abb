#include "movePatternWalk.h"
#include "movePatternSlide.h"
#include "player.h"

MovePatternWalk::MovePatternWalk()
{
}

void MovePatternWalk::Update(Player* object)
{
	// スライドタイプへ移行
	object->ChangeMovePattern(new MovePatternSlide);
}
