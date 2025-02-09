#include "gameObject.h"

bool GameObject::OBB(XMFLOAT3 _PositionA, GameObject* _object)
{
	{
		XMFLOAT3 objPosition = _object->GetPosition();
		XMFLOAT3 objScale = _object->GetScale();

		XMFLOAT3 direction;	// boxの中心から弾までのベクトル
		direction.x = _PositionA.x - objPosition.x;
		direction.y = _PositionA.y - objPosition.y;
		direction.z = _PositionA.z - objPosition.z;

		// X分離軸
		XMFLOAT3 axisX = _object->GetRight();
		// 内積の計算
		float dotX = direction.x * axisX.x + direction.y * axisX.y + direction.z * axisX.z;

		// Y分離軸
		XMFLOAT3 axisY = _object->GetUp();
		// 内積の計算
		float dotY = direction.x * axisY.x + direction.y * axisY.y + direction.z * axisY.z;

		// Z分離軸
		XMFLOAT3 axisZ = _object->GetForward();
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

}
bool GameObject::OBB(XMFLOAT3 _positionA,XMFLOAT3 _positionB, XMFLOAT3 _scaleB, XMFLOAT3 _axisBX, XMFLOAT3 _axisBY, XMFLOAT3 _axisBZ)
{

		XMFLOAT3 direction;	// boxの中心から弾までのベクトル
		direction.x = _positionA.x - _positionB.x;
		direction.y = _positionA.y - _positionB.y;
		direction.z = _positionA.z - _positionB.z;

		// 内積の計算
		float dotX = direction.x * _axisBX.x + direction.y * _axisBX.y + direction.z * _axisBX.z;

		// 内積の計算
		float dotY = direction.x * _axisBY.x + direction.y * _axisBY.y + direction.z * _axisBY.z;

		// 内積の計算
		float dotZ = direction.x * _axisBZ.x + direction.y * _axisBZ.y + direction.z * _axisBZ.z;

		if (-_scaleB.x < dotX && dotX < _scaleB.x)
		{
			if (-_scaleB.z < dotZ && dotZ < _scaleB.z)
			{
				if (-_scaleB.y < dotY && dotY < _scaleB.y)
				{
					//				_object.SetDestroy();
					return true;
				}
			}
		}
		return false;
}

bool GameObject::OBB(GameObject* _objectB)
{
	{
		XMFLOAT3 objPosition = _objectB->GetPosition();
		XMFLOAT3 objScale = _objectB->GetScale();

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
}

bool GameObject::OBBobjXscl(GameObject* _objectB, XMFLOAT3 _scale)
{
	XMFLOAT3 objPosition = _objectB->GetPosition();
	XMFLOAT3 objScale = _objectB->GetScale();

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


	if (-_scale.x < dotX && dotX < _scale.x)
	{
		if (-_scale.z < dotZ && dotZ < _scale.z)
		{
			if (-_scale.y < dotY && dotY < _scale.y)
			{
				//				_object.SetDestroy();
				return true;
			}
		}
	}
	return false;
}

XMFLOAT3 GameObject::Tracking(GameObject* _target)
{
	if (_target == nullptr) return XMFLOAT3(0.0f,0.0f,0.0f);

	XMFLOAT3 targetPos = _target->GetPosition();
	XMFLOAT3 direction;
	direction.y = targetPos.y - this->m_Position.y;
	direction.z = targetPos.z - this->m_Position.z;
	direction.x = targetPos.x - this->m_Position.x;

	XMVECTOR dirVector = XMLoadFloat3(&direction);
	dirVector = XMVector3Normalize(dirVector);
	XMStoreFloat3(&direction, dirVector);

	// X,Zを合成してどこにいても左右を向けるようにしておく
	float newRotation = atan2f(direction.x, direction.z);

	// 上下反転させて上にいるときに上を見るようにしておく
	return XMFLOAT3(-direction.y, newRotation, 0.0f);
}

// 引数：自身or親
XMFLOAT3 GameObject::TargetTracking(GameObject* _object)
{
	if (_object == nullptr) return Tracking(m_Target);

	XMFLOAT3 targetPos = _object->GetTargetPositionA();
	XMFLOAT3 direction;
	direction.y = targetPos.y - this->m_Position.y;
	direction.z = targetPos.z - this->m_Position.z;
	direction.x = targetPos.x - this->m_Position.x;

	XMVECTOR dirVector = XMLoadFloat3(&direction);
	dirVector = XMVector3Normalize(dirVector);
	XMStoreFloat3(&direction, dirVector);

	// X,Zを合成してどこにいても左右を向けるようにしておく
	float newRotation = atan2f(direction.x, direction.z);

	// 上下反転させて上にいるときに上を見るようにしておく
	return XMFLOAT3(-direction.y, newRotation, 0.0f);
}

GameObject* GameObject::GetTarget()
{
	if (m_Target == nullptr) return nullptr;
	return m_Target;
}

XMFLOAT3 GameObject::GetTargetPosition()
{
	if (m_Target == nullptr) return XMFLOAT3(0.0f,0.0f,0.0f);

	return m_Target->GetPosition();
}

XMFLOAT3 GameObject::GetTargetPositionA()
{
	if (m_Target == nullptr) return XMFLOAT3(0.0f, 0.0f, 0.0f);

	XMFLOAT3 position= m_Target->GetPosition();
	XMFLOAT3 plusPos;
	plusPos.x = (rand() % 101 - 100) * 0.01f;
	plusPos.y = (rand() % 101 - 100) * 0.01f;
	plusPos.z = (rand() % 101 - 100) * 0.01f;

	position.x += plusPos.x;
	position.y += plusPos.y;
	position.z += plusPos.z;

	return position;
}

GameObject* GameObject::GetParent()
{
	return m_Parent;
}
