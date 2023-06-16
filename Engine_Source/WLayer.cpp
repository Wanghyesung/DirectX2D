#include "WLayer.h"

namespace W
{
	Layer::Layer()
	{
		
	}
	Layer::~Layer()
	{
	}
	void Layer::Initialize()
	{
	}
	void Layer::Update()
	{
		for (GameObject* gameObj : m_vecGameObject)
		{
			gameObj->Update();
		}
	}
	void Layer::LateUpdate()
	{
		for (GameObject* gameObj : m_vecGameObject)
		{
			gameObj->LateUpdate();
		}
	}
	void Layer::Render()
	{
		for (GameObject* gameObj : m_vecGameObject)
		{
			gameObj->Render();
		}
	}
	void Layer::AddGameObject(GameObject* _pGameObj)
	{
		m_vecGameObject.push_back(_pGameObj);
	}

}