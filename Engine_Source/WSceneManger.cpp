#include "WSceneManger.h"
#include "WCamera.h"
//#include "WPlayScene.h"
//#include "WLeafreScene.h"
//#include "WValleyScene.h"
//#include "WValleyScene_2.h"
//#include "WCaveScene.h"
//#include "WTempleScene.h"
//#include "WTempleScene_2.h"
//#include "WTempleBossScene.h"
namespace W
{
	Scene* SceneManger::m_pActiveScene = nullptr;
	std::map<std::wstring, Scene*> SceneManger::m_mapScene = {};
	void SceneManger::Initialize()
	{
		//m_pActiveScene = nullptr;
		//PlayScene* pPlayScene = new PlayScene();
		//m_mapScene.insert(std::make_pair(L"PlayScene", pPlayScene));
		//LeafreScene* pLeaf  = new LeafreScene();
		//m_mapScene.insert(std::make_pair(L"Leafre", pLeaf));
		//ValleyScene* pValleyScene = new ValleyScene();
		//m_mapScene.insert(std::make_pair(L"Valley", pValleyScene));
		//ValleyScene_2* pValleyScene2 = new ValleyScene_2();
		//m_mapScene.insert(std::make_pair(L"Valley2", pValleyScene2));
		//CaveScene* pCaveSene = new CaveScene();
		//m_mapScene.insert(std::make_pair(L"Cave", pCaveSene));
		//TempleScene* pTemple = new TempleScene();
		//m_mapScene.insert(std::make_pair(L"Temple", pTemple));
		//TempleScene_2* pTemple2 = new TempleScene_2();
		//m_mapScene.insert(std::make_pair(L"Temple2", pTemple2));
		//TempleBossScene* pTempleBoss = new TempleBossScene();
		//m_mapScene.insert(std::make_pair(L"TempleBoss", pTempleBoss));
		//
		//m_pActiveScene = pLeaf;
		//
		//for (auto iter : m_mapScene)
		//{
		//	iter.second->Initialize();
		//}

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

	void SceneManger::Destroy()
	{
		m_pActiveScene->Destroy();
	}

	void SceneManger::Release()
	{
		for (auto &iter : m_mapScene)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}
	Scene* SceneManger::LoadScene(std::wstring _strName)
	{
		std::map<std::wstring, Scene*>::iterator iter =
			m_mapScene.find(_strName);

		if (iter == m_mapScene.end())
			return nullptr;

		m_pActiveScene->OnExit();
		m_pActiveScene = iter->second;
		m_pActiveScene->OnEnter();

		return iter->second;
	}
}
