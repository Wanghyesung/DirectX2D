#include "WGameObject.h"
#include "WRenderer.h"
#include "WGraphicDevice_Dx11.h"
#include "WTransform.h"

namespace W
{
	GameObject::GameObject() :
		m_eState(eState::Active)
	{
		AddComponent<Transform>();
	}
	GameObject::~GameObject()
	{
		
	}
	void GameObject::Initialize()
	{
		
	}
	void GameObject::Update()
	{
		for (Component* comp : m_vecComponent)
		{
			comp->Update();
		}
	}

	void GameObject::LateUpdate()
	{
		for (Component* comp : m_vecComponent)
		{
			comp->LateUpdate();
		}
	}
	void GameObject::Render()
	{
		for (Component* comp : m_vecComponent)
		{
			comp->Render();
		}
		//������۷� ��ġ���� ũ������, ����, ������Ʈ ������Ѵ�.
	}
	
	
}