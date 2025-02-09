/**************************************************
* GameObjectクラス
* [GameObject.h]
* Author    ：松本紘始
* Date      ：2024年05月15日
***************************************************/
#pragma once

#include "main.h"
#include "component.h"
#include "Collision.h"
#include <list>

enum goLayerType
{
	CameraObject = 0,
	Stage=1,
	Object3d=2,
	EffectBillboard,
	Billboard,
	Particle,
	wa,
	Texture2d,

	LayerTypeMax,
};

//==================================================
// GameObjectクラス
//==================================================
class GameObject
{
private:

protected:

	bool m_Destroy = false;	// 消去フラグ

	GameObject* m_Parent{};
	GameObject* m_Target{};

	XMFLOAT3	m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);	// 座標
	XMFLOAT3	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);	// 回転
	XMFLOAT3	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);		// 拡縮
	std::list<Component*> m_Component;

	bool m_Entity = true;	// 当たり判定必要か

public:
	virtual ~GameObject()
	{
		for (Component* component : m_Component)
		{
			component->Uninit();
			delete component;
		}
		m_Component.clear();
	}

	 virtual void	Init() = 0;			// 純粋仮想関数
	 virtual void	Uninit() = 0;

	 virtual void	Update() = 0;
	 virtual void	Draw() = 0;

	 void ComponentUpdate() 
	 {
		 for (Component* component : m_Component)
		 {			 
			 component->Update();
		 }
	 }

	 XMFLOAT3 GetPosition() { return m_Position; }
	 XMFLOAT3 GetRotation() { return m_Rotation; }
	 XMFLOAT3 GetScale() { return m_Scale; }

	 float GetPositionFX() { return m_Position.x; }
	 float GetPositionFY() { return m_Position.y; }
	 float GetPositionFZ() { return m_Position.z; }

	 bool GetEntity() { return m_Entity; }

	 void SetPosition(XMFLOAT3 position) { m_Position = position; }
	 void SetRotation(XMFLOAT3 rotation) { m_Rotation = rotation; }
	 void SetScale(XMFLOAT3 scale) { m_Scale = scale; }

	 void SetDestroy() { m_Destroy = true; }

	 bool Destroy()
	 {
		 if (!m_Destroy)	return false;

		 Uninit();
		 delete this;
		 return true;
	 }

	 XMFLOAT3 GetForward()	// 前方向ベクトル取得(分離軸)
	 {
	 // オイラー角から回転行列を生成
		 XMMATRIX rotationMatrix;
		 rotationMatrix = XMMatrixRotationRollPitchYaw
		 (m_Rotation.x, m_Rotation.y, m_Rotation.z);

		 // 正規化

//		 XMVECTOR fowardVector = XMVector3Normalize(rotationMatrix.r[2]);

		 XMFLOAT3 foward;
		 XMStoreFloat3(&foward, rotationMatrix.r[2]);
//		 XMStoreFloat3(&foward, fowardVector);

		 return foward;


	 }

	 XMFLOAT3 GetRight()	// 右方向ベクトル取得(分離軸)
	 {
		 // オイラー角から回転行列を生成
		 XMMATRIX rotationMatrix;
		 rotationMatrix = XMMatrixRotationRollPitchYaw
		 (m_Rotation.x, m_Rotation.y, m_Rotation.z);

		 XMFLOAT3 right;
		 XMStoreFloat3(&right, rotationMatrix.r[0]);

		 return right;
	 }

	 XMFLOAT3 GetUp()	// 右方向ベクトル取得(分離軸)
	 {
		 // オイラー角から回転行列を生成
		 XMMATRIX rotationMatrix;
		 rotationMatrix = XMMatrixRotationRollPitchYaw
		 (m_Rotation.x, m_Rotation.y, m_Rotation.z);

		 XMFLOAT3 up;
		 XMStoreFloat3(&up, rotationMatrix.r[1]);

		 return up;
	 }

	 template <typename T>	// テンプレート関数
	 T* AddComponent()
	 {
		 T* component = new T(this);
		 component->Init();

		 m_Component.push_back(component);

		 return component;
	 }

	 template <typename T>	// テンプレート関数
	 T* GetComponent()
	 {
		 for (Component* component : m_Component)
		 {
			 // dinamic_cast 変換できるときは変換。
			 // 型が違う等で変換できない時はnullを返す。

			 T* ret = dynamic_cast<T*>(component);

			 if (ret != nullptr)	return ret;

		 }
		 return nullptr;
	 }

	 float LengthSq(float ax,float az)const
	 {
		 float x = this->m_Position.x;
		 float z = this->m_Position.z;


		 float vx = x - ax;
		 float vy = z - az;
		 return vx * vx + vy * vy;
	 }

	 float LengthSq(XMFLOAT3 posA)const
	 {
		 float x = this->m_Position.x;
		 float y = this->m_Position.y;
		 float z = this->m_Position.z;
		 float ax = posA.x;
		 float ay = posA.y;
		 float az = posA.z;

		 float vx = x - ax;
		 float vy = y - ay;
		 float vz = z - az;


		 return (sqrtf(vx * vx) + (vy * vy) + (vz * vz));
	 }

	 bool STest(const GameObject* oA, const GameObject* oB)
	 {
		 float ax = oA->m_Position.x;
		 float ay = oA->m_Position.y;
		 float az = oA->m_Position.z;

		 float bx = oB->m_Position.x;
		 float by = oB->m_Position.y;
		 float bz = oB->m_Position.z;

		 float vx = bx - ax;
		 float vy = by - ay;
		 float vz = bz - az;

		 vx *= vx;
		 vy *= vy;
		 vz *= vz;


	 }


	 bool OBB(XMFLOAT3 _PositionA, GameObject* _object);
	 bool OBB(XMFLOAT3 _positionA, XMFLOAT3 _positionB, XMFLOAT3 _scaleB, XMFLOAT3 _axisBX, XMFLOAT3 _axisBY, XMFLOAT3 _axisBZ);
	 bool OBB(GameObject* _objectB);
	 bool OBBobjXscl(GameObject* _objectB, XMFLOAT3 _scale);
	 virtual XMFLOAT3 Tracking(GameObject* _target);
	 XMFLOAT3 TargetTracking(GameObject* _object);
	 virtual GameObject* GetTarget();

	 XMFLOAT3 GetTargetPosition();

	 XMFLOAT3 GetTargetPositionA();

	 virtual GameObject* GetParent();

};



//--------------------------------------------------
// 
//--------------------------------------------------



//////////////////// EOF ////////////////////
