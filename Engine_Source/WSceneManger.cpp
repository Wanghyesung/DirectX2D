#include "WSceneManger.h"
#include "WPlayScene.h"

namespace W
{
	Scene* SceneManger::m_pActiveScene = nullptr;
	void SceneManger::Initialize()
	{
		m_pActiveScene = new PlayScene();
		m_pActiveScene->Initialize();
	}
	void SceneManger::Update()
	{
		m_pActiveScene->Update();
	}
	void SceneManger::LateUpdate()
	{
		m_pActiveScene->LateUpdate();
	}
	void SceneManger::Render()
	{
		m_pActiveScene->Render();
	}
}
