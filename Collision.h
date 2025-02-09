#pragma once
#include <list>

enum colXYZ
{
	non = 0,
	x,
	xy,
	xz,
	y,
	yz,
	z,
	xyz,
};

void Update();

bool CollisionBB(XMFLOAT3 positionA, XMFLOAT3 positionB, XMFLOAT3 sizeA, XMFLOAT3 sizeB);
bool Collision(XMFLOAT3 positionA, XMFLOAT3 positionB, float r);
bool CollisionCircle(XMFLOAT3 positionA, XMFLOAT3 positionB, float r);
//bool OBB(XMFLOAT3 _PositionA, GameObject& _object);

class Enemy;
class TeamArea;
class EnemyMachine;

class SearchCollision : public Component
{
private:
	XMFLOAT3 m_Position{};
	XMFLOAT3 m_OffSet{};
	XMFLOAT3 m_Rotation{};
	XMFLOAT3 m_Scale{};
	
	GameObject* m_Parent = nullptr;

	std::list<EnemyMachine*> m_SearchList;
//	std::list<EnemyMachine*> m_SearchList;

	int m_ListIndex = 0;

public:
	using Component::Component;

	void Uninit();

	XMFLOAT3 GetPosition();
	XMFLOAT3 GetRotation(); 
	XMFLOAT3 GetScale();

	void SetPosition(XMFLOAT3 position);
	void SetOffSet(XMFLOAT3 offset);
	void SetRotation(XMFLOAT3 rotation);
	void SetScale(XMFLOAT3 scale);
	void SetParent(GameObject* parent);

	void UpdatePosition();

	void SearchListNearSort();
	EnemyMachine* GetNearEnemy(int nearNum);

	void SearchEnemy();
	bool TouchGameObject(float colSize);
	bool LRTouchGameObject(float colSize);

	void UpdateSearchCollisionPositionRotation();
	bool IsEnemyInSearchRange(EnemyMachine* enemy);
//	bool IsEnemyInSearchRange(EnemyMachine* enemy);
	/*
	template <typename T>	// テンプレート関数
	void SearchObject()
	{
		Scene* scene;
		scene = Manager::GetScene();


		m_ListIndex = 0;

		// 範囲内にあるオブジェクトを取得
		auto objectList = scene->GetGameObjects<T>();
		for (auto object : objectList)
		{
			XMFLOAT3 position = object->GetPosition();

			if (CollisionBB(this->GetPosition(), object->GetPosition(),
				this->GetScale(), object->GetScale()))
			{
				m_SeachList.push_back(object);
				m_ListIndex++;
			}
		}
	}
	*/

	bool TouchGameObject();

	bool OBB(GameObject* _objectB);
};
