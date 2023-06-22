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
		for (Component* comp : m_vecComponent)
		{
			if (comp == nullptr)
				continue;

			delete comp;
			comp = nullptr;
		}

		for (Script* script : m_vecScript)
		{
			if (script == nullptr)
				continue;

			delete script;
			script = nullptr;
		}
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

		for (Script* script : m_vecScript)
		{
			script->Update();
		}
	}

	void GameObject::LateUpdate()
	{
		for (Component* comp : m_vecComponent)
		{
			comp->LateUpdate();
		}

		for (Script* script : m_vecScript)
		{
			script->LateUpdate();
		}
	}
	void GameObject::Render()
	{
		for (Component* comp : m_vecComponent)
		{
			comp->Render();
		}
		//������۷� ��ġ���� ũ������, ����, ������Ʈ ������Ѵ�.

		for (Script* script : m_vecScript)
		{
			script->Render();
		}
	}
	
	
}