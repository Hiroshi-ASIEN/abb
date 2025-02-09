/**************************************************
* [collision.cpp]
* 当たり判定
* Author：松本紘始
* Date	：年月日
***************************************************/
#include "main.h"
#include "manager.h"
#include "Collision.h"
#include "enemyMachine.h"
#include "scene.h"

//--------------------------------------------------
// 関数
//--------------------------------------------------
void Update()
{
	Scene* scene = Manager::GetScene();
	Bullet* bullet = scene->GetGameObject<Bullet>();
	EnemyMachine* enemy = scene->GetGameObject<EnemyMachine>();

	for (int i = 0; i < scene->GetGameObjectLengs<Bullet>(); i++)
	{
	}
}

bool CollisionBB(XMFLOAT3 positionA, XMFLOAT3 positionB, XMFLOAT3 sizeA, XMFLOAT3 sizeB)
{
	float Axmax = positionA.x + (sizeA.x / 2);
	float Axmin = positionA.x - (sizeA.x / 2);
	float Aymax = positionA.y + (sizeA.y / 2);
	float Aymin = positionA.y - (sizeA.y / 2);
	float Azmax = positionA.z + (sizeA.z / 2);
	float Azmin = positionA.z - (sizeA.z / 2);

	float Bxmax = positionB.x + (sizeB.x / 2);
	float Bxmin = positionB.x - (sizeB.x / 2);
	float Bymax = positionB.y + (sizeB.y / 2);
	float Bymin = positionB.y - (sizeB.y / 2);
	float Bzmax = positionB.z + (sizeB.z / 2);
	float Bzmin = positionB.z - (sizeB.z / 2);

	if ((Axmax>Bxmin)&&(Axmin<Bxmax))
	{
		if ((Aymax > Bymin) && (Aymin < Bymax))
		{
			if ((Azmax > Bzmin) && (Azmin < Bzmax))
			{
				return true;
			}
		}
	}
	return false;
}

bool Collision(XMFLOAT3 positionA, XMFLOAT3 positionB,float r)
{
	XMFLOAT3 direction;
	direction.x = positionA.x - positionB.x;
	direction.y = positionA.y - positionB.y;
	direction.z = positionA.z - positionB.z;

	float length;
	length = sqrtf(direction.x * direction.x
		+ direction.y * direction.y
		+ direction.z * direction.z);

	if (length < r)		return true;


	return false;
}

bool CollisionCircle(XMFLOAT3 positionA, XMFLOAT3 positionB, float r)
{
	XMFLOAT3 direction;
	direction.x = positionA.x - positionB.x;
	direction.z = positionA.z - positionB.z;

	float length;
	length = sqrtf(direction.x * direction.x
		+ direction.z * direction.z);

	if (length < r)		return true;


	return false;
}


colXYZ CollisionBBxyz(XMFLOAT3 positionA, XMFLOAT3 positionB, XMFLOAT3 sizeA, XMFLOAT3 sizeB)
{
	int i = -1;

	float Axmax = positionA.x + (sizeA.x / 2);
	float Axmin = positionA.x - (sizeA.x / 2);
	float Aymax = positionA.y + (sizeA.y / 2);
	float Aymin = positionA.y - (sizeA.y / 2);
	float Azmax = positionA.z + (sizeA.z / 2);
	float Azmin = positionA.z - (sizeA.z / 2);

	float Bxmax = positionB.x + (sizeB.x / 2);
	float Bxmin = positionB.x - (sizeB.x / 2);
	float Bymax = positionB.y + (sizeB.y / 2);
	float Bymin = positionB.y - (sizeB.y / 2);
	float Bzmax = positionB.z + (sizeB.z / 2);
	float Bzmin = positionB.z - (sizeB.z / 2);

	if ((Axmax > Bxmin) && (Axmin < Bxmax))
	{
		i++;
		if ((Aymax > Bymin) && (Aymin < Bymax))
		{
			i++;
			if ((Azmax > Bzmin) && (Azmin < Bzmax))
			{
				i++;
			}
		}
	}
	switch (i)
	{
	case -1:
		return non;
	}
	return non;
}


//////////////////// EOF ////////////////////

void SearchCollision::SearchListNearSort()
{
	GameObject* parent = m_Parent;
	// 近い順
	for (int i = 0; i < m_ListIndex; i++)
	{
		m_SearchList.sort([parent](GameObject* a, GameObject* b)
			{
				float distanceA = parent->LengthSq(a->GetPosition());
				float distanceB = parent->LengthSq(b->GetPosition());
				return distanceA < distanceB;
				//				return distanceA > distanceB;
			}
		);
	}
}

EnemyMachine* SearchCollision::GetNearEnemy(int nearNum)
{
//	SearchObject<Enemy>();
	SearchEnemy();
	SearchListNearSort();

	if (m_ListIndex == 0)return nullptr;

	int i = 0;

	for (auto object : m_SearchList)
	{
		i++;
		if (i == nearNum)
		{
			EnemyMachine* target = dynamic_cast<EnemyMachine*>(object);
			
			return object;
		}
	}

	return nullptr;
}


