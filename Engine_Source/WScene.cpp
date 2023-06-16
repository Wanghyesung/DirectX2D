#include "WScene.h"

namespace W
{
	Scene::Scene()
	{
		m_vecLayer.resize((UINT)W::enums::eLayerType::End);
	}
	Scene::~Scene()
	{
	}
	void Scene::Initialize()
	{
		
	}
	void Scene::Update()
	{
		for (Layer& layer : m_vecLayer)
		{
			layer.Update();
		}
	}
	void Scene::LateUpdate()
	{
		for (Layer& layer : m_vecLayer)
		{
			layer.LateUpdate();
		}
	}
	void Scene::Render()
	{
		for (Layer& layer : m_vecLayer)
		{
			layer.Render();
		}
	}
	void Scene::AddGameObject(eLayerType _eType, GameObject* _pGameObj)
	{
		m_vecLayer[(UINT)_eType].AddGameObject(_pGameObj);
	}
}