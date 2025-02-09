#include "movePatternSlide.h"
#include "movePatternWalk.h"
#include "player.h"

MovePatternSlide::MovePatternSlide()
{
}

void MovePatternSlide::Update(Player* object)
{
	// 歩きタイプへ移行
	object->ChangeMovePattern(new MovePatternWalk);


}
