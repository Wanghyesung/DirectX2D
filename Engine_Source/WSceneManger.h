#pragma once

#include "WScene.h"
#include "WUI.h"

//editor에서 콜라이더 선
//하나의 메쉬콜라이더로 다른 물체들을 그림
//정보만 가지고있고 실제로 그리는 곳은 에디터쪽에서

namespace W
{
	class SceneManger
	{
	public:
		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render();
		static void Destroy();
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

		//template <typename T>
		//static T* GetUI()
		//{
		//	std::vector<UI*> vecUI = m_pActiveScene->FindObjectsOfType<UI>();
		//	for (UI* pUI : vecUI)
		//	{
		//		T* pTargetUI = dynamic_cast<T*>(pUI);
		//		if (pTargetUI != nullptr)
		//			return pTargetUI;
		//	}
		//	return nullptr;
		//}

		template <typename T>
		static T* GetUI()
		{
			std::vector<UI*> m_vecUI = m_pActiveScene->FindObjectsOfType<UI>();

			for (GameObject* pObj : m_vecUI)
			{
				UI* pUI = dynamic_cast<UI*>(pObj);

				std::queue<UI*> queue;
				queue.push(pUI);

				while (!queue.empty())
				{
					UI* pChildUI = queue.front();
					queue.pop();

					T* pTarget = dynamic_cast<T*>(pChildUI);
					if (pTarget != nullptr)
						return pTarget;

					if (pChildUI->GetState() == GameObject::eState::Dead)
						continue;
					else
					{
						const std::vector<UI*> vecChildUI = pChildUI->GetChildUI();

						for (UI* ChildUI : vecChildUI)
							queue.push(ChildUI);
					}
				}
			}
			return nullptr;
		}

	private:
		static Scene* m_pActiveScene;
		static std::map<std::wstring, Scene*> m_mapScene;
	};
}


