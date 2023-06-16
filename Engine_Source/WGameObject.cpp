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
		//상수버퍼로 위치정보 크기정보, 색깔, 업데이트 해줘야한다.
	}
	
	
}