void SearchCollision::SearchEnemy()
{
	Scene* scene;
	scene = Manager::GetScene();

	m_ListIndex = 0;

	// 範囲内にあるオブジェクトを取得
	auto objectList = scene->GetGameObjects<EnemyMachine>();
	for (auto object : objectList)
	{

		XMFLOAT3 position = object->GetPosition();

//		if (CollisionBB(this->GetPosition(), object->GetPosition(),
//			this->GetScale(), object->GetScale()))
		if(OBB(object))
		{

			m_SearchList.push_back(object);
			m_ListIndex++;
		}
	}
}

bool SearchCollision::TouchGameObject(float colSize)
{
	Scene* scene;
	scene = Manager::GetScene();

	XMFLOAT3 fPos;
	fPos.x = m_Parent->GetPosition().x + m_Parent->GetForward().x;
	fPos.y = m_Parent->GetPosition().y + m_Parent->GetForward().y;
	fPos.z = m_Parent->GetPosition().z + m_Parent->GetForward().z;


	// 範囲内にあるオブジェクトを取得
	auto objectList = scene->GetGameObjects<GameObject>();
	for (auto object : objectList)
	{
		if (CollisionCircle(fPos, object->GetPosition(),colSize))
		{
			if (m_Parent == object)continue;
			if(object->GetEntity())	return true;
		}
	}
	return false;
}

bool SearchCollision::LRTouchGameObject(float colSize)
{
	Scene* scene;
	scene = Manager::GetScene();

	XMFLOAT3 rPos,lPos;
	rPos.x = m_Parent->GetPosition().x + m_Parent->GetRight().x;
	rPos.y = m_Parent->GetPosition().y + m_Parent->GetRight().y;
	rPos.z = m_Parent->GetPosition().z + m_Parent->GetRight().z;

	lPos.x = m_Parent->GetPosition().x - m_Parent->GetRight().x;
	lPos.y = m_Parent->GetPosition().y - m_Parent->GetRight().y;
	lPos.z = m_Parent->GetPosition().z - m_Parent->GetRight().z;

	// 範囲内にあるオブジェクトを取得
	auto objectList = scene->GetGameObjects<GameObject>();
	for (auto object : objectList)
	{
		if (CollisionCircle(rPos, object->GetPosition(), colSize))
		{
			if (m_Parent == object)continue;
			if (object->GetEntity())	return true;
		}
	}
	return false;
}


void SearchCollision::Uninit()
{

	m_SearchList.clear();
}

XMFLOAT3 SearchCollision::GetPosition()
{
	XMFLOAT3 rPosition;
	rPosition.x = m_Parent->GetPosition().x + m_OffSet.x;
	rPosition.y = m_Parent->GetPosition().y + m_OffSet.y;
	rPosition.z = m_Parent->GetPosition().z + m_OffSet.z;

	return rPosition;
}

XMFLOAT3 SearchCollision::GetRotation()
{
	return m_Rotation;
}

XMFLOAT3 SearchCollision::GetScale()
{
	return m_Scale;
}

void SearchCollision::SetPosition(XMFLOAT3 position)
{
	XMFLOAT3 rPosition;
	rPosition.x = m_Parent->GetPosition().x + position.x;
	rPosition.y = m_Parent->GetPosition().y + position.y;
	rPosition.z = m_Parent->GetPosition().z + position.z;
	m_Position = rPosition;
}

void SearchCollision::SetOffSet(XMFLOAT3 offset)
{
	m_OffSet = offset;
}

void SearchCollision::SetRotation(XMFLOAT3 rotation)
{
	XMFLOAT3 pRotation;
	pRotation.x = m_Parent->GetRotation().x + rotation.x;
	pRotation.y = m_Parent->GetRotation().y + rotation.y;
	pRotation.z = m_Parent->GetRotation().z + rotation.z;
	m_Rotation = pRotation;
}

void SearchCollision::SetScale(XMFLOAT3 scale)
{
	m_Scale = scale;
}

void SearchCollision::SetParent(GameObject* parent)
{
	m_Parent = parent;
}

void SearchCollision::UpdatePosition()
{
	m_Parent->GetForward();

	m_Position.x = m_Parent->GetPosition().x + m_OffSet.x;
	m_Position.y = m_Parent->GetPosition().y + m_OffSet.y;
	m_Position.z = m_Parent->GetPosition().z + m_OffSet.z;


	XMFLOAT3 pRotation;
	pRotation.x = m_Parent->GetRotation().x + m_Rotation.x;
	pRotation.y = m_Parent->GetRotation().y + m_Rotation.y;
	pRotation.z = m_Parent->GetRotation().z + m_Rotation.z;
	m_Rotation = pRotation;

}

