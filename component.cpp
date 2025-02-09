#include "component.h"

Component::Component(GameObject* Object)
{
	 m_GameObject = Object; 
}

Component::~Component()
{
}

void Component::Init()
{
}

void Component::Uninit()
{
}

void Component::Update()
{
}

void Component::Draw()
{
}

