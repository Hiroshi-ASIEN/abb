#include "eMovePatternSearch.h"
#include "eMovePatternPTracking.h"
#include "enemy.h"
#include "player.h"
#include "manager.h"

EnemyMovePatternSearch::EnemyMovePatternSearch()
{
}

void EnemyMovePatternSearch::Update(Enemy* object, XMFLOAT3 targetPos)
{
	Scene* scene;
	scene = Manager::GetScene();

	Player* player = scene->GetGameObject<Player>();
	if (Collision(object->GetPosition(), player->GetPosition(),
		30.0f))
	{
		// プレイヤーを発見し、追従
		object->ChangeMovePattern(new EnemyMovePatternPTracking);
	}

	if (Collision(object->GetPosition(), targetPos, 2.0f))
	{

	}

}