void SearchCollision::UpdateSearchCollisionPositionRotation()
{
	if (!m_Parent) return;  // 親オブジェクトが設定されていない場合は何もしない

	XMFLOAT3 forward = m_Parent->GetForward();
	XMFLOAT3 parentPosition = m_Parent->GetPosition();

	// オフセットの距離を前方ベクトルに基づいて計算
//	float distance = 15.0f;  // 前方の中心位置
//	offset.x = forward.x * distance;
//	offset.y = forward.y * distance;
//	offset.z = forward.z * distance;

	XMFLOAT3 offset;
	offset.x = forward.x * m_OffSet.x;
	offset.y = forward.y * m_OffSet.y;
	offset.z = forward.z * m_OffSet.z;

	// 新しい位置を計算
	XMFLOAT3 newPosition;
	newPosition.x = parentPosition.x + offset.x;
	newPosition.y = parentPosition.y + offset.y;
	newPosition.z = parentPosition.z + offset.z;

	// SearchCollisionの位置を更新
	m_Position = newPosition;
}

bool SearchCollision::IsEnemyInSearchRange(EnemyMachine* enemy)
{
	// プレイヤーの位置と範囲
	XMFLOAT3 playerPosition = m_Parent->GetPosition();
	XMFLOAT3 forward = m_Parent->GetForward();
	// 敵の位置
	XMFLOAT3 enemyPosition = enemy->GetPosition();
	/*
	// 当たり判定処理（例として単純な距離計算）
	float distanceSquared = (enemyPosition.x - m_Position.x) * (enemyPosition.x - m_Position.x) +
		(enemyPosition.y - m_Position.y) * (enemyPosition.y - m_Position.y) +
		(enemyPosition.z - m_Position.z) * (enemyPosition.z - m_Position.z);

	// スケールに基づく判定範囲（例として単純な半径）
	float rangeSquared = (m_Scale.x * 0.5f) * (m_Scale.x * 0.5f);  // 半径の2乗

	return distanceSquared <= rangeSquared;
*/
// 敵までのベクトル
	XMVECTOR toEnemy = XMLoadFloat3(&enemyPosition) - XMLoadFloat3(&m_Position);
	XMVECTOR forwardVec = XMLoadFloat3(&forward);

	// 内積を計算して敵が視界内にいるかどうかを判断
	float dotProduct = XMVectorGetX(XMVector3Dot(forwardVec, XMVector3Normalize(toEnemy)));

	// 内積が0.7以上なら視界内にいると見なす（0.7は調整可能な閾値）
	return dotProduct > 0.5;
}

bool SearchCollision::TouchGameObject()
{
	return false;
}

bool SearchCollision::OBB(GameObject* _objectB)
{
	XMFLOAT3 objPosition = _objectB->GetPosition();
	XMFLOAT3 objScale = _objectB->GetScale();

	objScale.x += this->m_Scale.x;
	objScale.y += this->m_Scale.y;
	objScale.z += this->m_Scale.z;

	XMFLOAT3 direction;	// boxの中心から弾までのベクトル
	direction.x = this->GetPosition().x - objPosition.x;
	direction.y = this->GetPosition().y - objPosition.y;
	direction.z = this->GetPosition().z - objPosition.z;

	// X分離軸
	XMFLOAT3 axisX = _objectB->GetRight();
	// 内積の計算
	float dotX = direction.x * axisX.x + direction.y * axisX.y + direction.z * axisX.z;

	// Y分離軸
	XMFLOAT3 axisY = _objectB->GetUp();
	// 内積の計算
	float dotY = direction.x * axisY.x + direction.y * axisY.y + direction.z * axisY.z;

	// Z分離軸
	XMFLOAT3 axisZ = _objectB->GetForward();
	// 内積の計算
	float dotZ = direction.x * axisZ.x + direction.y * axisZ.y + direction.z * axisZ.z;


	if (-objScale.x < dotX && dotX < objScale.x)
	{
		if (-objScale.z < dotZ && dotZ < objScale.z)
		{
			if (-objScale.y < dotY && dotY < objScale.y)
			{
				//				_object.SetDestroy();
				return true;
			}
		}
	}
	return false;
}

/*
void SearchCollision::SearchEnemy()
{
	Scene* scene = Manager::GetScene();
	m_ListIndex = 0;
	m_SearchList.clear();

	// プレイヤーの回転に基づいてSearchCollisionの位置を更新
	UpdateSearchCollisionPositionRotation();

	// 範囲内にあるオブジェクトを取得
//	auto objectList = scene->GetGameObjects<Enemy>();
	auto objectList = scene->GetGameObjects<EnemyMachine>();

	for (auto object : objectList)
	{
		if (IsEnemyInSearchRange(object))
		{
			m_SearchList.push_back(object);
			m_ListIndex++;
		}
	}
}
*/