#pragma once

#include "WScene.h"
#include "WUI.h"

namespace W
{
	class SceneManger
	{
	public:
		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render();
		static void Release();

		template <typename T>
		static bool CreateScene(std::wstring name)
		{
			T* scene = new T();

			std::map<std::wstring, Scene*>::iterator iter
				= m_mapScene.find(name);

			if (iter != m_mapScene.end())
				return false;

			m_mapScene.insert(std::make_pair(name, scene));
			m_pActiveScene = scene;
			scene->Initialize();
			return true;
		}
		static Scene* GetActiveScene() { return m_pActiveScene; }
		static Scene* LoadScene(std::wstring _strName);

		static void AddGameObject(eLayerType _eType, GameObject* _pGameObj){ m_pActiveScene->AddGameObject(_eType, _pGameObj);}

		template <typename T>
		static T* GetUI()
		{
			std::vector<UI*> vecUI = m_pActiveScene->FindObjectsOfType<UI>();
			for (UI* pUI : vecUI)
			{
				T* pTargetUI = dynamic_cast<T*>(pUI);
				if (pTargetUI != nullptr)
					return pTargetUI;
			}
			return nullptr;
		}
	private:
		static Scene* m_pActiveScene;
		static std::map<std::wstring, Scene*> m_mapScene;
	};
}


